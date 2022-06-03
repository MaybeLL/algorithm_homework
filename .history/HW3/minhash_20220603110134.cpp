/*
 * @author WangXingyu
 * @date 2022/5/30
 */

#include "minhash.h"

typedef unsigned long long ull;
uint32_t p_value = 4930001;

// 读取singles集合, 生成特征矩阵
elemtype **generateFeatureMatrix(const char *filename, int &feature_dim) {
    FILE *fp = fopen(filename, "r");
    unsigned int **singles_matrix = (unsigned int **) malloc(DOCS_NUM * sizeof(unsigned int*));
    for (int i = 0; i < DOCS_NUM; i++) {
        singles_matrix[i] = (unsigned int *) malloc(SINGLES_NUM * sizeof(unsigned int));
    }

    // 利用unordered_set O(1)的查找效率记录所有不重复的singles
    std::vector<unsigned int> singles_vector;
    std::unordered_set<unsigned int> unique_singles;
    for (int i = 0; i < DOCS_NUM; i++) {
        for (int j = 0; j < SINGLES_NUM; j++) {
            fscanf(fp, "%u", &singles_matrix[i][j]);
            // 如果该single不在集合中, 将其加入
            auto iter = unique_singles.find(singles_matrix[i][j]);
            if (iter == unique_singles.end()) {
                unique_singles.emplace(singles_matrix[i][j]);
                singles_vector.push_back(singles_matrix[i][j]);
            }
        }
    }
    fclose(fp);

    // 特征矩阵的维度: DOCS_NUM * feature_dim
    feature_dim = singles_vector.size();

    std::sort(singles_vector.begin(), singles_vector.end());

    // 记录每个single与其索引的映射, 方便之后特征矩阵的生成
    std::unordered_map<unsigned int, int> single2idx_map;
    for (int i = 0; i < feature_dim; i++) {
        single2idx_map[singles_vector[i]] = i;
    }

    // feature_matrix[i][j]表示第j个single是否在文档i中(使用calloc, 初始为0)
    elemtype **feature_matrix = (elemtype **) malloc(DOCS_NUM * sizeof(elemtype *));
    for (int i = 0; i < DOCS_NUM; i++) {
        feature_matrix[i] = (elemtype *) calloc(feature_dim, sizeof(elemtype));
    }

    // 只需要将文档i所有singles对应的位置改为1即可
    // 即通过single2idx_map查找singles_matrix[i][j]的列索引
    for (int i = 0; i < DOCS_NUM; i++) {
        for (int j = 0; j < SINGLES_NUM; j++) {
            auto index = single2idx_map[singles_matrix[i][j]];
            feature_matrix[i][index] = 1;
        }
    }
    
    free(singles_matrix);
    return feature_matrix;
}

// 处理特征矩阵, 生成签名矩阵
void generateSignatureMatrix(elemtype **feature_matrix, int feature_dim, int **signature_matrix) {
    // h(x) = ((a*x + b) mod p_value) mod feature_num
    for (int i = 0; i < DOCS_NUM; i++) {
        for (int count = 0; count < SIGNATURES_NUM; count++) {
            // 将得到signatures_matrix[i][count]的值
            std::mt19937 rnd((unsigned int)time(NULL) + count);
            uint32_t a = rnd(), b = rnd();  // 生成a, b
            printf("%u %u\n", a, b);
            signature_matrix[i][count] = feature_dim; // 初始化需要足够大
            for (int j = 0; j < feature_dim; j++) {
                if (feature_matrix[i][j] != 1) continue;
                int hash_value = (((ull)a*j + b) % p_value) % feature_dim;
                if (hash_value < signature_matrix[i][count]) {
                    signature_matrix[i][count] = hash_value;
                }
            }
        }
    }
}

/*
int main()
{
    const char *filename = "SinglesSet.txt";  // singles集合
    int feature_dim;  // 特征矩阵的列的维度, 即不同singles的数量

    elemtype **feature_matrix = generateFeatureMatrix(filename, feature_dim);

    int **signature_matrix = generateSignatureMatrix(feature_matrix, feature_dim);

    FILE *fp_sigm = fopen("SigMat.txt", "w");
    for (int i = 0; i < DOCS_NUM; i++) {
        for (int j = 0; j < SIGNATURES_NUM; j++) {
            fprintf(fp_sigm, "%d ", signature_matrix[i][j]);
        }
        fprintf(fp_sigm, "\n");
    }

    free(feature_matrix);
    free(signature_matrix);
    return 0;
}
*/
