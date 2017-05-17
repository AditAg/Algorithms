#include <iostream>
#include <sys/time.h>
#include <stdio.h>
using namespace std;

void sleep(int delay){
    for(int i=1; i<=delay; i++)
        for(int j=1; j<=delay; j++)
            (i*j)%2;
}

float timedifference_msec(struct timeval t0, struct timeval t1){
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

int main(void){
   struct timeval t0;
   struct timeval t1;
   float elapsed;

   gettimeofday(&t0, 0);
   sleep(300);
   gettimeofday(&t1, 0);

   elapsed = timedifference_msec(t0, t1);

   printf("Code executed in %f milliseconds.\n", elapsed);

   return 0;
}
