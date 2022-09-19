
module Translator where

-- Imports
import Syntax
import Unbound.Generics.LocallyNameless qualified as Unbound
import Unbound.Generics.LocallyNameless.Unsafe (unsafeUnbind)


-- This is the main data structure, it takes in a Module and returns a
data InterDef =
  FunctionDef {functionName :: String, args :: [String], returnType :: String}
  |
  UNDEF

instance Show InterDef where
  show (FunctionDef funcName args returnType) =
    "FunctionDefinition {\n\t Name: " ++ funcName ++ ",\n\t Args: " ++ (show args) ++ ",\n\t return: " ++ returnType ++ "\n"
  show (UNDEF) = "UNDEF\n"
-- Main translator function
translate :: Module -> [InterDef]
translate m = translateModuleEntries $ moduleEntries m

-- Translating the module entries
translateModuleEntries :: [Decl] -> [InterDef]
translateModuleEntries [] = []
translateModuleEntries (decl:decls) = (translateModuleEntry decl) : (translateModuleEntries decls)

-- Translating a single module entry
translateModuleEntry :: Decl -> InterDef
translateModuleEntry (TypeSig sig) =
  generateFunctionDef (FunctionDef (Unbound.name2String $ sigName sig) [] "") (sigType sig)
translateModuleEntry (Def name term) = NIL
translateModuleEntry (RecDef name term) = undefined
translateModuleEntry (Demote epsilon) = undefined
translateModuleEntry (Data tcName telescope constructorDef) = undefined
translateModuleEntry (DataSig tcName telescope) = undefined

generateFunctionDef :: InterDef -> Type -> InterDef
generateFunctionDef funDef (Pos _ t) =
  generateFunctionDef funDef t
generateFunctionDef (FunctionDef name args returnType) TyChar =
  FunctionDef name args (generateCType TyChar) -- TODO refactor
generateFunctionDef (FunctionDef name args returnType) (Pi ep tyA bnd) = do
  generateFunctionDef (FunctionDef name ((generateCType tyA) : args) returnType) (snd $ unsafeUnbind bnd)

generateCType :: Type -> String
generateCType TyChar = "char"




