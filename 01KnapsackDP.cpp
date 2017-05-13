#include<stdio.h>
int max(int a,int b){
    return a>b?a:b;
}
void knapSack_iterative(int W,int values[],int weights[],int n){
    int ks[n+1][W+1];
    int i,j;
    for(i=0;i<=n;i++){
        for(j=0;j<=W;j++){
            if(i==0 || j==0){
                ks[i][j]=0;
            }
            else if (weights[i-1]>j){
                ks[i][j]=ks[i-1][j];
            }
            else{
                ks[i][j] = max(ks[i-1][j-weights[i-1]] +values[i-1] , ks[i-1][j] );
            }
        }
    }
    int N=n;
    int we=W;
    while(N>=0){
        if(N==0){
            N--;
            continue;
        }
        if(ks[N][we] > ks[N-1][we]){
            printf("%dth item with weight:%d and value:%d is selected\n",N,weights[N-1],values[N-1]);
            we -= weights[N-1];
        }
        N--;
    }
    printf("Max value obtained is %d:",ks[n][W]);
}
int knapSack_recursive(int noitems,int weight, int weights[],int values[]){
    if(noitems==0 || weight==0){
        return 0;
    }
    else if(weights[noitems-1]>weight){
        return knapSack_recursive(noitems-1,weight,weights,values);
    }
    else{
        return max(values[noitems-1]+knapSack_recursive(noitems-1,weight-weights[noitems-1],weights,values),knapSack_recursive(noitems-1,weight,weights,values));
    }
}
int main()
{
    int N,i;
    printf("Enter the no. of items you wish to have:\n");
    scanf("%d",&N);
    int weights[N],values[N];
    printf("Enter the values and weights for the items\n");
    for(i=0;i<N;i++)
    {
        printf("Enter value for %dth item: ",i+1);
        scanf("%d",&values[i]);
        printf("Enter weight for %dth item: ",i+1);
        scanf("%d",&weights[i]);
    }
    int W;
    printf("Enter the maximum capacity of the bag: ");
    scanf("%d",&W);
    knapSack_iterative(W,values,weights,N);
    printf("%d",knapSack_recursive(N,W,weights,values));
    return 0;
}
