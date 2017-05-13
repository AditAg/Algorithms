#include<iostream>
#include<vector>
#include<stack>
#include<math.h>
#include<stdlib.h>
#define PI 3.14159265
using namespace std;
typedef vector < pair<double,double> > vp;
typedef pair<double,double> pa;
typedef pair< pair<double,double> ,int > xx;
int ymin(vp points){
    int k=0;
    for(int i=0;i<points.size();i++){
        if((points[i].second<points[k].second) || (points[i].second==points[k].second && points[i].first<points[k].first)){
            k=i;
        }
    }
    return k;
}
vp swap(vp points,int index){
    pa temp=points[0];
    points[0]=points[index];
    points[index]=temp;
    return points;
}
double polarangle(pa p0,pa p1){
    double x=(p1.first-p0.first);
    double y=(p1.second-p0.second);
    double angle;
    if(y==0 && x>=0)    angle=0;
    else if(y==0 && x<0)    angle=180;
    else if(x==0 && y>0)    angle=90;
    else if(x==0 && y<0)    angle=270;
    else if(x>0 && y>0)     angle=atan(y/x)*(180.0/PI);
    else if(x>0 && y<0)     angle=360.0+(atan(y/x)*(180.0/PI));
    else if(x<0 && y>0)     angle=180.0+(atan(y/x)*(180.0/PI));
    else if(x<0 && y<0)     angle=180.0+(atan(y/x)*(180.0/PI));
    return angle;
}
double distSq(pa p1, pa p2){
    return (p1.first - p2.first)*(p1.first - p2.first) +
          (p1.second - p2.second)*(p1.second - p2.second);
}
int compare(const void *p1,const void *p2){
    xx *p=(xx *)p1;
    xx *p0=(xx *)p2;
    if((p->first).first>(p0->first).first)         return 1;
    else if((p->first).first<(p0->first).first)    return -1;
    else if((p->first).second>(p0->first).second)  return 1;
    else                                       return -1;
}
int orientation(pa p,pa q,pa r){
    int value=(r.second-q.second)*(q.first-p.first)-(r.first-q.first)*(q.second-p.second);
    if(value==0) return 0;
    return (value>0)?2:1;
}
pa nexttotop(stack<pa> s){
    pa p=s.top();
    s.pop();
    pa res=s.top();
    s.push(p);
    return res;
}
vp gscan(vp points){
    vp convexhull;
    int index=ymin(points);
    pa p0=points[index];
    points=swap(points,index);
    double pangle;
    double distance;
    vector <xx> angles;
    for(int i=1;i<points.size();i++){
        pangle=polarangle(points[0],points[i]);
        distance=distSq(points[0],points[i]);
        angles.push_back(make_pair(make_pair(pangle,distance),i));
    }
    qsort(&angles[0],angles.size(),sizeof(xx),compare);
    vp points2;
    points2.push_back(points[0]);
    for(int i=0;i<angles.size();i++){
            if(i<angles.size()-1 && angles[i].first.first==angles[i+1].first.first){
                continue;
            }
        points2.push_back(points[angles[i].second]);
    }
    if(points2.size()<3) {
        cout<<"Convex Hull not possible...Only straight line is possible.\n";
        return points2;
    }
    for(int i=0;i<points2.size();i++)
        cout<<points2[i].first<<" "<<points2[i].second<<endl;
    cout<<endl;
    stack<pa> s;
    s.push(points2[0]);
    s.push(points2[1]);
    s.push(points2[2]);
    for(int i=3;i<points2.size();i++){
        while(orientation(nexttotop(s),s.top(),points2[i])!=2)
            s.pop();
        s.push(points2[i]);
    }
    while(s.size()!=0){
        convexhull.push_back(s.top());
        s.pop();
    }
    return convexhull;
}
int main(){
    int N;
    cout<<"Enter how many points do you want to have?";
    vp points;
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
    vp convexhull=gscan(points);
    for(int i=0;i<convexhull.size();i++){
        cout<<convexhull[i].first<<" "<<convexhull[i].second<<endl;
    }
    return 0;
}
