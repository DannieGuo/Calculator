#include "matrix.h"
void InitMatrix(Matrix &mat)
{
    ElemType temp;
    for(int l=0;l<mat.mu;l++)
    {
        mat.rpos[l+1]=-1;
        for(int p=0;p<mat.nu;p++)
        {
            cin>>temp;
            if(temp!=0)
            {
                mat.data[mat.tu].e=temp;
                mat.data[mat.tu].i=l+1;//矩阵的行列坐标下标从1开始
                mat.data[mat.tu].j=p+1;
                if(mat.rpos[l+1]==-1) mat.rpos[l+1]=mat.tu;
                mat.tu++;//矩阵的数组里是从0开始存的
                        //但是因为后加了,所以是mat.tu个
            }
        }
    }
}
void PrintMatrix(Matrix mat)
{
    int temptu=0;
    for(int l=0;l<mat.mu;l++)
    {
        for(int p=0;p<mat.nu;p++)
        {
            if(mat.data[temptu].i==l+1&&mat.data[temptu].j==p+1&&temptu<mat.tu)
               {
                cout<<mat.data[temptu].e<<"  ";
                temptu++;
               }
            else//如果这个位置没有存的,就直接是0,可以直接输出0
                cout<<"0"<<"  ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void DestroyMatrix(Matrix &mat)
{
    mat.mu=0;
    mat.nu=0;
    mat.tu=0;
    free(mat.data);
}
Status AddMatrix(Matrix mat1,Matrix mat2,Matrix &mat)
{
    if(mat1.mu!=mat2.mu||mat1.nu!=mat2.nu)
        return ERROR;
    mat.mu=mat1.mu;
    mat.nu=mat1.nu;
    mat.tu=0;
    int tu1=0,tu2=0;
    for(int l=0;l<mat.mu;l++)
        for(int p=0;p<mat.nu;p++)
        {
            ElemType a1=0,a2=0;//初始化为0
            if(mat1.data[tu1].i==l+1&&mat1.data[tu1].j==p+1&&tu1<mat1.tu)
            {//如果该位置有值的就把值赋进去//没有值的其实也就是0
                a1=mat1.data[tu1].e;
                tu1++;
            }
            if(mat2.data[tu2].i==l+1&&mat2.data[tu2].j==p+1&&tu2<mat2.tu)
            {
                a2=mat2.data[tu2].e;
                tu2++;
            }
            if(a1+a2!=0)
            {
                mat.data[mat.tu].e=a1+a2;
                mat.data[mat.tu].i=l+1;
                mat.data[mat.tu].j=p+1;
                mat.tu++;
            }
        }
    return OK;
}
Status SubstractMatrix(Matrix mat1,Matrix mat2,Matrix &mat)
{
    if(mat1.mu!=mat2.mu||mat1.nu!=mat2.nu)
        return ERROR;
    mat.mu=mat1.mu;
    mat.nu=mat1.nu;
    mat.tu=0;
    int tu1=0,tu2=0;
    for(int l=0;l<mat.mu;l++)
        for(int p=0;p<mat.nu;p++)
        {
            ElemType a1=0,a2=0;
            if(mat1.data[tu1].i==l+1&&mat1.data[tu1].j==p+1&&tu1<mat1.tu)
            {
                a1=mat1.data[tu1].e;
                tu1++;
            }
            if(mat2.data[tu2].i==l+1&&mat2.data[tu2].j==p+1&&tu2<mat2.tu)
            {
                a2=mat2.data[tu2].e;
                tu2++;
            }
            if(a1-a2!=0)
            {
                mat.data[mat.tu].e=a1-a2;
                mat.data[mat.tu].i=l+1;
                mat.data[mat.tu].j=p+1;
                mat.tu++;
            }
        }
    return OK;
}
Status MultiplyMatrix(Matrix mat1,Matrix mat2,Matrix &mat)
{
    if(mat1.nu!=mat2.mu)
        return ERROR;
    mat.mu=mat1.mu;
    mat.nu=mat2.nu;
    mat.tu=0;
    if(mat1.tu==0||mat2.tu==0) return 0;
    ElemType rtemp[mat2.nu+1];

    for(int l=0;l<mat1.mu;l++)//对矩阵1的每一行
    {
        for(int p=0;p<mat2.nu+1;p++)//累加器清0
            rtemp[p]=0;

        int nowr1=mat1.rpos[l+1];//该行开始存的位置
        int nextr1;//下一行开始的位置或者最后一个

        if(l+1<mat1.mu)
        nextr1=mat1.rpos[l+2];
        else
        nextr1=mat1.tu;

        for(int p=nowr1;p<nextr1;p++)//对矩阵1的某行中每一个不是0的
        {//当前在矩阵1中的数的列对应在矩阵2的第几行的开始位置和结束位置
            int row2=mat1.data[p].j;//在矩阵2中对应第几行//存的下标是正常矩阵从1开始的
            int nowr2=mat2.rpos[row2];
            int nextr2;
            if(row2!=mat2.mu)
                nextr2=mat2.rpos[row2+1];
            else
                nextr2=mat2.tu;

            for(int u=nowr2;u<nextr2;u++)
            {
                rtemp[mat2.data[u].j]=rtemp[mat2.data[u].j]+mat2.data[u].e*mat1.data[p].e;
            }
        }

        for(int u=1;u<mat2.nu+1;u++)//存入最终的矩阵
        {
            if(rtemp[u]!=0)
            {
                mat.data[mat.tu].e=rtemp[u];
                mat.data[mat.tu].j=u;
                mat.data[mat.tu].i=l+1;
                mat.tu++;
            }
        }

    }


    return OK;
}
void TransMatrix(Matrix mat1,Matrix &mat)
{
    mat.tu=mat1.tu;
    mat.mu=mat1.nu;
    mat.nu=mat1.mu;

    int rnum[mat.mu+1];//记转置后各行有几个
    int rbegin[mat.mu+1];//记转置后各行开始位置

    for(int u=0;u<mat.mu+1;u++)
        rnum[u]=0;

    for(int p=0;p<mat1.tu;p++)//算转置后每行分别有几个
    {
        rnum[mat1.data[p].j]++;
    }

    rbegin[1]=0;

    for(int u=2;u<mat.mu+1;u++)//算转置后每行的开始位置
    {
        rbegin[u]=rbegin[u-1]+rnum[u-1];
    }

    for(int p=0;p<mat1.tu;p++)//对每一个进行转置
    {
        int row=mat1.data[p].j;//当前是第几行
        mat.data[rbegin[row]].e=mat1.data[p].e;
        mat.data[rbegin[row]].i=mat1.data[p].j;
        mat.data[rbegin[row]].j=mat1.data[p].i;
        rbegin[row]++;
    }

}
