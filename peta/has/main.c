#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#define N 4

pthread_mutex_t mutex;
int broj_jela = 100;
char* hrana_na_stolu = NULL;

void spava(char* ime)
{
    printf("%s spava\n", ime);    
    if(strcmp(ime, "Tin"))
    {
        sleep(10 + rand() % 5);
    }
    else 
    {
        sleep(5 + rand() % 5);
    }
    return;
}

int programira(char* ime)
{
    printf("%s programira\n", ime);
    int rez = 1;
    int n = rand() % 10 + 1;
    for(int i = 2; i < n; i++){
        rez *= i;
    }
    return rez;
}

int provjera(char* ime, char* hrana) {
    if(strcmp(ime, "Tin"))
    {
        if(strcmp(hrana, "janjetina") || strcmp(hrana, "cevapi"))
            return -1;
        return 1; 
    }   
    if(strcmp(ime, "Davor"))
    {
        if(strcmp(hrana, "cokolada") || strcmp(hrana, "keksi"))
            return -1;
        return 1; 
    }
    if(strcmp(ime, "Ivan"))
    {
        if(strcmp(hrana, "strukle"))
            return -1;
        return 1; 
    }
    if(strcmp(ime, "Ivica"))
    {
        if(strcmp(hrana, "kelj") || strcmp(hrana, "grah"))
            return -1;
        return 1; 
    }
    return -1;
}

void jede(char* ime, int* jede, int* hrana_odbijena, int* prazan_stol)
{
    char* hrana;
    pthread_mutex_lock(&mutex);
    hrana = hrana_na_stolu;
    if(hrana == NULL)
    {
        (*prazan_stol)++;
        pthread_mutex_unlock(&mutex);
        return;
    }

    if(provjera(ime, hrana))
    {
        (*jede)++;
        broj_jela--;
        hrana_na_stolu = NULL;
        printf("%s jede %s broj jela: %d\n", ime, hrana, broj_jela);
    } else
    {
        (*hrana_odbijena)++;
        printf("%s odbija %s broj jela: %d\n", ime, hrana, broj_jela);
    }
    pthread_mutex_unlock(&mutex);
    return;
}

void vozi_auto_na_servis(char* ime)
{
    printf("%s vozi auto na servis\n", ime);
    if(!strcmp(ime, "Tin"))
    {
        sleep(2  + rand() % 3); 
        return;
    }

    int post = rand() % 100 + 1;
    if(post <= 20)
        sleep(2);
    if(post <= 25)
        sleep(4);
    return;
}

void gleda_TV(char* ime) 
{
    printf("%s gleda Tv\n", ime);
    sleep(2 + rand() % 3);
}

void igra_tenis(char* ime) 
{
    printf("%s igra tenis\n", ime);
    sleep( 2 + rand() % 3);
}

void slusa_sviranje_klavira(char* ime)
{
    printf("%s slusa sviranje klavira\n", ime);
    sleep( 2 + rand() % 3);
}

void* ciklus_Tin(void* param)
{
    int has = 0, hrana_odbijena = 0, stol_prazan = 0;
    char* ime = (char*) param;
    printf("Ime iz thread %s\n", ime);
    while(1) {
        spava(ime);
        programira(ime);
        jede(ime, &has, &hrana_odbijena, &stol_prazan);
        vozi_auto_na_servis(ime);
        pthread_mutex_lock(&mutex);
        if(broj_jela == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);
    }
    printf("%s je jeo: %d, odbio je harnu: %d, stol je bio prazan: %d\n",ime, has, hrana_odbijena, stol_prazan);
    pthread_exit(NULL);
}

void* ciklus_Davor(void* param)
{
    int has = 0, hrana_odbijena = 0, stol_prazan = 0;
    char* ime = (char*) param;
    printf("Ime iz thread %s\n", ime);
    while(1) {
        spava(ime);
        jede(ime, &has, &hrana_odbijena, &stol_prazan);
        programira(ime);
        gleda_TV(ime);
        pthread_mutex_lock(&mutex);
        if(broj_jela == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);
    }
    printf("%s je jeo: %d, odbio je harnu: %d, stol je bio prazan: %d\n",ime, has, hrana_odbijena, stol_prazan);
    pthread_exit(NULL);
}

void* ciklus_Ivica(void* param)
{
    int has = 0, hrana_odbijena = 0, stol_prazan = 0;
    char* ime = (char*) param;
    printf("Ime iz thread %s\n", ime);
    while(1) {
        spava(ime);
        igra_tenis(ime);
        jede(ime, &has, &hrana_odbijena, &stol_prazan);
        programira(ime);
        pthread_mutex_lock(&mutex);
        if(broj_jela == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);
    }
    printf("%s je jeo: %d, odbio je harnu: %d, stol je bio prazan: %d\n",ime, has, hrana_odbijena, stol_prazan);
    pthread_exit(NULL);
}
void* ciklus_Ivan(void* param)
{
    int has = 0, hrana_odbijena = 0, stol_prazan = 0;
    char* ime = (char*) param;
    printf("Ime iz thread %s\n", ime);
    while(1) {
        spava(ime);
        slusa_sviranje_klavira(ime);
        jede(ime, &has, &hrana_odbijena, &stol_prazan);
        programira(ime);
        pthread_mutex_lock(&mutex);
        if(broj_jela == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);
    }
    printf("%s je jeo: %d, odbio je harnu: %d, stol je bio prazan: %d\n",ime, has, hrana_odbijena, stol_prazan);
    pthread_exit(NULL);
}

char* kuha(char *jela[])
{
    sleep(rand() % 2 + 1);
    char* jelo = jela[rand() % 8];
    printf("Kuharica kuha %s\n", jelo);
    return jelo;
}

void stavlja_jelo_na_stol(char* jelo)
{
    while(1)
    {
        sleep(rand() % 2 + 1);
        pthread_mutex_lock(&mutex);
        if(hrana_na_stolu == NULL)
        {
            printf("Kuharica staljva %s na stol\n", jelo);
            hrana_na_stolu = jelo;
            pthread_mutex_unlock(&mutex);
            return;
        }
        pthread_mutex_unlock(&mutex);
        printf("Kuharica ceka\n");
    }
}

void* kuharica(void* n)
{
    int kolicina_hrane = (int) n;
    char *jela[] = {"cokolada", "cevapi", "janjetina", "strukle", "grah", "keksi", "kelj", "jabuka"};

    printf("Kuharia kuha %d jela\n", kolicina_hrane);
    for(int i = 0; i < kolicina_hrane; i++)
    {
        stavlja_jelo_na_stol(kuha(jela));
    }
    printf("Kuharica gotova s kuhanjem\n");
    pthread_exit(NULL);
}

int main()
{
    pthread_mutex_init(&mutex,NULL);
    pthread_t opisnik[N + 1];
    pthread_create(&opisnik[0], NULL, &kuharica,(void*) broj_jela);
    pthread_create(&opisnik[1], NULL, &ciklus_Davor, "Davor\0");
    pthread_create(&opisnik[2], NULL, &ciklus_Ivica, "Ivica\0");
    pthread_create(&opisnik[3], NULL, &ciklus_Ivan, "Ivan\0");
    pthread_create(&opisnik[4], NULL, &ciklus_Tin, "Tin\0");

    for(int i = 0; i < N + 1; i++) {
        pthread_join(opisnik[i], NULL);
    }
    return 0;
}
