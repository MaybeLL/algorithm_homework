g++ -c data.cpp -o data.o
g++ -c bucket.cpp -o bucket.o
g++ -c main.cpp -o main.o
g++ data.o bucket.o main.o -o test
./test
python paint.py