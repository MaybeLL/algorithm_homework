// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <ctime>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

void Binary(int num, int arr[7]) {
	int k;
	for (int i = 0; i < 7; i++) {
		k = num % 2;
		arr[6 - i] = k;
		num /= 2;
	}
}

int main()
{
	ofstream out;
	ofstream out0;
	ofstream out1;
	ofstream out2;
	ofstream out3;
	ofstream out4;
	ofstream out5;
	ofstream out6;
	ifstream in;
	int integer;
	int binary[7];

	out.open("integer_1000000.dat", ios::app);
	out0.open("Binary_1000000_0.dat", ios::app);
	out1.open("Binary_1000000_1.dat", ios::app);
	out2.open("Binary_1000000_2.dat", ios::app);
	out3.open("Binary_1000000_3.dat", ios::app);
	out4.open("Binary_1000000_4.dat", ios::app);
	out5.open("Binary_1000000_5.dat", ios::app);
	out6.open("Binary_1000000_6.dat", ios::app);
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	mt19937 rand_num(seed);
	uniform_int_distribution<long long> dist(0, 127);
	for (int i = 0; i < 1000000; i++) {
		out << dist(rand_num) << "";
		out << "\n";
	}
	out.close();
	in.open("integer_1000000.dat", ios::in);
	if (!in.is_open())
		cout << "Open file failure" << endl;
	for (int j = 0; j < 1000000; j++) {
		in >> std::ws >> integer;
		Binary(integer, binary);
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


	return 0;
}



