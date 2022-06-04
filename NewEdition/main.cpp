/*
 * @author WangXingyu
 * @date 2022/6/3
 */

#define _CRT_SECURE_NO_DEPRECATE

#include "minhash.h"
#include "GenerateJaccard.h"
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <string>
#include <ctime>
#include <cmath>
#include <unordered_map>

#define BR_NUM 6       // 参数b, r的组合数
#define EXP_NUM 1000   // 实验次数


typedef unsigned long long ull;

void thread_task(int b, int r, elemtype **feature_matrix, int feature_dim, double **jaccard_matrix) {
    // 定义签名矩阵, 只开辟一次内存
    int** signature_matrix = (int**)malloc(DOCS_NUM * sizeof(int*));
    if (signature_matrix == NULL) {
        fprintf(stderr, "out of memory!");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < DOCS_NUM; i++) {
        signature_matrix[i] = (int*)malloc(SIGNATURES_NUM * sizeof(int));
        if (signature_matrix[i] == NULL) {
            fprintf(stderr, "out of memory!");
            exit(EXIT_FAILURE);
        }
    }

    // 记录文档i与j之间碰撞的次数
    std::unordered_map<ull, int> rel;
    for (int i = 0; i < DOCS_NUM; i++) {
        for (int j = i + 1; j < DOCS_NUM; j++) {
            rel[(ull)i << 32 | j] = 0;
        }
    }

    // 每组b, r实验1000次
    for (int n = 0; n < EXP_NUM; n++) {
        // 生成签名矩阵
        generateSignatureMatrix(feature_matrix, feature_dim, signature_matrix);
        // 判断文档i与j是否发生碰撞
        for (int i = 0; i < DOCS_NUM; i++) {
            for (int j = i + 1; j < DOCS_NUM; j++) {
                // 逐个比较band, 遇到相同的直接break
                for (int k = 0; k < b; k++) {
                    // 第k个band范围:  [k*r, k*r+r-1]
                    // 判断第k个band是否相同
                    bool band_equal = true;
                    for (int s = k * r; s <= k * r + r - 1; s++) {
                        if (signature_matrix[i][s] != signature_matrix[j][s]) {
                            band_equal = false;
                            break;
                        }
                    }
                    // 如果第k个band不相同, 继续下一个, 反之, 记录碰撞并break
                    if (band_equal == true) {
                        rel[(ull)i << 32 | j] += 1;
                        break;
                    }
                }
            }
        }
    }

    free(signature_matrix);

    // 记录1000次实验的碰撞结果
    std::string filename = std::to_string(b) + std::string("_") + std::to_string(r) + std::string(".txt");
    FILE* fp = fopen(filename.c_str(), "w");
    for (int i = 0; i < DOCS_NUM; i++) {
        for (int j = i + 1; j < DOCS_NUM; j++) {
            double prec = 1.0 - pow(1.0 - pow(jaccard_matrix[i][j], (double)r), (double)b);
            fprintf(fp, "(%d,%d) %.3f %.3f %.3f\n", i, j, (double)rel[(ull)i << 32 | j] / EXP_NUM, jaccard_matrix[i][j], prec);
        }
    }
    fclose(fp);
}

int main()
{
    clock_t start, end;
    start = clock();
    const char* filename = "SinglesSet.txt";  // singles集合
    int feature_dim;  // 特征矩阵的列的维度, 即不同singles的数量

    // 生成特征矩阵并计算Jaccard相似度
    elemtype** feature_matrix = generateFeatureMatrix(filename, feature_dim);
    double** jaccard_matrix = GenerateJaccard(feature_matrix, feature_dim);

    int b_array[BR_NUM] = { 2, 3, 5, 6, 10, 15 };
    int r_array[BR_NUM] = { 15, 10, 6, 5, 3, 2 };

    /* 多线程版本 */
    // 使用6个线程, 一个线程负责一个b,r组合
    std::thread threads[BR_NUM];
    for (int m = 0; m < BR_NUM; m++) {
        int b = b_array[m], r = r_array[m];
        threads[m] = std::thread(thread_task, b, r, feature_matrix, feature_dim, jaccard_matrix);
    }
    for (auto& t : threads) {
        t.join();
    }

    free(feature_matrix);
    free(jaccard_matrix);

    end = clock();
    printf("the run time is %.3f s\n", ((double)end - (double)start) / CLOCKS_PER_SEC);
    return 0;
}
