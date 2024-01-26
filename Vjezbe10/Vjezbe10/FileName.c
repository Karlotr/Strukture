#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _ListNode;
typedef struct _ListNode* PositionNode;
typedef struct _ListNode {
    char cityName[50];
    int numCitizens;
    PositionNode next;
} ListNode;

struct _BinaryTreeNode;
typedef struct _BinaryTreeNode* PositionTreeNode;
typedef struct _BinaryTreeNode {
    char countryName[50];
    PositionTreeNode left;
    PositionTreeNode right;
    PositionNode head;
} TreeNode;

PositionTreeNode readCountryNames(PositionTreeNode root);
PositionTreeNode insertCountry(PositionTreeNode root, char* countryName);
PositionNode insertCity(char* fileName);
int insertIntoList(PositionNode Head, int numOfCitizens, char* cityName);
PositionTreeNode search(PositionTreeNode root, char* countryName);
int inorder(PositionTreeNode root);
int printList(PositionNode Head);

int main() {
    PositionTreeNode root = NULL;

    root = readCountryNames(root);

    inorder(root);

    return 0;
}

PositionTreeNode readCountryNames(PositionTreeNode root) {
    FILE* filePointer = fopen("countries.txt", "r");
    if (!filePointer) {
        printf("Unable to open the countries file.\n");
        return NULL;
    }

    char countryName[50] = "", fileName[50] = "";
    fscanf(filePointer, " %s %s", countryName, fileName);
    root = insertCountry(root, countryName);

    PositionNode head = insertCity(fileName);
    root->head = head;

    while (!feof(filePointer)) {
        fscanf(filePointer, " %s %s", countryName, fileName);
        PositionTreeNode currentCountry = insertCountry(root, countryName);

        PositionNode head = insertCity(fileName);
        currentCountry->head = head;
    }
    fclose(filePointer);
    return root;
}

PositionTreeNode insertCountry(PositionTreeNode root, char* countryName) {
    if (root == NULL) {
        PositionTreeNode newElement = (PositionTreeNode)malloc(sizeof(TreeNode));
        if (newElement == NULL) {
            printf("Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
        else {
            strcpy(newElement->countryName, countryName);
            newElement->left = NULL;
            newElement->right = NULL;
            newElement->head = NULL;
        }
        root = newElement;
    }
    else if (strcmp(countryName, root->countryName) < 0) {
        root->left = insertCountry(root->left, countryName);
    }
    else if (strcmp(countryName, root->countryName) > 0) {
        root->right = insertCountry(root->right, countryName);
    }
    return root;
}

PositionNode insertCity(char* fileName) {
    FILE* filePointer = fopen(fileName, "r");
    if (!filePointer) {
        printf("Unable to open the city file: %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    ListNode Head = { .cityName = "", .numCitizens = 0, .next = NULL };

    while (!feof(filePointer)) {
        char cityName[50] = "";
        int numOfCitizens = 0;
        fscanf(filePointer, " %s %d", cityName, &numOfCitizens);
        insertIntoList(&Head, numOfCitizens, cityName);
    }
    fclose(filePointer);
    return &Head;
}

int insertIntoList(PositionNode Head, int numOfCitizens, char* cityName) {
    PositionNode newElement = (PositionNode)malloc(sizeof(ListNode));
    if (!newElement) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(newElement->cityName, cityName);
    newElement->numCitizens = numOfCitizens;
    newElement->next = NULL;

    if (Head->next != NULL) {
        while (Head->next != NULL && Head->next->numCitizens > numOfCitizens) {
            Head = Head->next;
        }
        newElement->next = Head->next;
        Head->next = newElement;
    }
    else {
        newElement->next = Head->next;
        Head->next = newElement;
    }
    return 0;
}

PositionTreeNode search(PositionTreeNode root, char* countryName) {
    if (root == NULL) {
        return NULL;
    }
    else if (strcmp(countryName, root->countryName) < 0) {
        root->left = search(root->left, countryName);
    }
    else if (strcmp(countryName, root->countryName) > 0) {
        root->right = search(root->right, countryName);
    }
    else if (strcmp(countryName, root->countryName) == 0) {
        return root;
    }
    return root;
}

int inorder(PositionTreeNode root) {
    if (root != NULL) {
        inorder(root->left);
        printf(" %s", root->countryName);
        inorder(root->right);
    }
    return 0;
}

int printList(PositionNode Head) {
    if (Head->next == NULL) {
        printf("Error: No cities available.\n");
        return -1;
    }
    else {
        PositionNode current = Head->next;
        while (current->next != NULL) {
            printf(" %s", current->cityName);
            current = current->next;
        }
    }
    return 0;
}
