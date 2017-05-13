#include<iostream>
#include<vector>
#include<utility>
using namespace std;
typedef vector<pair<double,double> > vv;
typedef pair<double,double> xx;
//remember to define datatypes as above we use typedef and not #define
vv merging(vv v1,vv v2){
    int i=0,j=0;
    vv v3;
    while(i<v1.size() && j<v2.size()){
        if(v1[i].first<v2[j].first){
            v3.push_back(v1[i]);
            i++;
        }
        else if (v1[i].first>v2[j].first){
            v3.push_back(v2[j]);
            j++;
        }
        else if (v1[i].second<v2[j].second){
            v3.push_back(v1[i]);
            i++;
        }
        else if (v1[i].second>v2[j].second){
            v3.push_back(v2[j]);
            j++;
        }
        else{
            cout<<"Two points are exactly same, considering only 1 of them....\n";
            v3.push_back(v1[i]);
            i++;
            j++;
        }
    }
    while(i<v1.size()){
        v3.push_back(v1[i]);
        i++;
    }
    while(j<v2.size()){
        v3.push_back(v2[j]);
        j++;
    }
    return v3;

}
vv mergesort(vv points){
    int x=points.size();
    if(x==1){
        return points;
    }
    vv firsthalf (points.begin(),(points.begin()+(x/2)));
    vv secondhalf((points.begin()+(x/2)),points.end());
    vv r1=mergesort(firsthalf);
    vv r2=mergesort(secondhalf);
    vv r3=merging(r1,r2);
    return r3;

}
vv hullmerge(vv x1,vv x2){
    xx ymaxright=x2[0];
    xx yminright=x2[0];
    xx ymaxleft=make_pair(x1[0].first,x1[0].second);
    xx yminleft=make_pair(x1[0].first,x1[0].second);
    for(int i=0;i<x1.size();i++){
        if(ymaxleft.second<=x1[i].second){
            ymaxleft.first=x1[i].first;
            ymaxleft.second=x1[i].second;
        }
        if(yminleft.second>=x1[i].second){
            yminleft.first=x1[i].first;
            yminleft.second=x1[i].second;
        }
    }
    for(int i=0;i<x2.size();i++){
        if(ymaxright.second<=x2[i].second){
            ymaxright.first=x2[i].first;
            ymaxright.second=x2[i].second;
        }
        if(yminright.second>=x2[i].second){
            yminright.first=x2[i].first;
            yminright.second=x2[i].second;
        }
    }
    /*cout<<yminleft.first<<" "<<yminleft.second<<endl;
    cout<<ymaxleft.first<<" "<<ymaxleft.second<<endl;
    cout<<yminright.first<<" "<<yminright.second<<endl;
    cout<<ymaxright.first<<" "<<ymaxright.second<<endl;*/
    vv r1;
    vv r2;
    for(int i=0;i<x1.size();i++){
        if((x1[i].first>=ymaxleft.first && x1[i].second>=x1[x1.size()-1].second && x1[i].second<ymaxleft.second) || (x1[i].first>=yminleft.first && x1[i].second<=x1[x1.size()-1].second && x1[i].second>yminleft.second)){
            continue;
        }
        else{
            r1.push_back(x1[i]);
        }
    }
    for(int i=0;i<x2.size();i++){
        if((x2[i].first<=ymaxright.first && x2[i].second>=x2[0].second && x2[i].second<ymaxright.second) || (x2[i].first<=yminright.first && x2[i].second<=x2[0].second && x2[i].second>yminright.second)){
            continue;
        }
        else{
            r2.push_back(x2[i]);
        }
        //if(x1[i].first>=yminleft.first && x1[i].second<=x1[x1.size()-1].second && x1[i].second>yminleft.second){
          //  x1.erase(x1.begin()+i);
        //}
    }
    vv r3;
    for(int i=0;i<r1.size();i++){
        r3.push_back(r1[i]);
    }
    for(int i=0;i<r2.size();i++){
        r3.push_back(r2[i]);
    }
    return r3;


}
vv convexhull(vv points){
    if(points.size()==3 || points.size()==2)
    {
        return points;
    }
    vv firsthalf(points.begin(),(points.begin()+(points.size()/2)));
    vv secondhalf((points.begin()+(points.size()/2)),points.end());
    vv r1=convexhull(firsthalf);
    vv r2=convexhull(secondhalf);
    vv r3=hullmerge(r1,r2);
    return r3;

}
int main(){
    int N;
    cout<<"Enter how many points do you want to have?";
    vv points;
    cin>>N;
    double x,y;
    for(int i=0;i<N;i++){
        cout<<"Enter the "<<i+1<<"th point:\n";
        cout<<"x-coordinate:";
        cin>>x;
        cout<<"y-coordinate:";
        cin>>y;
        points.push_back(make_pair(x,y));
    }
    points= mergesort(points);
    vv result=convexhull(points);
    for(int i=0;i<result.size();i++){
        cout<<result[i].first<<" "<<result[i].second<<endl;
    }
    return 0;
}
