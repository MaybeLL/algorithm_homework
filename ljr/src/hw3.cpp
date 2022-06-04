#include <iostream>
#include <cstdio>
#include <random>
#include <fstream>
// #include <string>

using namespace std;

// 获得第一个随机文档A1
string get_docu(){
    static default_random_engine e(time(0));
    static uniform_int_distribution<int> uni(0, 51);
    char list[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string A1;
    for(int i =0;i<500;i++){
        int t = uni(e);
        char temp = list[t];
        A1+=temp;
    }
    return A1;
}

// 接收一个文档（string），返回随机替换字符后的新的文档（string）
string change_docu(string s){
    static default_random_engine r(time(0));
    static uniform_int_distribution<int> unifor(0, 499);
    static uniform_int_distribution<int> c(0, 51);
    string all = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //随机挑选一个字符
    int index = unifor(r);
    //替换成一个随机字符
    s[index] = all[c(r)];
    return s;
}


int main(){

    ofstream outfile;
    outfile.open("documents.txt");
    string A1 = get_docu();
    outfile<<A1<<endl;
    for(int i=1;i<1000;i++){
        string new_s = change_docu(A1);
        outfile<<new_s<<endl;
        A1 = new_s;
    }
    outfile.close();

    return 0;
}