/*
 * @author yangni
 * @date 2022/5/31
 */

# include<iostream>
# include <fstream>
# include<string>

# include "CRC32.h"
# include "part2.h"
using namespace std;


void Shingle(const char *filename){

    ifstream infile(filename);
    ofstream outfile("ShinglesSet.txt",std::ios::app);
    string x;

    while(getline(infile,x)){

        for(int i=0; i<SHINGLES_NUM; i++){
            // 提取8位字符，利用CRC32算法转化成无符号整数
            unsigned int t = CRC32(&x[i],8);
            // 写入文件
            outfile <<t<<" ";

        }
        outfile <<"\n";

    }
    infile.close();
    outfile.close();

}

// int main(){

//     Shingle("documents.txt");
//     return 0;
// }
