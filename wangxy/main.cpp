/*
 * @author Wang Xingyu
 * @date 2022/3/29
 */

#include "data.h"
#include "bucket.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#define FILENUM 7          // 文件数量
#define WINDOWLEN 10000    // 窗口长度
#define INTERNAL 100000    // 打印间隔
#define STREAMLEN 1000000  // 文件长度
#define TIME1 10000        // 打印分桶情况的时间1
#define TIME2 500000       // 打印分桶情况的时间2
#define TIME3 1000000      // 打印分桶情况的时间3

int main(int argc, char *argv[])
{
    // 数据生成
    GenerateData();
    
    // 设置文件名
    const char *decimalfile = "integer_1000000.dat";
    const char *binaryfile[FILENUM];
    for (int i = 0; i < 7; i++) {
        string name = "Binary_1000000_" + to_string(i) + ".dat";
        binaryfile[i] = name.c_str();
    }

    // 打开十进制数据文件并读取数据
    int *decimaldata = (int*)malloc(STREAMLEN * sizeof(int));
    FILE *file = fopen(decimalfile, "r");
    // 若打开失败，处理异常
    if (file == NULL) {
        fprintf(stderr, "open %s error\n", decimalfile);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < STREAMLEN; i++) {
        fscanf(file, "%d", &decimaldata[i]);
    }
    fclose(file);

    // 打开比特流文件
    FILE *fd[FILENUM];
    for (int i = 0; i < FILENUM; i++) {
        fd[i] = fopen(binaryfile[i], "r");
        // 若打开失败，处理异常
        if (fd[i] == NULL) {
            fprintf(stderr, "open %s error\n", binaryfile[i]);
            exit(EXIT_FAILURE);
        }
    }

    // 设置比特流文件对应的链表
    vector<Linkedlist*> buckets;
    for (int i = 0; i < FILENUM; i++) {
        buckets.push_back(new Linkedlist);
    }

    // 数据读取与具体实现
    int true_value = 0;  // 真实值
    int time = 1;
    while (time <= STREAMLEN) {
        for (int i = 0; i < FILENUM; i++) {
            // 如果尾部桶timestamp=当前时间-窗口长度，舍弃
            if(buckets[i]->tail != nullptr && buckets[i]->tail->timestamp <= time-WINDOWLEN) {
                buckets[i]->delete_tail();
            }

            // 读取并处理到来的数据
            int sign;
            fscanf(fd[i], "%d", &sign);
            if (sign == 1) {
                // 建桶
                buckets[i]->head_insert(time, 1);
                // 判断新桶之后的两个桶的size是否等于当前桶size
                Node *p = buckets[i]->head;
                while (p->next != nullptr && p->next->next != nullptr && 
                p->size == p->next->size && p->next->size == p->next->next->size) {
                    p = p->next;
                    buckets[i]->merge(p);  // 合并
                }
            }
        }

        true_value += decimaldata[time-1];  // 时刻更新真实值
        // 超过窗口大小时。超出部分去掉
        if (time - 1 >= WINDOWLEN) {
            true_value -= decimaldata[time-1-WINDOWLEN];
        }

        // 在要求时间戳对比真实值与估计值
        if (time % INTERNAL == 0) {
            /*
            // 确定窗口长度
            int curr_win = WINDOWLEN;
            if (curr_win < WINDOWLEN) {
                curr_win = time;
            }
            */

            // 估计值的计算
            vector<int> num_1bit;  // 记录各比特流的当前1bit的估计值
            for (int i = 0; i < FILENUM; i++){
                int tmp = buckets[i]->eval();
                num_1bit.push_back(tmp);
            }

            int estimate = 0;  // 估计值
            for (int i = 0; i < FILENUM; i++) {
                // double c_i = (double) num_1bit[i] / (double) curr_win;
                double c_i = (double) num_1bit[i];
                estimate += c_i * pow(2, i);
            }

            cout << "timestamp = " << time << endl;
            cout << "\t" << "estimate: " << estimate << endl;
            cout << "\t" << "truth: " << true_value << endl;

            // 在要求时间戳时打印分桶情况
            if (time == TIME1 || time == TIME2 || time == TIME3) {
                cout << "Timestamp = " << time << endl;
                for (int i = 0; i < FILENUM; i++) {
                    buckets[i]->show();
                }
            }
        }
        time++;
    }
    free(decimaldata);

    // 关闭文件
    for (int i = 0; i < FILENUM; i++) {
        fclose(fd[i]);
    }
    return 0;
}
