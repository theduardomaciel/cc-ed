somar :: Int -> Int -> Int
somar x y = x + y

calc :: (Int -> Int -> Int) -> Int -> Int -> Int
calc f a b = f a b

main = do
    print (calc somar 2 3)