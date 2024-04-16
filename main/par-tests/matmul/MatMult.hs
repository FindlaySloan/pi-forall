module MatMult where

import Data.Bits

-----
-- Matrix pipeline: transpose & multiply

-- Brady '17, p302 (mod 100)
randoms :: Int -> Int -> [Int]
randoms 0 _    = []
randoms n seed = let seed' = 1664525 * seed + 1013904223 in
  (seed' `shiftR` 2) `mod` 100 : randoms (n-1) seed'
  -- seed' `mod` 100 : randoms (n-1) seed' -- if shiftR is not available

genMatrix :: Int -> Int -> Int -> [[Int]]
genMatrix 0 _ _ = []
genMatrix m n s = randoms n s : genMatrix (m-1) n (s*m)

transpose :: [[Int]] -> [[Int]]
transpose m = t' (split m) [] where
  split :: [[Int]] -> ([Int],[[Int]])
  split [] = ([],[])
  split ([] : _) = ([],[])
  split ((x:xs) : xss) = let (hd,tl) = split xss in (x : hd, xs : tl)

  t' :: ([Int], [[Int]]) -> [[Int]] -> [[Int]]
  t' ([],_) z = z
  t' (hds@(_:_),tls) z = t' (split tls) (z ++ [hds])

dot :: [Int] -> [Int] -> Int
dot [] _ = 0
dot _ [] = 0
dot (x:xs) (y:ys) = x*y + dot xs ys

-- assume they're the correct shape
mult :: [[Int]] -> [[Int]] -> [[Int]]
mult m1 m2 = let m3 = transpose m2 in mult' m1 m3 where
  mult' [] _ = []
  mult' (a:as) b = rowXcol a b : mult' as b

  rowXcol :: [Int] -> [[Int]] -> [Int]
  rowXcol _ [] = []
  rowXcol r (c:cs) = dot r c : rowXcol r cs

add :: [[Int]] -> [[Int]] -> [[Int]]
add [] [] = []
add (xs:xss) (ys:yss) = zipWith (+) xs ys : add xss yss
add _ _ = undefined

-- transpose -> matmult -- x pointless (we transpose during matmult)
-- matmult -> derivative -- x too involved
-- matmult -> eigenvalues -- x too involved
-- matmult -> gaussian elimination -- x too involved
-- addition -> matmult -> transpose -- okay?
  -- m1,m2+m3 -> m1*(m2+m3)

run :: Int -> Int -> IO ()
run m s =
  let
    m1 = genMatrix m m s
    m2 = genMatrix m m (s*m)
    m3 = genMatrix m m (s*m*2)
  in print (m1,m2,m3) >> print (f (m1,m2,m3))
  where
    f  = f3 . f2 . f1 -- pipeline
    f1 = \(m4,m5,m6) -> (m4,add m5 m6) -- first stage
    f2 = \(m7,m8) -> mult m7 m8        -- second stage
    f3 = \m9 -> transpose m9           -- third stage


