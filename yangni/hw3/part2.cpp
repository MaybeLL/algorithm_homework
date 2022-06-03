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
        
        for(int i=0; i<493; i++){
            // 提取8位字符，构造shingle
            string temp = x.substr(i,8);
     
            // 调用CRC32算法，把字符串转化为32位无符号整数
            unsigned int t = CRC32(&temp, 8);

            // 写入
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
