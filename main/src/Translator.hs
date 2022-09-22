
module Translator where

-- Imports
import Syntax
import Unbound.Generics.LocallyNameless qualified as Unbound
import Unbound.Generics.LocallyNameless.Unsafe (unsafeUnbind)
import Data.List

import Control.Monad.State

-- This is the main data structure, it takes in a Module and returns a
data InterDef =
  FunctionDef {functionName :: String, args :: [String], returnType :: String}
  |
  FunctionImpl {functionname :: String, argNames :: [String], cLines :: [String]}
  |
  UNDEF

instance Show InterDef where
  show (FunctionDef funcName args returnType) =
    "FunctionDefinition {\n\t Name: " ++ funcName ++ ",\n\t Args: " ++ (show args) ++ ",\n\t return: " ++ returnType ++ "\n}"
  show (FunctionImpl funcName args lines) =
      "FunctionImplementation {\n\t Name: " ++ funcName ++ ",\n\t Arg Names: " ++ (show args) ++ ",\n\t lines: " ++ (show lines) ++ "\n}"
  show (UNDEF) = "UNDEF\n"

-- | The state for the translator
{-- List of intermediate definitions--}
{-- Used to get a unique variable name--}
{-- Stack of synthetic variables to use--}
type TranslatorState = ([InterDef] , Int, [String])

-- | Default start translator state with empty Intermediate definitions and initial variable number starts at 0
startTranslatorState :: TranslatorState
startTranslatorState = ([], 0, [])

-- | Function to get a variable name
getVarName :: Int -> String
getVarName i = "_" ++ (show i)

-- | This function will take in the list of intermediate representations, the name of the function that the
-- | variable is in, and the variable name. It will return the type of the variable passed in
getTypeOfVariable :: [InterDef] -> String -> [String] -> String -> String
getTypeOfVariable interDefs funcName argNames varName = let funcDef = head [f | f@(FunctionDef funcName _ _) <- interDefs ]
                                                            index = case elemIndex varName argNames of
                                                              Nothing -> undefined -- Impossible
                                                              Just x  -> x
                                                        in (args funcDef) !! index

-- | This function will take in the list of intermediate representations and the name of the function. It will
-- | then return the return type of the named function
getRetTypeOfFunc :: [InterDef] -> String -> String
getRetTypeOfFunc interDefs funcName = let funcDef = head [f | f@(FunctionDef funcName _ _) <- interDefs]
                                      in returnType funcDef


-- Main translator function
translate :: Module -> [InterDef]
translate m = let (interDefs, _, _) = execState (translateModuleEntries $ moduleEntries m) startTranslatorState
              in interDefs
-- Translating the module entries
translateModuleEntries :: [Decl] -> State TranslatorState ()
translateModuleEntries [] = return ()
translateModuleEntries (decl:decls) = do
  toAdd <- translateModuleEntry decl -- Translating a module entry
  (interDefs, varNumber, varStack) <- get -- Getting the state
  put (interDefs ++ [toAdd], varNumber, varStack)
  translateModuleEntries decls
  return ()

-- Translating a single module entry
translateModuleEntry :: Decl -> State TranslatorState InterDef
translateModuleEntry (TypeSig sig) =
  generateFunctionDef (FunctionDef (Unbound.name2String $ sigName sig) [] "") (sigType sig)
translateModuleEntry (Def name term) =
  initialGenerateFunctionImpl (FunctionImpl (Unbound.name2String $ name) [] []) term
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
generateFunctionDef (FunctionDef name args _) TyChar = do
  returnType <- generateCType TyChar -- Getting the C Type for the TyChar (should be 'char')
  return $ FunctionDef name args returnType -- TODO refactor
-- | If found a pi type then we have a an ->, so we have found an arg on the right and need to recurse on left
-- | type
generateFunctionDef (FunctionDef name args returnType) (Pi ep tyA bnd) = do
  tyACType <- generateCType tyA -- Generating the C Type for the tyA (the argument)
  generateFunctionDef (FunctionDef name (args ++ [tyACType]) returnType) (snd $ unsafeUnbind bnd)
-- | If found a TCon type, then it is the last type in the signature, can directly update the return type of the
-- | function.
generateFunctionDef (FunctionDef name args _) t@(TCon tName tArgs) = do
  returnType <- generateCType t -- Generating the C Type for the TCon
  return $ FunctionDef name args returnType -- TODO refactor

-- | This function will be used to generate requreid C information for the implementation of the function. It will
-- | only construct FunctionImpl and no other InterDef's
initialGenerateFunctionImpl :: InterDef -> Term -> State TranslatorState InterDef
-- | Matches with a Pos term and removes and recalls the function
initialGenerateFunctionImpl funcImpl (Pos _ t) =
  initialGenerateFunctionImpl funcImpl t
-- | Matches ot a lambda, at this level it means we have some arguments. This will call the function that will
-- | keep matching Lambdas to get all the arguments then parse the final term
initialGenerateFunctionImpl funcImpl term@(Lam ep bnd) =
  generateFunctionImplFromLambdas funcImpl term
-- | Otherwise no specific argments given to the function, and parses the term

-- | This function will be called when an initial function implementation is generated and a lambda is found.
-- | It will extract all of the arg names before going back to general parse
generateFunctionImplFromLambdas :: InterDef -> Term -> State TranslatorState InterDef
-- | Matches with a Pos term and removes and recalls the function
generateFunctionImplFromLambdas funcImpl (Pos _ t) =
  generateFunctionImplFromLambdas funcImpl t
-- | Matches with lambda and adds to the list of args and recursivly checks for more lambdas
generateFunctionImplFromLambdas (FunctionImpl name argNames lines) (Lam ep bnd) =
  generateFunctionImplFromLambdas (FunctionImpl name (argNames ++ [xName]) lines) term
      where (xBnd, term) = unsafeUnbind bnd
            xName = Unbound.name2String xBnd
-- | Reached end of lambdas that contain the arguments, need to have a return statement and then generate the
-- | rest of the implmentation
generateFunctionImplFromLambdas f@(FunctionImpl name argNames lines) t = do
  (interDefs, varNumber, varStack) <- get -- Getting the state
  put (interDefs, varNumber + 1, ((getVarName $ varNumber + 1) : varStack))
  let newLines = ("return " ++ (getVarName $ varNumber + 1)) : lines
  generateFunctionImpl (FunctionImpl name argNames newLines) t

-- | This function will generate the C code for a function implementation, but it will be called after checking
-- | for the inital lambda (which gives the functions args).
generateFunctionImpl :: InterDef -> Term -> State TranslatorState InterDef
-- | This will skip over a Pos term and then generate for the innter term
generateFunctionImpl funcImpl (Pos _ t) =
  generateFunctionImpl funcImpl t
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
  (interDefs, varNumber, varStack) <- get -- Getting the state
  let syntheticVar = head varStack -- Popping the synthetic variable from the stack
  put (interDefs, varNumber, tail varStack) -- Updateing the state so the stack is updated
  let stringVarName = Unbound.name2String varName
  if elem stringVarName argNames -- Checking if the name is in the arguments
    then -- Name is in the arguments, can just use directly
      do -- Getting the type of the variable
         let newLines = ("auto " ++ syntheticVar ++ " = " ++ stringVarName) : lines -- Getting the new lines
             typeOfVar = getTypeOfVariable interDefs name argNames stringVarName
         return $ FunctionImpl name argNames newLines


    else -- Name is not in the arguments, it is a function or const global variable
      return UNDEF -- TODO Add to captures

-- | This function will take a squashed Application and then generated the structure to represent it. There
-- | should only be a couple cases for this as the term in the application must be a function, so either a
-- | lambda or a variable refering a a delcared function. (Note there could be an annotation for the anonomse
-- | lambda function
generateFunctionImplFromApp :: InterDef -> Term -> [Arg] -> State TranslatorState InterDef
-- | Skips over the position term and generates for the inner term
generateFunctionImplFromApp funcImpl (Pos _ t) args =
  generateFunctionImplFromApp funcImpl t args
-- | Handles the case when there is a annotated term
generateFunctionImplFromApp funcImpl (Ann term termType) args = undefined
generateFunctionImplFromApp (FunctionImpl name argNames lines) (Var varName) args = do
  (interDefs, varNumber, varStack) <- get -- Getting the state
  let syntheticVar = head varStack -- Popping the variable from the stack

  let argSyntheticVars = map (\(i, _) -> getVarName $ varNumber + i) (zip [1..] args) -- Generate the argument synthetic var
  put (interDefs, varNumber + (length args), argSyntheticVars ++ varStack) -- Putting the new vars on the stack
  let stringVarName = Unbound.name2String varName -- Getting the string name
  let newLines = ("auto " ++ syntheticVar ++ " = " {-- ++ castReturn --} ++ " " ++ functionCall) : lines -- Constructing the new lines
      funcReturnedType = getRetTypeOfFunc interDefs name -- string for the return type
      --castReturn = "(" ++ funcReturnedType ++ ")" -- String for the cast for the function call
      functionCall = stringVarName ++ "(" ++ argVarsAsString ++ ")" -- String for the function call with the args
      argVarsAsString = concat $ intersperse "," argSyntheticVars -- Generating the args string with the generated args
  -- Generating the C code for each of the args. The args need to be reversed as mapM is a foldr, so it will generate
  -- the last in list first, but stack needs the first in list to match up the variables
  interDefsForArgs <- mapM (generateFunctionImpl (FunctionImpl name argNames [])) (reverse $ map (unArg) args)
  -- Combining the lines generated for the args to the already generated lines into a new InterDef
  return $ FunctionImpl name argNames ((concat $ map (cLines) interDefsForArgs) ++ newLines)



generateCType :: Type -> State TranslatorState String
generateCType TyChar = return "char"
generateCType (TCon name args) = return name





