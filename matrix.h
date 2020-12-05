#ifndef MATRIX_H
#define MATRIX_H
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
#define Maxsize 50
#define MaxR 7
typedef double ElemType;
typedef int Status;
struct Triple{
  int i,j;
  ElemType e;
};
struct Matrix{
    int mu,nu,tu;
    Triple data[Maxsize];
    int rpos[MaxR];
};

void InitMatrix(Matrix &mat);
void PrintMatrix(Matrix mat);
void DestroyMatrix(Matrix &mat);
Status AddMatrix(Matrix mat1,Matrix mat2,Matrix &mat);
Status SubstractMatrix(Matrix mat1,Matrix mat2,Matrix &mat);
Status MultiplyMatrix(Matrix mat1,Matrix mat2,Matrix &mat);
void TransMatrix(Matrix mat1,Matrix &mat);


#endif // MATRIX_H
