#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    char s1[100],s2[100];
    printf("Enter the binary string 1:\n");
    scanf("%s",&s1);
    int i;
    for(i=0;i<strlen(s1);i++){
        if(s1[i]!='0' && s1[i]!='1'){
            printf("1st string is invalid.Try again");
            return 0;
        }
    }
    printf("Enter the binary string 2:\n");
    scanf("%s",&s2);
    for(i=0;i<strlen(s2);i++){
        if(s2[i]!='0' && s2[i]!='1'){
            printf("2nd string is invalid.Try again");
            return 0;
        }
    }
    int j,k,z,carry;
    int s3[200],c;
    int prev[200];
    for(i=0;i<200;i++){
        prev[i]=2;
    }
    char s4[100];
    if(strlen(s2)>strlen(s1)){
        strcpy(s4,s1);
        strcpy(s1,s2);
        strcpy(s2,s4);
    }
    for(i=strlen(s2)-1;i>=0;i--)
    {
        k=0;
        for(j=0;j<(strlen(s2)-1)-i;j++){
            s3[j]=0;
            k+=1;
        }
        for(j=strlen(s1)-1;j>=0;j--)
        {
            char c1[2],c2[2];
            c1[0]=s1[j];
            c1[1]='\0';
            c2[0]=s2[i];
            c2[1]='\0';
            s3[k]=(atoi(c1)*atoi(c2));
            k++;
        }
        s3[k]=2;
        z=0;
        carry=0;
        while(z!=k){
                if(prev[z]==2){
                    prev[z]=s3[z]+carry;
                    carry=prev[z]/2;
                    prev[z]=prev[z]%2;
                }
                else{
                    prev[z]=s3[z]+carry+prev[z];
                    if(prev[z]==3){
                        prev[z]=1;
                        carry=1;
                    }
                    else if(prev[z]==2){
                        prev[z]=0;
                        carry=1;
                    }
                    else{
                        prev[z]=prev[z];
                        carry=0;
                    }
                }
                z++;
            }

        if(carry==1){
            prev[z]=1;
            prev[z+1]=2;
        }

        else{
            prev[z]=2;
        }
    }

    k=0;
    while(prev[k]!=2){
        k++;
    }
    k=k-1;
    printf("The binary multiplication of the two binary strings given above using brute force is :  ");
    while(k!=-1){
        printf("%d",prev[k]);
        k--;
    }
    return 0;
}
