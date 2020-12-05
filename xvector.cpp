#include "xvector.h"
Status Initxiang(int n,Lxiang &x)//n维向量初始化
{
    x.elem=(ElemType*)malloc(sizeof(ElemType)*n);
    if(!x.elem) return OVERFLOW;
    x.len=n;
    for(int i=0;i<x.len;i++)
    {
        cin>>x.elem[i];
    }
    return OK;
}

Status Destroyxiang(Lxiang &x)
{
    free(x.elem);
    x.len=0;
    return OK;
}

Lxiang Addxiang(Lxiang x1,Lxiang x2)//n维向量加法
{
    Lxiang x3;
    x3.elem=(ElemType*)malloc(sizeof(ElemType)*x1.len);
    //if(!x3.elem) return OVERFLOW;
    x3.len=x1.len;
    for(int i=0;i<x3.len;i++)
    {
        x3.elem[i]=x1.elem[i]+x2.elem[i];
    }
    return x3;
}

Lxiang Minusxiang(Lxiang x1,Lxiang x2)//n维向量减法
{
    Lxiang x3;
    x3.elem=(ElemType*)malloc(sizeof(ElemType)*x1.len);
    //if(!x3.elem) return OVERFLOW;
    x3.len=x1.len;
    for(int i=0;i<x3.len;i++)
    {
        x3.elem[i]=x1.elem[i]-x2.elem[i];
    }
    return x3;
}

float Cosxiang(Lxiang x1,Lxiang x2)//夹角余弦值
{//cos<x,y>=(x*y)/ |x||y|
    float mul=0,x1m=0,x2m=0;
    for(int i=0;i<x1.len;i++)
    {
        mul=mul+x1.elem[i]*x2.elem[i];//x*y
        x1m=x1m+x1.elem[i]*x1.elem[i];
        x2m=x2m+x2.elem[i]*x2.elem[i];
    }
    x1m=sqrt(x1m);// |x|
    x2m=sqrt(x2m);// |y|
    return mul*1.0/(x1m*x2m);
}

void printx(Lxiang x)//打印向量
{
    for(int i=0;i<x.len;i++)
    {
        cout<<x.elem[i]<<" ";
    }
    cout<<endl<<endl;
}
