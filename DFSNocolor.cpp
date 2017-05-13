#include<iostream>
#include<vector>
using namespace std;
class Graph{
    int V;
    vector<int>* adjList;
    vector<int> TopSort;
public:
    Graph(int N){
        V=N;
        adjList = new vector<int>[N];
    }
    void addEdge(int src,int dest){
        adjList[src].push_back(dest);
    }
    void DFS_Util(int src,int visited[]);
    int get_vertices(){
        return V;
    }
    void DFS();
    void Top_Sort(){
        cout<<"Topological Sort is : "<<endl;
        for(int i=TopSort.size()-1;i>=0;i--){
            cout<<TopSort[i]<<" ";
        }
        cout<<endl;
    }
};
void Graph::DFS_Util(int src, int visited[]){
    visited[src]=1;
    cout<<src<<" ";
    vector<int>::iterator i;
    for(i=adjList[src].begin();i!=adjList[src].end();i++){
        if(visited[*i]==0){
            DFS_Util(*i,visited);
        }
    }
    TopSort.push_back(src);
}
void Graph::DFS(){
    int no_vertices = get_vertices();
    int *visited = new int[no_vertices];
    for(int i=0;i<no_vertices;i++){
        visited[i]=0;
    }
    for(int i=0;i<no_vertices;i++){
        if(visited[i]==0){
            DFS_Util(i,visited);
        }
    }
}
int main(){
    int N,E;
    cout<<"Enter the no. of vertices :";
    cin>>N;
    Graph G(N);
    cout<<"Enter the no. of edges :";
    cin>>E;
    int src,dest;
    for(int i=0;i<E;i++){
        cout<<"Enter source of edge "<<i+1<<" : ";
        cin>>src;
        cout<<"Enter destination of edge "<<i+1<<" : ";
        cin>>dest;
        G.addEdge(src,dest);
    }
    cout<<"The Depth-First Traversal of the graph is :\n";
    G.DFS();
    cout<<endl;
    G.Top_Sort();
    return 0;
}

