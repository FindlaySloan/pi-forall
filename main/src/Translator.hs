
module Translator where

-- Imports
import Syntax


import Unbound.Generics.LocallyNameless qualified as Unbound
import Unbound.Generics.LocallyNameless.Unsafe (unsafeUnbind)
import Data.List (elemIndex, intersperse, delete, (\\))
import Data.Char (toLower)
import Control.Monad.State
import Unsafe.Coerce
import System.IO.Unsafe
import Data.Foldable

-- This is the main data structure
data InterDef =
  FunctionDef {functionName :: String, templateArgs :: [String] , args :: [String], returnType :: String, definition :: String}
  |
  FunctionImpl {functionName :: String, argNames :: [String], cLines :: [String]}
  |
  DataType {typeName :: String, constructorNames :: [String], cLines :: [String]}
  |
  UNDEF

instance Show InterDef where
  show (FunctionDef funcName tempArgs args returnType definition) =
    "FunctionDefinition {\n\t Name: " ++ funcName ++ ",\n\t Template Args: " ++ (show tempArgs) ++ ",\n\t Args: " ++ (show args) ++ ",\n\t return: " ++ returnType ++ "\n\t def: " ++ definition ++ "\n}"
  show (FunctionImpl funcName args lines) =
      "FunctionImplementation {\n\t Name: " ++ funcName ++ ",\n\t Arg Names: " ++ (show args) ++ ",\n\t lines: " ++ (show lines) ++ "\n}"
  show (DataType name conNames lines) =
      "DataType {\n\t Name: " ++ name ++ ",\n\t conNames: " ++ (show conNames) ++ ",\n\t lines: " ++ (show lines) ++ "\n}"

  show (UNDEF) = "UNDEF\n"

-- | The state for the translator
{-- List of intermediate definitions--}
{-- Used to get a unique variable name--}
{-- Stack of synthetic variables to use--}
{-- Stack of variables to be captured -}
{-- Stack of terms in current function impl-}
{-- The list of declarations being checked-}
type TranslatorState = ([InterDef] , Int, [String], [String], [Term], [Decl])

-- | Default start translator state with empty Intermediate definitions and initial variable number starts at 0
startTranslatorState :: TranslatorState
startTranslatorState = ([], 0, [], [], [], [])

createTranslatorState :: [InterDef] -> TranslatorState
createTranslatorState initInterDefs = (initInterDefs, 0, [], [], [], [])

-- | Function to get a variable name
getVarName :: Int -> String
getVarName i = "_" ++ (show i)

-- | This function will take in the list of intermediate representations, the name of the function that the
-- | variable is in, and the variable name. It will return the type of the variable passed in
getTypeOfVariable :: [InterDef] -> String -> [String] -> String -> String
getTypeOfVariable interDefs funcName argNames varName = let funcDef = filter (\f -> functionName f == funcName ) [f | f@(FunctionDef name _ _ _ _) <- interDefs ]
                                                            index = case elemIndex varName argNames of
                                                              Nothing -> undefined -- Impossible
                                                              Just x  -> x
                                                        in case funcDef of
                                                          [] -> undefined
                                                          _  -> (args (head funcDef)) !! index

-- | This function will take in the list of intermediate representations and the name of the function. It will
-- | then return the return type of the named function
getRetTypeOfFunc :: [InterDef] -> String -> String
getRetTypeOfFunc interDefs fName = let funcDef = filter (\f -> functionName f == fName ) [f | f@(FunctionDef _ _ _ _ _) <- interDefs]
                                      in case funcDef of
                                        [] -> undefined
                                        _  -> returnType $ head funcDef

-- | This function will take in a constructor name and return the name of the overall type
getCTypeFromConstructorName :: [InterDef] -> String -> String
getCTypeFromConstructorName interDefs cName = let dataTypes = filter (\d -> elem cName $ constructorNames d) [d | d@(DataType _ _ _) <- interDefs]
                                              in case dataTypes of
                                                  [] -> undefined
                                                  _  -> typeName $ head dataTypes

-- | This function will take in a name and check if it is defined in the global state
isDefined :: [InterDef] -> String -> Bool
isDefined interDefs name = let funcDef = filter (\f -> functionName f == name ) [f | f@(FunctionDef _ _ _ _ _) <- interDefs]
                           in case funcDef of
                                [] -> False -- Empty list so no decleration
                                _  -> True  -- Non Empty list so there is decleration
-- Main translator function
translate :: Module -> [InterDef] -> [InterDef]
translate m initInterDefs = let (interDefs, _, _, _, _, _) = execState (translateModuleEntries $ moduleEntries m) $ createTranslatorState initInterDefs
              in interDefs
-- Translating the module entries
translateModuleEntries :: [Decl] -> State TranslatorState ()
translateModuleEntries [] = return ()
translateModuleEntries (decl:decls) = do
  (interDefs, varNumber, varStack, captureStack, typeStack, ds) <- get -- Getting the state
  put (interDefs, varNumber, varStack, captureStack, typeStack, ds ++ [decl])
  toAdd <- translateModuleEntry decl -- Translating a module entry
  (interDefs, varNumber, varStack, captureStack, typeStack, ds) <- get -- Getting the state
  put (interDefs ++ [toAdd], varNumber, varStack, captureStack, typeStack, ds)
  translateModuleEntries decls
  return ()

-- Translating a single module entry
translateModuleEntry :: Decl -> State TranslatorState InterDef
translateModuleEntry (TypeSig sig) =
  generateFunctionDef (FunctionDef (Unbound.name2String $ sigName sig) [] [] "" "") (sigType sig)
translateModuleEntry (Def name (term, ts)) = do
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  put (interDefs, varNumber, varStack, [], ts, decls) -- Putting the new type stack onto the state
  initialGenerateFunctionImpl (FunctionImpl (Unbound.name2String $ name) [] []) (term) --TODO CHANGE
translateModuleEntry (RecDef name (term, ts)) = do
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  put (interDefs, varNumber, varStack, [], ts, decls) -- Putting the new type stack onto the state
  initialGenerateFunctionImpl (FunctionImpl (Unbound.name2String $ name) [] []) (term) --TODO CHANGE
translateModuleEntry (Demote epsilon) = undefined
translateModuleEntry d@(Data tcName telescope constructorDefs) =
  generateData d
translateModuleEntry (DataSig tcName telescope) = undefined

-- | This function will be used generate the required C information from a Type signature. It will only construct
-- | A FunctionDef and no other InterDef's
generateFunctionDef :: InterDef -> Type -> State TranslatorState InterDef
generateFunctionDef funDef (Pos _ t) =
  generateFunctionDef funDef t
-- | If found a TyChar, then it is the last type in the signature, can directly update the return type of the func
generateFunctionDef (FunctionDef name tempArgs args _ definition) t@(Var a) = do
  varTy <- generateCType t
  return $ FunctionDef name tempArgs args varTy varTy
generateFunctionDef (FunctionDef name tempArgs args _ definition) TyChar = do
  cTyChar <- generateCType TyChar -- Getting the C Type for the TyChar (should be 'char')
  return $ FunctionDef name tempArgs args cTyChar cTyChar  -- TODO refactor
-- | If found a pi type then we have a an ->, so we have found an arg on the right and need to recurse on left
-- | type
generateFunctionDef f@(FunctionDef name tempArgs args retType definition) (Pi Irr tyA bnd) = do
  case tyA of
    Type -> generateFunctionDef (FunctionDef name (tempArgs ++ [(Unbound.name2String $ fst $ unsafeUnbind bnd)]) args retType definition) (snd $ unsafeUnbind bnd)
    (Pos _ Type) -> generateFunctionDef (FunctionDef name (tempArgs ++ [(Unbound.name2String $ fst $ unsafeUnbind bnd)]) args retType definition) (snd $ unsafeUnbind bnd)
    _    -> generateFunctionDef f (snd $ unsafeUnbind bnd)
generateFunctionDef (FunctionDef name tempArgs a retType def) (Pi Rel tyA bnd) = do
  tyACType <- generateCType tyA -- Generating the C Type for the tyA (the argument)
  newDef <- generateFunctionDef (FunctionDef name tempArgs (a ++ [tyACType]) retType "") (snd $ unsafeUnbind bnd)
  return $ FunctionDef name tempArgs (args newDef) (returnType newDef) ("std::function<" ++ (definition newDef) ++ "(" ++ tyACType ++ ")>")

-- | If found a TCon type, then it is the last type in the signature, can directly update the return type of the
-- | function.
generateFunctionDef (FunctionDef name tempArgs args _ definition) t@(TCon tName tArgs) = do
  cType <- generateCType t -- Generating the C Type for the TCon
  return $ FunctionDef name tempArgs args cType cType-- TODO refactor

-- | If found a Eq type
generateFunctionDef (FunctionDef name tempArgs args _ definition) t@(TyEq a b) = do
  cType <- generateCType t -- Generating the C Type for the TyEq
  return $ FunctionDef name tempArgs args cType cType-- TODO refactor

generateFunctionDef f t = undefined
-- | This function will be used to check if there is an inital lambda, if not then it will make an anaomyse C function
-- | as there is no intital lambda
initialGenerateFunctionImpl :: InterDef -> Term -> State TranslatorState InterDef
-- | Matches with a Pos term and removes and recalls the function
initialGenerateFunctionImpl funcImpl (Pos _ t) =
 initialGenerateFunctionImpl funcImpl t
initialGenerateFunctionImpl funcImpl (Ann t _) =
 initialGenerateFunctionImpl funcImpl t
-- | Matches ot a lambda, at this level it means we have some arguments. This will call the function that will
-- | keep matching Lambdas to get all the arguments then parse the final term
initialGenerateFunctionImpl funcImpl term@(Lam ep bnd) =
 generateFunctionImpl funcImpl term
-- | Otherwise no lamda, so need to create an anonomyse function
initialGenerateFunctionImpl funcImpl t = do
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  let syntheticVariable = (getVarName $ varNumber + 1) -- The synthetic variable for the return
  put (interDefs, varNumber + 1, syntheticVariable : varStack, captureStack, typeStack, decls) -- Putting the syntheticVariable onto the stack
  tInterDef <- generateFunctionImpl funcImpl t -- Generating the inter def for the term
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  let lines = "[" ++ (captures $ captureStack) ++ "]" ++ "() {" ++ (concat $ intersperse ";" $ cLines tInterDef) ++ "; return " ++ syntheticVariable ++ ";}()"
  return $ (FunctionImpl (functionName tInterDef) (argNames tInterDef) [lines] )
  where
    captures stack = concat $ intersperse "," stack

-- | This function will generate the C code for a function implementation, but it will be called after checking
-- | for the inital lambda (which gives the functions args).
generateFunctionImpl :: InterDef -> Term -> State TranslatorState InterDef
-- | This will skip over a Pos term and then generate for the innter term
generateFunctionImpl funcImpl (Pos _ t) =
  generateFunctionImpl funcImpl t
-- | This will handle when the term is an annotated term
generateFunctionImpl funcImpl (Ann term termType) = do
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  put (interDefs, varNumber, varStack, captureStack, tail typeStack, decls)
  generateFunctionImpl funcImpl term
-- | This will handle when the term is a lambda, an construct a std::function
generateFunctionImpl f@(FunctionImpl name argNames _) l@(Lam Irr bnd) = do
  let (varBnd, term) = unsafeUnbind bnd
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  put (interDefs, varNumber, varStack, captureStack, tail typeStack, decls)
  generateFunctionImpl f term
generateFunctionImpl f@(FunctionImpl name argNames _) l@(Lam Rel bnd) = do
  let (varBnd, term) = unsafeUnbind bnd
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  let syntheticVariable = (getVarName $ varNumber + 1)
  let stringVarName = Unbound.name2String varBnd
  put (interDefs, varNumber + 1, ((getVarName $ varNumber + 1) : varStack), captureStack, tail typeStack, decls)
  bndInterDef <- generateFunctionImpl f term
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get
  start <- case varStack of 
            [] -> do
              put (interDefs, varNumber, varStack, delete stringVarName captureStack, typeStack, decls)
              return ""
            _  -> do
              put (interDefs, varNumber, tail varStack, delete stringVarName captureStack, typeStack, decls)
              return $ "auto " ++ (head varStack) ++ " = "

  let cLambda = start ++ "[" ++ (captures $ delete stringVarName captureStack) ++ "](auto " ++ stringVarName ++ ") { "{--auto " ++ (head varStack) ++ " = " --}++ (innerLines bndInterDef) ++ "; return " ++ syntheticVariable  ++ ";}"
  return $ FunctionImpl name argNames [cLambda]
  where innerLines bndInterDef = case bndInterDef of
                                  (FunctionImpl _ _ lines) -> concat $ intersperse ";" lines
                                  _                        -> ""
        captures stack = concat $ intersperse "," stack

-- | This will generate for a function application
generateFunctionImpl f@(FunctionImpl name argNames lines) a@(App term arg) = do

---- TODO UNDO
--  case arg of
--    (Arg Irr argTerm) -> do
--       (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get
--       let syntheticVariable = (getVarName $ varNumber + 1)
--       put (interDefs, varNumber + 1, syntheticVariable : varStack, captureStack, tail typeStack, decls) -- Remving the ret type of app
--       termInterDef <- generateFunctionImpl f term
--       (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get
--       put (interDefs, varNumber, varStack, captureStack, tail typeStack, decls) -- Removing the arg type
--       return termInterDef
--    (Arg Rel argTerm) -> do
--      (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get
--      let termVar = (getVarName $ varNumber + 1)
--      let argVar = (getVarName $ varNumber + 2)
--      put (interDefs, varNumber + 2, termVar : argVar : varStack, captureStack, tail typeStack, decls) -- Remving the ret type of app
--      termInterDef <- generateFunctionImpl (FunctionImpl name argNames []) term
--      argInterDef <- generateFunctionImpl (FunctionImpl name argNames []) argTerm
--      return $ FunctionImpl name argNames ((cLines argInterDef) ++ (cLines termInterDef) ++ lines )
  let (funcTerm, args) = squashApps a -- Squashing the applications into a function and the list of args
  generateFunctionImplFromApp f funcTerm args

  where
    -- | This function will squash the applications so that we have a function term and a list of args, instead
    -- | of a chain on apps with single arg applications
    squashApps :: Term -> (Term, [Arg])
    squashApps (App term arg) = recurseSquashApp (term, [arg])

    -- | This function will recursivly squash nested Applications from the tree
    recurseSquashApp :: (Term, [Arg]) -> (Term, [Arg])
    recurseSquashApp ((App term arg), a)  = recurseSquashApp (term, a ++ [arg])
    recurseSquashApp toReturn = toReturn


-- | This will generate for a variable. A variable can either be in the arguments or it is another function call
generateFunctionImpl (FunctionImpl name argNames lines) (Var varName) = do

  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
--  s <- case head typeStack of
--            (Pi _ _ _) -> return "###PI###"
--            (TCon _ _) -> return "###TCON###"
--            _ -> return "###OTHER###"
  let stringVarName = Unbound.name2String varName -- Getting the name of the variable
  start <- case varStack of 
    [] -> do case isDefined interDefs stringVarName of
              True  -> put (interDefs, varNumber, varStack, captureStack, tail typeStack, decls)
              False -> put (interDefs, varNumber, varStack, appendIfNotInList captureStack stringVarName,tail typeStack, decls) -- Updateing the state so the variable stack and capture stack is updated
             return ""
          
    _  -> do let syntheticVar = head varStack
             -- Updateing state
             case isDefined interDefs stringVarName of
              True  -> put (interDefs, varNumber, tail varStack, captureStack, tail typeStack, decls)
              False -> put (interDefs, varNumber, tail varStack, appendIfNotInList captureStack stringVarName,tail typeStack, decls) -- Updateing the state so the variable stack and capture stack is updated
             return $ "auto " ++ syntheticVar ++ " = "

  -- Updateing state
--  case isDefined interDefs stringVarName of
--    True  -> put (interDefs, varNumber, tail varStack, captureStack)
--    False -> put (interDefs, varNumber, tail varStack, captureStack ++ [stringVarName]) -- Updateing the state so the variable stack and capture stack is updated

  
  let newLines = (start ++ stringVarName) : lines -- Getting the new lines
  return $ FunctionImpl name argNames newLines
  where
    appendIfNotInList list val = if elem val list
                                  then
                                    list
                                  else
                                    list ++ [val]

-- | Generates a char literal
generateFunctionImpl (FunctionImpl name argNames lines) (LitChar literal) = do
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  put (interDefs, varNumber, varStack, captureStack, tail typeStack, decls)
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  start <- case varStack of 
    [] -> do return ""
    _  -> do let syntheticVar = head varStack
             -- Updateing state           s
             put (interDefs, varNumber, tail varStack, captureStack, typeStack, decls)
             return $ "auto " ++ syntheticVar ++ " = "
  return $ FunctionImpl name argNames (( start ++ (show literal)) : lines)

-- | Generates for a case statement
generateFunctionImpl (FunctionImpl name argNames lines) (Case term matches) = do
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  
  let termType = head typeStack
  let termSyntheticVar = getVarName $ varNumber + 1 -- Generating the variable for the scrutinised term
  start <- case varStack of
          [] -> do put (interDefs, varNumber + 1, termSyntheticVar : varStack, captureStack, typeStack, decls) -- Updating the stack with term var
                   return ""
          _  -> do let syntheticVar = head varStack
                   -- Updateing state
                   put (interDefs, varNumber + 1, termSyntheticVar : (tail varStack), captureStack, typeStack, decls) -- Updating the stack with term var
                   return $ "auto " ++ syntheticVar ++ " = "
  termInterDef <- generateFunctionImpl (FunctionImpl name argNames []) term -- Generating the interDef for the term
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  put (interDefs, varNumber, termSyntheticVar : varStack, captureStack, typeStack, decls) -- Updating the stack
  case termType of
    (TCon "Bool" _ ) -> do
      let [(Match bnd1), (Match bnd2)] = matches
      let (patBnd1, term1) = unsafeUnbind bnd1
      let (patBnd2, term2) = unsafeUnbind bnd2
      let trueTerm = case patBnd1 of
                      (PatCon "True" [])  -> term1
                      (PatCon "False" []) -> term2
      let falseTerm = case patBnd1 of
                      (PatCon "True" [])  -> term2
                      (PatCon "False" []) -> term1
      (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
      let returnSyntheticVar = getVarName $ varNumber + 1
      put (interDefs, varNumber + 1, returnSyntheticVar : tail varStack, captureStack, typeStack, decls) -- Updating the stack, adding the return var and taking off the term var
      trueInterDef <- generateFunctionImpl (FunctionImpl name argNames []) trueTerm
      (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
      put (interDefs, varNumber, returnSyntheticVar : varStack, captureStack, typeStack, decls) -- Updating the stack
      falseInterDef <- generateFunctionImpl (FunctionImpl name argNames []) falseTerm
      let line = start ++ "[" ++ (concat $ intersperse "," captureStack) ++ "]() {" ++ (concat $ cLines termInterDef) ++ "; if ( " ++ termSyntheticVar ++ " ) {" ++ (concat $ intersperse "," (cLines trueInterDef)) ++ ";return " ++ returnSyntheticVar ++ "; } else {" ++ (concat $ intersperse "," (cLines falseInterDef)) ++ ";return " ++ returnSyntheticVar ++ ";} }()"
      return $ FunctionImpl name argNames (line : lines)
    _      -> do
      matchesInterDefs <- mapM (generateFunctionImplForMatch termType) matches
      (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state to remove the term Synthetic var from stack
      put (interDefs, varNumber, tail varStack, captureStack, typeStack, decls) -- Updating the stack
      let line = start ++ "[" ++ (concat $ intersperse "," captureStack) ++ "]() { " ++(concat $ intersperse ";" $ cLines termInterDef) ++ "; switch ( " ++ (show termType) ++ "  " ++ termSyntheticVar ++ ".type) { " ++ (concat $ concat $ map (cLines) matchesInterDefs) ++ "} }()"
      return $ FunctionImpl name argNames (line : lines)
--  let termType = TyChar


-- | Generates for a data constructor
generateFunctionImpl f@(FunctionImpl name argNames lines) t@(DCon conName args) =
  case conName of
    "True"  -> generateFunctionImplForBoolLiteral f t
    "False" -> generateFunctionImplForBoolLiteral f t
    -- "Zero"  -> generateFunctionImplForNatLiteral f t
    -- "Succ"  -> generateFunctionImplForNatLiteral f t
    _       -> do
      (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state -- TODO REFACTOR THIS OUT
      start <- case varStack of
        [] -> do return ""
        _  -> do let syntheticVar = head varStack
                 -- Updateing state
                 put (interDefs, varNumber, tail varStack, captureStack, typeStack, decls)
                 return $ "auto " ++ syntheticVar ++ " = "

      (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state -- TODO REFACTOR THIS OUT
      case typeStack of
        [] -> undefined
        _ -> do
          let actualType = head typeStack
      --      let mainType = getCTypeFromConstructorName interDefs conName

          mainType <- generateCType actualType
      --      tempInfo <- case head typeStack of
      --        (Pi _ _ _) -> return $ "###pi###"
      --        (TCon _ _) -> return $ "###tcon###"
      --        (TyChar) -> return $ "###char###"
      --        _ -> return $ "####other#####"
      --      tempInfo <- templateInfo $ actualType

          let argSyntheticVars = map (\(i, _) -> getVarName $ varNumber + i) (zip [1..] $ foldr (\a@(Arg e _) acc -> case e of
                                                                                                                        Irr -> acc
                                                                                                                        Rel -> a : acc
                                                                                                  ) [] args)
          put (interDefs, varNumber + (length args),  (argSyntheticVars ++ varStack), captureStack, tail typeStack, decls) -- Putting the new vars on the stack
      --      interDefForArgs <- mapM (generateFunctionImpl (FunctionImpl name argNames [])) (map (unArg) (foldr (\a@(Arg e _) acc -> case e of
      --                                                                                                                        Irr -> acc
      --                                                                                                                        Rel -> a : acc
      --                                                                                                  ) [] args))
          interDefForArgs <- mapM (\arg@(Arg ep term) -> case ep of
                                                              Irr -> do
                                                                (interDefs, varNumber, varStack , captureStack, typeStack, decls) <- get -- Getting new state
                                                                put (interDefs, varNumber, varStack, captureStack, tail typeStack, decls)
                                                                return $ FunctionImpl name argNames []
                                                              Rel -> (generateFunctionImpl (FunctionImpl name argNames []) term)) (args)
          return $ FunctionImpl name argNames ((concat $ map cLines interDefForArgs) ++ ( (start ++ mainType ++ "::_"++ conName ++ "(" ++ (concat $ intersperse "," (argSyntheticVars)) ++ ")") : lines))
      

      where
--        relevantArgs =
--        templateInfo (TCon name []) = return $ ""
--        templateInfo (TCon name args) = do
--          s <- mapM (generateCType) $ map (\(Arg Rel t) -> t) args
--          return $ "<" ++ (concat $ intersperse ", " s)   ++ ">"
--        (interDefs, varNumber, varStack, captureStack) <- get -- Getting the state
--          --let syntheticVar = head varStack -- Popping the variable from the stack
--
--          let argSyntheticVars = map (\(i, _) -> getVarName $ varNumber + i) (zip [1..] args) -- Generate the argument synthetic var
--          put (interDefs, varNumber + (length args),  ( varStack), captureStack) -- Putting the new vars on the stack
--          interDefForTerm <- generateFunctionImpl (FunctionImpl name argNames []) t -- Generating interDef for the term
--          let newLines = ({--"auto " ++ syntheticVar ++ " = " ++ " " ++ --}(concat functionCall)) : lines
--              functionCall = (cLines interDefForTerm) ++ [argsAsString]
--              argsAsString = concat $ map (\s ->  "(" ++ s ++ ")") argSyntheticVars
--          (interDefs, varNumber, varStack , captureStack) <- get -- Getting new state
--          put (interDefs, varNumber + (length args),  argSyntheticVars ++( varStack), captureStack) -- Putting the new vars on the stack
--          interDefsForArgs <- mapM (generateFunctionImpl (FunctionImpl name argNames [])) (reverse $ map (unArg) args)
--          return $ FunctionImpl name argNames ((concat $ map (cLines) interDefsForArgs) ++ newLines)

-- | Generates for a subst expression
generateFunctionImpl f@(FunctionImpl name argNames lines) t@(Subst a pf) = do
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state -- TODO REFACTOR THIS OUT
  start <- case varStack of
    [] -> do put (interDefs, varNumber, varStack, captureStack, tail typeStack, decls)
             return ""
    _  -> do let syntheticVar = head varStack
             -- Updateing state
             put (interDefs, varNumber, tail varStack, captureStack, tail typeStack, decls)
             return $ "auto " ++ syntheticVar ++ " = "

  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state -- TODO REFACTOR THIS OUT
  genedA <- generateFunctionImpl (FunctionImpl name argNames []) a 
  return $ FunctionImpl name argNames ((start ++ (concat $ cLines genedA)) : lines)

generateFunctionImpl f@(FunctionImpl name argNames lines) t@(Refl) = do
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state -- TODO REFACTOR THIS OUT
  start <- case varStack of
    [] -> do return ""
    _  -> do let syntheticVar = head varStack
             -- Updateing state
             put (interDefs, varNumber, tail varStack, captureStack, tail typeStack, decls)
             return $ "auto " ++ syntheticVar ++ " = "

  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state -- TODO REFACTOR THIS OUT
  return $ FunctionImpl name argNames ((start ++ "_TyEq::_Refl()") : lines)

generateFunctionImpl f@(FunctionImpl name argNames lines) t@(Contra p) = do
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state -- TODO REFACTOR THIS OUT
  start <- case varStack of
    [] -> do put (interDefs, varNumber, tail varStack, captureStack, tail typeStack, decls)
             return ""
    _  -> do let syntheticVar = head varStack
             -- Updateing state
             put (interDefs, varNumber, tail varStack, captureStack, tail typeStack, decls)
             return $ "auto " ++ syntheticVar ++ " = "

  return $ FunctionImpl name argNames ((start ++ "_Void()") : lines)

generateFunctionImpl f@(FunctionImpl name argNames lines) t@(TrustMe) = return $ FunctionImpl name argNames ("*************TRUSTME***********": lines) 

generateFunctionImplForMatch :: Type -> Match -> State TranslatorState InterDef
generateFunctionImplForMatch scrutType (Match bnd) = do
  let (patBnd, term) = unsafeUnbind bnd
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  let returnSyntheticVar = getVarName $ varNumber + 1
  put (interDefs, varNumber + 1, returnSyntheticVar : varStack, captureStack, typeStack, decls) -- Updating the stack
  lines <- generateFunctionImplForPattern patBnd scrutType
--  (interDefs, varNumber, varStack, captureStack) <- get -- Getting the state
--  case varStack of
--    [] -> return ()
--    _  -> put (interDefs, varNumber, tail varStack, captureStack) -- Updating the stack
  termInterDef <- generateFunctionImpl (FunctionImpl "" [] []) term
  let (PatCon name args) = patBnd
  let argNames = filter (/= "_") [Unbound.name2String t | (PatVar t, _) <- args]
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  put (interDefs, varNumber, varStack, captureStack \\ argNames, typeStack, decls) -- Updating the stack
  return $ FunctionImpl "" [] ([lines] ++ (map (\s -> s ++ ";") $ cLines termInterDef) ++ [" return " ++ returnSyntheticVar ++ ";}"])

generateFunctionImplForPattern :: Pattern -> Type -> State TranslatorState String
generateFunctionImplForPattern (PatCon name args) scrutType = do
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  let returnSyntheticVar = head varStack
  let scrutinisedSyntheticVar = head $ tail varStack
  let castedSyntheticVar = getVarName $ varNumber + 1
  tempInfo <- generateTemplate scrutType
  let patternType = "_" ++ (getCTypeFromConstructorName interDefs name) ++ "_" ++ name ++ tempInfo
  put (interDefs, varNumber + 1, (tail $ tail varStack), captureStack, typeStack, decls) -- Updating the stack
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  put (interDefs, varNumber, returnSyntheticVar : scrutinisedSyntheticVar : varStack, captureStack, typeStack, decls) -- Updating the stack
  argLines <- mapM (getArgsLines castedSyntheticVar) $ zip [1..] (foldr (\a@((PatVar t), e) acc -> case e of
                                                                                             Irr -> acc
                                                                                             Rel -> a : acc
                                                                       ) [] args)
  return $ (show scrutType) ++ " case " ++ name ++ ": {" ++ "auto " ++ castedSyntheticVar ++ " = " ++ "*(" ++ patternType ++ "*)" ++ scrutinisedSyntheticVar ++ ".data;" ++ (concat argLines)

  where
    getArgsLines _ (i, ((PatVar t), Irr)) = return ""
    getArgsLines castedSyntheticVar (i, ((PatVar t), Rel)) =
      case Unbound.name2String t of
        "_" -> do
          (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
          let syntheticVar = getVarName $ varNumber + 1
          put (interDefs, varNumber + 1, varStack, captureStack,  typeStack, decls) -- Updating the stack
          return $ "auto " ++ syntheticVar ++ " = " ++ castedSyntheticVar ++ "._" ++ (show i) ++ ";"
        n   -> do
          (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
          put (interDefs, varNumber, varStack, captureStack,  typeStack, decls) -- Updating the stack
          return $ "auto " ++ n ++ " = " ++ castedSyntheticVar ++ "._" ++ (show i) ++ ";"
    templateInfo (TCon name []) = return $ ""
    templateInfo (TCon name args) = do
      s <- mapM (generateCType) $ map (\(Arg Rel t) -> t) args
      return $ "<" ++ (concat $ intersperse ", " s)   ++ ">"
    generateTemplate (TCon name args) =
      case name of
        "Bool" -> return "bool" -- Special case for the boolean structure
        -- "Nat"  -> return "_Nat"  -- Special case for the natural structure
        _      -> do
          (interDefs, varNumber, varStack , captureStack, typeStack, decls) <- get -- Getting new state
          case filter (\(Data tcName _ _) -> tcName == name) [x | x@(Data tcName telescope constructorDefs) <- decls] of
            [] -> undefined
            ((Data tcName telescope constructorDefs):xs)  -> do
                let templateInfo = genTemplateTypes telescope
                let tInfo = genTemplateArgs templateInfo
                return $ tInfo
    generateTemplate (Pos _ t) = generateTemplate t
    -- generateTemplate t = unsafeCoerce $ unsafePerformIO $ putStrLn $ show t
    genTemplateArgs [] = ""
    genTemplateArgs types = "<" ++ (concat $ intersperse "," types) ++ ">"
    genTemplateTypes (Telescope decls) = foldr (\(TypeSig (Sig name e t)) acc -> case e of
                                                                                   Irr -> acc -- Irrelevant so ignore
                                                                                   Rel -> relInner (Unbound.name2String name) acc t
                                                ) [] decls
    relInner :: String -> [String] -> Type -> [String]
    relInner name acc (Pos _ t) = relInner name acc t
    relInner name acc (Ann t _) = relInner name acc t
    relInner name acc (Type) = name : acc
    relInner name acc t@(Pi _ _ bnd) = let (bndName, bndT) = unsafeUnbind bnd in relInner name acc bndT
    relInner name acc _ = acc



generateFunctionImplForPattern (PatVar name) scrutType = undefined -- NOTE: IF HERE THEN SOMETHING IS VERY WRONG



-- | Handles the special case of booleans
generateFunctionImplForBoolLiteral :: InterDef -> Term -> State TranslatorState InterDef
generateFunctionImplForBoolLiteral (FunctionImpl name argNames lines) (DCon conName _) = do
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state -- TODO REFACTOR THIS OUT
  start <- case varStack of 
    [] -> do return ""
    _  -> do let syntheticVar = head varStack
             -- Updateing state           
             put (interDefs, varNumber, tail varStack, captureStack, typeStack, decls)
             return $ "auto " ++ syntheticVar ++ " = "
  return $ FunctionImpl name argNames (( start ++ (map toLower conName)) : lines)

-- Handles the special case of the natural numbers
generateFunctionImplForNatLiteral :: InterDef -> Term -> State TranslatorState InterDef
generateFunctionImplForNatLiteral (FunctionImpl name argNames lines) t = do
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state -- TODO REFACTOR THIS OUT
  start <- case varStack of
    [] -> do return ""
    _  -> do let syntheticVar = head varStack
             -- Updateing state
             put (interDefs, varNumber, tail varStack, captureStack, typeStack, decls)
             return $ "auto " ++ syntheticVar ++ " = "
  let number = case isNumeral t of
                Nothing -> undefined
                Just x  -> x
  return $ FunctionImpl name argNames (( start ++ (show number)) : lines)

-- | This function will take a squashed Application and then generated the structure to represent it. There
-- | should only be a couple cases for this as the term in the application must be a function, so either a
-- | lambda or a variable refering a a delcared function. (Note there could be an annotation for the anonomse
-- | lambda function TODO, remove function and replace in calling location
generateFunctionImplFromApp :: InterDef -> Term -> [Arg] -> State TranslatorState InterDef
-- | Skips over the position term and generates for the inner term
-- generateFunctionImplFromApp funcImpl (Pos _ t) args =
--   generateFunctionImplFromApp funcImpl t args
-- -- | Handles the case when there is a annotated term
-- generateFunctionImplFromApp funcImpl (Ann term termType) args = undefined
generateFunctionImplFromApp (FunctionImpl name argNames lines) t args = do
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  --let syntheticVar = head varStack -- Popping the variable from the stack
  let newArgs = foldr (\a@(Arg ep term) acc -> case ep of
                                                  Irr -> acc
                                                  Rel -> a : acc
                      ) [] args
  let argSyntheticVars = map (\(i, _) -> getVarName $ varNumber + i) (zip [1..] newArgs) -- Generate the argument synthetic var
  put (interDefs, varNumber + (length args),  ( varStack), captureStack, drop (length args) typeStack, decls) -- Putting the new vars on the stack
  (interDefs, varNumber, varStack, captureStack, typeStack, decls) <- get -- Getting the state
  x <- case typeStack of
    [] -> undefined
    _  -> return 1
  let termType = head typeStack
  interDefForTerm <- generateFunctionImpl (FunctionImpl name argNames []) t -- Generating interDef for the term
  templateInfo <- generateTemplateInfo termType t args
  let newLines = ({--"auto " ++ syntheticVar ++ " = " ++ " " ++ --}(concat functionCall)) : lines
      functionCall = (cLines interDefForTerm) ++ [templateInfo] ++  [argsAsString]
      argsAsString = concat $ map (\s ->  "(" ++ s ++ ")") argSyntheticVars
  (interDefs, varNumber, varStack , captureStack, typeStack, decls) <- get -- Getting new state
  put (interDefs, varNumber,  argSyntheticVars ++ ( varStack), captureStack, typeStack, decls) -- Putting the new vars on the stack -TODO CHECK ALLOWED TO CHANGE
--  unsafeCoerce $ unsafePerformIO $ putStrLn $ show args
  interDefsForArgs <- mapM (\arg@(Arg ep term) -> case ep of
                                                          Irr -> do
                                                            (interDefs, varNumber, varStack , captureStack, typeStack, decls) <- get -- Getting new state
                                                            put (interDefs, varNumber, varStack, captureStack, tail typeStack, decls)
                                                            return $ FunctionImpl name argNames []
                                                          Rel -> (generateFunctionImpl (FunctionImpl name argNames []) term)) (reverse $ args)
  return $ FunctionImpl name argNames ((concat $ map (cLines) interDefsForArgs) ++ newLines)
  where

    generateTemplateInfo :: Type -> Type -> [Arg] -> State TranslatorState String
    generateTemplateInfo actualType (Var n) args = do
        let argsFilter = genTemplateFromPi actualType
        let templateArgs = map (\(b, (Arg e t)) -> t) $ filter (\(b, a) -> b) (zip argsFilter (reverse args))
        stringArgs <- mapM (generateCType) templateArgs
        if length stringArgs > 0
          then return $ "<" ++ (concat $ intersperse "," stringArgs) ++ ">"
          else return $ ""
    generateTemplateInfo _ _ _ = return ""
    genTemplateFromPi :: Type -> [Bool]
    genTemplateFromPi (Pi ep ty bnd) = genTemplateFromPi ty ++ genTemplateFromPi (snd $ unsafeUnbind bnd)
    genTemplateFromPi Type = [True]
    genTemplateFromPi (Pos _ t) = genTemplateFromPi t
    genTemplateFromPi t = [False]
-- generateFunctionImplFromApp (FunctionImpl name argNames lines) (Var varName) args = do
--   (interDefs, varNumber, varStack, captureStack) <- get -- Getting the state
--   let syntheticVar = head varStack -- Popping the variable from the stack

--   let argSyntheticVars = map (\(i, _) -> getVarName $ varNumber + i) (zip [1..] args) -- Generate the argument synthetic var
--   put (interDefs, varNumber + (length args), argSyntheticVars ++ (tail varStack), captureStack) -- Putting the new vars on the stack
--   let stringVarName = Unbound.name2String varName -- Getting the string name
--   let newLines = ("auto " ++ syntheticVar ++ " = " {-- ++ castReturn --} ++ " " ++ functionCall) : lines -- Constructing the new lines
--       funcReturnedType = getRetTypeOfFunc interDefs name -- string for the return type
--       --castReturn = "(" ++ funcReturnedType ++ ")" -- String for the cast for the function call
--       functionCall = stringVarName ++ "(" ++ argVarsAsString ++ ")" -- String for the function call with the args
--       argVarsAsString = concat $ intersperse "," argSyntheticVars -- Generating the args string with the generated args
--   -- Generating the C code for each of the args. The args need to be reversed as mapM is a foldr, so it will generate
--   -- the last in list first, but stack needs the first in list to match up the variables
--   interDefsForArgs <- mapM (generateFunctionImpl (FunctionImpl name argNames [])) (reverse $ map (unArg) args)
--   -- Combining the lines generated for the args to the already generated lines into a new InterDef
--   return $ FunctionImpl name argNames ((concat $ map (cLines) interDefsForArgs) ++ newLines)

generateData :: Decl -> State TranslatorState InterDef
generateData (Data tcName telescope constructorDefs)
  | tcName == "Unit" = return UNDEF
  | tcName == "Bool" = return UNDEF
  | otherwise =  do
  let templates = genTemplateTypes telescope
  let conNames = map (getConName) constructorDefs
  let enumDef =  enumName ++ " {" ++ (concat $ intersperse "," conNames) ++ "};"
  constructorFuncDefs <- mapM (constructorFuncDefsForMainClass tcName templates) constructorDefs
  let mainClassDef = (genTemplateDef templates) ++ "class _" ++ tcName ++ " { public: " ++ enumName ++ " type; void* data;" ++ (concat constructorFuncDefs) ++ "};"
  conClassDefs <- mapM (conClassDef tcName templates) constructorDefs
  inlineConstructorDefs <- mapM (inlineConstructorFuncDef tcName templates) constructorDefs
--  defs <- conClassDefs
  return $ DataType tcName conNames ([enumDef, mainClassDef] ++ conClassDefs ++ inlineConstructorDefs)

  where enumName = "enum _enum_" ++ tcName ++ "_type"
        getConName (ConstructorDef _ conName _) = conName
        constructorFuncDefsForMainClass name templates c@(ConstructorDef _ conName arg) = do
          attributes <- conClassAttributes c
          return $ "static _" ++ name ++ (genTemplateArgs templates) ++ " _" ++ conName ++ "(" ++ (concat $ intersperse ", " attributes) ++ ");"
        inlineConstructorFuncDef name templates c@(ConstructorDef _ conName arg) = do
           attributes <- conClassAttributes c
           return $ (genTemplateDef templates) ++ " inline _" ++ name ++ (genTemplateArgs templates) ++ " _" ++ name ++ (genTemplateArgs templates) ++ "::_" ++ conName ++ "(" ++ (concat $ intersperse ", " attributes) ++ ")" ++ "{ " ++ (conType name conName) ++ (genTemplateArgs templates) ++ "* _innerClass = new " ++ (conType name conName) ++ (genTemplateArgs templates) ++ "(" ++ (concat $ intersperse ", " $ map (\x -> head $ tail $ words x) attributes) ++ "); return  _" ++ name ++ (genTemplateArgs templates) ++ " { " ++ conName ++ ", _innerClass }; };"
        conType tName conName = "_" ++ tName ++ "_" ++ conName
        conClassDef name templates c@(ConstructorDef _ conName _) = do
          attributes <- conClassAttributes c
          constructor <- genConstructor name c
          return $ (genTemplateDef templates) ++ "class _" ++ name ++ "_" ++ conName ++ " { public: " ++ (concat $ map (\s -> s ++ ";") attributes) ++ constructor ++ " };"
        conClassAttributes (ConstructorDef _ _ (Telescope decls)) = genConAttributes decls 0 []
        genConAttributes [] _ acc = return $ acc
        genConAttributes (decl:decls) number acc = let var = getVarName (number + 1)
                                                   in case decl of
                                                        (TypeSig (Sig _ Irr sigType)) ->
                                                          genConAttributes decls number acc
                                                        (TypeSig (Sig _ Rel sigType)) -> do
                                                          t <- generateCType sigType
                                                          genConAttributes decls (number + 1) $ acc ++ [t ++ " " ++ var]
                                                        _             -> genConAttributes decls number acc -- Ignoring as it
        genConstructor tcName c@(ConstructorDef _ conName args) = do
            attributes <- conClassAttributes c
            return $ (conType tcName conName) ++ " (" ++ (concat $ intersperse ", " attributes) ++ ") {" ++ (concat $ map (\x -> let y = head $ tail $ words x in "this->" ++ y ++ "= " ++ y ++ ";") attributes) ++ "};"
        genTemplateTypes (Telescope decls) = foldr (\(TypeSig (Sig name e t)) acc -> case e of
                                                                                        Irr -> acc -- Irrelevant so ignore
                                                                                        Rel -> relInner (Unbound.name2String name) acc t
                                                   ) [] decls
        relInner :: String -> [String] -> Type -> [String]
        relInner name acc (Pos _ t) = relInner name acc t
        relInner name acc (Ann t _) = relInner name acc t
        relInner name acc (Type) = name : acc
        relInner name acc t@(Pi _ _ bnd) = let (bndName, bndT) = unsafeUnbind bnd in relInner name acc bndT
        relInner name acc _ = acc
        genTemplateDef [] = ""
        genTemplateDef types = "template <" ++ (concat $ intersperse ", " $ map (\t -> "class " ++ t) types) ++ "> "
        genTemplateArgs [] = ""
        genTemplateArgs types = "<" ++ (concat $ intersperse "," types) ++ ">"

generateCType :: Type -> State TranslatorState String
generateCType (Pos _ t) = generateCType t
generateCType TyChar = return "char"
generateCType (Pi ep tyA bnd) = do
  tyACType <- generateCType tyA -- Generating the C Type for the tyA (the argument)
  tyBndCType <- generateCType (snd $ unsafeUnbind bnd)
  return $ "std::function<" ++ (tyBndCType) ++ "(" ++ tyACType ++ ")>"

generateCType (TCon name args) = 
  case name of
    "Bool" -> return "bool" -- Special case for the boolean structure
--    "Nat"  -> return "int"  -- Special case for the natural structure
    _      -> do
      (interDefs, varNumber, varStack , captureStack, typeStack, decls) <- get -- Getting new state
      case filter (\(Data tcName _ _) -> tcName == name) [x | x@(Data tcName telescope constructorDefs) <- decls] of
        [] -> undefined
        ((Data tcName telescope constructorDefs):xs)  -> do
            templateInfo <- genTemplateTypes telescope args
            let tInfo = genTemplateArgs templateInfo
            return $ "_" ++ name ++ tInfo

    where
      genTemplateArgs [] = ""
      genTemplateArgs types = "<" ++ (concat $ intersperse "," types) ++ ">"
      genTemplateTypes (Telescope decls) args = mapM (generateCType) $ foldr (\((TypeSig (Sig name e t)), Arg ep argT) acc -> case e of
                                                                                     Irr -> acc -- Irrelevant so ignore
                                                                                     Rel -> relInner (Unbound.name2String name) acc t argT
                                                  ) [] (zip decls args)
      relInner :: String -> [Type] -> Type -> Type -> [Type]
      relInner name acc (Pos _ t) argT = relInner name acc t argT
      relInner name acc (Ann t _) argT = relInner name acc t argT
      relInner name acc (Type) argT = argT : acc
      relInner name acc t@(Pi _ _ bnd) argT = let (bndName, bndT) = unsafeUnbind bnd in relInner name acc bndT argT
      relInner name acc _ _ = acc
generateCType (Ann t _) = undefined
generateCType (App term arg) = generateCType term
generateCType (Var name) = return $ Unbound.name2String name
generateCType (Lam ep bnd) = undefined
generateCType Type = undefined
generateCType TyUnit = undefined
generateCType PrintMe = undefined
generateCType (Let _ _) = undefined
generateCType TrustMe = undefined
generateCType (LitChar c) = undefined
generateCType LitUnit = undefined
generateCType (LitBool b) = undefined
generateCType TyBool = undefined
generateCType (If _ _ _) = undefined
generateCType (Sigma _ _) = undefined
generateCType (Prod _ _) = undefined
generateCType (LetPair _ _) = undefined
generateCType (TyEq _ _) = return "_TyEq"
generateCType Refl = undefined
generateCType (Subst _ _) = undefined
generateCType (Contra _) = undefined
generateCType (DCon _ _) = undefined
generateCType (Case _ _) = undefined



