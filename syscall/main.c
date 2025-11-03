#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc, char** argv){
    if(argc < 4){
        printf("Error\n");
        return 1;
    }

    int bufferSize = atoi(argv[3]);

    int fdInput = open(argv[1], O_RDONLY);
    if (fdInput < 0) {
        printf("Error %s file dosent exits", argv[1]);
        return 1;
    }
    int fdOutput = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    char buffer[bufferSize]; //TODO fix
    
    int count;
    while(count = read(fdInput, buffer, bufferSize)) {
        write(fdOutput, buffer, count);
    }
    return 0;
}
