-- Nesta função, buscamos o elemento linearmente, e retornamos um booleano caso ele esteja ou não na lista 

linearSearch :: Int -> [Int] -> Bool
linearSearch element [] = False
linearSearch element (a:as) = 
    if (a == element) then 
        True
    else 
        linearSearch element as

main = do
    print (linearSearch 3 [1,2,3,4,5]) -- Retornará True