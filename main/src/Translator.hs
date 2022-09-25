
module Translator where

-- Imports
import Syntax
import Unbound.Generics.LocallyNameless qualified as Unbound
import Unbound.Generics.LocallyNameless.Unsafe (unsafeUnbind)
import Data.List (elemIndex, intersperse, delete)
import Data.Char (toLower)
import Control.Monad.State

-- This is the main data structure
data InterDef =
  FunctionDef {functionName :: String, args :: [String], returnType :: String, definition :: String}
  |
  FunctionImpl {functionName :: String, argNames :: [String], cLines :: [String]}
  |
  UNDEF

instance Show InterDef where
  show (FunctionDef funcName args returnType definition) =
    "FunctionDefinition {\n\t Name: " ++ funcName ++ ",\n\t Args: " ++ (show args) ++ ",\n\t return: " ++ returnType ++ "\n\t def: " ++ definition ++ "\n}"
  show (FunctionImpl funcName args lines) =
      "FunctionImplementation {\n\t Name: " ++ funcName ++ ",\n\t Arg Names: " ++ (show args) ++ ",\n\t lines: " ++ (show lines) ++ "\n}"
  show (UNDEF) = "UNDEF\n"

-- | The state for the translator
{-- List of intermediate definitions--}
{-- Used to get a unique variable name--}
{-- Stack of synthetic variables to use--}
{-- Stack of variables to be captured -}
type TranslatorState = ([InterDef] , Int, [String], [String])

-- | Default start translator state with empty Intermediate definitions and initial variable number starts at 0
startTranslatorState :: TranslatorState
startTranslatorState = ([], 0, [], [])

-- | Function to get a variable name
getVarName :: Int -> String
getVarName i = "_" ++ (show i)

-- | This function will take in the list of intermediate representations, the name of the function that the
-- | variable is in, and the variable name. It will return the type of the variable passed in
getTypeOfVariable :: [InterDef] -> String -> [String] -> String -> String
getTypeOfVariable interDefs funcName argNames varName = let funcDef = head $ filter (\f -> functionName f == funcName ) [f | f@(FunctionDef name _ _ _) <- interDefs ]
                                                            index = case elemIndex varName argNames of
                                                              Nothing -> undefined -- Impossible
                                                              Just x  -> x
                                                        in (args funcDef) !! index

-- | This function will take in the list of intermediate representations and the name of the function. It will
-- | then return the return type of the named function
getRetTypeOfFunc :: [InterDef] -> String -> String
getRetTypeOfFunc interDefs fName = let funcDef = head $ filter (\f -> functionName f == fName ) [f | f@(FunctionDef _ _ _ _) <- interDefs]
                                      in returnType funcDef


-- | This function will take in a name and check if it is defined in the global state
isDefined :: [InterDef] -> String -> Bool
isDefined interDefs name = let funcDef = filter (\f -> functionName f == name ) [f | f@(FunctionDef _ _ _ _) <- interDefs]
                           in case funcDef of
                                [] -> False -- Empty list so no decleration
                                _  -> True  -- Non Empty list so there is decleration
-- Main translator function
translate :: Module -> [InterDef]
translate m = let (interDefs, _, _, _) = execState (translateModuleEntries $ moduleEntries m) startTranslatorState
              in interDefs
-- Translating the module entries
translateModuleEntries :: [Decl] -> State TranslatorState ()
translateModuleEntries [] = return ()
translateModuleEntries (decl:decls) = do
  toAdd <- translateModuleEntry decl -- Translating a module entry
  (interDefs, varNumber, varStack, captureStack) <- get -- Getting the state
  put (interDefs ++ [toAdd], varNumber, varStack, captureStack)
  translateModuleEntries decls
  return ()

-- Translating a single module entry
translateModuleEntry :: Decl -> State TranslatorState InterDef
translateModuleEntry (TypeSig sig) =
  generateFunctionDef (FunctionDef (Unbound.name2String $ sigName sig) [] "" "") (sigType sig)
translateModuleEntry (Def name term) =
  generateFunctionImpl (FunctionImpl (Unbound.name2String $ name) [] []) term
translateModuleEntry (RecDef name term) = undefined
translateModuleEntry (Demote epsilon) = undefined
translateModuleEntry (Data tcName telescope constructorDef) = undefined
translateModuleEntry (DataSig tcName telescope) = undefined

-- | This function will be used generate the required C information from a Type signature. It will only construct
-- | A FunctionDef and no other InterDef's
generateFunctionDef :: InterDef -> Type -> State TranslatorState InterDef
generateFunctionDef funDef (Pos _ t) =
  generateFunctionDef funDef t
-- | If found a TyChar, then it is the last type in the signature, can directly update the return type of the func
generateFunctionDef (FunctionDef name args _ definition) TyChar = do
  cTyChar <- generateCType TyChar -- Getting the C Type for the TyChar (should be 'char')
  return $ FunctionDef name args cTyChar cTyChar  -- TODO refactor
-- | If found a pi type then we have a an ->, so we have found an arg on the right and need to recurse on left
-- | type
generateFunctionDef (FunctionDef name a retType def) (Pi ep tyA bnd) = do
  tyACType <- generateCType tyA -- Generating the C Type for the tyA (the argument)
  newDef <- generateFunctionDef (FunctionDef name (a ++ [tyACType]) retType "") (snd $ unsafeUnbind bnd)
  return $ FunctionDef name (args newDef) (returnType newDef) ("std::function<" ++ (definition newDef) ++ "(" ++ tyACType ++ ")>")

-- | If found a TCon type, then it is the last type in the signature, can directly update the return type of the
-- | function.
generateFunctionDef (FunctionDef name args _ definition) t@(TCon tName tArgs) = do
  cType <- generateCType t -- Generating the C Type for the TCon
  return $ FunctionDef name args cType cType-- TODO refactor

-- | This function will be used to generate requreid C information for the implementation of the function. It will
-- | only construct FunctionImpl and no other InterDef's
-- initialGenerateFunctionImpl :: InterDef -> Term -> State TranslatorState InterDef
-- initialGenerateFunctionImpl funcImpl t = generateFunctionImpl funcImpl t
-- | Matches with a Pos term and removes and recalls the function
-- initialGenerateFunctionImpl funcImpl (Pos _ t) =
--   initialGenerateFunctionImpl funcImpl t
-- -- | Matches ot a lambda, at this level it means we have some arguments. This will call the function that will
-- -- | keep matching Lambdas to get all the arguments then parse the final term
-- initialGenerateFunctionImpl funcImpl term@(Lam ep bnd) =
--   generateFunctionImplFromLambdas funcImpl term
-- | Otherwise no specific argments given to the function, and parses the term

-- | This function will be called when an initial function implementation is generated and a lambda is found.
-- | It will extract all of the arg names before going back to general parse
-- generateFunctionImplFromLambdas :: InterDef -> Term -> State TranslatorState InterDef
-- -- | Matches with a Pos term and removes and recalls the function
-- generateFunctionImplFromLambdas funcImpl (Pos _ t) =
--   generateFunctionImplFromLambdas funcImpl t
-- -- | Matches with lambda and adds to the list of args and recursivly checks for more lambdas
-- generateFunctionImplFromLambdas (FunctionImpl name argNames lines) (Lam ep bnd) =
--   generateFunctionImplFromLambdas (FunctionImpl name (argNames ++ [xName]) lines) term
--       where (xBnd, term) = unsafeUnbind bnd
--             xName = Unbound.name2String xBnd
-- -- | Reached end of lambdas that contain the arguments, need to have a return statement and then generate the
-- -- | rest of the implmentation
-- generateFunctionImplFromLambdas f@(FunctionImpl name argNames lines) t = do
--   (interDefs, varNumber, varStack, captureStack) <- get -- Getting the state
--   put (interDefs, varNumber + 1, ((getVarName $ varNumber + 1) : varStack), captureStack)
--   let newLines = ("return " ++ (getVarName $ varNumber + 1)) : lines
--   generateFunctionImpl (FunctionImpl name argNames newLines) t

-- | This function will generate the C code for a function implementation, but it will be called after checking
-- | for the inital lambda (which gives the functions args).
generateFunctionImpl :: InterDef -> Term -> State TranslatorState InterDef
-- | This will skip over a Pos term and then generate for the innter term
generateFunctionImpl funcImpl (Pos _ t) =
  generateFunctionImpl funcImpl t
-- | This will handle when the term is an annotated term
generateFunctionImpl funcImpl (Ann term termType) = do
  generateFunctionImpl funcImpl term
-- | This will handle when the term is a lambda, an construct a std::function
generateFunctionImpl f@(FunctionImpl name argNames _) l@(Lam ep bnd) = do
  let (varBnd, term) = unsafeUnbind bnd
  (interDefs, varNumber, varStack, captureStack) <- get -- Getting the state
  let syntheticVariable = (getVarName $ varNumber + 1)
  let stringVarName = Unbound.name2String varBnd
  put (interDefs, varNumber + 1, ((getVarName $ varNumber + 1) : varStack), captureStack)
  bndInterDef <- generateFunctionImpl f term
  (interDefs, varNumber, varStack, captureStack) <- get
  start <- case varStack of 
            [] -> do
              put (interDefs, varNumber, varStack, delete stringVarName captureStack)
              return ""
            _  -> do
              put (interDefs, varNumber, tail varStack, delete stringVarName captureStack)
              return $ "auto " ++ (head varStack) ++ " = "

  let cLambda = start ++ "[" ++ (captures $ delete stringVarName captureStack) ++ "](auto " ++ stringVarName ++ ") { "{--auto " ++ (head varStack) ++ " = " --}++ (innerLines bndInterDef) ++ "; return " ++ syntheticVariable  ++ ";}"

  return $ FunctionImpl name argNames [cLambda]
  where innerLines bndInterDef = case bndInterDef of
                                  (FunctionImpl _ _ lines) -> concat $ intersperse ";" lines
                                  _                        -> ""
        captures stack = concat $ intersperse "," stack

-- | This will generate for a function application
generateFunctionImpl f@(FunctionImpl name argNames lines) a@(App term arg) = do

-- TODO UNDO
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

  (interDefs, varNumber, varStack, captureStack) <- get -- Getting the state
  let stringVarName = Unbound.name2String varName -- Getting the name of the variable
  start <- case varStack of 
    [] -> do case isDefined interDefs stringVarName of
              True  -> put (interDefs, varNumber, tail varStack, captureStack)
              False -> put (interDefs, varNumber, tail varStack, captureStack ++ [stringVarName]) -- Updateing the state so the variable stack and capture stack is updated
             return ""
          
    _  -> do let syntheticVar = head varStack
             -- Updateing state
             case isDefined interDefs stringVarName of
              True  -> put (interDefs, varNumber, tail varStack, captureStack)
              False -> put (interDefs, varNumber, tail varStack, captureStack ++ [stringVarName]) -- Updateing the state so the variable stack and capture stack is updated
             return $ "auto " ++ syntheticVar ++ " = "

  -- Updateing state
  case isDefined interDefs stringVarName of
    True  -> put (interDefs, varNumber, tail varStack, captureStack)
    False -> put (interDefs, varNumber, tail varStack, captureStack ++ [stringVarName]) -- Updateing the state so the variable stack and capture stack is updated

  
  let newLines = (start ++ stringVarName) : lines -- Getting the new lines
  return $ FunctionImpl name argNames newLines
  

-- | Generates a char literal
generateFunctionImpl (FunctionImpl name argNames lines) (LitChar literal) = do
  (interDefs, varNumber, varStack, captureStack) <- get -- Getting the state
  start <- case varStack of 
    [] -> do return ""
    _  -> do let syntheticVar = head varStack
             -- Updateing state           
             put (interDefs, varNumber, tail varStack, captureStack)
             return $ "auto " ++ syntheticVar ++ " = "
  return $ FunctionImpl name argNames (( start ++ (show literal)) : lines)

-- | Generates for a data constructor
generateFunctionImpl f@(FunctionImpl name argNames lines) t@(DCon conName args) = 
  case conName of
    "True"  -> generateFuncionImplForBoolLiteral f t
    "False" -> generateFuncionImplForBoolLiteral f t
    _       -> undefined


-- | Handles the special case of booleans
generateFuncionImplForBoolLiteral :: InterDef -> Term -> State TranslatorState InterDef
generateFuncionImplForBoolLiteral (FunctionImpl name argNames lines) (DCon conName _) = do
  (interDefs, varNumber, varStack, captureStack) <- get -- Getting the state -- TODO REFACTOR THIS OUT
  start <- case varStack of 
    [] -> do return ""
    _  -> do let syntheticVar = head varStack
             -- Updateing state           
             put (interDefs, varNumber, tail varStack, captureStack)
             return $ "auto " ++ syntheticVar ++ " = "
  return $ FunctionImpl name argNames (( start ++ (map toLower conName)) : lines)


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
  (interDefs, varNumber, varStack, captureStack) <- get -- Getting the state
  --let syntheticVar = head varStack -- Popping the variable from the stack

  let argSyntheticVars = map (\(i, _) -> getVarName $ varNumber + i) (zip [1..] args) -- Generate the argument synthetic var
  put (interDefs, varNumber + (length args),  ( varStack), captureStack) -- Putting the new vars on the stack
  interDefForTerm <- generateFunctionImpl (FunctionImpl name argNames []) t -- Generating interDef for the term
  let newLines = ({--"auto " ++ syntheticVar ++ " = " ++ " " ++ --}(concat functionCall)) : lines
      functionCall = (cLines interDefForTerm) ++ [argsAsString]
      argsAsString = concat $ map (\s ->  "(" ++ s ++ ")") argSyntheticVars
  (interDefs, varNumber, varStack , captureStack) <- get -- Getting new state
  put (interDefs, varNumber + (length args),  argSyntheticVars ++( varStack), captureStack) -- Putting the new vars on the stack
  interDefsForArgs <- mapM (generateFunctionImpl (FunctionImpl name argNames [])) (reverse $ map (unArg) args)
  return $ FunctionImpl name argNames ((concat $ map (cLines) interDefsForArgs) ++ newLines)
  

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
    _      -> return name
    




