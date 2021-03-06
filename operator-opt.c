/*
    This implementation does some easy optimization on the baseline code.
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define L1 2000
#define L2 2000
#define LT 100
#define SEED 0
#define LS (L1 * L2)

char world[2][L1 + 2][L2 + 2];

double get_walltime() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return (double)(tp.tv_sec + tp.tv_usec * 1e-6);
}

int main(int argc, char* argv[]) {
    int i, j, t, x, y, x0, y0;
    int ineighbor, neighbors, population0, population;
    double time;

    // initialize data
    srand(SEED);
    population0 = 0;
    for (i = 1; i <= L1; i++) {
        for (j = 1; j <= L2; j++) {
            world[0][i][j] = rand() % 2;
            if (world[0][i][j] == 1) population0++;
        }
    }

    time = get_walltime();
    for (t = 0; t < LT; t++) {
        char world_d0 = t & 1;
        char result_d0 = (t + 1) & 1;

        for (i = 1; i <= L1; i++) {
            char* wi = world[world_d0][i];
            *(wi + 0) = *(wi + L2);
            *(wi + L2 + 1) = *(wi + 1);
        }

        char* wi_0 = world[world_d0][0];
        char* wi_1 = world[world_d0][1];
        char* wi_l1 = world[world_d0][L1];
        char* wi_l1_1 = world[world_d0][L1 + 1];
        for (j = 1; j <= L2; j++) {
            *(wi_0 + j) = *(wi_l1 + j);
            *(wi_l1_1 + j) = *(wi_1 + j);
        }
        *(wi_0 + 0) = *(wi_l1 + L2);
        *(wi_0 + L2 + 1) = *(wi_l1 + 1);
        *(wi_l1_1 + 0) = *(wi_1 + L2);
        *(wi_l1_1 + L2 + 1) = *(wi_1 + 1);

#pragma omp parallel for
        for (i = 1; i <= L1; i++) {
            char* im = world[world_d0][i - 1];
            char* in = world[world_d0][i];
            char* ia = world[world_d0][i + 1];
            char* r = world[result_d0][i];
            for (j = 1; j <= L2; j++) {
                neighbors = *(im + j - 1) + *(im + j) + *(im + j + 1) +
                            *(in + j - 1) + *(in + j) + *(in + j + 1) +
                            *(ia + j - 1) + *(ia + j) + *(ia + j + 1);
                *(r + j) = (neighbors == 3) || ((neighbors - *(in + j)) == 3);
            }
        }
    }
    population = 0;
#pragma omp parallel for collapse(2) reduction(+ : population)
    for (i = 1; i <= L1; i++) {
        for (j = 1; j <= L2; j++) {
            population += world[LT & 1][i][j];
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