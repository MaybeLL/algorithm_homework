/*
 * @author xuziyue
 * @date 2022/5/31
 */

#pragma once

typedef int elemtype;  // 特征矩阵元素类型, 后期可以修改
typedef unsigned long long ull;
typedef pair<int,int> pii;

typedef pair<pii,float> ppf;
typedef vector<ppf> rst_vec;

class LSH_DATA;

void LSH(elemtype ** SignatureMatrix, elemtype b, elemtype r);

elemtype ** compress(elemtype SignatureMatrix[][DOCS_NUM], elemtype r);
