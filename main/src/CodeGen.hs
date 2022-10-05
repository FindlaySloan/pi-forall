module CodeGen where

import Translator
import Data.List (intersperse)
import Control.Monad.State

type GeneratorState = [InterDef]

startGeneratorState :: GeneratorState
startGeneratorState = []

-- | The code generation function entry point. It will take a list of the intermediate representations
-- | and output a list of strings that is the C code for each representation.
generateCCode :: [InterDef] -> [String]
generateCCode interDefs =  evalState (mapM generateInterDef interDefs) interDefs

addNewline :: String -> String
addNewline s = s ++ "\n"

-- | This function will generate the C code for a single intermediate representation
generateInterDef :: InterDef -> State GeneratorState String
generateInterDef i@(FunctionDef funcName args retType def) = do
  s <- generateInterDefForFunctionDef i
  return $ addNewline s
generateInterDef i@(FunctionImpl funcName args lines) = do
  s <- generateInterDefForFunctionImpl i
  return $ addNewline s
generateInterDef i@(DataType _ _ _ ) = do
  s <- generateInterDefForDataType i
  return $ addNewline s
generateInterDef (UNDEF) = undefined -- TODO Remove


-- | Generates the C code for the function definition intermediate representation
generateInterDefForFunctionDef :: InterDef -> State GeneratorState String
generateInterDefForFunctionDef f@(FunctionDef funcName args returnType def) =
  return $ "extern " ++ def ++ " " ++ funcName ++ ";"

-- | Generates the code for the function implementation intermediate representation
generateInterDefForFunctionImpl :: InterDef -> State GeneratorState String
generateInterDefForFunctionImpl (FunctionImpl funcName args lines) = do
  interDefs <- get
  return $ (funcDefString interDefs funcName) ++ funcName ++ " = " ++ (lambdas args [] "") ++ (concat $ map (\l -> l ++ ";") lines  ) ++ ( concat $ take ( length args) $ repeat "};"  )
   where
     lambdas :: [String] -> [String] -> String -> String
     lambdas [] _ acc = acc
     lambdas (arg:args) argsSeen acc =
       case argsSeen of
         [] -> lambdas (args) (argsSeen ++ [arg]) $ acc ++ "[" ++ (captures argsSeen) ++ "] (" ++ "auto " ++ arg ++ ")" ++ "{"
         _  -> lambdas (args) (argsSeen ++ [arg]) $ acc ++ "return [" ++ (captures argsSeen) ++ "] (" ++ "auto " ++ arg ++ ")" ++ "{"

     captures :: [String] -> String
     captures args = concat $ intersperse "," args

     funcDefString interDefs name =
       let funcDef = head $ filter (\(FunctionDef fName _ _ _) -> fName == name)$ [f | f@(FunctionDef funcName _ _ _) <- interDefs ]
       in definition funcDef

generateInterDefForDataType :: InterDef -> State GeneratorState String
generateInterDefForDataType (DataType name conNames lines) = do
  return (concat lines)