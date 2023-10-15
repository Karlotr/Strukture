#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* Napisati program koji prvo procita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamicki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i ucitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrzi ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/

typedef struct {
	char ime[20];
	char prezime[20];
	int bodovi;
}studenti;

int main()
{
	studenti* student;
	int brojStudenata = 0;

	student = (studenti*)malloc(sizeof(studenti) * 10);

	FILE* fp;
	fp = fopen("studenti.txt", "r");
	while (!feof(fp)) {
		if (fgetc(fp) == '\n') {
			brojStudenata++;
		}
	}
	printf("broj studenata je %d", brojStudenata);
	fclose(fp);
	free(student);
	return 0;
}