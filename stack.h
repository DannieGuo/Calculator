#ifndef STACK_H
#define STACK_H
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<cmath>
#include<cstring>
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

struct Stackrand{
    ElemType* base;
    ElemType* top;
    int stacksize;
};//操作数栈
struct Stackrator{
    Operator* base;
    Operator* top;
    int stacksize;
};//操作符栈

struct Function{
  string name;
  char func[200];
};

Status InitStackrand(Stackrand &s);
Status InitStackrator(Stackrator &s);

template <class T1,class T2>
Status PopStack(T1 &s,T2 &e);

ElemType GetToprand(Stackrand s);//得到顶端操作数
Operator GetToprator(Stackrator s);//得到顶端操作符

template <class T1,class T2>
Status PushStack(T1 &s,T2 e);

Status Precede(char a,char b);//a是在栈中的 //判断优先级
ElemType Oper(ElemType a1,ElemType a2,Operator a4);//操作计算
ElemType Calculate(Stackrand &operand,Stackrator &rator,char bds[100]);
ElemType CalculateX(Stackrand &operand,Stackrator &rator,ElemType x,char bds[100]);

void CompareFunc(string &s,Function fucntion[20],int n,int xlen);
#endif // STACK_H
