#!/bin/bash
#SBATCH -n 4
#SBATCH -c 12
#SBATCH -x node10[01-32]

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

mpirun ./pi > pi.out
