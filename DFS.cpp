#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
typedef struct AdjacencyListNode{
    int dest;
    struct AdjacencyListNode *next;
}ALNode;
typedef struct AdjacencyList{
    struct AdjacencyListNode * head;
}AL;
struct Graph{
    int V;
    AL * A;
};
struct Graph *create_graph(int N){
    struct Graph *temp=(struct Graph *)(malloc(sizeof(struct Graph)));
    temp->V=N;
    temp->A=(AL *)(malloc(sizeof(AL)*N));
    int i=0;
    for(i=0;i<N;i++){
        temp->A[i].head=NULL;
    }
    return temp;
};
ALNode *create_Node(int dest){
    ALNode *x=(ALNode *)(malloc(sizeof(ALNode)));
    x->dest=dest;
    x->next=NULL;
    return x;
}
void addEdge(struct Graph *G,int src,int dest){
    ALNode *node =create_Node(dest);
    node->next= G->A[src].head;
    G->A[src].head = node;
}
int time,N;
int *discovery;
int *finaltime;
void dfs_visit(struct Graph *G,int src,int color[],int parent[]){
    color[src]=1;
    time=time+1;
    discovery[src]=time;
    printf("%d ",src);
    ALNode * first = G->A[src].head;
    while(first!=NULL){
        if(color[first->dest] == 0){
            parent[first->dest]=src;
            dfs_visit(G,first->dest,color,parent);
        }
        first=first->next;
    }
    color[src]=2;
    finaltime[src]=time+1;
    time=time+1;

}
void dfs_Traversal(struct Graph *G){
    int color[G->V],parent[G->V],i;
    for(i=0;i<G->V;i++){
        color[i]=0;
        parent[i]=-1;
    }
    time=0;
    printf("DFS Traversal is: \n");
    for(i=0;i<G->V;i++){
        if(color[i]==0){
            dfs_visit(G,i,color,parent);
        }
    }
}
int main(){
    int E,i;
    printf("Enter the no of vertices in the graph: ");
    scanf("%d",&N);
    struct Graph *G=create_graph(N);
    discovery = (int *)(malloc(sizeof(int)*N));
    finaltime = (int *)(malloc(sizeof(int) *N));
    printf("Enter the no. of edges: ");
    scanf("%d",&E);
    printf("Enter the edges:(vertices are from 0 to %d) \n",N-1);
    int src,dest;
    for(i=0;i<E;i++){
        printf("Enter the source of %dth edge: ",i+1);
        scanf("%d",&src);
        printf("Enter the destination of %dth edge: ",i+1);
        scanf("%d",&dest);
        addEdge(G,src,dest);
    }
    dfs_Traversal(G);
    vector <pair<int,int> > finaltimes;
    cout<<"\n";
    for(i=0;i<G->V;i++){
        cout<<discovery[i]<<" "<<finaltime[i]<<endl;
    }
    for(i=0;i<G->V;i++){
        finaltimes.push_back(make_pair(finaltime[i],i));
    }
    sort(finaltimes.begin(),finaltimes.end());
    cout<<"\n";
    for(i=0;i<G->V;i++){
        cout<<finaltimes[i].first<<" "<<finaltimes[i].second<<endl;
    }
    cout<<"Topological Sort is: \n";
    for(i=(G->V)-1;i>=0;i--){
        cout<<finaltimes[i].second<<" ";
    }
    return 0;
}
