{- pi-forall language -}

-- | The command line interface to the pi type checker. 
-- Also provides functions for type checking individual terms
-- and files.
module Main(goFilename,go,main) where

import Modules (getModules)
import PrettyPrint ( render, Disp(..) )
import Environment ( Env, ctx, emptyEnv, runTcMonad )
import TypeCheck ( tcModules, inferType )
import Parser ( parseExpr )
import Syntax
import Translator ( translate )
import CodeGen (generateCCode)
import Text.ParserCombinators.Parsec.Error ( errorPos, ParseError )
import Control.Monad.Except ( runExceptT )
import System.Environment(getArgs)
import System.Exit (exitFailure,exitSuccess)
import System.FilePath (splitFileName)



exitWith :: Either a b -> (a -> IO ()) -> IO b
exitWith res f = 
  case res of 
    Left x -> f x >> exitFailure 
    Right y -> return y
    
-- | Type check the given string in the empty environment
go :: String -> IO ()
go str = do
  case parseExpr str of
    Left parseError -> putParseError parseError
    Right term -> do 
      putStrLn "parsed as"
      putStrLn $ render $ disp term
      res <- runTcMonad emptyEnv (inferType term)
      case res of 
        Left typeError -> putTypeError typeError
        Right ty -> do
          putStrLn "typed with type"
          putStrLn $ render $ disp ty
  
-- | Display a parse error to the user  
putParseError :: ParseError -> IO ()  
putParseError parseError = do
  putStrLn $ render $ disp $ errorPos parseError
  print parseError
  
-- | Display a type error to the user  
putTypeError :: Disp d => d -> IO ()  
putTypeError typeError = do 
  putStrLn "Type Error:"
  putStrLn $ render $ disp typeError
      
-- | Type check the given file    
goFilename :: String -> IO ()  
goFilename pathToMainFile = do
  let prefixes = [currentDir, mainFilePrefix]
      (mainFilePrefix, name) = splitFileName pathToMainFile
      currentDir = "" 
  putStrLn $ "processing " ++ name ++ "..."
  v <- runExceptT (getModules prefixes name)
  val <- v `exitWith` putParseError
  putStrLn "type checking..."
  d <- runTcMonad emptyEnv (tcModules val)
  defs <- d `exitWith` putTypeError
--  putStrLn $ "-----------CTX AST---------------"
--  let initAST = ctx emptyEnv
--  putStrLn $ show $ ctx emptyEnv
--  putStrLn $ "-----------CTX INTERDEF---------------"
--  let cInterDefs = translate (Module "" [] (ctx emptyEnv) emptyConstructorNames) []-- TODO CHAGNE FROM LAST AS ONLY CHECKING LAST MODULE, not imports
--  putStrLn $ show cInterDefs
--  putStrLn $ "-----------CTX CODE---------------"
--  putStrLn $ concat $ generateCCode cInterDefs
--  putStrLn $ "-----------AST---------------"
--  putStrLn $ show (defs)
--  putStrLn $ "-----------INTERDEF-------------"
--  let interDefs = translate (Module "" [] ((initAST) ++ (moduleEntries (last defs))) (moduleConstructors (last defs))) [] -- TODO CHAGNE FROM LAST AS ONLY CHECKING LAST MODULE, not imports
--  putStrLn $ show interDefs
--  putStrLn $ "-----------INTERDEF CODE-------------"
--  let cCode = concat $ generateCCode interDefs
--  putStrLn cCode
--  output cCode
  putStrLn $ render $ disp (last defs)

-- | This function will write the code to a cpp file, main section is temp
output :: String -> IO ()
output code = do
  writeFile "out/out.cpp" $ "#include <functional>\n#include <iostream>\n" ++ code ++ "\nint main(){}"

-- | 'pi <filename>' invokes the type checker on the given 
-- file and either prints the types of all definitions in the module
-- or prints an error message.
main :: IO ()
main = do
  [pathToMainFile] <- getArgs
  goFilename pathToMainFile
  exitSuccess
  
