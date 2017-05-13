#include<iostream>
#include<vector>
#include<utility>
#include<graphics.h>
#include<windows.h>
#include<stdio.h>
using namespace std;
typedef vector<pair<double,double> > vv;
typedef pair<double,double> xx;
//remember to define datatypes as above we use typedef and not #define
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
int orientation(xx p,xx q,xx r){
    int value=(q.second-p.second)*(r.first-q.first)-(q.first-p.first)*(r.second-q.second);
    if(value==0) return 0;
    return (value>0)?1:2;
}
int main(){
    initwindow(1400, 1000,"GUI");
    settextstyle(4,0,2);
    int N;
    char name[200];
    setcolor(GREEN);
    sprintf(name,"Enter how many points do you want to have?");
    outtextxy(50,150,name);
    setcolor(RED);
    N=inputg_int(900,150);
    vv points;
    double x,y;
    cleardevice();
    int i=0;
    line(0,201,1500,201);
    while(true){
        POINT P;
        setcolor(RED);
        sprintf(name,"Points selected so far:");
        outtextxy(0,100,name);
        setcolor(BLUE);
        int z=350,y=100;
        settextstyle(3,0,1);
        for(int j=0;j<points.size();j++){
                if(j==points.size()-1){
                    sprintf(name,"(%d,%d)",(int)points[j].first,(int)points[j].second);
                }
                else  {sprintf(name,"(%d,%d),",(int)points[j].first,(int)points[j].second);}
                outtextxy(z,y,name);
                z=z+90;
                if(z>1200){
                    z=100;
                    y=130;
                }
        }
        if(i==N) {break;}
        settextstyle(4,0,2);
        setcolor(RED);
        sprintf(name,"Select the %d th point:",i+1);
        outtextxy(0,180,name);
        GetCursorPos(&P);
        if(GetAsyncKeyState(VK_LBUTTON)){
                x=(double)(P.x);
                y=(double)(P.y);
                points.push_back(make_pair(x,y));
                i=i+1;
                setcolor(YELLOW);
                circle(P.x-8,P.y-28,6);

                delay(200);
            }
    }
    points= mergesort(points);
    vector<int> indices;
    int pos=0,q;
    do{
        indices.push_back(pos);
        q=(pos+1)%N;
        for(int i=0;i<points.size();i++){
            if(orientation(points[pos],points[i],points[q])==2)
                q=i;
        }
        pos=q;
    }while(pos!=0);
    setcolor(BLUE);
    sprintf(name,"Convex Hull Points");
    outtextxy(1200,300,name);
    int r=330;
    for(i=0;i<indices.size()-1;i++){
        setcolor(BLUE);
        sprintf(name,"[%d,%d]",(int)points[indices[i]].first,(int)points[indices[i]].second);
        outtextxy(1200,r,name);
        r=r+30;
        circle(points[indices[i]].first-8,points[indices[i]].second-28,7);
        circle(points[indices[i+1]].first-8,points[indices[i+1]].second-28,7);
        setcolor(GREEN);
        line(points[indices[i]].first-8,points[indices[i]].second-28,points[indices[i+1]].first-8,points[indices[i+1]].second-28);
        delay(300);
    }
    setcolor(BLUE);
    sprintf(name,"[%d,%d]",(int)points[indices[i]].first,(int)points[indices[i]].second);
    outtextxy(1200,r,name);
    circle(points[indices[i]].first-8,points[indices[i]].second-28,7);
    circle(points[indices[0]].first-8,points[indices[0]].second-28,7);
    setcolor(GREEN);
    line(points[indices[i]].first-8,points[indices[i]].second-28,points[indices[0]].first-8,points[indices[0]].second-28);

    getch();
    closegraph();
    //sort(points.begin(),points.end());
    return 0;
}
