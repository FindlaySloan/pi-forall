module CodeGen where

import Translator
import Data.List (intersperse)

-- | The code generation function entry point. It will take a list of the intermediate representations
-- | and output a list of strings that is the C code for each representation.
generateCCode :: [InterDef] -> [String]
generateCCode interDefs = map generateInterDef interDefs



-- | This function will generate the C code for a single intermediate representation
generateInterDef :: InterDef -> String
generateInterDef i@(FunctionDef funcName args returnType) = ""
generateInterDef i@(FunctionImpl funcName args lines) = generateInterDefForFunctionImpl i
generateInterDef (UNDEF) = undefined -- TODO Remove

---- | Generates the C code for the function definition intermediate representation
--generateInterDefForFunctionDef :: InterDef -> String
--generateInterDefForFunctionDef f@(FunctionDef funcName args returnType) =
--  "const auto " ++ stdFuncType ++ funcName
--  where stdFuncType

-- | Generates the code for the function implementation intermediate representation
generateInterDefForFunctionImpl :: InterDef -> String
generateInterDefForFunctionImpl (FunctionImpl funcName args lines) =
  "auto " ++ funcName ++ " = " ++ (lambdas args [] "") ++ (concat $ map (\l -> l ++ ";") lines  ) ++ ( concat $ take ( length args) $ repeat "};"  )
   where
     lambdas :: [String] -> [String] -> String -> String
     lambdas [] _ acc = acc
     lambdas (arg:args) argsSeen acc =
       case argsSeen of
         [] -> lambdas (args) (argsSeen ++ [arg]) $ acc ++ "[" ++ (captures argsSeen) ++ "] (" ++ "auto " ++ arg ++ ")" ++ "{"
         _  -> lambdas (args) (argsSeen ++ [arg]) $ acc ++ "return [" ++ (captures argsSeen) ++ "] (" ++ "auto " ++ arg ++ ")" ++ "{"

     captures :: [String] -> String
     captures args = concat $ intersperse "," args