#ifndef XVECTOR_H
#define XVECTOR_H

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<cmath>
using namespace std;
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define LIST_INIT_SIZE 10
#define LISTINCREMENT 2
#define more 1
#define equal 0
#define less -1
typedef double ElemType;
typedef char Operator;
typedef int Status;
typedef float PElemType;

struct Lxiang{//向量
    ElemType* elem;
    int len;
};

Status Initxiang(int n,Lxiang &x);
Status Destroyxiang(Lxiang &x);
Lxiang Addxiang(Lxiang x1,Lxiang x2);
Lxiang Minusxiang(Lxiang x1,Lxiang x2);
float Cosxiang(Lxiang x1,Lxiang x2);
void printx(Lxiang x);

#endif // XVECTOR_H
