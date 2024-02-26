-- Criamos uma função que recebe outra função como parâmetro e um array
-- Esse array será filtrado com base na função passada como parâmetro e, em seguida, retornado após o filtro
myFilter :: (Int -> Bool) -> [Int] -> [Int]
myFilter f [] = []
myFilter f (a : as) = 
    if f a then
        [a] ++ myFilter f as
    else
        myFilter f as

-- Filtramos os elementos pares do array
filterEven :: Int -> Bool
filterEven x = mod x 2 == 0

main = do
    -- Somente os elementos pares do array serão impressos
    print (myFilter filterEven [1, 2, 3, 4, 5, 6, 7, 8, 9])
    
-- Lambda Expression: filter (\ x -> even x && x > 10) [1..20]