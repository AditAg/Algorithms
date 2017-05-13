#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>
using namespace std;
typedef struct AdjacencyListNode{
    int dst;
    int weight;
    struct AdjacencyListNode* next;
}ALNode;

typedef struct AdjacencyList{
    ALNode *head;
}AL;

class Graph{
private:
    int V;
    int E;
    vector< AL* > edges_list;
public:
    Graph(int no_vertices,int no_edges){
        V=no_vertices;
        E=no_edges;
        for(int i=0;i<V;i++){
            AL *List =(AL *)(new AL);
            List->head=NULL;
            edges_list.push_back(List);
        }
    }
    bool add_edge(int src, int dest, int weight){
        if(src >=V || dest>=V) {
            cout<<"Sorry the vertices entered are wrong. They should be between 0 and "<< V-1 <<endl;
            return false;
        }
        int a=0;
        ALNode* ptr = edges_list[src]->head;
        while(ptr!=NULL){
            if(ptr->dst == dest){
                a=1;
                break;
            }
            ptr=ptr->next;
        }
        if(a==1){
            cout<<"Sorry the edge already exists"<<endl;
            return false;
        }
        ALNode *node = (ALNode *)(new ALNode);
        node->dst=dest;
        node->weight=weight;
        node->next=edges_list[src]->head;
        edges_list[src]->head = node;
        return true;
    }
    ALNode* get_edges(int index){
        return edges_list[index]->head;
    }
    int get_vertices(){
        return V;
    }
};
class Priority_Queue{
private:
    vector< pair<int,int> > distances;
public:
    void swap(pair<int,int> *a, pair<int,int> *b){
        pair<int,int> temp=*a;
        *a=*b;
        *b=temp;
    }
    void insert(int distance,int index){
        pair<int,int> p=make_pair(distance,index);
        distances.push_back(p);
        int lastindex=distances.size()-1;
        int parent=(lastindex-1)/2;
        pair<int,int> temp;
        while(parent>=0 && (distances[lastindex].first < distances[parent].first)){
            swap(&distances[lastindex],&distances[parent]);
            lastindex=parent;
            parent=(lastindex-1)/2;
        }
    }
    void percolate_down(){
        int child1,child2,i=0;
        while(true){
            child1=2*i+1;
            child2=2*i+2;
            if(child1>=distances.size())    return;
            if(child2>=distances.size()){
                if(distances[i].first>distances[child1].first){
                    swap(&distances[i],&distances[child1]);
                }
                return;
            }
            if(distances[i].first>distances[child1].first || distances[i].first > distances[child2].first){
                if(distances[child1].first <= distances[child2].first){
                    swap(&distances[i],&distances[child1]);
                    i=child1;
                }
                else{
                    swap(&distances[i],&distances[child2]);
                    i=child2;
                }
            }
            else{
                return;
            }
        }
    }
    pair<int,int> deletemin(){
        pair<int,int> minimum=distances[0];
        swap(&distances[0],&distances[distances.size()-1]);
        //cout<<distances[0].first<<"      "<<distances[0].second<<endl;
        distances.pop_back();
        //cout<<distances.size()<<endl;
        percolate_down();
        return minimum;
    }
    void bubbleup(int position){
        int index=position;
        int parent=(index-1)/2;
        while(parent>=0 && distances[parent].first > distances[index].first){
            swap(&distances[parent],&distances[index]);
            index=parent;
            parent=(index-1)/2;
        }
    }
    void decreaseKey(int index,int newdistance){
        for(int i=0;i<distances.size();i++){
            if(distances[i].second == index){
                distances[i].first=newdistance;
                bubbleup(i);
            }
        }
    }
    int length(){   return distances.size();   }
    vector< pair<int,int> > get_PQ(){   return distances;   }

};
class Dijkstra{
private:
    Graph* G;
    bool* visited;
    int* distance;
    int *parent;
    int src;
    Priority_Queue PQ;
public:
    Dijkstra(int source,Graph* graph){
        G=graph;
        src=source;
        visited = new bool[G->get_vertices()];
        distance=new int[G->get_vertices()];
        parent=new int[G->get_vertices()];
        for(int i=0;i<G->get_vertices();i++){
            parent[i]=-1;
            visited[i]=false;
            distance[i]=std::numeric_limits<int>::max();
        }
        distance[source]=0;
        parent[source]=0;
    }
    void shortest_paths(){
        for(int i=0;i<G->get_vertices();i++){
            PQ.insert(distance[i],i);
        }
        vector< pair<int,int> > heap;
        while(PQ.length()!=0){
            pair<int,int> minimum=PQ.deletemin();
            visited[minimum.second]=true;
            ALNode* ptr=G->get_edges(minimum.second);
            while(ptr!=NULL){
                int destination=ptr->dst;
                if(!visited[destination] && distance[destination] > (distance[minimum.second]+ ptr->weight)){
                    distance[destination]=distance[minimum.second]+ptr->weight;
                    parent[destination]=minimum.second;
                    PQ.decreaseKey(destination,distance[destination]);
                }
                ptr=ptr->next;
            }
        }
    }
    void print_distances(){
        for(int i=0;i<(G->get_vertices());i++){
            cout<<"The shortest path from vertex "<<src<<" to vertex "<<i<<" is :"<<endl;
            int j=i;
            while(parent[j]!=j){
                cout<<j<<" <- ";
                j=parent[j];
            }
            cout<<j<<endl;
            cout<<"The minimum distance between "<<src<<" and "<<i<<" is : "<<distance[i];
            cout<<endl;
        }
    }
};

int main(){
    int V,E;
    cout<<"Enter the no. of vertices : ";
    cin>>V;
    cout<<"Enter the no. of edges : ";
    cin>>E;
    Graph G= Graph(V,E);
    int i=0,src,dest,weight;
    cout<<"Enter the edges"<<endl;
    while(i<E){
        cout<<"Enter source of "<<i+1 <<"th edge :";
        cin>>src;
        cout<<"Enter destination of "<<i+1 <<"th edge :";
        cin>>dest;
        cout<<"Enter weight of "<<i+1 <<"th edge :";
        cin>>weight;
        bool value=G.add_edge(src,dest,weight);
        if(value){
            i=i+1;
        }
    }
    Dijkstra DJ = Dijkstra(0,&G);
    DJ.shortest_paths();
    DJ.print_distances();
}
