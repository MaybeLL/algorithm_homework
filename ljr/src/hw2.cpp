#include <iostream>
#include <cstdio>
#include <random>
// #include <string>

using namespace std;





//均匀分布
int get_uniform_32bit(){
    static default_random_engine e(time(0));
    static bernoulli_distribution b(0.5);
    int a=0;
    for(int i =0;i<32;i++){
        int temp = b(e);
        a = (a | temp<<i);

    }
    return a;
}

//按2-8分布
int get_uneven_32bit(){
    static default_random_engine e(time(0));
    static bernoulli_distribution b(0.2);
    int a=0;
    for(int i =0;i<32;i++){
        int temp = b(e);
        a = (a | temp<<i);

    }
    return a;
}

//生成数据文件。  
void gen_data(int num,bool uniform){
    FILE* fp;
    if(uniform){
        fp = fopen("/home/ljl/work/algorithm_homework/ljr/src/uniform_vector1","wb+");
        for(int i=0;i<num;i++){
            int temp = get_uniform_32bit();
            cout<<temp<<endl;
            fwrite(&temp,1,4,fp);
        }
        fclose(fp);
        fp = fopen("/home/ljl/work/algorithm_homework/ljr/src/uniform_vector2","wb+");
        for(int i=0;i<num;i++){
            int temp = get_uniform_32bit();
            cout<<temp<<endl;
            fwrite(&temp,1,4,fp);
        }
        fclose(fp);
    }
    else{
        fp = fopen("/home/ljl/work/algorithm_homework/ljr/src/non_uniform_vector1","wb+");
        for(int i=0;i<num;i++){
            int temp = get_uneven_32bit();
            cout<<temp<<endl;
            fwrite(&temp,1,4,fp);
        }
        fclose(fp);
        fp = fopen("/home/ljl/work/algorithm_homework/ljr/src/non_uniform_vector2","wb+");
        for(int i=0;i<num;i++){
            int temp = get_uneven_32bit();
            cout<<temp<<endl;
            fwrite(&temp,1,4,fp);
        }
        fclose(fp);
    }
    
    return ;
}


//计算两个int的hamming距离
// void hamming_jaccord(int s1,int s2,int* h, int* j){

//     int stream1 = s1;
//     int stream2 = s2;
//     // cout<<(a^b)<<endl;

//     //读状态: 与1与
//     for(int i=0;i<32;i++){
//         int b1 = (stream1>>i)&1;
//         int b2 = (stream2>>i)&1;
//         // cout<<b1<<","<<b2<<endl;
//         if(b1^b2==1){
//             (*h)++;
//         }
//         else{
//             (*j)++;
//         }
//     }

// }

int hamming(int s1,int s2){
    int res = 0;
    int stream1 = s1;
    int stream2 = s2;

    //读状态: 与1与
    for(int i=0;i<32;i++){
        int b1 = (stream1>>i)&1;
        int b2 = (stream2>>i)&1;
        res += (b1^b2);
    }
    return res;
}

int cal_hamming(int count,const char* filepath1,const char* filepath2){
    FILE* fp1;
    FILE* fp2;
    fp1 = fopen(filepath1,"rb");
    fp2 = fopen(filepath2,"rb");
    if(fp1==nullptr||fp2==nullptr){
        cout<<"读文件失败";
        return -1;
    }
    int c= count;
    int hamm = 0;
    while(!feof(fp1)&&!feof(fp2)){

        int a;
        int b;
        fread(&a,sizeof(a),1,fp1);
        fread(&b,sizeof(b),1,fp2);
        hamm += hamming(a,b);

        c--;
        if(c<=0){
            break;
        }

    }
    return hamm;
}


int main()
{
    //十亿个bit就是31250000个int型
    //生成数据
    // gen_data(31250000,false);


    //评估
    int h = cal_hamming(31250000,"/home/ljl/work/algorithm_homework/ljr/src/uniform_vector1","/home/ljl/work/algorithm_homework/ljr/src/uniform_vector2");
    double jaccord=0;
    jaccord = 1-(double)h/1000000000;
    cout<<"uniform distribution:"<<endl;
    cout<<"    "<<"hamming distance:"<<h<<endl;   
    cout<<"    "<<"jaccard similarity:"<<jaccord<<endl;

    h = cal_hamming(31250000,"/home/ljl/work/algorithm_homework/ljr/src/non_uniform_vector1","/home/ljl/work/algorithm_homework/ljr/src/non_uniform_vector2");
    jaccord=0;
    jaccord = 1-(double)h/1000000000;
    cout<<"non-uniform distribution:"<<endl;
    cout<<"    "<<"hamming distance:"<<h<<endl;   
    cout<<"    "<<"jaccard similarity:"<<jaccord<<endl;
    return 0;
}