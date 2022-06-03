/*
 * @author xuziyue
 * @date 2022/5/31
 */

#pragma once
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>
#include <assert.h>
#include <utility>
#include <iostream>

using namespace std;

typedef int elemtype;  // 特征矩阵元素类型, 后期可以修改
typedef unsigned long long ull;
typedef pair<int,int> pii;

typedef pair<pii,float> ppf;
typedef vector<ppf> rst_vec;

class LSH_DATA;

void LSH(elemtype ** SignatureMatrix, elemtype b, elemtype r);

int ** compress(int **signature_matrix, int r);
