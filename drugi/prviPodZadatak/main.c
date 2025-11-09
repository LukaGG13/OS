#include <stdio.h>
#include <stdlib.h>

char a[(int)1e5];

int main() {

    for(int i = 0; i < (int)1e5; i++) {
        if(rand() % 2){
            a[i] = 1;
        }
        else {
            a[i] = -1;
        }
    }
    for(int i = 0; i < (int)1e5; i++) {
        printf("%d" , a[i]);
    }
    while(1){}
    return 0;
}
