#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct Edge{
    int src,dest,weight;
}Edge;
struct Graph{
    int V;
    int E;
    Edge *edge_list;
};
struct Graph *create_graph(int V,int E){
    struct Graph *newGraph=(struct Graph *)(malloc(sizeof(struct Graph)));
    newGraph->V=V;
    newGraph->E=E;
    newGraph->edge_list=(Edge *)(malloc(sizeof(Edge)*E));
    return newGraph;
};
Edge *create_edge(int src, int dest,int weight){
    Edge *E=(Edge *)(malloc(sizeof(Edge)));
    E->src=src;
    E->dest=dest;
    E->weight=weight;
    return E;
}
void insert(Edge *E,Edge X,int size){
    E[size]=X;
    int parent=(size-1)/2;
    int index=size;
    Edge Z;
    while(parent>=0 && E[parent].weight>E[index].weight){
        Z=E[index];
        E[index]=E[parent];
        E[parent]=Z;
        index=parent;
        parent=(index-1)/2;
    }
}
void percolatedown(Edge *A,int size){
    int i=0;
    int child1=2*i+1;
    if(child1>=size)    return;
    Edge temp;
    int child2=2*i+2;
    if(child2>=size){
        if(A[i].weight>A[child1].weight){
            temp=A[child1];
            A[child1]=A[i];
            A[i]=temp;
        }
        return;
    }
    while(i<size &&(A[i].weight>A[child1].weight || A[i].weight>A[child2].weight)){
        if(A[child1].weight>A[child2].weight){
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
        if(child1>=size)    return;
        child2=2*i+2;
        if(child2>=size){
            if(A[i].weight>A[child1].weight){
                temp=A[child1];
                A[child1]=A[i];
                A[i]=temp;
            }
            return;
        }
    }
    return;
}
Edge deletemin(Edge *A,int size){
    Edge temp;
    temp=A[0];
    A[0]=A[size-1];
    A[size-1]=temp;
    size-=1;
    percolatedown(A,size);
    return temp;
}
struct subset{
    int parent;
    int rank;
};
int find(struct subset subsets[],int i){
    if(subsets[i].parent!=i)
        subsets[i].parent=find(subsets,subsets[i].parent);
    return subsets[i].parent;
}
void Union(struct subset subsets[],int x,int y){
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
int main(){
    int V,E,i,j;
    printf("Enter the no. of vertices:");
    scanf("%d",&V);
    printf("Enter the no. of edges:");
    scanf("%d",&E);
    int src,dest,weight;
    Edge *edges=(Edge *)(malloc(sizeof(Edge)*E));
    struct Graph *G=create_graph(V,E);
    for(i=0;i<E;i++){
        printf("Enter the %d th edge:\n",i+1);
        printf("Enter source:");
        scanf("%d",&src);
        printf("Enter destination of edge:");
        scanf("%d",&dest);
        printf("Enter weight of this edge:");
        scanf("%d",&weight);
        Edge *E=create_edge(src,dest,weight);
        insert(edges,*E,i);
    }
    G->edge_list=edges;
    struct subset *subsets=(struct subset *)(malloc(sizeof(struct subset)*V));
    for(i=0;i<V;i++){
        subsets[i].parent=i;
        subsets[i].rank=0;
    }
    Edge *result=(Edge *)(malloc(sizeof(Edge)*(G->V-1)));
    i=0,j=0;
    Edge *notMST=(Edge *)(malloc(sizeof(Edge)*(G->E)));
    Edge X;
    int size=G->E;
    while(i<(G->V)-1 && size>0){
        X=deletemin(G->edge_list,size);
        size-=1;
        int x=find(subsets,X.src);
        int y=find(subsets,X.dest);
        if(x!=y){
            result[i]=X;
            i=i+1;
            Union(subsets,x,y);
        }
        else{
            notMST[j]=X;
            j=j+1;
        }
    }
    while(size>0){
        X=deletemin(G->edge_list,size);
        size-=1;
        notMST[j]=X;
        j=j+1;
    }
    if(i!=(G->V)-1){
        printf("Sorry MST not found....Try again");
    }
    else{
        printf("The edges in the MST are : \n");
        int r;
        for(r=0;r<i;r++){
            printf("%d - %d with weight %d \n",result[r].src,result[r].dest,result[r].weight);
        }
        printf("\n");
        Edge Old,New;
        int weightincrease,minwinc=INT_MAX;
        struct subset *subset2=(struct subset *)(malloc(sizeof(struct subset)*(G->V)));
        while(j>0){
            for(r=0;r<G->V;r++){
                    subset2[r].parent=subsets[r].parent;
                    subset2[r].rank=subsets[r].rank;
            }
            for(r=0;r<G->V;r++){ printf("%d\n",subsets[r].parent);}
            result[i]=notMST[j-1];
            Union(subset2,find(subset2,result[i].src),find(subset2,result[i].dest));
            j=j-1;
            int maxweight=0,index=-1;
            r=0;
            while(r<i){
                int x=find(subset2,result[r].src);
                int y=find(subset2,result[r].dest);
                if(x==y){
                    if((x!=(result[r].src) && x!=(result[i].dest))):
                    {
                        if(result[r].weight>maxweight){
                        maxweight=result[r].weight;
                        index=r;
                    }
                    }
                }
                r++;
            }
            weightincrease=result[i].weight-result[index].weight;
            if(weightincrease<minwinc){
                minwinc=weightincrease;
                Old=result[index];
                New=result[i];
            }
         }
         printf("The edge to be replaced in MST is:\n");
         printf("Old Edge : %d - %d with weight %d \n",Old.src,Old.dest,Old.weight);
         printf("New Edge : %d - %d with weight %d \n",New.src,New.dest,New.weight);
    }
    return 0;
}
