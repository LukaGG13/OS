#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int zbroj = 0;

void *Pozdrav(void *brojdretve)
{
    zbroj++;
    long brd;
    brd = (long) brojdretve;
    printf("Pozdrav! to sam ja, dretva #%ld!\n", brd);
    pthread_exit(NULL);
}

int main (int argc, char *argv[]){
    int broj_dretvi;
    int sto;
    long d;
    //pthread_t opisnik[MAX];
    if(argc!=2){
        printf("Pogrešan broj argumenata --> %s <broj_dretvi>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    broj_dretvi=atoi(argv[1]);
    pthread_t* opisnik = (pthread_t *)malloc(broj_dretvi * sizeof(pthread_t));
    int last = 0;
    for(d=0; d<broj_dretvi; d++){
        printf("U main(): stvaranje dretve %ld\n", d);
        sto = pthread_create(&opisnik[d], NULL, Pozdrav, (void *)d);
        if (sto){
            printf("GRESKA; povratak iz pthread_create() je %d\n", sto);
            if (sto == 11) {
                for(;last <= d; last++) {
                    printf("zatvram dretvu: %d\n", last);
                    pthread_join(opisnik[last], NULL); 
                }
            } else {
                exit(EXIT_FAILURE);
            }
        }

    }
    for(d=last; d<broj_dretvi; d++) {
        pthread_join(opisnik[d], NULL);
    }
    /* Posljednja radnja main() */
    printf("%d %d\n", broj_dretvi, zbroj);
    pthread_exit(NULL);

}
