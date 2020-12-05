#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
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

struct Polyn{
    PElemType* coef;
    int length;//数组下标最大为length-1
    int real_start;//其中可能有的项系数为0,这里记的是开始时第一个不是0的系数的位置,即为实际开始位置
    int real_end;//从后数第一个不是0的系数的位置,实际结束位置
};//都是表示第几项,下标要-1

typedef struct PolynNode{
    int expn;//指数
    float coef;//系数
    PolynNode* next;
}PolynNode,*PList;

Status CreateLPolyn(PList &p,int n);
Status DestroyPolynNode(PList &p);
Status PrintPolynNode(PList p);
PList AddPolynNode(PList p1,PList p2);
PList SubstractPolynNode(PList p1,PList p2);
PList MultiplyPolynNode(PList p1,PList p2);
PList DeriPolynNode(PList p);
void LinePolynNode(PList &p);//排序

Status RealLength(Polyn &polyn);//计算多项式实际开始结束的位置
Status CreatePolyn(Polyn &polyn,int n);
Status DestroyPolyn(Polyn &polyn);
void PrintPolyn(Polyn polyn);
Polyn AddPolyn(Polyn polyn1,Polyn polyn2);
Polyn SubstractPolyn(Polyn polyn1,Polyn polyn2);
Status DeriPolyn(Polyn polyn1,Polyn &polyn2);
Polyn MultiplyPolyn(Polyn polyn1,Polyn polyn2);



#endif // POLYNOMIAL_H
