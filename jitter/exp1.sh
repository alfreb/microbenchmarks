#! /bin/bash

set -eu


if [ "$#" -ne 3 ]
then
    echo -e "Usage: \n$0 non-isolated-core isolated-core filename-prefix"
    exit 42
fi    

PLAIN_CORE=$1
ISOL_CORE=$2

PREFIX=$3

TASK_SIZE=60000
TASK_COUNT=1000000

#FREQ_PLAIN=`cat /sys/devices/system/cpu/cpufreq/policy$PLAIN_CORE/cpuinfo_cur_freq`
#FREQ_ISOL=`cat /sys/devices/system/cpu/cpufreq/policy$ISOL_CORE/cpuinfo_cur_freq`



# CPU frequencies check

#if [ "$FREQ_ISOL" -ne "$FREQ_NOISOL" ]
#then
#    echo "CPU frequencies differ: $FREQ_ISOL vs. $FREQ_NOISOL"
#    exit 42
#else
#    echo "[x] CPU frequencies match - OK"
#fi



# CPU flags check

CPUFLAGS=`grep -m 1 ^flags /proc/cpuinfo | grep "constant_tsc" | grep "nonstop_tsc"`

if [ "$CPUFLAGS" == "" ]
then
    echo "rdtsc CPU flag MISSING"
    exit 42
else
    echo "[x] Required CPU flags present - OK"
fi


# NUMA node check

NODES=`numactl -H | grep available | cut -d' ' -f2`

if [ "$NODES" -ne "1" ]
then
    echo "Currently only 1 NUMA nodes supported"
    exit 42
else 
    echo "[x] NUMA node check OK"
fi

PLAIN_NUMA_NODE=0
ISOL_NUMA_NODE=0

# Build 
make 

# Timestamp this run
TIME=`date --iso-8601=seconds`



# Run NO isolcpu

echo -e "Running basic jitter experiment WITHOUT\tisolcpus - on core $PLAIN_CORE"

#numactl -C $PLAIN_CORE -m $PLAIN_NUMA_NODE ./main $TASK_SIZE $TASK_COUNT > "${PREFIX}_DEFAULT_${TIME}.txt"
taskset -c $PLAIN_CORE ./main $TASK_SIZE $TASK_COUNT > "${PREFIX}_DEFAULT_${TIME}.txt"

echo -e "Running basic jitter experiment WITH \tisolcpus - on core $ISOL_CORE"

#numactl -C $ISOL_CORE -m $ISOL_NUMA_NODE ./main $TASK_SIZE $TASK_COUNT > "${PREFIX}_ISOLCPU_${TIME}.txt"
taskset -c $ISOL_CORE  ./main $TASK_SIZE $TASK_COUNT > "${PREFIX}_ISOLCPU_${TIME}.txt"
