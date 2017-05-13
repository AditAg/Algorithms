#include<stdio.h>
#define SIZE 100
#define CUTOFF 10
int medianof3(int A[],int low,int high){
    int middle=(low)+((high-low)/2);
    if(A[low]<A[high]){
        if(A[high]<A[middle])  return high;
        else if (A[middle]<A[low]) return low;
        else if(A[middle]<=A[high]) return middle;
    }
    else if(A[high]<A[low]){
        if(A[low]<A[middle])  return low;
        else if (A[middle]<A[high]) return high;
        else if(A[middle]<=A[low]) return middle;
    }
    else if(A[high]==A[low]){
        if(A[middle]<A[high])   return middle;
        else                    return low;
    }
}
void swap(int **A,int a,int b){
    int temp=(*A)[a];
    (*A)[a]=(*A)[b];
    (*A)[b]=temp;
}
int partition(int **A,int low,int high){
    int length=(high-low)+1;
    /*if(length<=CUTOFF){
        insertionsort(A,low,high);
    }*/
    int index=medianof3((*A),low,high);
    swap(A,low,index);
    int i=low+1;
    int j=high;
    while(i<=j){
        while((*A)[i]<=(*A)[low]){
            i++;
        }
        while((*A)[j]>(*A)[low])    j--;
        if(j<i) break;
        swap(A,i,j);
    }
    return j;
}
void quicksort(int A[],int n){
    int low=0,i;
    int high=n-1;
    int stack[n];
    int top=-1,middle;
    stack[++top]=low;
    stack[++top]=high;
    while(top>=0){
        high=stack[top--];
        low=stack[top--];
        int p=partition(&A,low,high);
        swap(&A,low,p);
        //Implement to always take smaller array first
        middle=low+((high-low)/2);
        if(p<middle){
            if(p<high-1){
                stack[++top]=p+1;
                stack[++top]=high;
            }
            if(p>low+1){
                stack[++top]=low;
                stack[++top]=p-1;
            }
        }
        else{
            if(p>low+1){
                stack[++top]=low;
                stack[++top]=p-1;
            }
            if(p<high-1){
                stack[++top]=p+1;
                stack[++top]=high;
            }
        }
    }
    for(i=0;i<n;i++){
        printf("%d ",A[i]);
    }

}
int main(){
    //int A[SIZE];
    int i=0;
    /*printf("Enter the array of numbers:\n");
    char ch;
    while(1){
        printf("Enter the %dth element:\n",i+1);
        scanf("%d",&A[i]);
        i++;
        printf("Do you wish to enter more elements?(Enter Y or N)\n");
        scanf("%c",&ch);
        if(ch=='N' || ch=='n')  break;
    }
    int N=i;*/
    int N;
    printf("Enter the no. of elements you wish to enter:\n");
    scanf("%d",&N);
    int A[N];
    for(i=0;i<N;i++){
        printf("Enter the %dth element: ",i+1);
        scanf("%d",&A[i]);
    }
    quicksort(A,N);
    return 0;
}
