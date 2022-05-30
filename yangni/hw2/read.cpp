#include "read.h"
#include <fstream>
# include<iostream>
using namespace std;

// 文件在函数外部打开,每次返回32bit
void read(FILE *fp1, FILE *fp2,unsigned int &num1,unsigned int &num2) {

    if (fp1 == NULL || fp2 == NULL) {
        cout<<"Cannot open the file!"<<endl;
        return;
    }

    fread(&num1, 4, 1, fp1);
    fread(&num2, 4, 1, fp2);
}
