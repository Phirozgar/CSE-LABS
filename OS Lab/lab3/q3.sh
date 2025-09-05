#!/bin/bash

echo "Enter a: "
read a
echo "Enter b: "
read b
echo "Enter c: "
read c

echo "Quadratic expression: ($a)x^2 + ($b)x + ($c)"

d=$(($b * $b - 4 * $a * $c))

echo "root(s) : "

case $d in 
-*)
	echo "No real roots"
;;
0)
	echo "(0 + $b) / (2 * $a)" | bc -l
;;
*)
	echo "(0 - $b + sqrt($d)) / (2 * $a)" | bc -l
	echo "(0 - $b - sqrt($d)) / (2 * $a)" | bc -l
;;
esac
