import Data.Array;

binarySearch :: (Ord a) => [a] -> a -> Int -> Int -> Int
binarySearch array element begin end
  | begin > end = - 1
  | element > array !! middle = binarySearch array element (middle + 1) end
  | element < array !! middle = binarySearch array element begin (end - 1)
  | otherwise = middle
  where
      middle = begin + (end - begin) `div` 2

binarySearchAlt :: (Ord a) => [a] -> a -> Int -> Int -> Int
binarySearchAlt array element begin end = 
    if (begin > end) then
        -1
    else if (element > array !! middle) then
        binarySearchAlt array element (middle + 1) end
    else if (element < array !! middle) then
        binarySearchAlt array element begin (end - 1)
    else
        middle
    where middle = begin + (end - begin) `div` 2

main = do
    let sortedList = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    let targetElement = 7
    let result = binarySearch sortedList targetElement 0 (length sortedList - 1)
    putStrLn $ "O índice do elemento " ++ show targetElement ++ " é: " ++ show result
