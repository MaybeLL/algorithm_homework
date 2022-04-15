/*
 * @author Wang Xingyu
 * @date 2022/3/28
 */

#include "data.h"
#include "bucket.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

#define FILENUM 7          // 文件数量
#define WINDOWLEN 10000    // 窗口长度
#define INTERNAL 100000    // 打印间隔
#define STREAMLEN 1000000  // 文件长度
#define TIME1 10000        // 打印分桶情况的时间1
#define TIME2 500000       // 打印分桶情况的时间2
#define TIME3 1000000      // 打印分桶情况的时间3

int main()
{
    // 数据生成
    GenerateData();
    
    // 设置文件名
    const char *decimalfile = "integer_1000000.dat";
    const char *binaryfile[FILENUM];
    for (int i = 0; i < FILENUM; i++) {
        string name = "Binary_1000000_" + to_string(i) + ".dat";
        binaryfile[i] = name.c_str();
        cout<<binaryfile[i]<<endl;
    }

    // 打开十进制数据文件并读取数据
    int *decimaldata = (int*)malloc(STREAMLEN * sizeof(int));
    FILE *file = fopen(decimalfile, "r");
    // 若打开失败，处理异常
    if (file == NULL) {
        printf("open decimalfile error\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < STREAMLEN; i++) {
        fscanf(file, "%d", &decimaldata[i]);
    }
    fclose(file);

    // 打开比特流文件
    FILE *fd[FILENUM];
    for (int i = 0; i < FILENUM; i++) {
        string name = "Binary_1000000_" + to_string(i) + ".dat";
        fd[i] = fopen(name.c_str(), "r");
        // 若打开失败，处理异常
        if (fd[i] == NULL) {
            printf("open %d error\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // 设置比特流文件对应的链表
    vector<Linkedlist*> buckets;
    for (int i = 0; i < FILENUM; i++) {
        buckets.push_back(new Linkedlist);
    }

    // 数据读取与具体实现
    // 存储需要输出的时间戳、估计值、真实值
    vector<int> time_array;
    vector<int> esti_array;
    vector<int> true_array;
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
        // 超过窗口大小时，超出部分去掉
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

            int esti_value = 0;  // 估计值
            for (int i = 0; i < FILENUM; i++) {
                // double c_i = (double) num_1bit[i] / (double) curr_win;
                double c_i = (double) num_1bit[i];
                esti_value += c_i * pow(2, i);
            }

            time_array.push_back(time);
            esti_array.push_back(esti_value);
            true_array.push_back(true_value);
        }

        // 在要求时间戳时打印分桶情况
        if (time == TIME1 || time == TIME2 || time == TIME3) {
            cout << "Timestamp = " << time << endl;
            for (int i = 0; i < FILENUM; i++) {
                buckets[i]->show();
                cout << endl;
            }
            cout << "*****************************************" << endl;
        }

        // 读取处理下一个数据
        time++;
    }
    free(decimaldata);

    vector<pair<int,int>> rst4paint;

    // 输出时间戳、估计值、真实值
    for (unsigned i = 0; i <= time_array.size()-1; i++) {
        cout << "timestamp = " << time_array[i] << endl;
        cout << "\t" << "estimate: " << esti_array[i] << endl;
        cout << "\t" << "truth: " << true_array[i] << endl;
        rst4paint.push_back(make_pair(esti_array[i], true_array[i]));
    }

    // for (unsigned i = 0; i<10; i++){
    //     cout<<rst4paint[i].first<<" "<<rst4paint[i].second<<endl;
    // }


    // 关闭文件
    for (int i = 0; i < FILENUM; i++) {
        fclose(fd[i]);
    }

    // 结果输出到rst4paint.txt，然后用python画loss图，画图这步要在run.sh中进行
    ofstream outfile("rst4paint.txt");
    if (outfile.is_open()){
       for (unsigned i = 0; i<10; i++){
        // cout<<rst4paint[i].first<<" "<<rst4paint[i].second<<endl;
        outfile<<rst4paint[i].first<<"\t"<<rst4paint[i].second<<endl;
    }}
    outfile.close();
    return 0;
}
