#define _CRT_SECURE_NO_WARNINGS
#define FILE_NOT_OPENED (-1)
#define MAX_LINE (1024)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct osoba Osoba;
typedef Osoba* Poz;
struct  osoba{
    char name[30],surname[30];
    int god;
    Poz next;
};

int Add(Poz P, char name[30],char surname[30],int god);
int Print(Poz P);
int AddEnd(Poz P, char name[30],char surname[30],int god);
Poz Find(Poz P, char surname[30]);
Poz FindPrev(Poz P, char surname[30]);
int Delete(Poz PrevLoc);
int DeletePerson(Poz P, char name[]);

int main(){
    Osoba Head;
    Head.next = NULL;

    Add(&Head, "toni", "radanovic", 2003);
    Add(&Head, "karlo", "trogrlic", 2003);
    AddEnd(&Head, "petar", "metar", 2003);
    Print(Head.next);

    return 0;
}

int DeletePerson(Poz P, char surname[]){
	Poz temp = FindPrev(Poz P, surname);
	Delete(temp);
	return 0;
}

int Delete(Poz P) {
     Poz temp;
     if (P != NULL)
     {
         temp = P->next;
         P->next = temp->next;
         free(temp);
     }

     return 0;
}

Poz Find(Poz P, char surname[30]){
    while (P != NULL && strcmp(P->surname, surname) != 0){
        P = P->next;
    }
    return P;
}

Poz FindPrev(Poz P, char surname[30]){
    while (P->next != NULL && strcmp(P->next->surname, surname) != 0){
         P = P->next;
     }
     if (P->next == NULL)
         return NULL;
     else
         return P;
}

int AddEnd(Poz P, char name[30],char surname[30],int god){
    Poz q;
    q = (Poz)malloc(sizeof(Osoba));
    strcpy(q->name, name);
    strcpy(q->surname, surname);
    q->god = god;

    while (P->next != NULL){
        P = P->next;
    }
    q->next = P->next;
    P->next = q;
}

int Add(Poz P, char name[30],char surname[30],int god){
    Poz q;
    q = (Poz)malloc(sizeof(Osoba));
    strcpy(q->name, name);
    strcpy(q->surname, surname);
    q->god = god;

    q->next = P->next;
    P->next = q;
}

int Print(Poz P){
    while(P != NULL){
        printf("\n---------------------------------------");
        printf("\n ime: %s\n prezime: %s\n god: %d", P->name, P->surname, P->god);
        P = P->next;
    }
}