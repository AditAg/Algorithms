#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/time.h>
int max(int a,int b,int c){
    if(a>=b && a>=c) return a;
    else if(b>=a && b>=c)   return b;
    else    return c;
}
void print_matrix(int l1,int **A){
    int i,j;
    for(i=0;i<l1;i++){
        for(j=0;j<l1;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
}
int **matrix_add(int **A,int **B,int l){
    int i,j;
    int **C=(int **)(malloc(sizeof(int *)*l));
    for(i=0;i<l;i++){
        C[i]=(int *)malloc(sizeof(int)*l);
        for(j=0;j<l;j++){
            C[i][j]=A[i][j]+B[i][j];
        }
    }
    return C;
}
int **matrix_sub(int **A,int **B,int l){
    int i,j;
    int **C=(int **)(malloc(sizeof(int *)*l));
    for(i=0;i<l;i++){
        C[i]=(int *)malloc(sizeof(int)*l);
        for(j=0;j<l;j++){
            C[i][j]=A[i][j]-B[i][j];
        }
    }
    return C;
}
int **brute_mul(int **A,int **B,int l1){
    int i,j,k;
    int **C=(int **)malloc(sizeof(int *)*l1);
    for(i=0;i<l1;i++){
        C[i]=(int *)malloc(sizeof(int)*l1);
        for(j=0;j<l1;j++){
            C[i][j]=0;
            for(k=0;k<l1;k++){
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
    return C;
}
int **matrix_mul(int **A,int **B,int l1){
    if(l1<2){
        int **C=brute_mul(A,B,l1);
        return C;
    }
    int i,j;
    int **A11=(int **)(malloc(sizeof(int *)*(l1/2)));
    int **A12=(int **)(malloc(sizeof(int *)*(l1/2)));
    int **A21=(int **)(malloc(sizeof(int *)*(l1/2)));
    int **A22=(int **)(malloc(sizeof(int *)*(l1/2)));
    int **B11=(int **)(malloc(sizeof(int *)*(l1/2)));
    int **B12=(int **)(malloc(sizeof(int *)*(l1/2)));
    int **B21=(int **)(malloc(sizeof(int *)*(l1/2)));
    int **B22=(int **)(malloc(sizeof(int *)*(l1/2)));
    for(i=0;i<(l1/2);i++){
        A11[i]=(int *)(malloc(sizeof(int)*(l1/2)));
        A12[i]=(int *)(malloc(sizeof(int)*(l1/2)));
        A21[i]=(int *)(malloc(sizeof(int)*(l1/2)));
        A22[i]=(int *)(malloc(sizeof(int)*(l1/2)));
        B11[i]=(int *)(malloc(sizeof(int)*(l1/2)));
        B12[i]=(int *)(malloc(sizeof(int)*(l1/2)));
        B21[i]=(int *)(malloc(sizeof(int)*(l1/2)));
        B22[i]=(int *)(malloc(sizeof(int)*(l1/2)));
        for(j=0;j<(l1/2);j++){
            A11[i][j]=A[i][j];
            A12[i][j]=A[i][j+(l1/2)];
            A21[i][j]=A[i+(l1/2)][j];
            A22[i][j]=A[i+(l1/2)][j+(l1/2)];
            B11[i][j]=B[i][j];
            B12[i][j]=B[i][j+(l1/2)];
            B21[i][j]=B[i+(l1/2)][j];
            B22[i][j]=B[i+(l1/2)][j+(l1/2)];
        }
    }
    int **p,**q,**r,**s,**t,**u,**v;
    p=matrix_mul(matrix_add(A11,A22,(l1/2)),matrix_add(B11,B22,(l1/2)),l1/2);
    q=matrix_mul(matrix_add(A21,A22,(l1/2)),B11,(l1/2));
    r=matrix_mul(A11,matrix_sub(B12,B22,(l1/2)),l1/2);
    s=matrix_mul(A22,matrix_sub(B21,B11,(l1/2)),l1/2);
    t=matrix_mul(matrix_add(A11,A12,(l1/2)),B22,(l1/2));
    u=matrix_mul(matrix_sub(A21,A11,(l1/2)),matrix_add(B11,B12,(l1/2)),(l1/2));
    v=matrix_mul(matrix_sub(A12,A22,(l1/2)),matrix_add(B21,B22,(l1/2)),(l1/2));
    int **C11,**C12,**C21,**C22;
    C11=matrix_add(matrix_add(p,v,(l1/2)),matrix_sub(s,t,(l1/2)),l1/2);
    C12=matrix_add(r,t,l1/2);
    C21=matrix_add(q,s,l1/2);
    C22=matrix_add(matrix_add(p,u,(l1/2)),matrix_sub(r,q,(l1/2)),l1/2);
    int **Cmatrix=(int **)(malloc(sizeof(int *)*l1));
    for(i=0;i<l1/2;i++){
            Cmatrix[i]=(int *)malloc(sizeof(int)*l1);
            Cmatrix[i+(l1/2)]=(int *)malloc(sizeof(int)*l1);
            for(j=0;j<l1/2;j++){
                Cmatrix[i][j]=C11[i][j];
                Cmatrix[i][j+(l1/2)]=C12[i][j];
                Cmatrix[i+(l1/2)][j]=C21[i][j];
                Cmatrix[i+(l1/2)][j+(l1/2)]=C22[i][j];
            }
    }
    return Cmatrix;
}
int main(){
    int length1,length2,breadth1,breadth2;
    printf("Enter the size of 1st matrix: \n");
    scanf("%d %d",&breadth1,&length1);
    printf("Enter the size of 2nd matrix: \n");
    scanf("%d %d",&breadth2,&length2);
    if(length1!=breadth2){
        printf("Sorry the matrix multiplication is not possible\n.The sizes do not match\n");
        return 0;
    }
    int l1=max(length1,breadth1,length2);
    l1=pow(2,ceil(log2(l1)));
    int **A=(int **)(malloc(sizeof(int *)*l1));
    int **B=(int **)malloc(sizeof(int *)*l1);
    int i,j;
    for(i=0;i<breadth1;i++){
        A[i]=(int *)(malloc(sizeof(int)*l1));
        for(j=0;j<length1;j++){
            printf("A[%d][%d]= ",i,j);
            scanf("%d",&A[i][j]);
        }
        while(j<l1){ A[i][j]=0;
        j++;}
    }
    while(i<l1){
        A[i]=(int *)(malloc(sizeof(int)*l1));
        for(j=0;j<l1;j++){
            A[i][j]=0;
        }
        i++;
    }
    printf("\n");
    for(i=0;i<breadth2;i++){
        B[i]=(int *)(malloc(sizeof(int)*l1));
        for(j=0;j<length2;j++){
            printf("B[%d][%d]= ",i,j);
            scanf("%d",&B[i][j]);
        }
        while(j<l1){ B[i][j]=0;
        j++;}
    }
    while(i<l1){
        B[i]=(int *)(malloc(sizeof(int)*l1));
        for(j=0;j<l1;j++){
            B[i][j]=0;
        }
        i++;
    }
    //print_matrix(l1,A);
    //printf("\n");
    //print_matrix(l1,B);
    int **C,**D;
    clock_t start,endt;
    double elapsed;
    start=clock();
    C=matrix_mul(A,B,l1);
    elapsed=(((double) (clock() - start)/ CLOCKS_PER_SEC));
    printf("Code executed in %lf seconds.\n", elapsed);
    start=clock();
    D=brute_mul(A,B,l1);
    endt=clock();
    elapsed=(((double) (endt - start)) / CLOCKS_PER_SEC);
    printf("Code executed in %lf seconds.\n", elapsed);
    print_matrix(l1,C);
    printf("Brute force\n");
    print_matrix(l1,D);
    return 0;
}
