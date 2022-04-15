#include "data.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

//定义整数转换二进制数的函数
void Binary(int num, int arr[7]) {
	int k;
	for (int i = 0; i < 7; i++) {
		k = num % 2;
		arr[6 - i] = k;//用一个大小为7个元素的数组分别保存二进制七位数字
		num /= 2;
	}
}

//整体产生整数数据文件以及二进制数据文件的函数
void GenerateData() {
	ofstream out;//整数文件
	//7个二进制文件
	ofstream out0;
	ofstream out1;
	ofstream out2;
	ofstream out3;
	ofstream out4;
	ofstream out5;
	ofstream out6;
	ifstream in;//用于读取整数文件
	int integer;//依次表示整数文件中的每一个数字
	int binary[7];//用于表示每个整数转换为二进制形式表示的每一位数字

	out.open("integer_1000000.dat", ios::app);
	out0.open("Binary_1000000_0.dat", ios::app);
	out1.open("Binary_1000000_1.dat", ios::app);
	out2.open("Binary_1000000_2.dat", ios::app);
	out3.open("Binary_1000000_3.dat", ios::app);
	out4.open("Binary_1000000_4.dat", ios::app);
	out5.open("Binary_1000000_5.dat", ios::app);
	out6.open("Binary_1000000_6.dat", ios::app);
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	mt19937 rand_num(seed);//采用mt19937产生快速高质量的随机数
	uniform_int_distribution<long long> dist(0, 127);
	//均匀产生范围为0-127的随机数并写入相应文件中
	for (int i = 0; i < 1000000; i++) {
		out << dist(rand_num) << "";
		out << "\n";
	}
	out.close();
	in.open("integer_1000000.dat", ios::in);
	if (!in.is_open())
		cout << "Open file failure" << endl;
	for (int j = 0; j < 1000000; j++) {
		in >> std::ws >> integer;//依次读取文件中的每一个整数传入integer
		Binary(integer, binary);//将每一个整数转换为二进制数，并依次存入数组写入相应的文件中
		out0 << binary[0] << "\n";
		out1 << binary[1] << "\n";
		out2 << binary[2] << "\n";
		out3 << binary[3] << "\n";
		out4 << binary[4] << "\n";
		out5 << binary[5] << "\n";
		out6 << binary[6] << "\n";
	}
	out0.close();
	out1.close();
	out2.close();
	out3.close();
	out4.close();
	out5.close();
	out6.close();
}
