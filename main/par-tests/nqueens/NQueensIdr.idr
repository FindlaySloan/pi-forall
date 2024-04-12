module NQueensIdr

-- data List : (a : Type) -> Type where
--  []  : List a  
--  Cons : a -> List a -> List a 

-- data Nat : Type where
--  Z : Nat 
--  S : (n : Nat) -> Nat 

-- plus : Nat -> Nat -> Nat
-- plus n m =
--  case n of
--    Z => m
--    S pred => S (plus pred m)

length : (a : Type) -> List a -> Nat   
length a xs = case xs of 
  [] => 0
  (y::ys) => plus 1 (length a ys)

append : (a:Type) -> List a -> List a -> List a
append a xs ys = case xs of 
  [] => ys
  (x::xs2) => x :: (append a xs2 ys)

orb : Bool -> Bool -> Bool
orb b1 b2 = 
  case b1 of 
    True => True
    False => b2

andb : Bool -> Bool -> Bool
andb b1 b2 = 
  case b1 of 
     True => b2
     False => False

nat_eq : Nat -> Nat -> Bool
nat_eq x y =
  case x of 
     Z => case y of
        Z => True
        S n2 => False
     S m2 => case y of 
        Z => False
        S n2 => nat_eq m2 n2

-- minus : Nat -> Nat -> Nat
-- minus n m =
--   case n of
--     Z => Z
--     S pred => case m of
--                    Z => n
--                    S mpred => minus pred mpred

data Tuple2 : (a : Type) -> (b : Type) -> Type where 
    MkTuple2 : a -> b -> Tuple2 a b   

fst : (a : Type) -> (b : Type) -> (t : Tuple2 a b) -> a 
fst a b t = case t of 
        MkTuple2 t1 t2 => t1 

snd : (a : Type) -> (b : Type) -> (t : Tuple2 a b) -> b 
snd a b t = case t of 
        MkTuple2 t1 t2 => t2 

zip : (a : Type) -> (b : Type) -> List a -> List b -> List (Tuple2 a b)
zip a b l1 l2 = case l2 of 
 [] => [] 
 y::ys => 
  case l1 of 
   []       => []
   x::xs => (MkTuple2 x y) :: (zip a b xs ys)


foldr : (a : Type) -> (b : Type) -> (a -> b -> b) -> b -> List a -> b
foldr a b fn acc list = case list of 
        [] => acc 
        x::xs => fn x (foldr a b fn acc xs)

negb : Bool -> Bool
negb b = if b then False else True

check : (t1 : Tuple2 Nat Nat) -> (t2 : Tuple2 Nat Nat) -> Bool 
check t1 t2 = 
            case t1 of  
                MkTuple2 c l => 
                    case t2 of 
                        MkTuple2 i j => 
                            orb (orb (nat_eq l j) (nat_eq (plus c j) (plus i j))) (nat_eq (minus c l) (minus i j))

mkSafeList : (p : List (Tuple2 Nat Nat)) -> (y : Tuple2 Nat Nat) -> List Bool
mkSafeList p y = case p of 
                [] => [] 
                x:: xs => (negb (check x y)) :: (mkSafeList xs y)

listSeq : (n : Nat) -> (c : Nat) -> List Nat 
listSeq n c = case c of 
            Z => []  
            S m => c :: (listSeq (S n) m) 

safe2 : (n : Nat) -> List Nat ->  Bool 
safe2 na ap = foldr Bool Bool (\x , y => andb x y) True (mkSafeList (zip Nat Nat (listSeq 1 (length Nat ap)) ap) (MkTuple2 (plus (length Nat ap) 1) na))  

makeList : (p : List (List Nat)) -> (n : List Nat) -> List (List Nat)
makeList p n = case p of 
                     [] => [] 
                     pH :: pT =>
                        case n of 
                            [] => [] 
                            nH :: nT =>
                                case safe2 nH pH of 
                                    True => (append Nat pH (nH :: [])) :: (makeList pT nT)
                                    False => makeList pT nT

-- rainhas2(0, Linha, Numero) -> [[]];
-- rainhas2(M, Linha, Numero) -> [lists:append(P, [N]) || P <- rainhas2(M-1, Linha, Numero), N <- lists:append(lists:seq(Linha, Numero), lists:seq(1, Linha-1)), safe(P, N)].

rainhasList : (p : List (List Nat)) -> (n : List Nat) -> (linHa : Nat) -> (numero : Nat) -> List (List Nat)
rainhasList p n linHa numero = case p of 
            [] => [] 
            pH :: pT => case n of 
                [] => [] 
                nH :: nT => case append Nat (listSeq linHa numero) (listSeq 1 (minus linHa 1)) of 
                        [] => case safe2 nH pH of 
                                True => (append Nat pH []) :: [] 
                                False => [] 
                        aH :: aT => case safe2 nH pH of 
                                True => (append Nat pH (nH :: [])) :: (rainhasList pT nT linHa numero)
                                False => rainhasList pT nT linHa numero 

rainhas2 : (n : Nat) -> (linHa : Nat) -> (numero : Nat) -> List (List Nat) 
rainhas2 n linHa numero = 
       case n of 
            Z      => [] :: [] 
            (S n2) => 
                case rainhas2 n2 linHa numero of 
                    [] => [] 
                    rH :: rT => 
                        case append Nat (listSeq linHa numero) (listSeq 1 (minus linHa 1)) of 
                            [] => [] 
                            aH :: aT => 
                                rainhasList (rH :: rT) (aH :: aT) linHa numero      


prainhas : (numero : Nat) -> (linHa : Nat) -> List (List Nat) 
prainhas numero linHa = rainhas2 numero linHa numero

-- search(Numero, N) -> lists:takewhile( fun (A) -> head(A) == N end, prainhas(Numero, N)).

takeWhile : (a : Type) -> (p : a -> Bool) -> List a -> List a 
takeWhile a p xs = case xs of 
                [] => [] 
                x :: ts => case p x of 
                                True => x :: (takeWhile a p ts) 
                                False => [] 

head : List Nat -> Nat
head xs = case xs of 
		[] => Z 
		y :: ys => y 

search : (numero : Nat) -> (n : Nat) -> List (List Nat) 
search numero n = 
            takeWhile (List Nat) (\a => nat_eq (head a) n) (prainhas numero n)

map : (a : Type) -> (b : Type) -> (f : a -> b) -> List a -> List b
map a b f xs = case xs of
	[] => []
	y :: ys => (f y) :: (map a b f ys) 


rainhas : (n : Nat) -> List (List (List Nat)) 
rainhas n = map Nat (List (List Nat)) (\x => search n x) (listSeq 1 n)

run : (n : Nat) -> List (List (List Nat))
run n = rainhas n 
{-
run n = case rainhas n of 
		[] impossible
		Cons x xs => case x of 
 			[] => Z
			Cons y ys =>  case y of
					[] => Z  
					Cons z zs => z  
            -}
-- IO Monad
{- 
data IO : (A : Type) -> Type where
    MkIO of (A)

returnIO : [A : Type] -> A -> IO A
returnIO = \[A] a . MkIO a

bindEq : [A : Type] -> [B : Type] -> IO A -> (A -> IO B) -> IO B
bindEq = \ [A] [B] a f . case a of
                            MkIO inner -> f inner

bind : [A : Type] -> [B : Type] -> IO A -> IO B -> IO B
bind = \ [A] [B] a b . bindEq [A] [B] a (\ c . b : A -> IO B)

print : List Char -> IO Unit
print = TRUSTME

printList : List (List Char) -> IO Unit
printList = \ l . case l of
  [] -> returnIO [Unit] ()
  Cons x xs -> bind [Unit] [Unit] (print x) (printList xs)

-- Timing Functions

getTime : Nat -> IO Nat
getTime = TRUSTME

-- Function to turn a Nat to String
natToString : Nat -> List Char
natToString = TRUSTME

end : IO Unit
end = TRUSTME


runInIO : [A : Type] -> (f : A) -> IO Unit
runInIO = \ [A] f . (returnIO [Unit] ())

baseRun : [A : Type] -> List A -> (f : A -> A) -> IO Unit
baseRun = \ [A] inList func .
  bindEq [Nat] [Unit] (getTime 0)
    (\ startTime1 .
    bind [Unit] [Unit] (print (natToString startTime1)) (
    bind [Unit] [Unit] (runInIO [List A] (map [A] [A] (func) inList)) (
    bindEq [Nat] [Unit] (getTime 0)
    (\ endTime1 .
      bind [Unit] [Unit] (print (natToString endTime1)) (end)))))

genListI : (n : Nat) -> List Nat
genListI = \ n . case n of 
      Z -> []
      S m -> Cons 3 (genListI m)

mainFunc : IO Unit
mainFunc = baseRun [Nat] (genListI 1) (run)
-}