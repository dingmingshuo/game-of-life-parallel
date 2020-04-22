# game-of-life-parallel
A parallel implementation of John Conway's game of life.

## Introduction
This is a homework of the Course "Parallel Computing II" in Peking University taught by Prof. Chao Yang.
A baseline version of Conway's game of life is provided by teacher, our target is to optimize this program using OpenMP or MPI.

Compile the program using:

> make *.out

If you want to run any program compiled under slurm system, please modify the `run.slurm` file (especially the 12th line), and:

> sbatch run.slurm

## Methods

### Baseline

A naive simulation of Conway's game of life.

### Easy optimization

This code does some easy optimization on the baseline code.

Reduce conditional branches of the macro `index(i,L)` in the baseline code.
Change the `world` and `result` array into two-dimentional arrays, avoid the calculation of indexes.
And use OpenMP to achieve parallel optimization.

### Operator optimization

The calculation of the two-dimentional arrays' indexes in easyopt version will use the `imul` assembler instruction, which is quite slow.
So I simply use pointers to avoid `imul` instruction.


## Result

| Methods | Wall Time |
|-|-|
| Baseline | 7.146458s |
| Easy opt (8 threads) | 0.458212s |
| Operator opt (8 threads) | 0.253401s |