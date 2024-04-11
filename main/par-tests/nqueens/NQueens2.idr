module NQueens2 

import Data.List

andb : Bool -> Bool -> Bool
andb b1 b2 = 
  case b1 of 
     True => b2
     False => False

nat_eq : Nat -> Nat -> Bool
nat_eq  x y =
  case x of 
     Z => case y of
        Z => True
        S n2 => False
     S m2 => case y of 
        Z => False
        S n2 => nat_eq m2 n2

negb : Bool -> Bool
negb b = if b then False else True

safe : Nat -> Nat -> List Nat -> Bool 
safe x d [] = True 
safe x d (q :: l) = andb (andb (andb (negb (nat_eq x q)) (negb (nat_eq x (plus q d)))) (negb (nat_eq x (minus q d)))) (safe x (plus d 1) l)

listSeq : (n : Nat) -> (c : Nat) -> List Nat 
listSeq n c = case c of 
            Z => []  
            S m => n :: (listSeq (S n) m) 

append : List a -> List a -> List a
append xs ys = case xs of 
  [] => ys
  x :: xs2 => x :: (append xs2 ys)

-- [(q:b) | b <- [[1,2], [2,3,4]], q <- [1..10]]  
-- [[1,1,2],[2,1,2],[3,1,2],[4,1,2],[5,1,2],[6,1,2],[7,1,2],[8,1,2],[9,1,2],[10,1,2],[1,2,3,4],[2,2,3,4],[3,2,3,4],[4,2,3,4],[5,2,3,4],[6,2,3,4],[7,2,3,4],[8,2,3,4],[9,2,3,4],[10,2,3,4]]



combineWith : (Nat -> List Nat -> Bool) -> List Nat -> List Nat -> List (List Nat) -> List (List Nat)
combineWith f or [] ys = combineWith f or or ys 
combineWith f or xs [] = []
combineWith f (x::xs) (y::ys) = if f x y then (x :: y) :: (combineWith f or xs (y::ys)) else combineWith f or xs (y::ys) 
 
gen : Nat -> Nat -> List (List Nat)
gen nq Z = [ [] ]
gen nq n = combineWith (\q,b => safe q 1 b) (listSeq 1 nq) (gen nq (minus n 1))