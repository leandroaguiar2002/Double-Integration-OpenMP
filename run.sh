#!/bin/bash
threads=( 1 2 4 8 )
intervals=( 1000 10000 100000 )
output="results.csv"
header="Threads, Intervals_x_axis, Intervals_y_axis, Time Taken"

> $output
echo $header > $output

gcc -g -Wall -fopenmp -o main  main.c -lm
if [ $? -ne 0 ]
then
  echo "Erro ao compilar main.c"
  exit 1
fi

for thread in ${threads[@]}
  do
  for interval_x in ${intervals[@]}
    do
    for interval_y in ${intervals[@]}
      do
        ./main $thread $interval_x $interval_y >> $output
      done
    done
  done    




