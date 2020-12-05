#include <iostream>
#include"stack.h"
#include"xvector.h"
#include"polynomial.h"
#include"matrix.h"
using namespace std;
int main()
{   
    int what;
        cout<<"What do you want to count "<<endl;
        cout<<"1.Vector    2.Polynomial with one variable    3.Calculate an expression "<<endl
           <<"4.Expression with one variable   5.Define and Run function  6.Matrix"<<endl;
        cin>>what;
        if(what==1)//向量计算
        {
            int n;
            cout<<"Enter the dimension of the vector"<<endl;
            cin>>n;//向量维数
            Lxiang x1,x2,x3;
            cout<<"Enter the first vector"<<endl;
            Initxiang(n,x1);
            cout<<"Enter the second vector"<<endl;
            Initxiang(n,x2);
            while(1)
            {
                cout<<"What do you want to calculate"<<endl;
                cout<<"1.Add 2.Subtract 3.Cos 4.Exit"<<endl;
                int what1;
                cin>>what1;
                if(what1==1)//加法
                {
                    x3=Addxiang(x1,x2);
                    cout<<"The answer is: "<<endl;
                    printx(x3);
                }
                else
                if(what1==2)//减法
                {
                    x3=Minusxiang(x1,x2);
                    cout<<"The answer is: "<<endl;
                    printx(x3);
                }
                else
                if(what1==3)//cos
                    cout<<"The answer is : "<<Cosxiang(x1,x2)<<endl<<endl;
                else
                if(what1==4)//退出
                    { cout<<"End"<<endl; break;}
                else cout<<"error";
            }
            Destroyxiang(x1);
            Destroyxiang(x2);
            Destroyxiang(x3);
        }
        else
        if(what==2)//一元多项式
        {
            int what1;
            cout<<"use what to calculate 1.sequence list  2.chain table"<<endl;
            cin>>what1;
            if(what1==1)//顺序表
            {//顺序表的要先确定最大指数才能分配出相应空间
                //顺序表是每一个指数位上的都要存
                Polyn polyn1,polyn2,polyn3,polyn4;
                int n,what2;
                cout<<"enter the largest index of the first polynomial"<<endl;
                cin>>n;//指数最大值
                cout<<"enter the coefficients of terms in the first polynomial( in ascending order of indexs)(enter 0 if there is no )(totally n+1)"<<endl;
                cout<<"For example: the largest index is 3 ,enter 1 2 0 3  means 1+2*x+3*x^3"<<endl;
                CreatePolyn(polyn1,n);
                cout<<"the first polynomial is:  "<<endl;
                PrintPolyn(polyn1);

                cout<<"enter the largest index of the second polynomial"<<endl;
                cin>>n;
                cout<<"enter the coefficients of terms in the second polynomial( in ascending order of indexs)(enter 0 if there is no )(totally n+1)"<<endl;
                cout<<"For example: the largest indexis 3 ,enter 1 2 0 3  means 1+2*x+3*x^3"<<endl;
                CreatePolyn(polyn2,n);
                cout<<"the second polynomial is:  "<<endl;
                PrintPolyn(polyn2);

                while(1)
                {
                cout<<"What do you want to calculate: 1.Add  2.Subtract  3.Multiply  4.Derivation 5.Exit"<<endl;
                cin>>what2;
                if(what2==1)//加法
                {
                    polyn3=AddPolyn(polyn1,polyn2);
                    cout<<"The answer is:"<<endl;
                    PrintPolyn(polyn3);
                }
                else
                if(what2==2)//减法
                {
                    polyn3=SubstractPolyn(polyn1,polyn2);
                    cout<<"The answer is:"<<endl;
                    PrintPolyn(polyn3);
                }
                else
                if(what2==3)//乘法
                {
                    polyn3=MultiplyPolyn(polyn1,polyn2);
                    cout<<"The answer is:"<<endl;
                    PrintPolyn(polyn3);
                }
                else
                if(what2==4)//求导
                {
                    cout<<"to calculate whose derivation: 1.the first polynomial 2.the second polynomial"<<endl;
                    cin>>n;
                    cout<<"Please enter how many derivatives you want"<<endl;
                    int m;
                    cin>>m;
                    if(n==1)//求多项式1的导数
                    {
                        cout<<"The "<<m<<"st derivation of the first polynomial is : " <<endl;
                        if(m>polyn1.real_end-1) cout<<0<<endl<<endl;//如果要求的阶数大于多项式里最大阶数
                        else
                        if(m==0) PrintPolyn(polyn1);
                        else if(m<0) cout<<"error"<<endl;
                        else
                        {
                            DeriPolyn(polyn1,polyn3);
                            for(int i=2;i<=m;i++)
                            {
                                if(i%2==0)//p3求导,存在p4里
                                    DeriPolyn(polyn3,polyn4);
                                else//p4求导,存在p3里
                                    DeriPolyn(polyn4,polyn3);
                            }
                            if(m%2==0)
                                PrintPolyn(polyn4);
                            else
                                PrintPolyn(polyn3);
                        }
                    }
                    else
                        if(n==2)
                        {
                            cout<<"The "<<m<<"st derivation of the second polynomial is : " <<endl;
                            if(m>polyn2.real_end-1) cout<<0<<endl<<endl;
                            else
                            if(m==0) PrintPolyn(polyn2);
                            else if(m<0) cout<<"error"<<endl;
                            else
                            {
                            DeriPolyn(polyn2,polyn3);
                            for(int i=2;i<=m;i++)
                            {
                                if(i%2==0)
                                    DeriPolyn(polyn3,polyn4);
                                else
                                    DeriPolyn(polyn4,polyn3);
                            }
                            if(m%2==0)
                                PrintPolyn(polyn4);
                            else
                                PrintPolyn(polyn3);
                            }
                        }
                    else cout<<"ERROR"<<endl;
                }
                else if(what2==5)
                {
                    cout<<"End"<<endl;
                    break;
                }
                else cout<<"ERROR"<<endl;

                }
                DestroyPolyn(polyn1);
                DestroyPolyn(polyn2);
                DestroyPolyn(polyn3);
                DestroyPolyn(polyn4);
            }
            else
            if(what1==2)
            {
                int n,what2;
                PList p1,p2,p3;
                cout<<"enter how many items the first polynomial has"<<endl;
                cin>>n;//用链表算的要先知道多项式一共有多少项
                cout<<"enter the coefficient and index of each item"<<endl;
                cout<<"for example: the first polynomial has 3 items, enter 3 3 2 1 1 0 means 1+2*x+3*x^3"<<endl;
                cout<<"coefficient  index"<<endl;//系数 指数
                CreateLPolyn(p1,n);
                cout<<"the first polynomial is :"<<endl;
                PrintPolynNode(p1);

                cout<<"enter how many items the second polynomial has"<<endl;
                cin>>n;
                cout<<"enter the coefficient and index of each item "<<endl;
               cout<<"for example: the first polynomial has 3 items, enter 3 3 2 1 1 0 means 1+2*x+3*x^3"<<endl;
                cout<<"coefficient  index"<<endl;
                CreateLPolyn(p2,n);
                cout<<"the second polynomial is :"<<endl;
                PrintPolynNode(p2);

                while(1)
                {
                cout<<"What do you want to calculate: 1.Add  2.Subtract  3.Multiply  4.Derivation 5.Exit"<<endl;
                cin>>what2;
                if(what2==1)
                {
                    cout<<"the answer is"<<endl;
                    p3=AddPolynNode(p1,p2);
                    PrintPolynNode(p3);
                }
                else
                if(what2==2)
                {
                    cout<<"the answer is"<<endl;
                    p3=SubstractPolynNode(p1,p2);
                    PrintPolynNode(p3);
                }
                else
                if(what2==3)
                {
                    cout<<"the answer is"<<endl;
                    p3=MultiplyPolynNode(p1,p2);
                    PrintPolynNode(p3);
                }
                else
                if(what2==4)
                {
                    int m;
                    cout<<"to calculate whose derivation: 1.the first polynomial 2.the second polynomial"<<endl;
                    cin>>n;
                    cout<<"Please enter how many derivatives you want"<<endl;
                    cin>>m;
                    if(n==1)
                    {
                        cout<<"The "<<m<<"st derivation of the first polynomial is : " <<endl;
                        if(m>p1->expn)//在头结点里存了多项式里最高项的指数
                        cout<<0<<endl<<endl;
                        else if(m==0) PrintPolynNode(p1);
                        else if(m<0) cout<<"error"<<endl;
                        else
                        {
                            p3=DeriPolynNode(p1);
                            for(int i=2;i<=m;i++)
                            {
                                p3=DeriPolynNode(p3);
                            }
                            PrintPolynNode(p3);
                        }
                    }
                    else
                    if(n==2)
                    {
                         cout<<"The "<<m<<"st derivation of the second polynomial is : " <<endl;
                        if(m>p2->expn)
                            cout<<0<<endl<<endl;
                        else if(m==0) PrintPolynNode(p2);
                        else if(m<0) cout<<"error"<<endl;
                        else
                        {
                            p3=DeriPolynNode(p2);
                            for(int i=2;i<=m;i++)
                            {
                                p3=DeriPolynNode(p3);
                            }
                            PrintPolynNode(p3);
                        }
                    }
                    else cout<<"ERROR"<<endl;
                }
                else if(what2==5)
                {
                    cout<<"End"<<endl;
                    break;
                }
                else cout<<"ERROR"<<endl;
                }
                DestroyPolynNode(p1);
                DestroyPolynNode(p2);
                DestroyPolynNode(p3);
            }
            else
            {
                cout<<"ERROR"<<endl;
            }
        }
        else
        if(what==3)//四则运算求值//搞到栈里计算
        {
            char k[1];
            gets(k);
            Stackrand Rand;//操作数栈
            Stackrator Rator;//操作符栈
            cout<<"Please enter the expression (add # at the end of the expression!)(if there is a negative,add ())"<<endl;
            cout<<"for example: (-3)+4*(5+6/3)#"<<endl;
            cout<<"please make sure that the expression is valid"<<endl;
            char bds[100];
            gets(bds);//读入表达式
            cout<<Calculate(Rand,Rator,bds);//读入表达式也在其中完成
            cout<<endl<<endl<<"End"<<endl;
        }
        else
        if(what==4)//含单变量的表达式求值
        {
            char k[1];
            gets(k);
            ElemType x;
            Stackrand Rand;
            Stackrator Rator;
            cout<<"Please enter the expression (add # at the end of the expression!)(if there is a negative,add ())"<<endl;
            cout<<"for example: (-3)+4*(x2y+6/3)#"<<endl;
            cout<<"please make sure that the expression is valid"<<endl;
            char bds[100];
            gets(bds);//读入表达式
            cout<<"Please enter the value of the variable"<<endl;
            cin>>x;//读入变量的值
            cout<<"When the variable is "<<x<<" the answer is : "<<endl;
            cout<<CalculateX(Rand,Rator,x,bds)<<endl;

            cout<<"Please enter the value of the variable"<<endl;
            cin>>x;
            cout<<"When the variable is "<<x<<" the answer is : "<<endl;
            cout<<CalculateX(Rand,Rator,x,bds)<<endl;

            cout<<"Please enter the value of the variable"<<endl;
            cin>>x;
            cout<<"When the variable is "<<x<<" the answer is : "<<endl;
            cout<<CalculateX(Rand,Rator,x,bds)<<endl;

            cout<<endl<<"End"<<endl;
        }
        else
        if(what ==5)//定义并运行函数
        {
            Function function[20];
            int n=0;//当前有几个函数
            int p=0;//记录是否要读回车
            while(1)
            {
                cout<<endl<<"DEF or RUN a function  or EXIT"<<endl;
                cout<<"PS: If you want to DEF a function, add a # at the end of the function"<<endl;
                char k[1];
                if(p==0)
                {
                    gets(k);//读回车
                    p=1;
                }
                char temp[100];
                char how[5];
                gets(temp);//暂时存住式子
                sscanf(temp, "%[^ ]", how);//判断是定义还是运行
                if(how[0]=='D')//如果是定义一个函数
                {
                    char nametemp[10];
                    sscanf(temp, "%*[^ ]%[^(]", nametemp);
                    function[n].name=nametemp;
                    function[n].name.erase(0,1);//记录函数名


                    int xlen;
                    char xname[10];
                    sscanf(temp,"%*[^(]%[^)]",xname);
                    xlen=strlen(xname)-1;//记录变量名有多长

                    char functemp[100]; //先暂时把函数体放到这里
                    sscanf(temp, "%*[^=]%[^\n]", functemp);
                    sscanf(functemp, "%*c%s", functemp);

                    string cmtemp=functemp;
                    CompareFunc(cmtemp,function,n,xlen);//用来判断是否调用函数并进行处理

                    const char *strtemp=cmtemp.c_str();
                    int len=cmtemp.length();

                    char* bugtemp=(char*)malloc(sizeof(char)*(len+1));
                    for(int k=0;k<len;k++)
                        bugtemp[k]=strtemp[k];

                    for(int k=0;k<len;k++) //把处理完的函数存进去
                        function[n].func[k]=bugtemp[k];
                    free(bugtemp);

                    n++;
                }
                else
                if(how[0]=='R')
                {
                    char nametemp[10];
                    sscanf(temp, "%*[^ ]%[^(]", nametemp);
                    string name=nametemp;
                    name.erase(0,1);
                    int num=-1;
                    for(int i=0;i<n;i++)//匹配要运行的是哪个函数
                    {
                        if(name==function[i].name)
                        {
                            num=i;
                            break;
                        }
                    }//要用的函数是function[num]
                    //接下来得读出要带入的数字
                    if(num==-1)
                        cout<<"this function has not been defined"<<endl;//如果找不到该函数
                    else
                    {
                        char var[20];//也有可能是有小数的,参照原来的//就改成除了数字和小数点之外的不读
                        sscanf(temp,"%*[^(]%[^)]",var);
                        ElemType x;//参数的值
                        x=0;
                        int len=strlen(var);
                        int d=0,a[20],b[20],ai=0,bi=0;
                        int neg=0;
                        for(int i=1;i<len;i++)
                        {
                            if(i==1&&var[i]=='-')
                            {
                                neg=1;
                                continue;
                            }
                            if(var[i]>=48&&var[i]<=57&&d==0)
                            {
                                a[ai]=var[i]-48;
                                ai++;
                            }
                            else
                            if(var[i]>=48&&var[i]<=57&&d==1)
                            {
                                b[bi]=var[i]-48;
                                bi++;
                            }
                            else
                            if(var[i]==46)
                            {
                                d=1;
                            }
                        }
                        int tempx=0;
                        for(int i=0;i<ai;i++)
                            tempx=tempx*10+a[i];
                        for(int i=bi-1;i>=0;i--)
                            x=x*0.1+b[i];
                        x=x*0.1+tempx;//得到参数的值
                        if(neg==1)
                            x=-x;

                        ElemType answer;
                        Stackrand Rand;
                        Stackrator Rator;
                        answer=CalculateX(Rand,Rator,x,function[num].func);
                        cout<<"the answer is  :   "<<answer<<endl<<endl;
                    }//找到函数的

                }//run的
                else
                    if(how[0]=='E')
                    {
                        for(int i=0;i<n;i++)
                        {
                            free(function[i].func);
                        }
                        cout<<"END"<<endl;
                        break;
                    }
                else
                    cout<<"Error"<<endl<<endl;
            }//循环整个过程
        }
        else
        if(what==6)//矩阵
        {
            cout<<"Enter the size of your first matrix"<<endl<<"for example,enter 3 2 for a matrix of 3x2"<<endl;
            Matrix matrix1;
            cin>>matrix1.mu>>matrix1.nu;
            matrix1.tu=0;
            cout<<"Please enter the matrix"<<endl;
            InitMatrix(matrix1);
            cout<<"the first matrix is : "<<endl;
            PrintMatrix(matrix1);

            cout<<"Enter the size of your second matrix"<<endl<<"for example,enter 3 2 for a matrix of 3x2"<<endl;
            Matrix matrix2;
            cin>>matrix2.mu>>matrix2.nu;
            matrix2.tu=0;
            cout<<"Please enter the matrix"<<endl;
            InitMatrix(matrix2);
            cout<<"the second matrix is : "<<endl;
            PrintMatrix(matrix2);

            while(1)
            {
                cout<<"what do you want to calculate "<<endl;
                cout<<"1. Add 2.Substract 3.Multiply 4.Transpose 5.Exit"<<endl;
                int what1;
                cin>>what1;
                if(what1==1)//加法
                {
                    Matrix matrix3;
                    if(AddMatrix(matrix1,matrix2,matrix3))
                    {
                        cout<<"the answer is : "<<endl;
                        PrintMatrix(matrix3);
                    }
                    else cout<<"they cann't be added"<<endl<<endl;
                    DestroyMatrix(matrix3);
                }
                else
                 if(what1==2)//减法
                 {
                     Matrix matrix3;
                     if(SubstractMatrix(matrix1,matrix2,matrix3))
                     {
                         cout<<"the answer is : "<<endl;
                         PrintMatrix(matrix3);
                     }
                     else cout<<"they cann't be substracted"<<endl<<endl;
                     DestroyMatrix(matrix3);
                 }
                else
                if(what1==3)//乘法
                {
                    Matrix matrix3;
                    if(MultiplyMatrix(matrix1,matrix2,matrix3))
                    {
                        cout<<"the answer is : "<<endl;
                        PrintMatrix(matrix3);
                    }
                    else cout<<"they cann't be multiplied"<<endl<<endl;
                    DestroyMatrix(matrix3);
                }
                else
                if(what1==4)//转置
                {
                    cout<<"which one do you want to transpos? 1.the first matrix  2. the second matrix"<<endl;
                    int what2;
                    cin>>what2;
                    Matrix matrix3;
                    if(what2==1)
                    {
                        TransMatrix(matrix1,matrix3);
                        PrintMatrix(matrix3);
                    }
                    else
                    if(what2==2)
                    {
                        TransMatrix(matrix2,matrix3);
                        PrintMatrix(matrix3);
                    }
                    else cout<<"ERROR"<<endl;
                    DestroyMatrix(matrix3);
                }
                else
                 if(what1==5)
                     break;
                else cout<<"ERROR"<<endl;
            }
            DestroyMatrix(matrix1);
            DestroyMatrix(matrix2);
         }
        else cout<<"ERROR"<<endl;
    return 0;
}
