#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdatomic.h>
#define N 100
int polje[N];
int bar[N];
atomic_int done = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void microsoft_oblak_auth(int brd){
    printf("microsoft_oblak_auth %d\n", brd);
    int vremenska_prognoza = rand() % 5 + 1;
    sleep(vremenska_prognoza);
    return;
}

int* diskta_u_atlanskom_oceanu(int brd) {
    printf("diskta_u_atlanskom_oceanu %d\n", brd);
    sleep(rand() % 3 + 1);
    return polje;
}

void ispis_aviona() {
    printf("     __|__\n__@__@(_)@__@__\n");
}

int odabir_stajaceg_mjesta(int brd) {
    printf("odabir_stajaceg_mjesta %d\n", brd);
    ispis_aviona();
    int odabir;
    int provjera = 1;
    do {
        odabir = rand() % 100;
        provjera = polje[odabir];
    } while(provjera == 1);
    return odabir;
}

int dali_korisnik_prihvaca_stajce_mejsto(int brd) {
    printf("dali_korisnik_prihvaca_stajce_mejsto %d\n", brd);
    return rand() % 2;
}

void spremanje_promjena_na_oblka(int indeks, int brd) {
    printf("spremanje_promjena_na_oblka %d\n", brd);
    int vrmeneska_prognoza = rand() % 1 + 1;
    sleep(vrmeneska_prognoza);
    polje[indeks] = 1;
}
void *Pozdrav(void *brojdretve)
{
    long brd;
    brd = (long) brojdretve;
    printf("\nPozdrav! to sam ja, dretva #%ld!\n", brd);
    
    microsoft_oblak_auth(brd);
    diskta_u_atlanskom_oceanu(brd);
    int indeks;
    pthread_mutex_lock(&mutex);
    do {
        indeks = odabir_stajaceg_mjesta(brd);
    }while(!dali_korisnik_prihvaca_stajce_mejsto(brd));
    spremanje_promjena_na_oblka(indeks, brd);
    pthread_mutex_unlock(&mutex);
    atomic_fetch_add(&done, 1);
    bar[brd] = 1;
    pthread_exit(NULL);
}

int korisnik_spojena_na_wifi() {
    return rand() % 1;
}

void* Postotak(void *d) 
{
    while (atomic_load(&done) < N) {
        printf("\r%d / %d done", atomic_load(&done), N);
    }
    printf("\r%d / %d done", atomic_load(&done), N);
    pthread_exit(NULL);
}

int main (int argc, char *argv[]){
    int broj_korisnika = N;
    int sto;
    long d = 0;
    //pthread_mutex_init(&mutex,NULL);
    pthread_t* opisnik = (pthread_t *)malloc(broj_korisnika * sizeof(pthread_t));
    pthread_t post;
    pthread_create(&post, NULL, Postotak, (void*)d);
    int last = 0;
    for(d=0; d<broj_korisnika; d++){
        printf("U main(): stvaranje dretve %ld\n", d);

        if(!korisnik_spojena_na_wifi()){
            sleep(1);
        }
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

    for(d=0; d<broj_korisnika; d++) {
        pthread_join(opisnik[d], NULL);
    }
    int broj_zazetih_stolica = 0;
    for(d = 0; d < broj_korisnika; d++) {
        if(polje[d] == 1){
         broj_zazetih_stolica++;
        }
    }
    printf("Broj zauzetih stolice: %d, Broj korinska: %d\n",broj_zazetih_stolica, broj_korisnika);
    /* Posljednja radnja main() */
    pthread_exit(NULL);
}
