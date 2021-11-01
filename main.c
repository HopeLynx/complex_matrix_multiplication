#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NULL ((void *)0)

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

// Ф-ия проверки выделения памяти
int malloc_check(struct complex_num *arr){
    if (arr==NULL) {
        perror("malloc\n");
        return 1;
    }
    else {
        return 0;
    }
}

void create_test_files(){
    //TODO сделать создание НУЖНЫХ ФАЙЛОВ ДЛЯ ТЕСТА
}

int main()
{
    //TODO сделать чтение файлов ДЛЯ ТЕСТА
    int fd1 = open("cn1.dat",O_RDONLY);
    int fd2 = open("cn2.dat",O_RDONLY);

    if (fd1<0 || fd2<0) {
        perror("open cn files");
        return -1;
    }

    /*
    // Создание двумерного динамического массива
    struct complex_num** cn_matrix = (struct complex_num**)malloc(sizeof(struct complex_num*) * c1);
        if (malloc_check(*cn_matrix)) return 1;

        for(int i = 0; i < c1; i++){
            cn_matrix[i] = (struct complex_num*)malloc(sizeof(char) * size*10);
            if (malloc_check(str[i])) return 1;
            scanf("%s",str[i]);
        }
    */
    int r1, c1, r2, c2;
    float tmp_re=0.0,tmp_im=0.0;

    if (read(fd1,&r1,sizeof(unsigned int))>0) printf("%d\n",r1);
    if (read(fd1,&c1,sizeof(unsigned int))>0) printf("%d\n",c1);
    struct complex_num *cnm1;
    cnm1 = (struct complex_num*)malloc(r1*c1 * sizeof(struct complex_num));
    if (malloc_check(cnm1)) return 1;
    for (int i = 0; i<r1; i++)  // цикл по строкам
    {
        for (int j = 0; j<c1; j++)  // цикл по столбцам
        {
            /*
          printf("a[%d][%d] = ", i, j);
          scanf("%d", (a + i*m + j));
          */
            if (!(read(fd1,&tmp_re,sizeof(float))>0)) perror("read error");
            if (!(read(fd1,&tmp_im,sizeof(float))>0)) perror("read error");
            printf("%f %fi ",tmp_re,tmp_im);
            cnm1[i*r1+j]=create_cn_params(tmp_re,tmp_im);
        }
        printf("\n");
    }
    close(fd1);

    if (read(fd2,&r2,sizeof(unsigned int))>0) printf("%d\n",r2);
    if (read(fd2,&c2,sizeof(unsigned int))>0) printf("%d\n",c2);
    struct complex_num *cnm2;
    cnm2 = (struct complex_num*)malloc(r2*c2 * sizeof(struct complex_num));
    if (malloc_check(cnm2)) return 1;
    for (int i = 0; i<r2; i++)  // цикл по строкам
    {
        for (int j = 0; j<c2; j++)  // цикл по столбцам
        {
            if (!(read(fd2,&tmp_re,sizeof(float))>0)) perror("read error");
            if (!(read(fd2,&tmp_im,sizeof(float))>0)) perror("read error");
            printf("%f %fi ",tmp_re,tmp_im);
            cnm1[i*r2+j]=create_cn_params(tmp_re,tmp_im);
        }
        printf("\n");
    }
    close(fd2);

    struct complex_num *ans;

    if(c1==r2 && r1==c2){
        struct complex_num temp;
        ans = (struct complex_num*)malloc(r1*c2 * sizeof(struct complex_num));
        if (malloc_check(ans)) return 1;

        for(int i=0;i<r1;i++)
        {
            for(int j=0;j<c2;j++)
            {
                temp=create_cn();
                for(int k=0;k<r2;k++)
                {
                    add(temp,multiply(cnm1[i*r1+k],cnm2[j*r2+k]));
                }
                ans[i*r1+j]=temp;
            }
        }

        printf("\nMatrix multiplication of A*B : ");
        for(int i=0;i<r1;i++)
        {
            printf("\n\t");
            for(int j=0;j<c2;j++)
            {
                temp = ans[i*r1+j];
                printf("\t%f %fi",temp.re,temp.im);
            }
            printf("\n");
        }
    } else printf("\nMatrix Multiplication is not possible...!!!");


    free(cnm1);free(cnm2);free(ans);






    int a[r1][c1], b[r2][c2], ab[r1][c2], ba[r2][c1],i,j,k,temp;

    if(c1==r2 && r1==c2)
    {
        /*
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
        */
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
