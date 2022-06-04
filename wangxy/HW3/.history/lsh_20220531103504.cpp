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
#include <unordered_set>
#include <unordered_map>

#define SIGNATURES_NUM 30     // 签名数量

typedef unsigned long long ull;
uint32_t p_value = 4930001;

// 处理特征矩阵, 生成签名矩阵
int **generateSignatureMatrix(elemtype **feature_matrix, int feature_dim) {
    int **signature_matrix = (int **) malloc(DOCS_NUM * sizeof(int *));
    for (int i = 0; i < DOCS_NUM; i++) {
        signature_matrix[i] = (int *) malloc(SIGNATURES_NUM * sizeof(int));
    }

    // h(x) = ((a*x + b) mod p_value) mod feature_num

    for (int count = 0; count < SIGNATURES_NUM; count++) {
        // 生成a, b
        std::mt19937 rnd((unsigned int)time(NULL) + count * count);
        uint32_t a = rnd(), b = rnd();
        // printf("a=%u, b=%u\n", a, b);
        for (int i = 0; i < DOCS_NUM; i++) {
            // 将得到signatures_matrix[i][count]的值, 初始化为足够大的值
            signature_matrix[i][count] = feature_dim;
            // printf("signature matrix[%d][%d]:\n", i, count);
            for (int s = 0; s < feature_dim; s++) {
                if (feature_matrix[i][s] != 1) continue;
                int hash_value = (((ull)a*s + b) % p_value) % feature_dim;
                // printf("%d ", hash_value);
                if (hash_value < signature_matrix[i][count]) {
                    signature_matrix[i][count] = hash_value;
                }
            }
            // printf("\n");
        }
    }
    return signature_matrix;
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
