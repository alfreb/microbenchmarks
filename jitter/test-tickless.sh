#!/bin/bash

# Requires "yum install stress perf"

echo "Testing for tickless kernel. Without nohz_full we expect around 1000 interrupts per core"

CORES="0 6 7"

echo "Testing cores ${CORES}"

for CPU in ${CORES}; do
	echo "----"
	echo "Testing timer interrupts on core $CPU for 1 sec"
	perf stat -C $CPU -e irq_vectors:local_timer_entry taskset -c $CPU stress -t 1 -c 1
done
