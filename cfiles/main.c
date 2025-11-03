#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv){
    if(argc < 4){
        printf("Error\n");
        return 1;
    }

    int bufferSize = atoi(argv[3]);
    //printf("Enter the size of buffer to test \n");
    //scanf("%d", &bufferSize);

    FILE* input = fopen(argv[1], "rb");
    if (input == NULL) {
        printf("Error %s file dosent exits", argv[1]);
        return 1;
    }
    FILE* output = fopen(argv[2], "wb");
    char buffer[bufferSize]; //TODO fix
    
    while(fread(buffer, bufferSize, 1, input) == 1) {
        fwrite(buffer, bufferSize, 1, output);
    }
    return 0;
}
