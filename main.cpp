#include <iostream>
#include "bucket.h"
#include <array>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main() {
//    int a = gen_data();
    //7个比特流对应的桶
    vector<Linkedlist*> buckets;
    for(int i=0;i<7;i++){
        buckets.push_back(new Linkedlist());
    }
    //检查一下
    buckets[0]->show();
    buckets[1]->show();
//    Linkedlist* l0 = new Linkedlist();
//    Linkedlist* l1 = new Linkedlist();
//    Linkedlist* l2 = new Linkedlist();
//    Linkedlist* l3 = new Linkedlist();
//    Linkedlist* l4 = new Linkedlist();
//    Linkedlist* l5 = new Linkedlist();
//    Linkedlist* l6 = new Linkedlist();
//    l0->show();
//    l3->show();
    array<int,22> mydata = {0,1, 0, 1, 1, 0,0,0,1,0,0,1,0,0,1,1,1,0,1,1,0,1};
    int datasize = mydata.size();

//    TODO 读数据文件到下面的数组
//    vector<vector<int>> binaryflow(7,vector<int> (1000000));
//    for(int i=0;i<7;i++){
//        for(int j=0;j<1000000;j++){
////            binaryflow[i][j] =
//        }
//    }
//    vector<int> interflow;



    int window = 10000;
    //打印估计值和真实的值的间隔
    int eval_interval = 100000;
    //真实值
    int true_value =0;
    //什么时候显示桶的情况
    int show_bucket_time1 = 10000;
    int show_bucket_time2 = 500000;
    int show_bucket_time3 = 1000000;
    int current_time = 1;
    //移动指针，判断移除最旧桶（头插法建表的，链表的尾节点
    while(current_time<=datasize){
        //对于7个比特流对应的桶, 都去判断是否有落后的桶
        for (int i =0;i<7;i++){
            if ((buckets[i]->tail!= nullptr) && (buckets[i]->tail->timestamp<=current_time-window)){
                //删除尾节点/落后的桶
                buckets[i]->delete_tail();
            }
        }

        //1到来：
        //TODO 需根据读取数据方式修改
        if (mydata[current_time-1]==1){
            //建桶
            buckets[i]->head_insert(current_time,1);
            //查看后两个桶的size是否等于当前桶size
            Node* p = buckets[i]->head;
            while(p->next!= nullptr&&p->next->next!= nullptr&&p->size==p->next->size&&p->next->size==p->next->next->size){
                //指针后移
                p=p->next;
                //合并桶
                buckets[i]->merge(p);
            }


        }
        //------桶已更新完---

        //计算真实值:  根据整数流计算窗口内的数值和
        //  TODO 需根据读取数据方式修改  （这里是读数组所以计算简单，如果是数据流可能要缓存之前的数据）
        true_value += interflow[current_time-1];    //进入窗口
        if (current_time-1-window>=0){
            true_value-= interflow[current_time-1-window];  //移出窗口
        }

        //TODO 需根据读取数据方式修改
        if (current_time%eval_interval==0){
            //评估函数：每个二进制流的1在窗口中的占比,最后计算估计值。
            //确定当前窗口长度
            int current_window = window;
            if (current_time-window<0){
                current_window = current_time;
            }
            //计算7个二进制流的估计值
            vector<int> num_1bit;   //记录各比特流的当前1bit的估计值
            for(int i =0;i<7;i++){
                int tmp = buckets[i]->eval();
                num_1bit.push_back(tmp);
            }
            // 计算各位的1bit概率,再乘各位权重（2^i） == 估计值
            int estimate = 0;
            for (int i=0;i<7;i++){
                double c_i = (double) num_1bit[i]/(double) current_window;
                estimate+= c_i*pow(2,i);
            }
            cout<<"timestamp="<<current_time<<endl;
            cout<<"        "<<"estimate: "<<estimate<<endl;
            cout<<"timestamp="<<current_time<<endl;
            cout<<"        "<<"truth: "<<true_value<<endl;

//            //打印当前所有桶
//            l->show();
//            //验证:打印当前窗口
//            cout<<"current window: "<<"[";
//
//            for (int i = current_time-window;i<current_time;i++){
//                if(i>=0){
//                    cout<<mydata[i]<<",";
//                }
//            }
//            cout<<"]"<<endl;
//            cout<<"eval value:"<<l->eval()<<endl;
//            cout<<"true value:"<<true_value<<endl;
//            cout<<"-----------------------"<<endl;
        }
        //打印桶
        if (current_time==show_bucket_time1){
            cout<<"Timestamp=10000"<<endl;
            for(int i=0;i<7;i++){
                buckets[i]->show();
            }
        }
        if (current_time==show_bucket_time2){
            cout<<"Timestamp=500000"<<endl;
            for(int i=0;i<7;i++){
                buckets[i]->show();
            }
        }
        if (current_time==show_bucket_time3){
            cout<<"Timestamp=1000000"<<endl;
            for(int i=0;i<7;i++){
                buckets[i]->show();
            }
        }
        //接收下一bit数据
        current_time++;
    }

    return 0;
}
