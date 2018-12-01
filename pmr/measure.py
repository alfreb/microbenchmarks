#! /usr/bin/python

import subprocess
import os

print "Measuring allocation time"

build_dir = "./build/"
packets = 100000
packetsize = 1500
results = {"test" : [], "test_pmr" : [], "test_stdalloc" : [] }
iterations = 50

def build():
    os.system("mkdir -p " + build_dir + ";pushd " + build_dir + "; cmake ..; make -j4 ; popd")

def run(binary):
    cmd = ["time",  build_dir + binary, str(packets), str(packetsize)]    
    print "Running ", cmd
    res = subprocess.check_output(cmd, stderr=subprocess.STDOUT)
    
    cmd, output, time_str, ignore = res.split("\n")
    real, realstr, user, userstr, sys, sysstr = time_str.split()    

    assert("failed: 0" in output)    
    results[binary].append({"real" : float(real), "user" : float(user), "sys" : float(sys)})

def average_time(binary):
    sums  = {"real" : 0, "user" : 0, "sys" : 0}
    avg   = {"real" : 0, "user" : 0, "sys" : 0}
    
    count = len(results[binary])
    
    for entry in results[binary]:
        sums["real"] += entry["real"]
        sums["user"] += entry["user"]
        sums["sys"]  += entry["sys"]                

    avg["real"] = round(sums["real"] / count, 3)
    avg["user"] = round(sums["user"] / count, 3)
    avg["sys"]  = round(sums["sys"]  / count, 3)

    return avg


def print_averages():
    baseline = "test"
    print ""
    print "Averages over ", iterations, " iterations interleaved"
    print "Baseline: ", baseline, " with std::shared_ptr<std::vector>"
    avg_base = average_time(baseline)
    print baseline, "   \t real: ", avg_base["real"], "\tuser: ", avg_base["user"], "\tsys: ", avg_base["sys"]    
    
    for binary in results.keys():
        if (binary == baseline):
            continue
        avg  = average_time(binary)
        diff = avg["real"] / avg_base["real"]
        diffstr = "(" + str(round(diff * 100, 1)) + "% of baseline)"
        
        print binary, "\t real: ", avg["real"], "\tuser: ", avg["user"], "\tsys: ", avg["sys"], diffstr
    

build()
    
for i in range(0, iterations):
    for binary in results.keys():
        run(binary);

print_averages()        
