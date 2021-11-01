//gcc main.c -o mult
// ./mult

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

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
    //TODO сделать создание НУЖНЫХ ФАЙЛОВ ДЛЯ ТЕСТА DONE
    int fd1 = open("cn1.dat",O_WRONLY|O_CREAT|O_TRUNC,0644);
    int fd2 = open("cn2.dat",O_WRONLY|O_CREAT|O_TRUNC,0644);
    if (fd1<0 || fd2<0) {
        perror("create/open cn files");
        return;
    }
    unsigned int r1=2,c1=3,r2=3,c2=2;
    if(write(fd1,&r1,sizeof(unsigned int))<0)perror("write1");
    if(write(fd1,&c1,sizeof(unsigned int))<0)perror("write1");
    for (unsigned int j=1;j<=r1;j++){
        for (unsigned int i=1;i<=c1*2;i++){
            float tmp =(j*i*1.0);
            if(write(fd1,&tmp,sizeof(float))<0)perror("write1");
        }
    }
    close(fd1);

    if(write(fd2,&r2,sizeof(unsigned int))<0)perror("write2");
    if(write(fd2,&c2,sizeof(unsigned int))<0)perror("write2");
    for (unsigned int j=1;j<=r2;j++){
        for (unsigned int i=1;i<=c2*2;i++){
            float tmp =(j*i*1.0);
            if(write(fd2,&tmp,sizeof(float))<0)perror("write2");
        }
    }
    close(fd2);
}

int main()
{
    create_test_files();
    //TODO сделать чтение файлов ДЛЯ ТЕСТА DONE
    int r1, c1, r2, c2;
    struct stat sb;
    char *p;
    int pgs,sz;

    int fd1 = open("cn1.dat",O_RDONLY);
    int fd2 = open("cn2.dat",O_RDONLY);

    if (fd1<0 || fd2<0) {
        perror("open cn files");
        return -1;
    }

    if(fstat(fd1,&sb)==1){perror("fstat");return 1;}
    if(!S_ISREG(sb.st_mode)){perror("file_type");return 1;}
    pgs = sysconf(_SC_PAGESIZE);
    sz=((sb.st_size-1)/pgs+1)*pgs;
    p = mmap(0,sz,PROT_READ,MAP_SHARED,fd1,0);
    if (p == MAP_FAILED) {perror("mmap");return 1;}
    if (close (fd1)==1){perror("close");return 1;}

    long offset =0;
    memcpy(&r1,p+offset,sizeof(unsigned int)); offset+= sizeof(unsigned int);
    memcpy(&c1,p+offset,sizeof(unsigned int)); offset+= sizeof(unsigned int);
    printf("%d %d\n",r1,c1);
    float tmp_re=0.0,tmp_im=0.0;
    struct complex_num *cnm1;
    cnm1 = (struct complex_num*)malloc(r1*c1 * sizeof(struct complex_num));
    if (malloc_check(cnm1)) return 1;
    for (int i = 0; i<r1; i++){  // цикл по строкам
        for (int j = 0; j<c1; j++){  // цикл по столбцам
            memcpy(&tmp_re,p+offset,sizeof(float)); offset+= sizeof(float);
            memcpy(&tmp_im,p+offset,sizeof(float)); offset+= sizeof(float);
            printf("%f,%fi ",tmp_re,tmp_im);
            cnm1[i*c1+j]=create_cn_params(tmp_re,tmp_im);
        }
        printf("\n");
    }
    if(munmap(p,sz)==1)perror("munmap");

    if(fstat(fd2,&sb)==1){perror("fstat");return 1;}
    if(!S_ISREG(sb.st_mode)){perror("file_type");return 1;}
    pgs = sysconf(_SC_PAGESIZE);
    sz=((sb.st_size-1)/pgs+1)*pgs;
    p = mmap(0,sz,PROT_READ,MAP_SHARED,fd2,0);
    if (p == MAP_FAILED) {perror("mmap");return 1;}
    if (close (fd2)==1){perror("close");return 1;}

    offset =0;
    memcpy(&r2,p+offset,sizeof(unsigned int)); offset+= sizeof(unsigned int);
    memcpy(&c2,p+offset,sizeof(unsigned int)); offset+= sizeof(unsigned int);
    printf("%d %d\n",r2,c2);
    struct complex_num *cnm2;
    cnm2 = (struct complex_num*)malloc(r2*c2 * sizeof(struct complex_num));
    if (malloc_check(cnm2)) return 1;
    for (int i = 0; i<r2; i++){  // цикл по строкам
        for (int j = 0; j<c2; j++){  // цикл по столбцам
            memcpy(&tmp_re,p+offset,sizeof(float)); offset+= sizeof(float);
            memcpy(&tmp_im,p+offset,sizeof(float)); offset+= sizeof(float);
            printf("%f,%fi ",tmp_re,tmp_im);
            cnm2[i*c2+j]=create_cn_params(tmp_re,tmp_im);
        }
        printf("\n");
    }
    if(munmap(p,sz)==1)perror("munmap");
    offset =0;

    printf("\n");

    struct complex_num *ans;
    if(c1==r2 && r1==c2){
        struct complex_num temp;
        ans = (struct complex_num*)malloc(r1*c2 * sizeof(struct complex_num));
        if (malloc_check(ans)) return 1;
        for(int i=0;i<r1;i++){
            for(int j=0;j<c2;j++){
                temp=create_cn();
                for(int k=0;k<r2;k++){
                    struct complex_num lul = multiply(cnm1[i*c1+k],cnm2[j+c2*k]);
//                    printf("%f %fi * %f %fi\n",cnm1[i*c1+k].re,cnm1[i*c1+k].im,cnm2[j+c2*k].re,cnm2[j+c2*k].im);
                    temp = add(temp,lul);
                }
                ans[i*r1+j]=temp;
            }
        }
        //TODO вывод в файл DONE
        int fd = open("filres.dat",O_RDWR|O_CREAT|O_TRUNC,0644);

        if(fstat(fd,&sb)==1){perror("fstat");return 1;}
        if(!S_ISREG(sb.st_mode)){perror("file_type");return 1;}
        pgs = sysconf(_SC_PAGESIZE);
        sz=((sb.st_size-1)/pgs+1)*pgs;
        if(write(fd,"",1)!= 1) perror("write ans error");
        p = mmap(0,sz,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        if (p == MAP_FAILED) {perror("mmap");return 1;}
        if (close (fd)==1){perror("close");return 1;}
        memcpy(p+offset,&r1,sizeof(unsigned int));offset+=sizeof(unsigned int);
        memcpy(p+offset,&c2,sizeof(unsigned int));offset+=sizeof(unsigned int);
        printf("Matrix multiplication of A*B:\n");
        for(int i=0;i<r1;i++){
            for(int j=0;j<c2;j++){
                temp = ans[i*c2+j];
                memcpy(p+offset,&temp.re,sizeof(unsigned int));offset+=sizeof(unsigned int);
                memcpy(p+offset,&temp.im,sizeof(unsigned int));offset+=sizeof(unsigned int);
                printf("\t%f %fi",temp.re,temp.im);
            }
            printf("\n");
        }
        if(munmap(p,sz)==1)perror("munmap");
    } else printf("\nMatrix Multiplication is not possible...!!!");
    free(cnm1);free(cnm2);
    free(ans);
    /*
    EXPECTED OUT:
    2 3
    1.000000,2.000000i 3.000000,4.000000i 5.000000,6.000000i
    2.000000,4.000000i 6.000000,8.000000i 10.000000,12.000000i
    3 2
    1.000000,2.000000i 3.000000,4.000000i
    2.000000,4.000000i 6.000000,8.000000i
    3.000000,6.000000i 9.000000,12.000000i

    Matrix multiplication of A*B:
        -34.000000 72.000000i	-46.000000 172.000000i
        -68.000000 144.000000i	-92.000000 344.000000i
    */


    return 0;
}
