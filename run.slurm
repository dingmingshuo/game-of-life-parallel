#!/bin/bash

#SBATCH -o job.out
#SBATCH --partition=cpu
#SBATCH -J life_game
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=8
#SBATCH --cpus-per-task=1
#SBATCH -t 30:00

export OMP_NUM_THREADS=8
./operator-opt.out
