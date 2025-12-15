#include<stdio.h>
#include<stdlib.h>

int zbroj = 0;
int main(int argc, char** argv) 
{
    if (argc < 2)
    {
        printf("Unesi n\n");
        return -1;
    }

    int n = atoi(argv[1]);
    for (int i = 0; i < n; i++)
    {
        pid_t pid = fork();
        if(pid != 0)
        {
        } 
        else 
        {
            printf("inc\n");
            zbroj++;
            exit(0);
        }
        wait(NULL);
    }
    printf("Ocekivani broj %d, stvarni broj %d, razlika %d\n", n, zbroj, n - zbroj);

    return 0;
}
