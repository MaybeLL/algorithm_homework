#include <cstdio>
#include <cstdlib>
#include <random>
#include <ctime>

#define BITLEN 1000000000   // 十亿 bits
#define BYTELEN 125000000   // 1.25亿 bytes
#define ROLLS 31250000      // 一次写入4字节，共需31250000次

void UniformData(FILE *fp1, FILE *fp2) {
    std::default_random_engine g(time(0));
    std::bernoulli_distribution d(0.5);
    unsigned int rel1 = 0, rand_num1;
    unsigned int rel2 = 0, rand_num2;
    for (int i = 0; i < 32; i++) {
        rand_num1 = d(g);
        rel1 = (rel1 | rand_num1 << i);
        rand_num2 = d(g);
        rel2 = (rel2 | rand_num2 << i);
    }
    fwrite(&rel1, 1, 4, fp1);
    fwrite(&rel2, 1, 4, fp2);
}

void NonUniformData(FILE *fp1, FILE *fp2) {
    std::default_random_engine g(time(0));
    std::bernoulli_distribution d(0.2);
    unsigned int rel1 = 0, rand_num1;
    unsigned int rel2 = 0, rand_num2;
    for (int i = 0; i < 32; i++) {
        rand_num1 = d(g);
        rel1 = (rel1 | rand_num1 << i);
        rand_num2 = d(g);
        rel2 = (rel2 | rand_num2 << i);
    }
    fwrite(&rel1, 1, 4, fp1);
    fwrite(&rel2, 1, 4, fp2);
}

// judge=true，生成均匀分布; judge=false，生成非均匀分布
void GenerateData(const char *filename1, const char *filename2, bool judge) {
    FILE *fp1 = fopen(filename1, "wb");
    FILE *fp2 = fopen(filename2, "wb");
    if (fp1 == NULL || fp2 == NULL) {
        fprintf(stderr, "error: fail to open file!\n");
        exit(EXIT_FAILURE);
    }
    int roll = 0;
    while (roll < ROLLS) {
        if (judge) UniformData(fp1, fp2);
        else NonUniformData(fp1, fp2);
        roll++;
    }
    fclose(fp1);
    fclose(fp2);
}

void Calculate(const char *filename1, const char *filename2, int &hamming, double &jaccard) {
    FILE *fp1 = fopen(filename1, "rb");
    FILE *fp2 = fopen(filename2, "rb");
    if (fp1 == NULL || fp2 == NULL) {
        fprintf(stderr, "error: open file unsuccessfully!\n");
        exit(EXIT_FAILURE);
    }
    // jaccard的分子(交集)与分母(并集)
    int inter_set = 0, union_set = 0;
    int count = 0;
    unsigned int num1, num2;
    while (!feof(fp1) || !feof(fp2)) {
        fread(&num1, 4, 1, fp1);
        fread(&num2, 4, 1, fp2);
        unsigned int xor_v = num1 ^ num2;
        unsigned int and_v = num1 & num2;
        unsigned int or_v = num1 | num2;
        int cnt1 = 0, cnt2 = 0, cnt3 = 0;
        // 统计 & 运算结果中1的个数
        while (and_v != 0) {
            cnt1 += and_v & 1;
            and_v = and_v >> 1;
        }
        // 统计 | 运算结果中1的个数
        while (or_v != 0) {
            cnt2 += or_v & 1;
            or_v = or_v >> 1;
        }
        // 统计 ^ 运算结果中1的个数
        while (xor_v != 0) {
            cnt3 += xor_v & 1;
            xor_v = xor_v >> 1;
        }
        inter_set += cnt1;
        union_set += cnt2;
        hamming += cnt3;
        count++;
        if (count >= ROLLS) break;
        // if (count % 1000000 == 0) printf("%d\n", count);
    }
    printf("totol num is %d\n", count);
    if (union_set == 0) {
        fprintf(stderr, "the size of union set is 0!\n");
        exit(EXIT_FAILURE);
    }
    jaccard = (double) inter_set / union_set;
    fclose(fp1);
    fclose(fp2);
}

int main(int argc, char **argv)
{
    clock_t start, end;
    start = clock();
    const char *filename1_1 = "data/uniform_1";
    const char *filename1_2 = "data/uniform_2";
    const char *filename2_1 = "data/non_uniform_1";
    const char *filename2_2 = "data/non_uniform_2";
    int hamming_1 = 0, hamming_2 = 0;
    double jaccard_1 = 0, jaccard_2 = 0;
    // GenerateData(filename1_1, filename1_2, true);
    // GenerateData(filename2_1, filename2_2, false);
    Calculate(filename1_1, filename1_2, hamming_1, jaccard_1);
    Calculate(filename2_1, filename2_2, hamming_2, jaccard_2);
    end = clock();
    printf("the run time is %.3f s\n", double(end-start) / CLOCKS_PER_SEC);
    printf("Uniform Distribution:\n");
    printf("\tJaccard Similarity:%f\n", jaccard_1);
    printf("\tHamming Distance:%d\n", hamming_1);
    printf("Non-Uniform Distribution:\n");
    printf("\tJaccard Similarity:%f\n", jaccard_2);
    printf("\tHamming Distance:%d\n", hamming_2);
    return 0;
}
