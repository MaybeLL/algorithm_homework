手动编译与运行：

g++ -c data.cpp

g++ -c bucket.cpp

g++ -c main.cpp

g++ data.o bucket.o main.o -o test

./test

修改文件时，只需要重新编译修改的文件，然后链接即可
