-- Nesta função, buscamos o elemento linearmente, e retornamos um booleano caso ele esteja ou não na lista 

linearSearch :: Int -> [Int] -> Bool
linearSearch e [] = False
linearSearch e (a:as) = 
    if (a == e) then 
        True
    else 
        linearSearch e as

main = do
    print (linearSearch 3 [1,2,3,4,5]) -- Retornará True