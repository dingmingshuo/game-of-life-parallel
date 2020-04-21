/*
    This implementation does some easy optimization on the baseline code.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>

#define L1 2000
#define L2 2000
#define LT 100
#define SEED 0
#define LS (L1 * L2)

char world[L1 + 2][L2 + 2];
char result[L1 + 2][L2 + 2];

double get_walltime() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return (double)(tp.tv_sec + tp.tv_usec * 1e-6);
}

int main(int argc, char *argv[]) {
    int i, j, t, x, y, x0, y0;
    int ineighbor, neighbors, population0, population;
    double time;

    // initialize data
    srand(SEED);
    population0 = 0;
    for (i = 0; i < L1; i++) {
        for (j = 0; j < L2; j++) {
            world[i + 1][j + 1] = rand() % 2;
            if (world[i + 1][j + 1] == 1) population0++;
        }
    }

    // set OpenMP threads
    omp_set_num_threads(8);

    // naive implementation
    time = get_walltime();
    for (t = 0; t < LT; t++) {
        #pragma omp parallel for
        for (i = 1; i <= L1; i++) {
            world[i][0] = world[i][L2];
            world[i][L2 + 1] = world[i][1];
        }
        #pragma omp parallel for
        for (j = 1; j <= L2; j++) {
            world[0][j] = world[L1][j];
            world[L1 + 1][j] = world[1][j];
        }
        world[0][0] = world[L1][L2];
        world[0][L2 + 1] = world[L1][1];
        world[L1 + 1][0] = world[1][L2];
        world[L1 + 1][L2 + 1] = world[1][1];

        #pragma omp parallel for collapse(2)
        for (i = 1; i <= L1; i++) {
            for (j = 1; j <= L2; j++) {
                neighbors = world[i - 1][j - 1] + world[i - 1][j] +
                            world[i - 1][j + 1] + world[i][j - 1] +
                            world[i][j + 1] + world[i + 1][j - 1] +
                            world[i + 1][j] + world[i + 1][j + 1];
                result[i][j] = (neighbors == 3 || (neighbors == 2 && (world[i][j] != 0)));
            }
        }
        memcpy(world, result, sizeof(world));
    }   
    population = 0;
    #pragma omp parallel for collapse(2)
    for (i = 1; i <= L1; i++) {
        for (j = 1; j <= L2; j++) {
            population += world[i][j];
        }
    }
    time = get_walltime() - time;

    // report results
    printf("World size: %d x %d, total generations: %d\n", L1, L2, LT);
    printf("Population is changed from %d to %d\n", population0, population);
    printf("Max Threads: %d\n", omp_get_max_threads());
    printf("Wall time: %f\n", time);

    return 0;
}