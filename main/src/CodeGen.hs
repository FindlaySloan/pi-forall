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
generateInterDef i@(FunctionDef funcName tempArgs args retType def) = do
  s <- generateInterDefForFunctionDef i
  return $ addNewline s
generateInterDef i@(FunctionImpl funcName args lines) = do
  s <- generateInterDefForFunctionImpl i
  return $ addNewline s
generateInterDef i@(DataType _ _ _ ) = do
  s <- generateInterDefForDataType i
  return $ addNewline s
generateInterDef (UNDEF) = return ""


-- | Generates the C code for the function definition intermediate representation
generateInterDefForFunctionDef :: InterDef -> State GeneratorState String
generateInterDefForFunctionDef f@(FunctionDef funcName tempArgs args returnType def) =
  return $ "" --(genTemplate tempArgs) ++ "extern " ++ def ++ " " ++ funcName ++ ";"
  where
    genTemplate [] = ""
    genTemplate args = "template <" ++ (concat $ intersperse "," (map (\s -> "class " ++ s) args)) ++ "> "
-- | Generates the code for the function implementation intermediate representation
generateInterDefForFunctionImpl :: InterDef -> State GeneratorState String
generateInterDefForFunctionImpl (FunctionImpl funcName args lines) = do
  interDefs <- get
  return $ (funcDefString interDefs funcName) ++ " " ++ funcName ++ " = " ++ (concat $ map (\l -> l ++ ";") lines  ) ++ ( concat $ take ( length args) $ repeat "};"  )
   where

     captures :: [String] -> String
     captures args = concat $ intersperse "," args

     funcDefString interDefs name =
       let f@(FunctionDef fName tempArgs _ _ _) = head $ filter (\(FunctionDef fName _ _ _ _) -> fName == name)$ [f | f@(FunctionDef funcName _ _ _ _) <- interDefs ]
       in (genTemplate tempArgs) ++ definition f
     genTemplate [] = ""
     genTemplate args = "template <" ++ (concat $ intersperse "," (map (\s -> "class " ++ s) args)) ++ "> "

generateInterDefForDataType :: InterDef -> State GeneratorState String
generateInterDefForDataType (DataType name conNames lines) = do
  return (concat lines)