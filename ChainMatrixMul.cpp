#include<iostream>
#include<vector>
#include<limits>
#define ll long long int
using namespace std;

void printParenthesis(vector<char> *Stack,int i,int j,int N, int **factor,char &name){
    if(i==j){
        (Stack)->push_back('(');
        (Stack)->push_back(name);
         name++;
        (Stack)->push_back(')');
        return;
    }
    (Stack)->push_back('(');
    printParenthesis(Stack,i,factor[i][j],N,factor,name);
    printParenthesis(Stack,factor[i][j]+1,j,N,factor,name);
    (Stack)->push_back(')');
    return;
}
int main(){
    int N;
    cout<<"Enter the no. of matrices you wish to enter : ";
    cin>>N;
    ll sizes[N+1];
    ll rows,columns;
    int j=0,i=0;
    while(i<N){
        cout<<"Enter the no. of rows of "<<i+1<<"th matrix: ";
        cin>>rows;
        cout<<"Enter the no. of columns of "<<i+1<<"th matrix: ";
        cin>>columns;
        if(i==0 && rows>0 && columns>0 ){
            sizes[j]=rows;
            j++;
            sizes[j]=columns;
            j++;
            i++;
        }
        else if(i>0 && rows!=sizes[j-1]){
            cout<<"Sorry the sizes of the matrices aren't compatible for multiplication....Try again\n";
            continue;
        }
        else{
            sizes[j]=columns;
            j++;
            i++;
        }
    }
    ll Costs[N][N];
    int **Factor;
    Factor=new int *[N];
    for(i=0;i<N;i++){
        Factor[i]=new int[N];
    }
    int length=0;
    while(length<N){
        for(i=0;i<(N-length);i++){
            int k,j=i+length,index;
            ll minimum=std::numeric_limits<int>::max();
            ll value;
            for(k=i;k<=(j-1);k++){
                value=Costs[i][k]+Costs[k+1][j]+(sizes[i]*sizes[k+1]*sizes[j+1]);
                if(value<minimum){
                    minimum=value;
                    index=k;
                }
            }
            if(i==j){   Costs[i][j]=0;
                        Factor[i][j]=-1;   }
            else    {   Costs[i][j]=minimum;
                        Factor[i][j]=index;}
        }
        length=length+1;
    }
    for(i=0;i<N;i++){
        for(int j=i;j<N;j++){
            cout<<"Cost["<<i<<"]["<<j<<"] = "<<Costs[i][j]<<"      and Factor["<<i<<"]["<<j<<"] = "<<Factor[i][j]<<endl;
        }
    }
    char name = 'A';
    vector < char > Stack;
    cout << "Optimal Parenthesization is : ";
    printParenthesis(&Stack,0, N-1,N,Factor,name);
    for(i=0;i<Stack.size();i++){
        cout<<Stack[i]<<" ";
    }
    cout<<endl;
    cout<< "The minimal cost of computing the above chain matrix multiplication is: "<<Costs[0][N-1]<<endl;
    return 0;
}
