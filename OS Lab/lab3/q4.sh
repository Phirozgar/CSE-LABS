#!/bin/bash

echo "Enter number: "

read num

x=1
fact=1

while [ $x -le $num ]
do
fact=$((fact*x))
x=$((x+1))
done

echo "Factorial of $num is $fact"
