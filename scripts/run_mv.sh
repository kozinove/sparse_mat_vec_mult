#!/bin/sh

#SBATCH --time=3500

export KMP_AFFINITY="granularity=fine,compact,1,0"

rm res.csv

OMP_NUM_THREADS=1 perl ./run_tests.pl  1
#cp res.csv res_1.csv

OMP_NUM_THREADS=5 perl ./run_tests.pl  1
#cp res.csv res_5.csv

OMP_NUM_THREADS=10 perl ./run_tests.pl 1
#cp res.csv res_10.csv

OMP_NUM_THREADS=20 perl ./run_tests.pl 1
#cp res.csv res_20.csv

OMP_NUM_THREADS=1 perl ./run_tests.pl  5
#cp res.csv res_1.csv                  
                                       
OMP_NUM_THREADS=5 perl ./run_tests.pl  5
#cp res.csv res_5.csv                  
                                       
OMP_NUM_THREADS=10 perl ./run_tests.pl 5
#cp res.csv res_10.csv                 
                                       
OMP_NUM_THREADS=20 perl ./run_tests.pl 5
#cp res.csv res_20.csv