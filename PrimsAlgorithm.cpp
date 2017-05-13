#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct AdjacencyListNode{
    int dest;
    int weight;
    struct AdjacencyListNode *next;
}ALNode;
typedef struct AdjacencyList{
    ALNode *head;
}AL;
struct Graph{
    int no_vertices;
    AL *array;
};
struct Graph *create_graph(int N){
    struct Graph *temp=(struct Graph *)(malloc(sizeof(struct Graph)));
    temp->no_vertices=N;
    temp->array=(AL *)(malloc(sizeof(AL)*N));
    int i=0;
    for(i=0;i<N;i++){
        temp->array[i].head=NULL;
    }
    return temp;
};
ALNode *create_Node(int dest,int weight){
    ALNode *x=(ALNode *)(malloc(sizeof(ALNode)));
    x->dest=dest;
    x->weight=weight;
    x->next=NULL;
    return x;
}
void addEdge(struct Graph *G, int src, int dest,int weight){
    ALNode *newNode=create_Node(dest,weight);
    newNode->next=G->array[src].head;
    G->array[src].head=newNode;
    newNode=create_Node(src,weight);
    newNode->next=G->array[dest].head;
    G->array[dest].head=newNode;
}
int getminKey(int key[],int N,int mstSet[]){
    int min=INFINITY,i,min_index;
    for(i=0;i<N;i++){
        if(key[i]<min && mstSet[i]==0){
            min=key[i];
            min_index=i;
        }
    }
    return min_index;
}
int main()
{
    int N,i,E;
    printf("Enter the no of vertices in the graph\n");
    scanf("%d",&N);
    printf("Enter no. of edges: ");
    scanf("%d",&E);
    struct Graph *G=create_graph(N);
    printf("Enter the edges (assuming the vertices to be labelled from 0 to %d)\n",N-1);
    char ch;
    int src,dest,weight;
    for(i=0;i<E;i++){
        printf("Enter source of edge: ");
        scanf("%d",&src);
        if(src>N-1) {printf("Sorry source vertex is invalid..Try Again\n"); continue;}
        printf("Enter destination of edge: ");
        scanf("%d",&dest);
        if(dest>N-1) {printf("Sorry destination vertex is invalid..Try Again\n"); continue;}
        printf("Enter weight of edge: ");
        scanf("%d",&weight);
        addEdge(G,src,dest,weight);
    }
    int key[N],mstSet[N],parent[N];
    for(i=0;i<N;i++) {
        key[i]=INFINITY;
        mstSet[i]=0;
    }
    key[0]=0;
    parent[0]=-1;
    for(i=0;i<N-1;i++){
        int u=getminKey(key,N,mstSet);
        mstSet[u]=1;
        ALNode *node=G->array[u].head;
        while(node!=NULL){
            if(mstSet[node->dest]==0 && node->weight<key[node->dest]){
                parent[node->dest]=u;
                key[node->dest]=node->weight;
            }
            node=node->next;
        }
    }
    printf("The edges in the MST are\n");
    for(i=1;i<N;i++){
        weight=0;
        ALNode *node=G->array[parent[i]].head;
        while(node!=NULL){
            if(node->dest==i){
                    weight=node->weight;
                    break;
            }
            node=node->next;
        }
        printf("%d - %d with weight %d  \n",parent[i],i,weight);
    }
    return 0;
}
