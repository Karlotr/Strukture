#define _CRT_SECURE_NO_WARNINGS
#define ERROR_FILE_OPEN (1)
#define ALLOCATION_ERROR (NULL)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u čvorove binarnog stabla.
//a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
//sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraća
//pokazivač na korijen stabla.
//b) Napisati funkciju replace koja će svaki element stabla zamijeniti sumom elemenata u
//njegovom lijevom i desnom podstablu(tj.sumom svih potomaka prije zamjene
//    vrijednosti u tim potomcima).Npr.stablo sa slike Slika 1 transformirat će se u stablo na
//    slici Slika 2.
//    c) Prepraviti program na način da umjesto predefiniranog cjelobrojnog polja korištenjem
//    funkcije rand() generira slučajne brojeve u rasponu <10, 90>.Također, potrebno je
//    upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
//    dijela zadatka.

typedef struct Node Node;
typedef Node* Position;
struct Node {
    int element;
    Position left;
    Position right;
};


Position insertElement(Position root, int newElement);
int replaceElements(Position root);
int writeInOrderToFile(Position root, FILE* file);

int main() {
    Position root = NULL;

    root = insertElement(root, 2);
    int elements[] = {5, 7, 8, 11, 1, 4, 2, 3, 7 };
    int numElements = sizeof(elements) / sizeof(elements[0]);

    for (int i = 0; i < numElements; i++) {
        root = insertElement(root, elements[i]);
    }

    FILE* file = fopen("data.txt", "w");
    writeInOrderToFile(root, file);
    fprintf(file, "\n");
    replaceElements(root);
    writeInOrderToFile(root, file);
    fclose(file);
    Position randRoot = NULL;
    srand(time(NULL));

    int x = 0;
    for (int i = 0; i < 8; i++) {
        x = rand() % 81 + 10;
        randRoot = insertElement(randRoot, x);
    }
    
    free(root);
    return 0;
}

Position insertElement(Position root, int newElement) {
    if (root == NULL) {
        Position newNode = (Position)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("Error allocating memory\n");
            return ALLOCATION_ERROR;
        }
        newNode->element = newElement;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (newElement >= root->element) {
        root->left = insertElement(root->left, newElement);
    }
    else {
        root->right = insertElement(root->right, newElement);
    }
    return root;
}

int replaceElements(Position root) {

    if (root == NULL) {
        return 0;
    }
    int originalElement = root->element;   
    root->element = replaceElements(root->left) + replaceElements(root->right);
    originalElement += root->element;

    return originalElement;
}

int writeInOrderToFile(Position root, FILE* file) {

    if (file == NULL) {
        printf("Error opening file\n");
        return ERROR_FILE_OPEN;
    }

    if (root == NULL) {
        return 0;
    }
    writeInOrderToFile(root->left, file);
    fprintf(file, "%d, ", root->element);
    writeInOrderToFile(root->right, file);

    return 0;
}