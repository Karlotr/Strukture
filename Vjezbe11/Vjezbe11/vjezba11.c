#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 11

struct City;
typedef struct City* CityPosition;
typedef struct City {
    char name[20];
    int residents;
    CityPosition right;
    CityPosition left;
} City;

struct Country;
typedef struct Country* CountryPosition;
typedef struct Country {
    char name[20];
    CityPosition city;
    CountryPosition next;
} Country;

int addCountry(CountryPosition countryHead, char* name, char* data);
int addCity(CityPosition p, char* data);
CityPosition insertCity(CityPosition p, char* name, int residents);
int countryPrint(CountryPosition countryHead);
int cityPrint(CityPosition p);
CountryPosition findCountry(CountryPosition countryHead, char* name);
int findCity(CityPosition p, int number);

int keyForCountry(char* nameCountry);

int main(void) {
    Country head = { .name = "", .city = NULL, .next = NULL };
    Country hash[N];

    FILE* file = NULL;
    char nameCountry[20];
    char dataCity[20];
    CountryPosition countryHead = NULL;
    int number = 0;
    CityPosition cityHead = NULL;
    int key = 0;
    int i = 0;

    for (i = 0; i < N; i++) {
        hash[i].city = NULL;
        hash[i].next = NULL;
        strcpy(hash[i].name, "");
    }

    file = fopen("countries.txt", "r");
    if (file == NULL) {
        perror("Couldn't open file\n");
        return -1;
    }
    while (!feof(file)) {
        fscanf(file, "%s %s", nameCountry, dataCity);
        key = keyForCountry(nameCountry);
        addCountry(&hash[key], nameCountry, dataCity);
    }
    fclose(file);

    printf("Country list:\n");
    for (i = 0; i < N; i++) {
        countryPrint(hash[i].next);
    }
    printf("\n\n");

    printf("Enter the country you want to check: ");
    scanf("%s", nameCountry);
    key = keyForCountry(nameCountry);
    countryHead = findCountry(&hash[key], nameCountry);
    if (countryHead == NULL) {
        printf("That country doesn't exist.\n");
        return 0;
    }
    printf("Minimal number of residents: ");
    scanf("%d", &number);
    printf("\nCities from that country (%s) with more than %d residents:\n", countryHead->name, number);
    findCity(countryHead->city, number);

    return 0;
}

int addCountry(CountryPosition countryHead, char* name, char* data) {
    CountryPosition newElement = NULL;
    CountryPosition previous = NULL;
    CityPosition cityHead = NULL;

    newElement = (CountryPosition)malloc(sizeof(Country));
    if (newElement == NULL) {
        perror("Couldn't allocate memory\n");
        return -1;
    }
    strcpy(newElement->name, name);
    newElement->city = cityHead;

    cityHead = (CityPosition)malloc(sizeof(City));
    if (cityHead == NULL) {
        perror("Couldn't allocate memory\n");
        return -1;
    }
    strcpy(cityHead->name, "");
    cityHead->residents = 0;
    cityHead->right = NULL;
    cityHead->left = NULL;
    newElement->city = cityHead;
    addCity(newElement->city, data);

    previous = countryHead;
    while (countryHead != NULL) {
        if (countryHead->next == NULL) {
            countryHead->next = newElement;
            newElement->next = NULL;
            break;
        }
        if (strcmp(newElement->name, previous->next->name) < 0) {
            newElement->next = previous->next;
            previous->next = newElement;
            break;
        }
        previous = countryHead;
        countryHead = countryHead->next;
    }
    return 0;
}

int addCity(CityPosition city, char* data) {
    FILE* file = NULL;
    char name[20];
    int residents = 0;

    file = fopen(data, "r");
    if (file == NULL) {
        perror("Couldn't open file\n");
        return -1;
    }

    while (!feof(file)) {
        fscanf(file, "%s %d", name, &residents);
        city = insertCity(city, name, residents);
    }
    fclose(file);
    return 0;
}

CityPosition insertCity(CityPosition cityHead, char* name, int residents) {
    CityPosition newElement = NULL;
    if (cityHead == NULL) {
        newElement = (CityPosition)malloc(sizeof(City));
        if (newElement == NULL) {
            perror("Couldn't allocate memory\n");
            return NULL;
        }
        strcpy(newElement->name, name);
        newElement->residents = residents;
        newElement->left = NULL;
        newElement->right = NULL;
        return newElement;
    }
    if (residents > cityHead->residents)
        cityHead->right = insertCity(cityHead->right, name, residents);
    if (residents < cityHead->residents)
        cityHead->left = insertCity(cityHead->left, name, residents);
    if (residents == cityHead->residents) {
        if (strcmp(name, cityHead->name) >= 0)
            cityHead->right = insertCity(cityHead->right, name, residents);
        else
            cityHead->left = insertCity(cityHead->left, name, residents);
    }

    return cityHead;
}

int countryPrint(CountryPosition countryHead) {
    while (countryHead != NULL) {
        printf("\t%s\n", countryHead->name);
        cityPrint(countryHead->city->right);
        countryHead = countryHead->next;
    }
    return 0;
}

int cityPrint(CityPosition city) {
    if (city == NULL)
        return 0;
    cityPrint(city->left);
    printf("\t\t%s\n", city->name);
    cityPrint(city->right);
    return 0;
}

CountryPosition findCountry(CountryPosition countryHead, char* name) {
    while (countryHead != NULL) {
        if (strcmp(countryHead->name, name) == 0)
            return countryHead;
        countryHead = countryHead->next;
    }
    return countryHead;
}

int findCity(CityPosition city, int number) {
    if (city == NULL)
        return 0;
    findCity(city->left, number);
    if (city->residents >= number)
        printf("\t%s %d\n", city->name, city->residents);
    findCity(city->right, number);
    return 0;
}

int keyForCountry(char* nameCountry) {
    int key = 0;

    for (int i = 0; i < 5; i++)
        key += (int)nameCountry[i];

    return key % N;
}
