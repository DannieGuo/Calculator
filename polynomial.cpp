#include "polynomial.h"

//链表求一元多项式
Status CreateLPolyn(PList &p,int n)//带头结点的 //有n个非0项
{
    p=(PList)malloc(sizeof(PolynNode));
    if(!p) return OVERFLOW;
    p->coef=0;
    p->expn=0;
    p->next=NULL;
    for(int i=1;i<=n;i++)
    {
        PolynNode* temp;
        temp=(PolynNode*)malloc(sizeof(PolynNode));
        cin>>temp->coef>>temp->expn;
        temp->next=p->next;
        p->next=temp;
    }
    LinePolynNode(p);//按指数从小到大排序

    PolynNode* temp;
    temp=p;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    p->expn=temp->expn;//在头结点记录多项式里最高项指数的值 //方便指数计算

    return OK;
}
Status DestroyPolynNode(PList &p)
{
    PList temp;
    while(p!=NULL)
    {
        temp=p->next;
        p->next=temp->next;
        free(temp);
    }
    return OK;
}
Status PrintPolynNode(PList p)
{
    PolynNode* temp;
    temp=p;
    while(temp->next!=NULL)
    {
        if(temp!=p)
        {
            if(temp->next->coef>0)
            cout<<'+'<<temp->next->coef<<"x^"<<temp->next->expn;
            else
            cout<<temp->next->coef<<"x^"<<temp->next->expn;
        }
        else
        {
            cout<<temp->next->coef<<"x^"<<temp->next->expn;
        }
        temp=temp->next;
    }
    cout<<endl<<endl;
    return OK;
}
PList AddPolynNode(PList p1,PList p2)
{
    PList p3;
    p3=(PList)malloc(sizeof(PolynNode));
    //if(!p3) return OVERFLOW;
    p3->coef=0;
    p3->expn=0;
    p3->next=NULL;
    PList t1,t2,now;
    t1=p1->next;
    t2=p2->next;
    now=p3;
    while(t1!=NULL&&t2!=NULL)
    {//都是从小到大排序的,所以分别遍历
        //对应指数项相等的直接相加,不等的相当于把指数小的那项加0
        if(t1->expn < t2->expn)
        {
            PolynNode* temp;
            temp=(PolynNode*)malloc(sizeof(PolynNode));
            temp->coef=t1->coef;
            temp->expn=t1->expn;
            temp->next=NULL;
            now->next=temp;
            now=now->next;
            t1=t1->next;
        }
        else
        if(t1->expn > t2->expn)
        {
            PolynNode* temp;
            temp=(PolynNode*)malloc(sizeof(PolynNode));
            temp->coef=t2->coef;
            temp->expn=t2->expn;
            temp->next=NULL;
            now->next=temp;
            now=now->next;
            t2=t2->next;
        }
        else
        if(t1->expn == t2->expn)//指数相等时可以相加
        {
            float a=t1->coef+t2->coef;
            if(a!=0)//系数之和不为0时可以存入
            {
                PolynNode* temp;
                temp=(PolynNode*)malloc(sizeof(PolynNode));
                temp->coef=a;
                temp->expn=t1->expn;
                temp->next=NULL;
                now->next=temp;
                now=now->next;
            }
            t1=t1->next;
            t2=t2->next;
        }
    }
    if(t1==NULL)//如果有一个多项式已经全加进去了
    {
        while(t2!=NULL)//就直接把另一个多项式剩下的项加进去
        {
            PolynNode* temp;
            temp=(PolynNode*)malloc(sizeof(PolynNode));
            temp->coef=t2->coef;
            temp->expn=t2->expn;
            temp->next=NULL;
            now->next=temp;
            now=now->next;
            t2=t2->next;
        }
        now->next=NULL;
    }
    if(t2==NULL)
    {
        while(t1!=NULL)
        {
            PolynNode* temp;
            temp=(PolynNode*)malloc(sizeof(PolynNode));
            temp->coef=t1->coef;
            temp->expn=t1->expn;
            temp->next=NULL;
            now->next=temp;
            now=now->next;
            t1=t1->next;
        }
    }
    return p3;
}
PList SubstractPolynNode(PList p1,PList p2)
{//加法的算法同理
    PList p3;
    p3=(PList)malloc(sizeof(PolynNode));
    //if(!p3) return OVERFLOW;
    p3->coef=0;
    p3->expn=0;
    p3->next=NULL;
    PList t1,t2,now;
    t1=p1->next;
    t2=p2->next;
    now=p3;
    while(t1!=NULL&&t2!=NULL)
    {
        if(t1->expn < t2->expn)
        {
            PolynNode* temp;
            temp=(PolynNode*)malloc(sizeof(PolynNode));
            temp->coef=t1->coef;
            temp->expn=t1->expn;
            temp->next=NULL;
            now->next=temp;
            now=now->next;
            t1=t1->next;
        }
        else
        if(t1->expn > t2->expn)
        {
            PolynNode* temp;
            temp=(PolynNode*)malloc(sizeof(PolynNode));
            temp->coef=-t2->coef;
            temp->expn=t2->expn;
            temp->next=NULL;
            now->next=temp;
            now=now->next;
            t2=t2->next;
        }
        else
        if(t1->expn == t2->expn)
        {
            float a=t1->coef-t2->coef;
            if(a!=0)
            {
                PolynNode* temp;
                temp=(PolynNode*)malloc(sizeof(PolynNode));
                temp->coef=a;
                temp->expn=t1->expn;
                temp->next=NULL;
                now->next=temp;
                now=now->next;
            }
            t1=t1->next;
            t2=t2->next;
        }
    }
    if(t1==NULL)
    {
        while(t2!=NULL)
        {
            PolynNode* temp;
            temp=(PolynNode*)malloc(sizeof(PolynNode));
            temp->coef=-t2->coef;
            temp->expn=t2->expn;
            temp->next=NULL;
            now->next=temp;
            now=now->next;
            t2=t2->next;
        }
        now->next=NULL;
    }
    if(t2==NULL)
    {
        while(t1!=NULL)
        {
            PolynNode* temp;
            temp=(PolynNode*)malloc(sizeof(PolynNode));
            temp->coef=t1->coef;
            temp->expn=t1->expn;
            temp->next=NULL;
            now->next=temp;
            now=now->next;
            t1=t1->next;
        }
    }
    return p3;
}
PList MultiplyPolynNode(PList p1,PList p2)
{
    PList p3;
    p3=(PList)malloc(sizeof(PolynNode));
    p3->expn=0;
    p3->coef=0;
    p3->next=NULL;

    PolynNode* t1;
    PolynNode* t2;
    t1=p1->next;
    t2=p2->next;

    while(t2!=NULL)
    {//t2中的每一项
        while(t1!=NULL)
        {//相当于拿出t2中的一项与t1中的每一项相乘,然后把每一项相乘的结果相加
            PolynNode *temp,*tp;
            temp=(PolynNode*)malloc(sizeof(PolynNode));
            tp=(PolynNode*)malloc(sizeof(PolynNode));
            temp->expn=t1->expn+t2->expn;
            temp->coef=t1->coef*t2->coef;
            temp->next=NULL;
            tp->next=temp;//tp相当于头结点
            p3=AddPolynNode(p3,tp);//add里是要两条链表里的多项式相加,所以用tp和temp造出一条链表
            t1=t1->next;
        }
        t2=t2->next;
        t1=p1;
    }
    return p3;
}
PList DeriPolynNode(PList p)//求导
{
    PList t,p1,now;
    t=p->next;
    p1=(PList)malloc(sizeof(PolynNode));//造一条新的链表来存导数
    p1->expn=0;
    p1->coef=0;
    p1->next=NULL;
    now=p1;
    while(t!=NULL)
    {
        if(t->expn!=0)
        {
            PolynNode* temp;
            temp=(PolynNode*)malloc(sizeof(PolynNode));
            temp->coef=t->coef*t->expn;
            temp->expn=t->expn-1;
            temp->next=NULL;
            now->next=temp;
            now= now->next;
        }
        t=t->next;
    }
    return p1;
}
void LinePolynNode(PList &p)//按指数从小到大排序
{
    PolynNode* i=p->next;
    PolynNode* j;
    int e;
    float c;
    //冒泡排序
    while(i->next!=NULL)
    {
        j=i->next;
        while(j!=NULL)
        {
            if(j->expn<i->expn)//直接交换结点上的值
            {
                e=j->expn;
                j->expn=i->expn;
                i->expn=e;
                c=j->coef;
                j->coef=i->coef;
                i->coef=c;
            }
            j=j->next;
        }
        i=i->next;
    }
}


//用顺序表求一元多项式
Status CreatePolyn(Polyn &polyn,int n)//n为最大幂次
{//所以实际就有n+1项 //数组下标最大为n
    polyn.coef=(PElemType*)malloc(sizeof(PElemType)*(n+5));
    if(!polyn.coef) return OVERFLOW;
    polyn.length=n+1;
    for(int i=0;i<=n;i++)
    {
        cin>>polyn.coef[i];
    }
    RealLength(polyn);
    return OK;
}
Status DestroyPolyn(Polyn &polyn)
{
    polyn.length=0;
    polyn.real_start=0;
    polyn.real_end=0;
    free(polyn.coef);
    return OK;
}
void PrintPolyn(Polyn polyn)
{
    //cout<<polyn.length<<" "<<polyn.real_start<<" "<<polyn.real_end<<endl;
    for(int i=polyn.real_start-1;i<polyn.real_end;i++)//从实际有值的项开始
    {
        if(polyn.coef[i]!=0)//如果这项上有值
        {
            if(i!=polyn.real_start-1)
            {//非第一项
                if(polyn.coef[i]>0)
                    cout<<'+'<<polyn.coef[i]<<"x^"<<i;
                else
                    cout<<polyn.coef[i]<<"x^"<<i;
            }
            else
            if(i!=0)
            {
                cout<<polyn.coef[i]<<"x^"<<i;
            }
            else
            {//常数项
                cout<<polyn.coef[i];
            }
        }
    }
    cout<<endl<<endl;
}
Polyn AddPolyn(Polyn polyn1,Polyn polyn2)
{
    Polyn polyn3;
    polyn3.length=polyn1.length>polyn2.length? polyn1.length:polyn2.length;//对加法的结果预设长度
    polyn3.coef=(PElemType*)malloc(sizeof(PElemType)*polyn3.length);
    //if(!polyn3.coef) return OVERFLOW;
    for(int i=0;i<polyn3.length;i++)
    {
        if(i<polyn2.length&&i<polyn1.length)
        {//直接把p1p2上对应指数位上的系数相加再存入
            polyn3.coef[i]=polyn1.coef[i]+polyn2.coef[i];
        }
        if(i>=polyn1.length)//有一个多项式已经加完了
        {//把另一个多项式剩下的都加进去
            polyn3.coef[i]=polyn2.coef[i];
        }
        if(i>=polyn2.length)
        {
            polyn3.coef[i]=polyn1.coef[i];
        }
    }
    RealLength(polyn3);
    return polyn3;
}
Polyn SubstractPolyn(Polyn polyn1,Polyn polyn2)
{//同理加法
    Polyn polyn3;
    polyn3.length=polyn1.length>polyn2.length? polyn1.length:polyn2.length;
    polyn3.coef=(PElemType*)malloc(sizeof(PElemType)*polyn3.length);
    //if(!polyn3.coef) return OVERFLOW;
    for(int i=0;i<polyn3.length;i++)
    {
        if(i<polyn2.length&&i<polyn1.length)
        {
            polyn3.coef[i]=polyn1.coef[i]-polyn2.coef[i];
        }
        if(i>=polyn1.length)
        {
            polyn3.coef[i]=-polyn2.coef[i];
        }
        if(i>=polyn2.length)
        {
            polyn3.coef[i]=polyn1.coef[i];
        }
    }
    RealLength(polyn3);
    return polyn3;
}
Status DeriPolyn(Polyn polyn1,Polyn &polyn2)
{
    polyn2.length=polyn1.length;
    polyn2.coef=(PElemType*)malloc(sizeof(PElemType)*polyn2.length);
    if(!polyn2.coef) return OVERFLOW;
    for(int i=0;i<polyn2.length;i++)
    {//先把每一个系数初始化为0,以防p1在该指数位上没有值
        polyn2.coef[i]=0;
    }
    for(int i=polyn1.real_start-1;i<polyn1.real_end;i++)
    {
        if(i>=1)
        polyn2.coef[i-1]=i*polyn1.coef[i];
        //求导完指数会-1
    }
    RealLength(polyn2);
    return OK;
}
Polyn MultiplyPolyn(Polyn polyn1,Polyn polyn2)
{//一个一个乘进去
    Polyn polyn3;
    polyn3.length=polyn1.length+polyn2.length;
    polyn3.coef=(PElemType*)malloc(sizeof(PElemType)*polyn3.length);
    for(int i=0;i<polyn3.length;i++)
    {
        polyn3.coef[i]=0;
    }
    for(int i=polyn1.real_start-1;i<polyn1.real_end;i++)
     for(int j=polyn2.real_start-1;j<polyn2.real_end;j++)
     {//直接把p1p2里每一项相乘
        polyn3.coef[i+j]=polyn3.coef[i+j]+polyn1.coef[i]*polyn2.coef[j];
     }
     RealLength(polyn3);
     return polyn3;
}
Status RealLength(Polyn &polyn)//计算多项式实际开始位置和结束位置
{
    int k=0;
    for(int i=polyn.length-1;i>=0;i--)
    {
        if(polyn.coef[i]==0) k++;
        else break;
    }
    polyn.real_end=polyn.length-k;
    k=0;
    for(int i=0;i<polyn.length;i++)
    {
        if(polyn.coef[i]==0) k++;
        else break;
    }
    polyn.real_start=k+1;
    return OK;
}
