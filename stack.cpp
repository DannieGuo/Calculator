#include "stack.h"
Status InitStackrand(Stackrand &s)//初始化操作数
{
    s.base=(ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    if(!s.base) return OVERFLOW;
    s.top=s.base;
    s.stacksize=LIST_INIT_SIZE;
    return OK;
}
Status InitStackrator(Stackrator &s)//初始化操作符
{
    s.base=(Operator*)malloc(sizeof(Operator)*LIST_INIT_SIZE);
    if(!s.base) return OVERFLOW;
    s.top=s.base;
    s.stacksize=LIST_INIT_SIZE;
    return OK;
}

template <class T1,class T2>
Status PopStack(T1 &s,T2 &e)//弹出
{
    if(s.top==s.base) return ERROR;
    s.top=s.top-1;
    e=*s.top;
    return OK;
}

ElemType GetToprand(Stackrand s)//得到顶端操作数
{
    return *(s.top-1);
}

Operator GetToprator(Stackrator s)//得到顶端操作符
{
    return *(s.top-1);
}

template <class T1,class T2>
Status PushStack(T1 &s,T2 e)//压入
{
    if(s.top-s.base>=s.stacksize)
    {
        s.base=(T2*)realloc(s.base,sizeof(T2)*(s.stacksize+LISTINCREMENT));
        if(!s.base) return OVERFLOW;
        s.top=s.base+s.stacksize;//还是原来的top
        s.stacksize=s.stacksize+LISTINCREMENT;
    }
    *s.top=e;
    s.top++;
    return OK;
}

Status Precede(char a,char b)//a是在栈中的 //判断优先级
{//#35   (40  )41  *42  +43  -45  /47   ^94
    int a1,b1;
    if(a=='#') a1=-1;
    if(a==40) a1=4;//如果是左括号,一定压入,所以优先级设得高
    if(a==41) a1=0;//如果是右括号,得把括号间的都计算了且不进栈,所以优先级设得低
    if(a=='+'||a=='-') a1=1;
    if(a=='*'||a=='/') a1=2;
    if(a==94) a1=3;

    if(b=='#') b1=-1;
    if(b==40) b1=4;
    if(b==41) b1=0;
    if(b=='+'||b=='-') b1=1;
    if(b=='*'||b=='/') b1=2;
    if(b==94) b1=3;

    if(a1==b1&&a1==-1) return equal;//都是#
    if(a1==b1&&a1!=0) return more;//相等,先入栈的优先级高
    if(a1==4&&b1==0) return equal;//左右括号碰上
    if(a1>b1&&a1==4) return less; //左括号和运算符
    if(a1>b1) return more;
    if(a1<b1) return less;
}

ElemType Oper(ElemType a1,ElemType a2,Operator a4)//操作计算
{
    if(a4==42) return a1*a2;
    if(a4==43) return a1+a2;
    if(a4==45) return a1-a2;
    if(a4==47) return a1/a2;
    if(a4==94)
    {
        ElemType temp=1;
        if(a2==0) return temp;
        if(a2>0)
        {
            for(int i=1;i<=a2;i++)
                temp=temp*a1;
            return temp;
        }
        if(a2<0)
        {
            for(int i=1;i<=(-a2);i++)
                temp=temp*a1;
            return 1/temp;
        }
    }
}


//不含变量的计算//可以算带小数的//可以浮点数科学计数法//可以算负数
ElemType Calculate(Stackrand &operand,Stackrator &rator,char bds[100])
{
    InitStackrand(operand);
    InitStackrator(rator);
    PushStack(rator,'#');
    int a[10],b[10],k=0,j=0,d=0;
    int ife=0;//记录是否在存浮点数的科学计数法
    int i=0;
    //a记录整数位,b记录小数位,k判断整数记到第几位,j记录小数记到第几位,d用来判断现在是否在记录小数
    char c=bds[i];//表达式
    while(c!='#'||GetToprator(rator)!='#')
    {
        if(c>=48&&c<=57&&d==0)//字符是数字且在记录整数位
        {
            a[k]=c-48;
            k++;
            i++;
            c=bds[i];
        }
        else
        if(c>=48&&c<=57&&d==1)//在记录小数位
        {
            b[j]=c-48;
            j++;
            i++;
            c=bds[i];
        }
        else//如果读入的字符不是数字
        {//小数点//运算符
            //如果前面暂存着数字,就要压入
            if(k!=0&&c!=46&&d==0)//如果读入的字符不是小数点,且没有记录小数位
            {
                ElemType temp=0;
                for(int v=0;v<=k-1;v++)
                {//把记录的整数位还原成正确的数
                        temp=temp*10+a[v];
                }
                k=0;//初始化
                PushStack(operand,temp);//压入操作数栈
            }
            else
            if(k!=0&&c!=46&&d==1)//如果读入的字符不是小数点,且有记录小数位
            {
                double all=0;
                int temp=0;
                //整数位
                for(int v=0;v<=k-1;v++)
                {
                    temp=temp*10+a[v];
                }
                k=0;
                //小数位
                for(int v=j-1;v>=0;v--)
                {
                    all=all*0.1+b[v];
                }
                //还原实际的数
                all=all*0.1+temp;
                j=0;
                d=0;
                PushStack(operand,all);
            }
            else
            if(c==46)//如果读入的字符是小数点,则设置当前要开始记录小数位了
            {
                d=1;
                i++;
                c=bds[i];
            }
            else
            if(c=='e')//标记用了浮点数的科学计数法
            {
                 ife=1;
                 i++;
                 c=bds[i];
             }
            else//剩下的是读到操作符的
            {
                 if(ife==1)//如果记录了刚才有读一个浮点数的科学计数法
                 {//计算该数并压入
                     Operator a1;
                     ElemType a2,a3;
                     a1='^';
                     PopStack(operand,a2);
                     PopStack(operand,a3);
                     ElemType e=10;
                     ElemType all=a3*Oper(e,a2,a1);
                     PushStack(operand,all);
                     ife=0;
                 }
                char t=c;
                switch(Precede(GetToprator(rator),c))//比较操作符优先级
                {
                    case less:
                        PushStack(rator,c);
                        i++;
                        c=bds[i];
                        break;
                    case equal:
                        Operator tp;
                        PopStack(rator,tp);
                        i++;
                        c=bds[i];
                        break;
                    case more:
                        Operator a1;
                        ElemType a2,a3;
                        PopStack(rator,a1);
                        PopStack(operand,a2);
                        PopStack(operand,a3);
                        PushStack(operand,Oper(a3,a2,a1));//注意对应顺序
                        break;
                }//switch
                if(t=='('&&c=='-')//即判断接下来括号里的是否是负数//是的话压入一个0
                {
                    ElemType tpp=0;
                    PushStack(operand,tpp);
                }
            }
        }
    }//while
    if(k!=0)//如果只输入了一个数字的情况
    {
        if(d==1)
        {
            double all=0;
            int temp=0;
            //整数位
            for(int v=0;v<=k-1;v++)
            {
                temp=temp*10+a[v];
            }
            //小数位
            for(int v=j-1;v>=0;v--)
            {
                all=all*0.1+b[v];
            }
            //还原实际的数
            all=all*0.1+temp;
            PushStack(operand,all);
        }
        if(d==0)
        {
            ElemType temp=0;
            for(int v=0;v<=k-1;v++)
            {//把记录的整数位还原成正确的数
                    temp=temp*10+a[v];
            }
            PushStack(operand,temp);//压入操作数栈
        }
    }
    if(ife==1)//如果这个数字是科学计数法写的
    {
        Operator a1;
        ElemType a2,a3;
        a1='^';
        PopStack(operand,a2);
        PopStack(operand,a3);
        ElemType e=10;
        ElemType all=a3*Oper(e,a2,a1);
        PushStack(operand,all);
        ife=0;
    }
    return GetToprand(operand);
}


//含单变量的表达式求值
ElemType CalculateX(Stackrand &operand,Stackrator &rator , ElemType x , char bds[100])
{
    InitStackrand(operand);
    InitStackrator(rator);
    PushStack(rator,'#');
    //int a[10],k=0,i=0;
    int i=0;
    int ife=0;
    char c=bds[i];//表达式
    int a[10],b[10],k=0,j=0,d=0;
    while(c!='#'||GetToprator(rator)!='#')
    {
        if(c>=48&&c<=57&&d==0)//字符是数字且在记录整数位
        {
            a[k]=c-48;
            k++;
            i++;
            c=bds[i];
        }
        else
        if(c>=48&&c<=57&&d==1)//在记录小数位
        {
                b[j]=c-48;
                j++;
                i++;
                c=bds[i];
         }
        else//输入的不是数字
       {//先得把之前存的数字压入
                if(k!=0&&c!=46&&d==0)//如果读入的字符不是小数点,且没有记录小数位
                {
                    ElemType temp=0;
                    for(int i=0;i<=k-1;i++)
                    {//把记录的整数位还原成正确的数
                            temp=temp*10+a[i];
                    }
                    k=0;//初始化
                    PushStack(operand,temp);//压入操作数栈
                }
                else
                if(k!=0&&c!=46&&d==1)//如果读入的字符不是小数点,且有记录小数位
                {
                    double all=0;
                    int temp=0;
                    //整数位
                    for(int i=0;i<=k-1;i++)
                    {
                        temp=temp*10+a[i];
                    }
                    k=0;
                    //小数位
                    for(int i=j-1;i>=0;i--)
                    {
                        all=all*0.1+b[i];
                    }
                    //还原实际的数
                    all=all*0.1+temp;
                    j=0;
                    d=0;
                    PushStack(operand,all);
                }
                else
                if(c==46)//如果读入的字符是小数点,则设置当前要开始记录小数位了
                {
                    d=1;
                    i++;
                    c=bds[i];
                }
                else
                if((!(bds[i-1]>=48&&bds[i-1]<=57))&&((c>=65&&c<=90)||(c>=97&&c<=122)||c==95))//字母或者下划线
                {//且不是科学计数法(即前一位不是数字)
                    PushStack(operand,x);
                    i++;
                    c=bds[i];
                    while(c>47&&c!='^')//如果在这个变量后的字符不是操作符,则后面的字符也是变量名的一部分
                    {//所以往下读直到读到操作符
                        i++;
                        c=bds[i];
                    }
                }
                else
                if((bds[i-1]>=48&&bds[i-1]<=57)&&c=='e')//科学计数法
                {
                    ife=1;
                    i++;
                    c=bds[i];
                }
                else//剩下的是操作符
                {
                    if(ife==1)//如果刚才是个浮点数的科学计数法
                        {
                            Operator a1;
                            ElemType a2,a3;
                            a1='^';
                            PopStack(operand,a2);
                            PopStack(operand,a3);
                            ElemType e=10;
                            ElemType all=a3*Oper(e,a2,a1);
                            PushStack(operand,all);
                            ife=0;
                        }
                    char t=c;
                    switch(Precede(GetToprator(rator),c))
                    {
                        case less:
                            PushStack(rator,c);
                            i++;
                            c=bds[i];
                            break;
                        case equal:
                            Operator tp;
                            PopStack(rator,tp);
                            i++;
                            c=bds[i];
                            break;
                        case more:
                            Operator a1;
                            ElemType a2,a3;
                            PopStack(rator,a1);
                            PopStack(operand,a2);
                            PopStack(operand,a3);
                            PushStack(operand,Oper(a3,a2,a1));
                            break;
                    }//switch
                    if(t=='('&&c=='-')
                    {
                        ElemType tpp=0;
                        PushStack(operand,tpp);
                    }
                }
       }
    }//while
    if(k!=0)//如果只输入了一个数字的情况
    {
        if(d==1)
        {
            double all=0;
            int temp=0;
            //整数位
            for(int i=0;i<=k-1;i++)
            {
                temp=temp*10+a[i];
            }
            //小数位
            for(int i=j-1;i>=0;i--)
            {
                all=all*0.1+b[i];
            }
            //还原实际的数
            all=all*0.1+temp;
            PushStack(operand,all);
        }
        if(d==0)
        {
            ElemType temp=0;
            for(int i=0;i<=k-1;i++)
            {//把记录的整数位还原成正确的数
                    temp=temp*10+a[i];
            }
            PushStack(operand,temp);//压入操作数栈
        }
    }
    if(ife==1)
    {
        Operator a1;
        ElemType a2,a3;
        a1='^';
        PopStack(operand,a2);
        PopStack(operand,a3);
        ElemType e=10;
        ElemType all=a3*Oper(e,a2,a1);
        PushStack(operand,all);
        ife=0;
    }
    return GetToprand(operand);
}


void CompareFunc(string &s,Function function[20],int n,int xlen)
{
    for(int i=0;i<n;i++)//对已经定义了的函数进行遍历
    {
        string findname=function[i].name;
        string temp="(";

        string repfunc=temp+function[i].func;
        int wherech=repfunc.find('#',0);
        repfunc.replace(wherech,repfunc.length()-wherech,")");//repfunc是把被调用的函数的函数体外加括号

        findname=findname+temp;//调用的时候是函数名后面加 ( 的

        int where=0;
        where=s.find(findname,where);
        int len=s.length();
        while(where<=len&&where>=0)//可能调用多次同个函数 //直到找不到为止
        {
            int namelen=findname.length()+2+xlen-1;
            s.erase(where,namelen);//把被调用的函数的函数体替换进去
            s.insert(where,repfunc);
            where=s.find(findname,where);
        }
    }
}
