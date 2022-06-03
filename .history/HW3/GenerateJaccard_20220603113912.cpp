#include <cstdio>
#include <cstdlib>
#include 'GenerateJaccard.h'
#define SINGLES_NUM 493 //singles num
#define DOCS_NUM 1000 //documents num


double **GenerateJaccard(int** feature_matrix, int feature_dim) {
    // double **jaccard_matrix = (double **) malloc(DOCS_NUM * sizeof(double *));
    double **jaccard_matrix = new double *[DOCS_NUM];
    for (int i = 0; i < DOCS_NUM; i++) {
        jaccard_matrix[i] = (double *) malloc(DOCS_NUM * sizeof(double));
    }
    for (int i = 0; i < DOCS_NUM-1; i++) {
        for (int j = i + 1; j < DOCS_NUM; j++) {
            int inter_set = 0,
                union_set = 0;
            for (int k = 0; k < feature_dim; k++) {
                inter_set += feature_matrix[i][k] & feature_matrix[j][k];
                union_set += feature_matrix[i][k] | feature_matrix[j][k];
            }
            jaccard_matrix[i][j] = (double)inter_set / union_set;
            jaccard_matrix[j][i] = jaccard_matrix[i][j];
        }
    }
    return jaccard_matrix;
}
