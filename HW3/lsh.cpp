/*
 * @author xuziyue
 * @date 2022/5/31
 */

#include "minhash.h"
#include "lsh.h"

#define SIGNATURES_NUM 30 // 签名数量
#define DOCS_NUM 1000     // 文档数量
// #define SIGNATURES_NUM 12     // 测试签名数量

class LSH_DATA
{
public:
    elemtype times = 1;
    elemtype prob[elemtype(DOCS_NUM * (DOCS_NUM - 1) / 2)] = {0};

    pii transform(elemtype doc_idx)
    {
        elemtype a = elemtype(doc_idx / DOCS_NUM);
        elemtype b = doc_idx % DOCS_NUM;
        return pii(a, b);
    }

    void lsh(elemtype **CompressedSignatureMatrix, elemtype b, elemtype r)
    {
        // assert(b * r == SIGNATURES_NUM);
        elemtype traverse_num = elemtype(DOCS_NUM * (DOCS_NUM - 1) / 2);
        elemtype first = 0, second = 0;
        for (elemtype i = 0; i < traverse_num; i++)
        {
            pii tmp = transform(i);
            first = tmp.first;
            second = tmp.second;
            for (elemtype j = 0; j < b; j++)
            {
                if (CompressedSignatureMatrix[j][first] == CompressedSignatureMatrix[j][second])
                {
                    this->prob[i] += 1;
                    break;
                }
            }
        }
    }

    rst_vec get_rst()
    {
        rst_vec rst;
        elemtype traverse_num = elemtype(DOCS_NUM * (DOCS_NUM - 1) / 2);
        elemtype first = 0, second = 0;
        for (elemtype i = 0; i < traverse_num; i++)
        {
            pii tmp = transform(i);
            first = tmp.first;
            second = tmp.second;
            rst.push_back(ppf(pii(first, second), float(this->prob[i] / this->times)));
        }
        return rst;
    }
};

// elemtype ** compress(elemtype SignatureMatrix[][DOCS_NUM], elemtype r){
//     elemtype **tmp_SignatureMatrix = new elemtype *[DOCS_NUM];
//     for(elemtype i = 0; i<elemtype(SIGNATURES_NUM / r); i++){
//         tmp_SignatureMatrix[i] = new elemtype[DOCS_NUM];
//     }
//     for(elemtype i = 0; i < elemtype(SIGNATURES_NUM / r); i++){
//         for(elemtype j = 0; j < DOCS_NUM; j++){
//             tmp_SignatureMatrix[i][j] = 100 * SignatureMatrix[i * r][j]
//                                         + 10 * SignatureMatrix[i * r + 1][j]
//                                         + SignatureMatrix[i * r + 2][j];
//             // cout<<tmp_SignatureMatrix[i][j]<<endl;
//         }
//     }
//     return tmp_SignatureMatrix;
// }

elemtype **compress(elemtype **signature_matrix, elemtype r)
{
    for (elemtype i = 0; i < SIGNATURES_NUM; i++)
    {
        if (i % r == 0)
        {
            for (elemtype j = 0; j < DOCS_NUM; j++)
            {
                for (elemtype k = 1; k < r; k++)
                {
                    signature_matrix[i][j] *= 10;
                    signature_matrix[i][j] += signature_matrix[i + k][j];
                    // cout<<tmp_SignatureMatrix[i][j]<<endl;
                }
            }
        }
    }
}

/*
elemtype main()
{
    elemtype tmp_SignatureMatrix[SIGNATURES_NUM][DOCS_NUM] = {2,2,1,0,0,1,3,2,5,0,3,
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
    elemtype ** compress_matrix = compress(tmp_SignatureMatrix, 3);
    // cout<<elemtype(SIGNATURES_NUM / 3)<<endl;
    // cout<<compress_matrix<<endl;
    for (elemtype i = 0; i < elemtype(SIGNATURES_NUM / 3); i++) {
        for (elemtype j = 0; j < DOCS_NUM; j++) {
            printf("%d ", compress_matrix[i][j]);
        }
        printf("\n");
    }
    LSH_DATA lsh_data;
    lsh_data.lsh(compress_matrix, 4, 3);
    rst_vec rst = lsh_data.get_rst();
    for(elemtype i = 0; i < rst.size(); i++){
        cout<<"("<<rst[i].first.first<<","<<rst[i].first.second<<") probability = "<<rst[i].second<<endl;
    }
    return 0;
}
*/
