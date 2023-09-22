#!/bin/sh

#SBATCH --time=3500

export KMP_AFFINITY="granularity=fine,compact,1,0"


OMP_NUM_THREADS=1 perl ./run_tests.pl
cp res.csv res_1.csv

OMP_NUM_THREADS=5 perl ./run_tests.pl
cp res.csv res_5.csv

OMP_NUM_THREADS=10 perl ./run_tests.pl
cp res.csv res_10.csv

OMP_NUM_THREADS=10 perl ./run_tests.pl
cp res.csv res_20.csv