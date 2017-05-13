#include<stdio.h>
#include<math.h>
#define SIZE 100
//int A[100];
//Implement heapify function to add a batch of n elements in O(n) time.
int size=1,N=0;
void doublesize(int *A){
    int size2=2*size;
    int B[size2],i;
    for(i=0;i<N;i++){
       B[i]=A[i];
    }
    size=size2;
    A=B;
    return;
    //if I return B here then it gives error.Why?......But the above works;
}
void decreasesize(int *A){
    int size2=(size/2);
    int B[size2],i;
    for(i=0;i<N;i++){
       B[i]=A[i];
    }
    size=size2;
    A=B;
    return;
}
void insert(int *A,int key){
    if(N>=size){
        doublesize(A);
    }
    A[N]=key;
    N=N+1;
    int lastelementindex=N-1;
    int parent=(lastelementindex-1)/2,temp;
    while(parent>=0 && A[parent]>A[lastelementindex]){
        temp=A[parent];
        A[parent]=A[lastelementindex];
        A[lastelementindex]=temp;
        lastelementindex=parent;
        parent=(lastelementindex-1)/2;
    }
    return;
}
void percolatedown(int *A){
    int i=0;
    int child1=2*i+1;
    if(child1>=N)    return;
    int temp;
    int child2=2*i+2;
    if(child2>=N){
        if(A[i]>A[child1]){
            temp=A[child1];
            A[child1]=A[i];
            A[i]=temp;
        }
        return;
    }
    while(i<N &&(A[i]>A[child1] || A[i]>A[child2])){
        if(A[child1]>A[child2]){
            temp=A[child2];
            A[child2]=A[i];
            A[i]=temp;
            i=child2;
        }
        else{
            temp=A[child1];
            A[child1]=A[i];
            A[i]=temp;
            i=child1;
        }
        child1=2*i+1;
        if(child1>=N)    return;
        child2=2*i+2;
        if(child2>=N){
            if(A[i]>A[child1]){
                temp=A[child1];
                A[child1]=A[i];
                A[i]=temp;
            }
            return;
        }
    }
    return;
}
int deletemin(int *A){
    int temp;
    temp=A[0];
    A[0]=A[N-1];
    A[N-1]=temp;
    N=N-1;
    percolatedown(A);
    if(N==((size)/4) && N>0){
        decreasesize(A);
    }
    return temp;

}
int position(int *A,int key){
    int i=0;
    for(i=0;i<N;i++){
        if(A[i]==key)   return i;
    }
    return -1;
}
void bubbleup(int *A,int pos,int key){
    int parent=(pos-1)/2,temp;
    while(parent>=0 && A[pos]<A[parent]){
                temp=A[pos];
                A[pos]=A[parent];
                A[parent]=temp;
                pos=parent;
                parent=(pos-1)/2;
    }
    return;
}
void deletespecific(int *A,int key){
    int pos=position(A,key);
    if(pos==-1){
        printf("Sorry key not found in heap\n");
        return;
    }
    if(pos==N-1){
        N=N-1;
        printf("DONE\n");
        return;
    }
    if(pos==0){
        deletemin(A);
        return;
    }
    A[pos]=A[N-1];
    N=N-1;
    int parent=(pos-1)/2;
    if(A[pos]<A[parent]){
        bubbleup(A,pos,A[pos]);
        printf("DONE\n");
        return;
    }
    int left=2*pos+1;
    int right=2*pos+2,temp;
    while(right<N){
        if (A[pos] <= A[left] && A[pos] <= A[right])
            return;
        if (A[right] > A[left])
        {
            temp = A[pos];
            A[pos] = A[left];
            A[left] = temp;
            pos = left;
        }
        else
        {
            temp = A[pos];
            A[pos] = A[right];
            A[right] = temp;
            pos = right;
        }
        left = 2 * pos + 1;
        right = 2 * pos + 2;
    }
    if(left==N-1 && A[pos]>A[left]){
        temp=A[left];
        A[left]=A[pos];
        A[pos]=temp;
    }
    printf("DONE\n");
    if (N==((size)/4) && N>0)   decreasesize(A);
    return;


}
void printheap(int *A){
    int i;
    if(N==0)    printf("\n\n");
    for(i=0;i<N;i++){
        printf("%d\n",A[i]);
    }
}
int main(){
    int A[size];
    int ch,i;
    while(1){
        printf("1.Insert item\n2.Delete Minimum\n3.Heapsort\n4.Print the heap\n5.Delete specific key\n6.Exit\n");
        scanf("%d",&ch);
        int B[N],top,key;
        switch(ch){
            case 1:
                printf("Enter the key to insert into the heap:");
                scanf("%d",&key);
                insert(A,key);
                printf("The heap after inserting the given key is:\n");
                printheap(A);
                break;

            case 2:
                top=deletemin(A);
                printf("The top element of the heap was:%d\n",top);
                printf("The heap after deleting the minimum element is:\n");
                printheap(A);
                printf("The size of heap after deleting is:%d\n",size);
                break;
            case 3:
                for(i=0;i<N;i++){
                    B[i]=A[i];
                }
                int z=N;
                printf("The heap sort for the given heap is:\n");
                for(i=0;i<z;i++){
                    printf("%d\n",deletemin(A));
                }
                for(i=0;i<z;i++)
                {
                    A[i]=B[i];
                }
                N=z;
                printf("The original heap was:\n");
                printheap(A);
                break;
            case 4:
                printf("The heap is:\n");
                printheap(A);
                break;
            case 5:
                printf("Enter key to delete:\n");
                scanf("%d",&key);
                deletespecific(A,key);
                printf("The heap after deleting the specified key is:\n");
                printheap(A);
                printf("The size of the heap after deleting is:%d\n",size);
                break;
            case 6:
                exit(0);
            default:
                printf("Sorry wrong choice\n");
                break;
        }
    }
    return 0;
}
