/*
 * @author WangXingyu
 * @date 2022/5/30
 */

#pragma once

typedef int elemtype;  // 特征矩阵元素类型, 后期可以修改

#define SINGLES_NUM 493       // singles数量
#define DOCS_NUM 1000         // 文档数量
#define SIGNATURES_NUM 30     // 签名数量

// 读取singles集合, 生成特征矩阵
elemtype **generateFeatureMatrix(const char *filename, int &feature_dim);

// 处理特征矩阵, 生成签名矩阵
void generateSignatureMatrix(elemtype **feature_matrix, int feature_dim, int **signature_matrix);
