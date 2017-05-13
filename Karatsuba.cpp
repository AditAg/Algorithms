#include<iostream>
#include<string>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<algorithm>

using namespace std;
string sum(string s1,string s2){
    string s3;
    //2nd Way is to first make both the strings of equal length and then add them so that the
    //x1 = x2  and they reach -1 at same time..
    int carry=0,x1=s1.length()-1;
    int x2=s2.length()-1,z;
    while(x1!=-1 && x2!=-1){
        z=carry+(s1[x1]-'0')+(s2[x2]-'0');
        if(z==3){
            s3.push_back('1');
            carry=1;
        }
        else if(z==2){
            s3.push_back('0');
            carry=1;
        }
        else if(z==1){
            carry=0;
            s3.push_back('1');
        }
        else{
            carry=0;
            s3.push_back('0');
        }
        x1--;
        x2--;
    }
    while(x2!=-1){
        z=(s2[x2]-'0')+carry;
        if(z==2){
            s3.push_back('0');
            carry=1;
        }
        else if(z==1){
            s3.push_back('1');
            carry=0;
        }
        else{
            s3.push_back('0');
            carry=0;
        }
        x2--;
    }
    while(x1!=-1){
        z=(s1[x1]-'0')+carry;
        if(z==2){
            s3.push_back('0');
            carry=1;
        }
        else if(z==1){
            s3.push_back('1');
            carry=0;
        }
        else{
            s3.push_back('0');
            carry=0;
        }
        x1--;
    }
    if(carry==1){
        s3.push_back('1');
    }
    reverse(s3.begin(),s3.end());
    return s3;
}
string twoscomplement(string s2){
    int i=s2.length()-1;
    while(i!=-1){
        if(s2[i]=='1'){
            s2[i]='0';
        }
        else{
            s2[i]='1';
        }
        i--;
    }
    string s3;
    s3.push_back('1');
    string s4=sum(s2,s3);
    return s4;
}
string diff(string s1,string s2){
    //This difference function is not general.It is when s1>s2 which is the case in Karatsuba.
    //To generalize just put the condn in the else portion instead of 'x'
    string s3,s4;
    if(s2.length()<s1.length()){
        int i=s1.length()-s2.length();
        while(i>0){
            s2='0'+s2;
            i--;
        }
    }
    s4=twoscomplement(s2);
    if(s4.length()>s2.length()){
        s4=s4.substr(1);
    }
    s3=sum(s1,s4);
    int i=0;
    if(s3.length()>s1.length()){
    while(i<s3.length()){
        s3[i]=s3[i+1];
        i++;
    }
    }
    else{
        s3='x'+s3;
    }
    return s3;
}
string karatsuba(string s1,string s2){
    if(s1.length()==1 && s2.length()==1){
        string s3;
        int z=((s1[0]-'0')*(s2[0]-'0'));
        if(z==0){
            s3.push_back('0');
        }
        else s3.push_back('1');
        return s3;
    }
    else if(s2.length()==1){
        if(s2[0]=='0') return s2;
        else           return s1;
    }
    else if(s1.length()==1){
        if(s1[0]=='0') return s1;
        else           return s2;

    }
    string s3,s4,s5;
    int i;
    if(s1.length()>s2.length()){
        for(i=0;i<(s1.length()-s2.length());i++){
            s5.push_back('0');
        }
        s2=s5+s2;
    }
    int fh,sh;
    if(s1.length()%2==0){
        fh=s1.length()/2;
        sh=s1.length()-fh;
    }
    else{
        fh=(s1.length()/2)+1;
        sh=s1.length()-fh;
    }
    s3=s1.substr(fh,sh);
    s1=s1.substr(0,fh);
    s4=s2.substr(fh,sh);
    s2=s2.substr(0,fh);
    string s6,s7,s8,s9,s10;
    s6=(karatsuba(s1,s2));
    s7=(karatsuba(s3,s4));
    s8=sum(s1,s3);
    s9=sum(s2,s4);
    s8=karatsuba(s8,s9);
    s9=sum(s6,s7);
    s10=diff(s8,s9);
    int l1=2*s3.length();
    i=0;
    while(i<l1){
        s6.push_back('0');
        i++;
    }
    i=0;
    s10=s10.substr(0,s10.length()-1);
    while(i<s3.length()){
        s10.push_back('0');
        i++;
    }
    string result=sum(s6,s7);
    result=sum(result,s10);
    return result;
}

int main(){
    string s1,s2;
    printf("Enter the binary string 1:\n");
    cin>>s1;
    for(int i=0;i<s1.length();i++){
        if(s1[i]!='0' && s1[i]!='1'){
            printf("1st string is invalid.Try again");
            return 0;
        }
    }
    printf("Enter the binary string 2:\n");
    cin>>s2;
    for(int i=0;i<s2.length();i++){
        if(s2[i]!='0' && s2[i]!='1'){
            printf("2nd string is invalid.Try again");
            return 0;
        }
    }
    if(s2.length()>s1.length()){
        s1.swap(s2);
    }
    string s3;
    s3=karatsuba(s1,s2);
    cout<<"The binary multiplication of the 2 binary numbers using Divide & Conquer Algorithm(Karatsuba Algorithm) is:"<<s3;
    return 0;

}
