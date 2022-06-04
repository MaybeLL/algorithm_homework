#include <cstdio>
#include <cstdlib>
#include "GenerateJaccard.h"
#define SINGLES_NUM 493 //singles num
#define DOCS_NUM 1000 //documents num


double** GenerateJaccard(int** feature_matrix, int feature_dim) {
    double** jaccard_matrix = (double**)malloc(DOCS_NUM * sizeof(double*));
    if (jaccard_matrix == NULL) {
        fprintf(stderr, "out of memory!");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < DOCS_NUM; i++) {
        jaccard_matrix[i] = (double*)malloc(DOCS_NUM * sizeof(double));
        if (jaccard_matrix[i] == NULL) {
            fprintf(stderr, "out of memory!");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < DOCS_NUM - 1; i++) {
        for (int j = i + 1; j < DOCS_NUM; j++) {
            int inter_set = 0,
                union_set = 0;
            for (int k = 0; k < feature_dim; k++) {
                inter_set += feature_matrix[i][k] & feature_matrix[j][k];
                union_set += feature_matrix[i][k] | feature_matrix[j][k];
            }
            jaccard_matrix[i][j] = (double)inter_set / union_set;
            jaccard_matrix[j][i] = jaccard_matrix[i][j];
            /*
            if (i == 0) {
                printf("%.3f ", jaccard_matrix[i][j]);
            }
            */
        }
    }
    return jaccard_matrix;
}
