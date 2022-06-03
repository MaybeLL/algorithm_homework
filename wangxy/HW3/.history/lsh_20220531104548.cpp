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

int tmp_SignatureMatrix[12][11];
int tmp_SignatureMatrix = {{2,2,1,0,0,1,3,2,5,0,3},
                           {1,3,2,0,2,2,1,4,2,1,2},
                           {3,0,3,0,4,3,2,0,0,4,2},
                           {0,4,3,1,5,3,3,2,3,5,4},
                           {2,1,1,0,4,1,2,1,4,2,5},
                           {4,2,1,0,5,2,3,2,3,5,4},
                           {2,4,3,0,5,3,3,4,4,5,3},
                           {0,2,4,1,3,4,3,2,2,2,4},
                           {0,2,1,0,5,1,1,1,1,5,1},
                           {0,5,1,0,2,1,3,2,1,5,4},
                           {1,3,1,0,5,2,3,3,6,3,2},
                           {0,5,2,1,5,1,2,2,26,}}

void LSH(int ** SignatureMatrix, int b, int r){
    assert(b * r == SIGNATURES_NUM);

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
