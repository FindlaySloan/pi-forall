import System.Environment


main = do
	[arg] <- getArgs
	print $ nsoln $ read arg

nsoln nq = length (gen nq nq)

safe :: Int -> Int -> [Int] -> Bool
safe x d []    = True
safe x d (q:l) = x /= q && x /= q+d && x /= q-d && safe x (d+1) l

gen :: Int -> Int -> [[Int]]
gen nq 0 = [[]]
gen nq n = [ (q:b) | b <- gen nq (n-1), q <- [1..nq], safe q 1 b]
