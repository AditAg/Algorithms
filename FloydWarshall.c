#include<stdio.h>
#include<limits.h>
int V;
void floyd_Warshall(int graph[V][V]){
    int distance[V][V];
    int cut[V][V];
    int i,j,k;
    for(i=0;i<V;i++){
        for(j=0;j<V;j++){
            distance[i][j]=graph[i][j];
            if(distance[i][j] == (INT_MAX)/2){
                cut[i][j]=-1;
            }
            else{
                cut[i][j]=j;
            }
        }
    }
    for(k=0;k<V;k++){
        for(i=0;i<V;i++){
            for(j=0;j<V;j++){
                if(distance[i][j]>distance[i][k] + distance[k][j]){
                    distance[i][j]=distance[i][k]+distance[k][j];
                    cut[i][j]=cut[i][k];
                }
            }
        }
    }
    int p,q;
    for(i=0;i<V;i++){
        for(j=0;j<V;j++){
            printf("Path from vertex %d to vertex %d is: \n",i,j);
            if(cut[i][j]==-1){
                printf("No path exists\n");
                continue;
            }
            printf("%d --->",i);
            p=i;
            q=j;
            while(cut[p][q]!=q){
                printf("%d --->",cut[p][q]);
                p=cut[p][q];
            }
            printf("%d with distance %d  \n",q,distance[i][j]);
        }
    }
}
int main()
{
    printf("Enter the no. of vertices in the graph: ");
    scanf("%d",&V);
    int graph[V][V],i,j;
    for(i=0;i<V;i++){
        for(j=0;j<V;j++){
            if(i==j){graph[i][j]=0;}
            else{graph[i][j]=(INT_MAX)/2;}
        }
    }
    /*do{
        printf("Enter source of the %dth edge: ",i);
        scanf("%d",&src);
        printf("Enter the destination of the %dth edge:",i);
        scanf("%d",&dest);
        if(src > V-1 || dest > V-1){
            printf("Sorry, the specified vertex doesn't exist.....Try again\n");
            continue;
        }
        printf("Enter the weight of the %dth edge: ",i);
        scanf("%d",weight);
        graph[src][dest] = weight;
        i++;
        printf("Enter Y to enter more edges and N to stop entering edges :");
        scanf(" %c",&ch);
        //if(ch<65 || (ch >90 && ch<97) || (ch>122)){
        if(ch!='Y' && ch!='y' && ch!='N' && ch!='n'){
            printf("Sorry you entered wrong value\n");
            return 0;
        }

    }while ((ch == 'Y') || (ch == 'y'));*/
    int E;
    printf("Enter the no. of edges: ");
    scanf("%d",&E);
    printf("Enter the edges: (vertices are from 0 to %d) \n",V-1);
    char ch ='N';
    int src,dest,weight;
    i=1;
    while(i<=E){
        printf("Enter source of the %dth edge: ",i);
        scanf("%d",&src);
        printf("Enter the destination of the %dth edge:",i);
        scanf("%d",&dest);
        if(src > V-1 || dest > V-1){
            printf("Sorry, the specified vertex doesn't exist.....Try again\n");
            continue;
        }
        printf("Enter the weight of the %dth edge: ",i);
        scanf("%d",&weight);
        graph[src][dest] = weight;
        i++;
    }
    floyd_Warshall(graph);
    return 0;
}
