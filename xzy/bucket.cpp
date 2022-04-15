//
// Created by 赖金荣 on 2022/3/27.
//

#include "bucket.h"
#include <iostream>
using namespace std;

//构造函数
Node::Node(int timestamp, int size) {
    this->timestamp = timestamp;
    this->size = size;
    this->next = nullptr;
}

Node::~Node(){}


//定义构造函数
Linkedlist::Linkedlist() {
    this->len=0;
    this->head = nullptr;
    this->tail = nullptr;
}

void Linkedlist::show() {
    Node* p = this->head;
    while(p!= nullptr){
        cout<<"("<<p->timestamp<<","<<p->size<<")"<<"-->";
        if (p->next== nullptr){
            cout<<"null"<<endl;
        }
        p = p->next;
    }
}

// 头插法
void Linkedlist::head_insert(int timestamp, int size) {
    if (this->len==0){
        Node* t = new Node(timestamp, size);
        this->head = t;
        this->tail = t;
        this->len++;
    }
    else{
        Node* t = new Node(timestamp, size);
        t->next = this->head;
        this->head = t;
        this->len++;
    }
}

void Linkedlist::delete_tail() {
    //链表空
    if (this->len==0){
        return;
    }
    //只有一个节点
    if (this->len==1){
        this->len = 0;
        this->head = nullptr;
        this->tail = nullptr;
        return;
    }
    //找尾节点的前一个节点
    Node* p = this->head;
    while(p->next!=this->tail){
        p = p->next;
    }
    Node* tmp = this->tail;
    delete tmp;
    p->next = nullptr;
    this->tail = p;
    this->len--;
}
//合并p节点和p->next节点
void Linkedlist::merge(Node *p) {
    //指针是否合法
    if (p!= nullptr&&p->next!= nullptr){
        Node * tmp = p->next;
        p->size = p->size + tmp->size;
        //删除p.next节点
        if(tmp->next!= nullptr){
            p->next = p->next->next;
        }else{
            this->tail = p;
            p->next = nullptr;
        }
        delete tmp;
        this->len--;
    }
    else{
        cout<<"合并位置为空，无法合并"<<endl;
    }
}
//计算1bit个数
int Linkedlist::eval() {
    if (this->len==0){
        return 0;
    }
    int res=0;
    Node* p =head;
    while(p->next!= nullptr){
        res = res + p->size;
        p = p->next;
    }
    //尾节点/最后一个桶 如果有超出
    res += 0.5*p->size;
    return res;
}
