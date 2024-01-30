-- array of numbers, return
mySum :: [Int] -> Int
mySum [] = 0
mySum (a:as) = a + mySum as;
-- Como parâmetro, passamos o array sem o primeiro elemento, e assim por diante, até que o array esteja vazio

-- number, power, return
myPow :: Int -> Int -> Int
myPow _ 0 = 1 -- Qualquer número elevado a 0 é 1
myPow number power = number * myPow number (power - 1)
-- Como parâmetro, passamos o número e o expoente menos 1, até que o expoente seja 0. Por exemplo, ao calcular 2^3, teremos:
-- CHAMADA: myPow 2 3
-- 2 * myPow 2 2
-- 2 * (2 * myPow 2 1)
-- 2 * (2 * (2 * myPow 2 0))
-- 2 * (2 * (2 * 1))
-- 2 * (2 * 2)
-- 2 * 4
-- 8

-- array of numbers, number, return
nesimo :: [Int] -> Int -> Int
nesimo (a:_) 1 = a; -- Se o número for 1, retornamos o primeiro elemento do array
nesimo (_:as) number = nesimo as (number - 1);
-- Como parâmetro, passamos o array sem o primeiro elemento, e assim por diante, diminuindo o número de elementos até que só reste um elemento

-- array of numbers, return
size :: [Int] -> Int
size [] = 0
size (a:as) = 1 + size as

myProduct :: [Int] -> Int
myProduct [] = 1
myProduct (a:as) = a * myProduct as

inverter :: [Int] -> [Int]
inverter [] = []
inverter (a:as) = inverter as++[a] 

linearSearch :: [Int] -> Int -> Bool
linearSearch [] _ = False
linearSearch (a: as) key =
    if a == key then
        True
    else
        linearSearch as key

linearSearchAlt :: [Int] -> Int -> Bool
linearSearchAlt [] _ = False
linearSearchAlt (a: as) key = a == key || linearSearchAlt as key

decimalToBinary :: Int -> [Int]
decimalToBinary 0 = [0]
decimalToBinary 1 = [1]
decimalToBinary number = decimalToBinary (number `div` 2) ++ [number `mod` 2]

binaryToDecimal :: [Int] -> Int
binaryToDecimal [] = 0
binaryToDecimal (a:as) = a * 2 ^ (length as) + binaryToDecimal as

main :: IO ()
main = do
    putStrLn $ "Soma dos elementos da lista: " ++ show (mySum [1, 2, 3, 4, 5])
    putStrLn $ "Produto dos elementos da lista: " ++ show (myProduct [5, 5, 5])
    putStrLn $ "Tamanho da lista: " ++ show (size [1, 2, 3, 4, 5])
    putStrLn $ "Potenciação b ^ e: " ++ show (myPow 2 3)
    putStrLn $ "n-ésimo elemento da lista (2): " ++ show (nesimo [3, 4, 7, 9, 12] 2)
    putStrLn $ "Inverter lista: " ++ show (inverter [1, 2, 3, 4, 5])
    putStrLn $ "Busca linear de 2 em [1, 2, 3, 4, 5]: " ++ show (linearSearchAlt [1, 2, 3, 4, 5] 2)
    putStrLn $ "Busca linear de 8 em [1, 2, 3, 4, 5]: " ++ show (linearSearchAlt [1, 2, 3, 4, 5] 8)
    putStrLn $ "Decimal para binário de 10: " ++ show (decimalToBinary 10)
    putStrLn $ "Binário para decimal de [1, 0, 1, 0]: " ++ show (binaryToDecimal [1, 0, 1, 0])