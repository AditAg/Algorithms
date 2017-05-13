#include<stdio.h>
#include<string.h>
#include<math.h>
void merging(int A[],int left,int mid,int right){
    int i=left,j=mid+1;
    int k=0;
    int B[right-left+1];
    while(i<=mid && j<=right){
        if(A[i]<A[j]){
            B[k]=A[i];
            i++;
        }
        else{
            B[k]=A[j];
            j++;
        }
        k++;
    }
    while(i<=mid){
        B[k]=A[i];
        k++;
        i++;
    }
    while(j<=right){
        B[k]=A[j];
        k++;
        j++;
    }
    for(i=0;i<k;i++){
        A[left+i]=B[i];
    }
}
void mergesort(int A[],int N){
        int x,i,leftpoint,mid,rightpoint;
        //int z=pow(2,ceil(log2(N)));
        for(x=1;x<N;x=2*x){
            for(leftpoint=0;leftpoint<N-1;leftpoint+=(2*x)){
                rightpoint=leftpoint+(2*x)-1;
                mid=leftpoint+((rightpoint-leftpoint)/2);
                //or mid=leftpoint+x-1;
                if(rightpoint>N-1){
                    rightpoint=N-1;
                }
                //mid=leftpoint+((rightpoint-leftpoint)/2);//Very iMportant this doesn't work as the division isn't necessary
                //at this mid maybe array is 1 4 10 20 3 then it divides at 10 instead of taking 3 separately.

                merging(A,leftpoint,mid,rightpoint);
            }
        }

}
int main(){
    printf("Enter the number of elements you want to have:\n");
    int N;
    scanf("%d",&N);
    int i,A[N];
    for(i=0;i<N;i++){
        printf("Enter the %dth element: ",i+1);
        scanf("%d",&A[i]);
    }
    mergesort(A,N);
    for(i=0;i<N;i++)    printf("%d ",A[i]);
    return 0;
}
