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

void dfs_visit(struct Graph *G,int src,bool visited[],int discovery[],int low[],int parent[],bool ap[]){
    time=time+1;
    discovery[src]=time;
    low[src]=time;
    int children=0;
    visited[src]=true;
    ALNode * first = G->A[src].head;
    while(first!=NULL){
        if(first->dest == parent[src]){
                first=first->next;
                continue;
        }
        else if(!visited[first->dest]){
            parent[first->dest]=src;
            children++;
            dfs_visit(G,first->dest,visited,discovery,low,parent,ap);
            low[src]=min(low[src],low[first->dest]);
            if(parent[src]!=-1 && low[first->dest]>=discovery[src]){
                ap[src]=true;
            }
            if(parent[src]==-1 && children > 1){
                ap[src]=true;
            }

        }
        else{
            low[src]=min(low[src],discovery[first->dest]);
        }
        first=first->next;
    }

}
void dfs_Traversal(struct Graph *G){
    bool *visited = new bool[G->V];
    int *discovery = new int[G->V];
    int *low = new int[G->V];
    int *parent = new int[G->V];
    bool *articulation_point = new bool[G->V];
    int i=0;
    for (i=0;i<G->V;i++)
    {
        parent[i] = -1;
        visited[i] = false;
        articulation_point[i] = false;
    }
    time=0;
    for (i=0;i<G->V;i++){
        if (visited[i]==false){
            dfs_visit(G,i, visited, discovery, low, parent, articulation_point);
        }
    }
    cout<<"The Articulation Points are: "<<endl;
    for(i=0;i<G->V;i++){
        if(articulation_point[i]==true){
            cout<<i<<" is an articulation point"<<endl;
        }
    }
}
int main(){
    int E,i;
    printf("Enter the no of vertices in the graph: ");
    scanf("%d",&N);
    struct Graph *G=create_graph(N);
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
        addEdge(G,dest,src);
    }
    dfs_Traversal(G);

    return 0;
}
