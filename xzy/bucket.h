//
// Created by 赖金荣 on 2022/3/27.
//

#ifndef ALGORITHM_HOMEWORK_BUCKET_H
#define ALGORITHM_HOMEWORK_BUCKET_H

//声明节点
class Node{
public:
    int timestamp;
    int size;
    Node* next;

    Node(int t,int size);

    ~Node();
};

//声明链表
class Linkedlist{
public:
    int len;
    Node* head;
    Node* tail;

    Linkedlist();
    void show();
    void head_insert(int times,int s);
    void delete_tail();
    void merge(Node* p);
    int eval();
};

#endif //ALGORITHM_HOMEWORK_BUCKET_H
