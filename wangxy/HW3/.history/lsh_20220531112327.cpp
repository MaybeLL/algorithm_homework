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
#define DOCS_NUM 11           // 测试文档数量
#define SIGNATURES_NUM 12     // 测试签名数量

typedef unsigned long long ull;

class LSH_data{
    int times = 0;
    float prob[DOCS_NUM * (DOCS_NUM-1) / 2];
}

void LSH(int ** SignatureMatrix, int b, int r){
    // assert(b * r == SIGNATURES_NUM);
    lsh_data = LSH_data()

}

int main()
{
    int tmp_SignatureMatrix[12][11] = {{2,2,1,0,0,1,3,2,5,0,3},
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
                            {0,5,2,1,5,1,2,2,6,5,4}};
    printf("signature matrix:\n");
    for (int i = 0; i < DOCS_NUM; i++) {
        for (int j = 0; j < SIGNATURES_NUM; j++) {
            printf("%d ", tmp_SignatureMatrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
