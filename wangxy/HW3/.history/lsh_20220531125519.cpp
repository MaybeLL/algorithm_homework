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
#include <iostream>

#define SIGNATURES_NUM 30     // 签名数量
#define DOCS_NUM 11           // 测试文档数量
#define SIGNATURES_NUM 12     // 测试签名数量

using namespace std;

typedef unsigned long long ull;
typedef pair<int,int> pii;

class LSH_DATA{
public:
    int times = 0;
    int prob[int(DOCS_NUM * (DOCS_NUM-1) / 2)] = {0};

    pii transform(int doc_idx){
        int a = int(doc_idx / DOCS_NUM);
        int b = doc_idx % DOCS_NUM;
        return pii(a, b);
    }
    void lsh(int ** CompatedSignatureMatrix, int b, int r){
    // assert(b * r == SIGNATURES_NUM);
    int traverse_num = int(DOCS_NUM * (DOCS_NUM-1) / 2);
    LSH_DATA lsh_data;
    }
};

int ** compat(int SignatureMatrix[][DOCS_NUM], int r){
    int **tmp_SignatureMatrix = new int *[DOCS_NUM];
    for(int i = 0; i<int(SIGNATURES_NUM / r); i++){
        tmp_SignatureMatrix[i] = new int[DOCS_NUM];
    }
    for(int i = 0; i < int(SIGNATURES_NUM / r); i++){
        for(int j = 0; j < DOCS_NUM; j++){
            tmp_SignatureMatrix[i][j] = 100 * SignatureMatrix[i * r][j]
                                        + 10 * SignatureMatrix[i * r + 1][j]
                                        + SignatureMatrix[i * r + 2][j];
            // cout<<tmp_SignatureMatrix[i][j]<<endl;
        }
    }
    return tmp_SignatureMatrix;
}

int main()
{
    int tmp_SignatureMatrix[SIGNATURES_NUM][DOCS_NUM] = {2,2,1,0,0,1,3,2,5,0,3,
                                                        1,3,2,0,2,2,1,4,2,1,2,
                                                        3,0,3,0,4,3,2,0,0,4,2,
                                                        0,4,3,1,5,3,3,2,3,5,4,
                                                        2,1,1,0,4,1,2,1,4,2,5,
                                                        4,2,1,0,5,2,3,2,3,5,4,
                                                        2,4,3,0,5,3,3,4,4,5,3,
                                                        0,2,4,1,3,4,3,2,2,2,4,
                                                        0,2,1,0,5,1,1,1,1,5,1,
                                                        0,5,1,0,2,1,3,2,1,5,4,
                                                        1,3,1,0,5,2,3,3,6,3,2,
                                                        0,5,2,1,5,1,2,2,6,5,4};
    int ** compat_matrix = compat(tmp_SignatureMatrix, 3);
    // cout<<int(SIGNATURES_NUM / 3)<<endl;
    // cout<<compat_matrix<<endl;
    for (int i = 0; i < int(SIGNATURES_NUM / 3); i++) {
        for (int j = 0; j < DOCS_NUM; j++) {
            printf("%d ", compat_matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
