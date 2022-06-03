/*
 * @author xuziyue
 * @date 2022/5/31
 */

#pragma once

typedef int elemtype;  // 特征矩阵元素类型, 后期可以修改

// 读取singles集合, 生成特征矩阵
elemtype **generateFeatureMatrix(const char *filename, int &feature_dim);

// 处理特征矩阵, 生成签名矩阵
int **generateSignatureMatrix(elemtype **feature_matrix, int feature_dim);

void LSH(int ** SignatureMatrix, )