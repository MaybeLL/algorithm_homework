#include <cstdio>
#include <cstdlib>
#define SINGLES_NUM 493 //singles num
#define DOCS_NUM 1000 //documents num


void GenerateJaccard(int** singles_matrix, double** jaccard_matrix) {
    for (int i = 0; i < DOCS_NUM-1; i++) {
        for (int j = i + 1; j < DOCS_NUM; j++) {
            int inter_set = 0,
                union_set = 0;
            for (int k = 0; k < SINGLES_NUM; k++) {
                inter_set += singles_matrix[i][k] & singles_matrix[j][k];
                union_set += singles_matrix[i][k] | singles_matrix[j][k];
            }
            jaccard_matrix[i][j] = (double)inter_set / union_set;
        }
    }
}
