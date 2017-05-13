#include <iostream>
#include <sys/time.h>
#include <stdio.h>
#include<math.h>
using namespace std;

void n2algo(long long int delay){
    long long int x=delay*delay;
    for(long long int i=1; i<=x; i++){
        x=x+1;
        x=x-1;
    }
}
void nalgo(long long int delay){
    long long int x=delay;
    for(long long int i=1; i<=x; i++){
        x=x+1;
        x=x-1;
    }
}
void nlognalgo(long long int delay){
    long long int x=delay*log(float(delay));
    for(long long int i=1; i<=x; i++){
        x=x+1;
        x=x-1;
    }
}



int main(void){
    clock_t start,endt;
    double elapsed;
    long long int n;
    printf("Enter N: ");
    scanf("%lld",&n);
    start=clock();
    nalgo(n);
    elapsed=(((double) (clock() - start)/ CLOCKS_PER_SEC));
    printf("Code executed in %lf seconds.\n", elapsed);
    start=clock();
    n2algo(n);
    endt=clock();
    elapsed=(((double) (endt - start)) / CLOCKS_PER_SEC);
    printf("Code executed in %lf seconds.\n", elapsed);
    start=clock();
    nlognalgo(n);
    endt=clock();
    elapsed=(((double) (endt - start)) / CLOCKS_PER_SEC);
    printf("Code executed in %lf seconds.\n", elapsed);


   return 0;
}
