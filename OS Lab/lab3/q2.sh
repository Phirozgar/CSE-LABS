#!/bin/bash

echo "Enter n: "
read n
n=$((2 * $n))
x=1
echo "Odd numbers: "
while [ $x -le $n ]
do
	echo "$x "
	x=$(( 2 + $x ))
done

