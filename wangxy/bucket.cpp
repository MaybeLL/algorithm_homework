//
// Created by 赖金荣 on 2022/3/27.
//

#include "bucket.h"
#include <iostream>
using namespace std;

//构造函数
Node::Node(int t, int size) {
    this->timestamp = t;
    this->size = size;
    this->next = nullptr;
}


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

void Linkedlist::head_insert(int times, int s) {
    if (this->len==0){
        Node* t = new Node(times,s);
        this->head = t;
        this->tail = t;
        this->len++;
    }
    else{
        Node* t = new Node(times,s);
        t->next = head;
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
    //
    Node* p = head;
    while(p->next!=tail){
        p = p->next;
    }
    p->next = nullptr;
    this->tail = p;
    this->len--;
}

void Linkedlist::merge(Node *p) {
    //指针是否合法
    if (p!= nullptr&&p->next!= nullptr){
        p->size = p->size + p->next->size;
        //删除p.next节点
        if(p->next->next!= nullptr){
            p->next = p->next->next;
            this->len--;
        }else{
            this->tail  = p;
            p->next = nullptr;
            this->len--;
        }
    }
    else{
        cout<<"合并位置为空，无法合并"<<endl;
    }
}

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
    res+= 0.5*p->size;
    return res;
}
