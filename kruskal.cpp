#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<windows.h>
#include<math.h>
int inputg_int(int x,int y,char s[]="integer"){
    char ch;
    char name[100];
    int i=0;
    int sign=1;
    do{
        ch=getch();
        if(int(ch)==8){
                if(i>0)
            name[--i]='\0';
        else
            sign=1;
        }
        if(int(ch)>=48 && int(ch)<=57){
                name[i++]=ch;
                name[i]='\0';
                if(name[0]=='0')i--;
        }
        outtextxy(x,y,"                                                   ");
        if(((ch=='-' && i==0) || sign==-1) && s!="whole"){
            outtextxy(x,y,"-");
            sign=-1;
        }
        outtextxy(x+20,y,name);
    }while(int(ch)!=13 && int(ch)!=32);
    if(s=="whole")
        sign=1;
    return atoi(name)*sign;
}
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
int is_valid_point(int x_pos[],int y_pos[],int cmx,int cmy,int x,int r=2){
    for(int i=0;i<x;i++){
        if(pow(x_pos[i]-cmx,2)+pow(y_pos[i]-cmy,2)<r*r){
            return i;
        }
    }
    return -1;
}
int main(){
    initwindow(1400, 1000,"GUI");
    settextstyle(4,0,2);
    int V,E;
    setcolor(YELLOW);
    rectangle(10,10,1350,250);
    rectangle(14,14,1346,246);
    setcolor(GREEN);
    outtextxy(100,100,"Enter the no. of vertices: ");
    setcolor(RED);
    V=inputg_int(500,100);
    setcolor(GREEN);
    outtextxy(100,130,"Enter the No of Edges: ");
    setcolor(RED);
    E=inputg_int(500,130);
    cleardevice();
    int n=V,i=0;
    int pos_x[V],pos_y[V];
    char name[200];
    setcolor(RED);
    line(0,201,1500,201);
    while(true){
        POINT P;
        setcolor(RED);
        sprintf(name,"Enter position of %d Vertices ...",n);
        outtextxy(100,100,name);
        GetCursorPos(&P);
        if(GetAsyncKeyState(VK_LBUTTON)){
            pos_x[i]=P.x;
            pos_y[i++]=P.y;
            n--;
            setcolor(YELLOW);
            circle(P.x-8,P.y-28,6);
            if(i==V){
                break;
            }
            delay(200);
        }
    }
    struct Graph* G=create_graph(V,E);
    int src,dest,weight;
    Edge *edges=(Edge *)(malloc(sizeof(Edge)*E));
    n=E;
    int s,e;
    i=0;
    delay(200);
    setfillstyle(5,GREEN);
    bar(0,0,1500,200);
    while(true){
            setcolor(RED);
            POINT P;
            GetCursorPos(&P);
            setcolor(RED);
            sprintf(name,"Edge %d :",i+1);
            setcolor(GREEN);
            outtextxy(100,50,name);
            sprintf(name,"Select Source of edge: ");
            outtextxy(100,80,name);
            if(GetAsyncKeyState(VK_LBUTTON)){
                s=is_valid_point(pos_x,pos_y,P.x,P.y,V,8);
            delay(300);
                if(s!=-1){
                    setcolor(BLUE);
                    circle(pos_x[s]-8,pos_y[s]-28,7);
                    setcolor(RED);
                    sprintf(name,"(%d,%d)",pos_x[s],pos_y[s]);
                    outtextxy(500,80,name);
                    delay(300);
                    sprintf(name,"Select Destination of edge : ");
                    outtextxy(800,80,name);
                    while(true){
                        GetCursorPos(&P);
                        if(GetAsyncKeyState(VK_LBUTTON)){
                            e=is_valid_point(pos_x,pos_y,P.x,P.y,V,8);
                            if(e!=-1 and e!=s){
                                break;
                            }
                            delay(300);
                        }
                    }
                    setcolor(BLUE);
                    circle(pos_x[e]-8,pos_y[e]-28,7);
                    setcolor(RED);
                    sprintf(name,"(%d,%d)",pos_x[e],pos_y[e]);
                    outtextxy(1200,80,name);
                    setcolor(RED);
                    line(pos_x[s]-8,pos_y[s]-28,pos_x[e]-8,pos_y[e]-28);
                    src=s;dest=e;
                    sprintf(name,"Enter Weight of This Edge : ");
                    outtextxy(200,110,name);
                    weight=inputg_int(600,110);
                    sprintf(name,"[%d]",weight);
                    outtextxy((pos_x[s]+pos_x[e])/2-8,(pos_y[s]+pos_y[e])/2-28,name);
                    setfillstyle(5,GREEN);
                    bar(0,0,1500,200);
                    Edge *edge=create_edge(src,dest,weight);
                    insert(edges,*edge,i);
                    i++;
                    setcolor(BLACK);
                    circle(pos_x[s]-8,pos_y[s]-28,7);
                    circle(pos_x[e]-8,pos_y[e]-28,7);
                    setcolor(RED);
                    if(i>=E)
                        break;
                }
            }

    }
    G->edge_list=edges;
    Edge X;
    int size=G->E;
    struct subset *subsets=(struct subset *)(malloc(sizeof(struct subset)*(G->V)));
    for(i=0;i<V;i++){
        subsets[i].parent=i;
        subsets[i].rank=0;
    }
    Edge *result=(Edge *)(malloc(sizeof(Edge)*((G->V)-1)));
    i=0;
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
    }
    if(i!=(G->V)-1){
            cleardevice();
            sprintf(name,"Sorry MST couldn't be found. Specify proper edges");
            outtextxy(350,300,name);
    }
    else {
        cleardevice();
        setfillstyle(2,GREEN);
        bar(0,0,1500,200);
        sprintf(name,"The edges in the MST are:\n");
        outtextxy(100,100,name);
        for(i=0;i<(G->V)-1;i++){
                    setcolor(BLUE);
                    circle(pos_x[result[i].src]-8,pos_y[result[i].src]-28,7);
                    circle(pos_x[result[i].dest]-8,pos_y[result[i].dest]-28,7);
                    setcolor(GREEN);
                    line(pos_x[result[i].src]-8,pos_y[result[i].src]-28,pos_x[result[i].dest]-8,pos_y[result[i].dest]-28);
                    setcolor(YELLOW);
                    sprintf(name,"[%d]",result[i].weight);
                    outtextxy((pos_x[result[i].src]+pos_x[result[i].dest])/2-8,(pos_y[result[i].src]+pos_y[result[i].dest])/2-28,name);
                    delay(300);
        }
    }
    getch();
    closegraph();
    return 0;
}
