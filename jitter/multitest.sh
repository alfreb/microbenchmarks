#!/bin/bash
max=$1
size=$2
count=$3
for t in $(seq 1 $max); do
taskset -c $t nice -20 ./main $size $count 2>&1 > result${t}.csv&
done

for t in $(seq 1 $max); do
echo "taskset -c $t nice -20 ./main $size $count 2>&1 > result${t}.csv&"
done

