/*
 * @author xuziyue
 * @date 2022/5/31
 */

#pragma once

typedef int elemtype;  // 特征矩阵元素类型, 后期可以修改

void LSH(elemtype ** SignatureMatrix, int b, int r);

elemtype ** compress(int SignatureMatrix[][DOCS_NUM], int r);
