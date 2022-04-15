### 请直接运行以下指令:
```
bash run.sh
```
其中run.sh中包含以下指令:

rm *.dat    //删除之前生成的数据,便于重新生成数据

make clean  //删除所有.o文件以重新编译

g++ -c data.cpp -o data.o   //编译data.cpp

g++ -c bucket.cpp -o bucket.o   //编译bucket.cpp

g++ -c main.cpp -o main.o   //编译main.cpp

g++ data.o bucket.o main.o -o test  //生成可执行文件test

./test  //执行test

python paint.py //画"误差图"
