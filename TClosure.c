#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct Graph{
    int V;
    bool **AdjMatrix;
};
struct Graph *create_graph(int N){
    struct Graph *temp = (struct Graph *)(malloc(sizeof(struct Graph)));
    temp->V = N;
    temp->AdjMatrix = (bool **)(malloc(sizeof(bool *)*N));
    int i,j;
    for(i=0;i<N;i++){
        temp->AdjMatrix[i] = (bool *)(malloc(sizeof(bool)*N));
        for(j=0;j<N;j++){
            temp->AdjMatrix[i][j]=false;
        }
    }
    return temp;
}
bool AND(bool a, bool b){
    if(a==true && b== true){ return true; }
    else{ return false; }
}
bool OR(bool a,bool b){
    if(a==false && b==false){ return false;}
    else{ return true; }
}
void transitive_closure(struct Graph *G){
    bool T[G->V][G->V];
    int i,j,k;
    for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++){
            T[i][j] = G->AdjMatrix[i][j];
            if(i==j){
                T[i][j] = true;
            }
        }
    }
    for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++){
            for(k=0;k<G->V;k++){//Here k is over the entire set of vertices and not from i to j since we can have say
                    //a path from 1 to 0 and then 0 to 4.
                T[i][j] = OR(T[i][j],AND(T[i][k],T[k][j]));
            }
        }
    }
    printf("\nThe transitive closure for the graph is : \n");
    for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++){
            printf("%d ",T[i][j]);
        }
        printf("\n");
    }
}
void add_Edge(int src,int dest,struct Graph *G){
    G->AdjMatrix[src][dest]=true;
}
int main(){
    int N,E,i;
    printf("Enter the no. of vertices in the graph :");
    scanf("%d",&N);
    struct Graph *G = create_graph(N);
    printf("Enter the no. of edges :");
    scanf("%d",&E);
    int src,dest;
    for(i=0;i<E;i++){
        printf("Enter source of edge %d : ",i+1);
        scanf("%d",&src);
        printf("Enter destination of Edge %d : ",i+1);
        scanf("%d",&dest);
        add_Edge(src,dest,G);
    }
    transitive_closure(G);
    return 0;
}

