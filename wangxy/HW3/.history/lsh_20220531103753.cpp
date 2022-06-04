/*
 * @author xuziyue
 * @date 2022/5/31
 */

#include "part3.h"
#include "lsh.h"

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>
#include <assert.h>
#include <utility>

#define SIGNATURES_NUM 30     // 签名数量

typedef unsigned long long ull;

void LSH(int ** SignatureMatrix, int b, int r){
    assert(b*r == SIGNATURES_NUM)
}

int main()
{
    const char *filename = "SinglesSet.txt";  // singles集合
    int feature_dim;  // 特征矩阵的列的维度, 即不同singles的数量

    elemtype **feature_matrix = generateFeatureMatrix(filename, feature_dim);

    printf("feature matrix:\n");
    for (int i = 0; i < DOCS_NUM; i++) {
        for (int j = 0; j < feature_dim; j++) {
            printf("%d ", feature_matrix[i][j]);
        }
        printf("\n");
    }

    int **signature_matrix = generateSignatureMatrix(feature_matrix, feature_dim);

    printf("signature matrix:\n");
    for (int i = 0; i < DOCS_NUM; i++) {
        for (int j = 0; j < SIGNATURES_NUM; j++) {
            printf("%d ", signature_matrix[i][j]);
        }
        printf("\n");
    }

    free(feature_matrix);
    free(signature_matrix);
    return 0;
}
