#include "minhash.h"
#include "GenerateJaccard.h"
#include "lsh.h"
#include <cstdlib>

#define BR_NUM 6       // 参数b, r的组合数
#define EXP_NUM 1000   // 实验次数

int main()
{
    const char *filename = "SinglesSet.txt";  // singles集合
    int feature_dim;  // 特征矩阵的列的维度, 即不同singles的数量

    // 生成特征矩阵并计算Jaccard相似度
    elemtype **feature_matrix = generateFeatureMatrix(filename, feature_dim);
    double **jaccard_matrix = GenerateJaccard(feature_matrix, feature_dim);

    int b_array[BR_NUM] = {2, 3, 5, 6, 10, 15};
    int r_array[BR_NUM] = {15, 10, 6, 5, 3, 2};

    // 定义签名矩阵, 只开辟一次内存
    int **signature_matrix = (int **) malloc(DOCS_NUM * sizeof(int *));
    for (int i = 0; i < DOCS_NUM; i++) {
        signature_matrix[i] = (int *) malloc(SIGNATURES_NUM * sizeof(int));
    }

    // 共六组b, r
    for (int m = 0; m < BR_NUM; m++) {
        int b = b_array[m], r = r_array[m];
        // 每组b, r实验1000次
        for (int n = 0; n < EXP_NUM; n++) {
            // 生成签名矩阵
            generateSignatureMatrix(feature_matrix, feature_dim, signature_matrix);
            // todo
            
        }
    }

    return 0;
}
