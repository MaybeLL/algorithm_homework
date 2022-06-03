/*
 * @author xuziyue
 * @date 2022/5/31
 */

#pragma once

typedef int elemtype;  // 特征矩阵元素类型, 后期可以修改

void LSH(int ** SignatureMatrix, int b, int r);

int ** compress(int SignatureMatrix[][DOCS_NUM], int r)；