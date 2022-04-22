#include <iostream>
#include <fstream>
using namespace std;

// 1.桶的定义
typedef struct bucket{
    int timestamp;
    int size;
    struct bucket *next;
}bucket,*pbkt;

// 2.桶的操作

// 3.获取数据
void getData(N, low, high){
        
}

// 4.judge()
bool judge(){}


// 5.管理桶（丢弃、合并）
int bucketManage(int i,int time, pbkt *p){
    if(num==0){
        curWindow++;
        return;
    }
    if(num==1 && curWindow<window){
        new a bucket,store data;
        if(judge())
            merge();
      
    }else{
        p=p->next;
    }
    if(!time%100000)
        getResult();
}

// 5.获取结果
int getResult(){

}

// 6.打印桶
void printBucket(){

}

// 7.绘图分析
int N=1000000, low=1, high=127;
int window=100000, curWindow=0;
int results[10][2] = 0; // 存放十次输出的两种结果

int main() {
  
    getData(N, low, high);  // 生成数据
    
    for(int time=0; time<1000000;time++){
        for(int i=0;i<7;i++){
            bucketManage(i,time,&s[i]); // 读取数据，更新桶(丢弃、合并),s[i]：i桶的头指针
                     
        }
      
        if(time==10000 || time==500000 || time==1000000)
            printBucket(time,&s);
            
    }
  
    plotResult(results);
    

    return 0;
}
