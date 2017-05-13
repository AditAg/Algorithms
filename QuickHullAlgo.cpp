#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<math.h>
#include<graphics.h>
#include<windows.h>
#include<stdio.h>
using namespace std;
typedef vector<pair<double,double> > vv;
typedef pair<double,double> xx;
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
vv findhull(vv convexhull,vv s,xx p1,xx p2){
    if(s.size()==0){
        return convexhull;
    }
    int a,b,c;//ax+by+c=0
    a=p2.second-p1.second;
    b=p1.first-p2.first;
    c=(p1.second*p2.first)-(p1.first*p2.second);
    double distance=0.0,z=0.0;
    int index=0;
    for(int i=0;i<s.size();i++){
        int value=abs((int)((a*(s[i].first))+(b*(s[i].second))+c));
        z=(double)value/(sqrt(a*a+b*b));
        if(z>distance){
            distance=z;
            index=i;
        }
    }
    //int aa=find(convexhull.begin(),convexhull.end(),p2)-convexhull.begin();
    //convexhull.insert(convexhull.begin()+aa,s[index]);
    convexhull.push_back(s[index]);
    vv s1,s2;
    int a1,b1,c1,a2,b2,c2;
    //as earlier now we have 2 lines
    a1=s[index].second-p1.second;
    b1=p1.first-s[index].first;
    c1=(p1.second*s[index].first)-(p1.first*s[index].second);
    a2=p2.second-s[index].second;
    b2=s[index].first-p2.first;
    c2=(s[index].second*p2.first)-(s[index].first*p2.second);
    for(int i=0;i<s.size();i++){
        int value1=((a1*s[i].first)+(b1*s[i].second)+c1);
        int value2=(a2*s[i].first)+(b2*s[i].second)+c2;
        if(value1>0){
            s1.push_back(s[i]);
        }
        if(value2>0){
            s2.push_back(s[i]);
        }
    }
    convexhull=findhull(convexhull,s1,p1,s[index]);
    convexhull=findhull(convexhull,s2,s[index],p2);
    return convexhull;

}
vv quickhull(vv points){
    vv convexhull;
    int x=points.size()-1;
    convexhull.push_back(points[0]);
    convexhull.push_back(points[x]);
    vv s1,s2;
    //(y-y1)=((y2-y1)/(x2-x1))*(x-x1)
    //(y2-y1)x + (x1-x2)y +(y1(x2-x1)+x1(y1-y2))=0
    // (y2-y1)x + (x1-x2)y +(y1x2-x1y2)=0
    int a,b,c;//ax+by+c=0
    a=points[x].second-points[0].second;
    b=points[0].first-points[x].first;
    c=(points[0].second*points[x].first)-(points[0].first*points[x].second);
    //cout<<a<<" "<<b<<" "<<c<<endl;
    for(int i=1;i<points.size()-1;i++){
        int value=(a*points[i].first)+(b*points[i].second)+c;
        if(value>0){
            s2.push_back(points[i]);
        }
        else if(value<0){
            s1.push_back(points[i]);
        }
    }
    convexhull=findhull(convexhull,s2,points[0],points[x]);
    convexhull=findhull(convexhull,s1,points[x],points[0]);

    return convexhull;
}
int main(){
    initwindow(1500,1000,"Convex Hull");
    settextstyle(6,0,2);
    setfillstyle(10,GREEN);
    bar(0,0,10000,10000);
    char name[200];
    int N;
    while(true){
        setcolor(RED);
        outtextxy(100,100,"ENTER NUMBER OF POINTS :            ");
        try{
            setcolor(BLUE);
            N=inputg_int(550,100);
            throw N;
        }
        catch (int x){
            if(x<3){
                setcolor(RED);
                outtextxy(100,150,"VALUE MUST BE GREATER THAN EQUAL TO 3 AND INTEGER");
                outtextxy(100,180,"TRY AGAIN ...");
            }
            else{
                break;
            }
        }
    }
    vv points;
    double x,y;
    int i=0;
    cleardevice();
    setcolor(GREEN);
    settextstyle(6,0,2);
    setfillstyle(10,GREEN);
    bar(0,0,10000,200);
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
    sort(points.begin(),points.end());
    vv convexhull;
    convexhull=quickhull(points);
    int a,b,c,value;
    a=points[points.size()-1].second-points[0].second;
    b=points[0].first-points[points.size()-1].first;
    c=(points[0].second*points[points.size()-1].first)-(points[0].first*points[points.size()-1].second);
    vv pointsup,pointsdown;
    for(int i=2;i<convexhull.size();i++){
        value=(a*convexhull[i].first)+(b*convexhull[i].second)+c;
        if(value>0){ pointsup.push_back(convexhull[i]);}
        else if(value<0){ pointsdown.push_back(convexhull[i]);}
    }
    sort(pointsup.begin(),pointsup.end());
    sort(pointsdown.begin(),pointsdown.end());
    setfillstyle(10,GREEN);
    bar(0,0,1500,200);
    setcolor(RED);
    settextstyle(6,0,5);
    sprintf(name,"CONVEX HULL:\n");
    outtextxy(400,100,name);
    setcolor(BLUE);
    settextstyle(4,0,1);
    circle(convexhull[0].first-8,convexhull[0].second-28,7);
    sprintf(name,"(%d,%d)",(int)convexhull[0].first,(int)convexhull[0].second);
    outtextxy(convexhull[0].first-32,convexhull[0].second-20,name);
    circle(convexhull[1].first-8,convexhull[1].second-28,7);
    sprintf(name,"(%d,%d)",(int)convexhull[1].first,(int)convexhull[1].second);
    outtextxy(convexhull[1].first-32,convexhull[1].second-20,name);
    setcolor(RED);
    settextstyle(4,0,1);
    sprintf(name,"Convex Hull Points");
    outtextxy(1100,300,name);
    int r=330;
    for(int i=0;i<convexhull.size();i++){
        sprintf(name,"[%d,%d]",(int)convexhull[i].first,(int)convexhull[i].second);
        outtextxy(1100,r,name);
        r+=30;
    }

    settextstyle(6,0,2);
    setcolor(GREEN);
    if(pointsup.size()==0 && pointsdown.size()==0){
        cleardevice();
        setcolor(RED);
        outtextxy(100,150,"SORRY THE POINTS ARE COLLINEAR");
        outtextxy(100,180,"TRY AGAIN ...");
        getch();
        closegraph();
        return 0;
    }
    if(pointsup.size()==0){
        pointsup.push_back(convexhull[1]);
    }
    if(pointsdown.size()==0){
        pointsdown.push_back(convexhull[1]);
    }
    line(convexhull[0].first-8,convexhull[0].second-28,pointsup[0].first-8,pointsup[0].second-28);
    delay(300);
    line(convexhull[0].first-8,convexhull[0].second-28,pointsdown[0].first-8,pointsdown[0].second-28);
    delay(300);
    line(convexhull[1].first-8,convexhull[1].second-28,pointsup[pointsup.size()-1].first-8,pointsup[pointsup.size()-1].second-28);
    delay(300);
    line(convexhull[1].first-8,convexhull[1].second-28,pointsdown[pointsdown.size()-1].first-8,pointsdown[pointsdown.size()-1].second-28);
    delay(300);
    settextstyle(4,0,1);
    for(int i=0;i<pointsup.size()-1;i++){
        setcolor(BLUE);
        circle(pointsup[i].first-8,pointsup[i].second-28,7);
        sprintf(name,"(%d,%d)",(int)pointsup[i].first,(int)pointsup[i].second);
        outtextxy(pointsup[i].first-32,pointsup[i].second-20,name);
        circle(pointsup[i+1].first-8,pointsup[i+1].second-28,7);
        sprintf(name,"(%d,%d)",(int)pointsup[i+1].first,(int)pointsup[i+1].second);
        outtextxy(pointsup[i+1].first-32,pointsup[i+1].second-20,name);
        setcolor(GREEN);
        line(pointsup[i].first-8,pointsup[i].second-28,pointsup[i+1].first-8,pointsup[i+1].second-28);
        delay(300);
    }
    for(int i=0;i<pointsdown.size()-1;i++){
        setcolor(BLUE);
        circle(pointsdown[i].first-8,pointsdown[i].second-28,7);
        sprintf(name,"(%d,%d)",(int)pointsdown[i].first,(int)pointsdown[i].second);
        outtextxy(pointsdown[i].first-32,pointsdown[i].second-20,name);
        circle(pointsdown[i+1].first-8,pointsdown[i+1].second-28,7);
        sprintf(name,"(%d,%d)",(int)pointsdown[i+1].first,(int)pointsdown[i+1].second);
        outtextxy(pointsdown[i+1].first-32,pointsdown[i+1].second-20,name);
        setcolor(GREEN);
        line(pointsdown[i].first-8,pointsdown[i].second-28,pointsdown[i+1].first-8,pointsdown[i+1].second-28);
        delay(300);
    }
    getch();
    closegraph();
    return 0;
}
