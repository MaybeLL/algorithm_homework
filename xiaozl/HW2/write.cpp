#include "write.h"
#include <fstream>
#include <random>
using namespace std;

void write(const char* fu1, const char* fu2, const char* fnu1, const char* fnu2) {
    std::mt19937 rand(time(0));
    std::bernoulli_distribution dist(0.5);//利用二项分布来产生均匀的随机数
    std::bernoulli_distribution distn(0.2);//利用二项分布产生非均匀随机数，生成1的概率设置为80%

    unsigned int
        rub1 = 0, rub2 = 0,//分别表示生成的均匀的32个二进制位
        run1, run2,//分别表示利用随机数生成均匀的01
        rnub1 = 0, rnub2 = 0,//分别表示生成的非均匀的32个二进制位
        rnun1, rnun2;//分别表示利用随机数生成非均匀的01
    //4个文件分别为两个非均匀的随机数序列和两个均匀的随机数序列   
    FILE* fpu1 = fopen(fu1, "wb");
    FILE* fpu2 = fopen(fu2, "wb");
    FILE* fpnu1 = fopen(fnu1, "wb");
    FILE* fpnu2 = fopen(fnu2, "wb");

    for (int i = 0; i < 31250000; i++) {//由于总共生成1000000000个二进制数，但是C++读写只能按字节读写，
        for (int j = 0; j < 32; j++) {//所以将其表示为unsigned int一次写四个字节也就是32位，所以总共写31250000次
            run1 = dist(rand);
            run2 = dist(rand);
            rnun1 = distn(rand);
            rnun2 = distn(rand);
            rub1 = (rub1 | run1 << i);
            rub2 = (rub2 | run2 << i);
            rnub1 = (rnub1 | rnun1 << i);
            rnub2 = (rnub2 | rnun2 << i);

        }
        fwrite(&rub1, 1, 4, fpu1);
        fwrite(&rub2, 1, 4, fpu2);
        fwrite(&rnub1, 1, 4, fpnu1);
        fwrite(&rnub2, 1, 4, fpnu2);
    }
    fclose(fpu1);
    fclose(fpu2);
    fclose(fpnu1);
    fclose(fpnu2);
}

