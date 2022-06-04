g++ -c GenerateJaccard.cpp -o GenerateJaccard.o
g++ -c minhash.cpp -o minhash.o
g++ -c main.cpp -o main.o
g++ data.o bucket.o main.o -o test
./test