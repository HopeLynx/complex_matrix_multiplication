#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


    //TODO сделать структуру компл числа, умножение и сложение для них DONE
struct complex_num{float re;float im;};

struct complex_num create_cn(){
    struct complex_num cn;
    cn.re = 0.0;
    cn.im =0.0;
    return cn;
}

struct complex_num create_cn_params(float re, float im){
    struct complex_num cn;
    cn.re = re;
    cn.im = im;
    return cn;
}

struct complex_num add(struct complex_num cn1, struct complex_num cn2){
    struct complex_num cn;
    cn.re = cn1.re+cn2.re;
    cn.im = cn1.im+cn2.im;
    return cn;
}

struct complex_num multiply(struct complex_num cn1, struct complex_num cn2){
    struct complex_num cn;
    cn.re = cn1.re*cn2.re - cn1.im*cn2.im;
    cn.im = cn1.re*cn2.im + cn1.im*cn2.re;
    return cn;
}


int main()
{
    //TODO сделать создание НУЖНОГО ФАЙЛА ДЛЯ ТЕСТА

    //TODO сделать чтение файла ДЛЯ ТЕСТА

    //TODO сделать структуру компл числа, умножение и сложение для них

    int r1, c1, r2, c2;

    printf("Enter number of rows and columns for matrix A : ");
    scanf("%d %d",&r1,&c1);

    printf("Enter number of rows and columns for matrix B : ");
    scanf("%d %d",&r2,&c2);

    int a[r1][c1], b[r2][c2], ab[r1][c2], ba[r2][c1],i,j,k,temp;

    if(c1==r2 && r1==c2)
    {
        printf("\nEnter element in matrix A : ");
        for(i=0;i<r1;i++)
        {
            for(j=0;j<c1;j++)
            {
                printf("\n Enter element : ");
                scanf("%d",&a[i][j]);
            }
        }
        printf("\nEnter element in B : ");
        for(i=0;i<r2;i++)
        {
            for(j=0;j<c2;j++)
            {
                printf("\nEnter element : ");
                scanf("%d",&b[i][j]);
            }
        }
        for(i=0;i<r1;i++)
        {
            for(j=0;j<c2;j++)
            {
                temp=0;
                for(k=0;k<r2;k++)
                {
                    temp+=a[i][k]*b[j][k];
                }
                ab[i][j]=temp;
            }
        }
        for(i=0;i<r2;i++)
        {
            for(j=0;j<c1;j++)
            {
                temp=0;
                for(k=0;k<r1;k++)
                {
                    temp+=b[i][k]*a[k][j];
                }
                ba[i][j]=temp;
            }
        }
        printf("\nMatrix A : ");
        for(i=0;i<r1;i++)
        {
            printf("\n\t");
            for(j=0;j<c1;j++)
            {
                printf("%d",a[i][j]);
            }
            printf("\n");
        }
        printf("\nMatrix B : ");
        for(i=0;i<r2;i++)
        {
            printf("\n\t");
            for(j=0;j<c2;j++)
            {
                printf("%d",b[i][j]);
            }
        }
        printf("\nMatrix multiplication of A*B : ");
        for(i=0;i<r1;i++)
        {
            printf("\n\t");
            for(j=0;j<c2;j++)
            {
                printf("\t%d",ab[i][j]);
            }
            printf("\n");
        }
        printf("\nMatrix multiplication of B*A : ");
        for(i=0;i<r2;i++)
        {
            printf("\n\t");
            for(j=0;j<c1;j++)
            {
                printf("\t%d",ba[i][j]);
            }
            printf("\n");
        }
    }
    else
        printf("\nMatrix Multiplication is not possible...!!!");
    return 0;
}
