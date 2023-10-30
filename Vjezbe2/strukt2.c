#define _CRT_SECURE_NO_WARNINGS

#define FILE_NOT_OPENED (-1)
#define MAX_LINE (1024)
#define MAX_SIZE (128)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct _Person;
typedef struct _Person* Poz;
typedef struct  _Person{
    char name[MAX_SIZE],surname[MAX_SIZE];
    int god;
    Poz next;
}_person;

int Add(Poz P, char name[MAX_SIZE],char surname[MAX_SIZE],int god);
//Dodavanje na pocetak
int Print(Poz P);
<<<<<<< HEAD
//Printanje cijele liste
int AddEnd(Poz P, char name[MAX_SIZE],char surname[MAX_SIZE],int god);
//Dodavanje na kraj
Poz Find(Poz P, char surname[MAX_SIZE]);
//Traženje po prezimenu
Poz FindPrev(Poz P, char surname[MAX_SIZE]);
//Traženje prethodnog po prezimenu
int DeleteByPosition(Poz PrevLoc);
//Brisanje unosom pozicije prethodnika
int DeletePerson(Poz P, char surname[MAX_SIZE]);
//Brisanje unosom prezimena
Poz AllocateMemory();
=======
int AddEnd(Poz P, char name[30],char surname[30],int god);
Poz Find(Poz P, char surname[30]);
Poz FindPrev(Poz P, char surname[30]);
int Delete(Poz PrevLoc);
int DeletePerson(Poz P, char name[]);
>>>>>>> 88c04baa85d17a935bcd251be8c40642b4467838

int main(){
    _person Head = { .next = NULL, .name = {0},.surname = {0}, .god = 0 };

    Add(&Head, "toni", "radanovic", 2003);
    Add(&Head, "karlo", "trogrlic", 2003);
    AddEnd(&Head, "petar", "metar", 2003);
    DeletePerson(&Head, "trogrlic");
    Print(Head.next);

    return 0;
}

<<<<<<< HEAD
Poz AllocateMemory(){
    Poz q = NULL;
    q = (Poz)malloc(sizeof(_person));
    if (!q){
        printf("Neuspješna alokacija memorije");
        return NULL;
    }
    return q;
}

int DeletePerson(Poz P, char surname[MAX_SIZE]){
    Poz temp = NULL;
    temp = FindPrev(P, surname);
        if (temp != NULL)
            DeleteByPosition(temp);
}

int DeleteByPosition(Poz P) {
=======
int DeletePerson(Poz P, char surname[]){
	Poz temp = FindPrev(Poz P, surname);
	Delete(temp);
	return 0;
}

int Delete(Poz P) {
>>>>>>> 88c04baa85d17a935bcd251be8c40642b4467838
     Poz temp;
     if (P != NULL)
     {
         temp = P->next;
         P->next = temp->next;
         free(temp);
     }

     return 0;
}

Poz Find(Poz P, char surname[MAX_SIZE]){
    while (P != NULL && strcmp(P->surname, surname) != 0){
        P = P->next;
    }
    return P;
}

Poz FindPrev(Poz P, char surname[MAX_SIZE]){
    while (P->next != NULL && strcmp(P->next->surname, surname) != 0){
         P = P->next;
     }
     if (P->next == NULL)
         return NULL;
     else
         return P;
}

int AddEnd(Poz P, char name[MAX_SIZE],char surname[MAX_SIZE],int god){
    Poz q = NULL;
    q = AllocateMemory();
    strcpy(q->name, name);
    strcpy(q->surname, surname);
    q->god = god;

    while (P->next != NULL){
        P = P->next;
    }
    q->next = P->next;
    P->next = q;
}

int Add(Poz P, char name[MAX_SIZE],char surname[MAX_SIZE],int god){
    Poz q = NULL;
    q = AllocateMemory();
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