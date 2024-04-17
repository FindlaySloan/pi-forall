module Script where

import Parsing
import Data.List
import Data.Char 
import Data.Maybe


calcSeqs [] = [] 
calcSeqs (l1:l2:lines) = let before = (read l1) :: Float 
                             after  = (read l2) :: Float 
                             time = after - before 
                         in time : calcSeqs lines 

calcPars [] = [] 
calcPars (_:l1:l2:lines) = let before = (read l1) :: Float 
                               after  = (read l2) :: Float  
                               time = after - before
                          in time : calcPars lines 

every n xs = case drop (n-1) xs of
              y : ys -> y : every n ys
              [] -> []

every2 c n xs 
  | n > 13    = putStrLn ""
  | otherwise = do 
                let s1 = xs !! n 
                    s2 = xs !! (n + 14) 
                    s3 = xs !! (n + 14 + 14)
                    s4 = xs !! (n + 14 + 14 + 14)
                    s5 = xs !! (n + 14 + 14 + 14 + 14)
                    res = (s1 + s2 + s3 + s4 + s5) / 5
                putStrLn $ (show c) ++ " , " ++ show res 
                every2 (c + 2) (n+1) xs 

parseEntries [] = return ""
parseEntries i = do let (seq, rest) = splitAt 10 i 
                    let seqTimes = calcSeqs seq 
                    let seqAvgT  = (sum seqTimes) / 5
                    putStrLn $ "1" ++ " , " ++ (show seqAvgT)

                    let parTimes = calcPars rest

                    -- putStrLn (show parTimes)

                    every2 2 0 parTimes 

                    -- putStrLn parTimes2

                    return ""

run name = do      
                h <- readFile name 
                entries <- parseEntries (lines h)
                putStrLn entries 
                return ()