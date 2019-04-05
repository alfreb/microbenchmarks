#!/bin/bash

for t in $(seq 1 $1); do
  echo Test on core ${t}
  tail -1 result${t}.csv
  Rscript -e 'args=commandArgs(TRUE);res=read.csv(file=args[1],header=TRUE,sep="\n");summary (res);percentile=quantile(res,probs=c(0.99,0.999,0.9999,0.99999,0.999999,0.9999999),na.rm =TRUE);data.frame(percentile)' result${t}.csv
done
