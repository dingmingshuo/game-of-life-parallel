# game-of-life-parallel
A parallel implementation of John Conway's game of life.

## Introduction
This is a homework of the Course "Parallel Computing II" in Peking University taught by Prof. Chao Yang.
A baseline version of Conway's game of life is provided by teacher, our target is to optimize this program using OpenMP or MPI.

Compile the program using:

> make *.out

If you want to run any program compiled under slurm system, please modify the `run.slurm` file (especially the 12th line), and:

> sbatch run.slurm

## Result

| Methods | Wall Time |
|-|-|
| Baseline | 7.146458s |
| Easyopt (8 threads) | 0.458212s |