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
#define DOCS_NUM 11
#define SIGNATURES_NUM 12


typedef unsigned long long ull;

void LSH(int ** SignatureMatrix, int b, int r){
    assert(b * r == SIGNATURES_NUM);

}

int main()
{
    printf("signature matrix:\n");
    for (int i = 0; i < DOCS_NUM; i++) {
        for (int j = 0; j < SIGNATURES_NUM; j++) {
            printf("%d ", tmp_SignatureMatrix[i][j]);
        }
        printf("\n");
    }

    free(feature_matrix);
    free(signature_matrix);
    return 0;
}
