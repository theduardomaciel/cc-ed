-- Criamos uma função que recebe outra função como parâmetro e um array
-- Esse array será mapeado com base na função passada como parâmetro e, em seguida, retornado após o mapeamento
myMap :: (Int -> Int) -> [Int] -> [Int]
myMap f [] = []
myMap f (a : as) = [f a] ++ myMap f as
-- ou  myMap f = foldr (\ a -> (++) [f a]) []

square :: Int -> Int
square x = x * x

factorial :: Int -> Int
factorial x = if x == 0 then 1 else x * factorial (x - 1)

factorialAlt :: Int -> Int
factorialAlt 0 = 1
factorialAlt x = x * factorialAlt (x - 1)

main = do
  -- O quadrado de cada elemento do array será impresso
  print (myMap square [2, 3, 4, 5])
  -- O fatorial de cada elemento do array será impresso
  print (myMap factorialAlt [2, 3, 4, 5])

-- Lambda Expression: map (\ x -> x^2 + x) [1..10]