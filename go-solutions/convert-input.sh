#!/bin/bash

echo "Enter the array:"
read input

output=${input//[/\{}
output=${output//]/\}}

echo "Array in Golang/C format:"
echo "$output"
