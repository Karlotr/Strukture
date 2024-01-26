#define _CRT_SECURE_NO_WARNINGS
#define ALLOCATION_ERROR (NULL)
#define MAX_SIZE (128)
#define MAX_LINE (1024)
#define ERROR_FINDING_BOOK (NULL)
#define MAX_COPY 50


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Members;
typedef struct Members* members;

struct Book;
typedef struct Book* book;

typedef struct Members {
    char name[MAX_LINE];
    members members_next;
    book books[MAX_COPY];
}_Members;

typedef struct Book {
    char name[MAX_LINE];
    char author[MAX_LINE];
    int year_of_release;
    int copies;
    members members[MAX_COPY];
    book book_next;
}_Book;

///////////////////////////////////////////////
//////////////////////////////////////////////

int Add_Member(members Head, char name[MAX_LINE]);
int Remove_Member(members Head, char member_name[MAX_LINE]);

void Print_Members(members Head_next);
void Print_Books(members Head_next);

int Add_Book(members Head, char name[MAX_LINE], char author[MAX_LINE], int copies, int year);
int Return_Book(members Member, char book_name[MAX_LINE]);
int Borrow_Book(book Head_next,char book_name[MAX_LINE], int quanity);
int Add_Book_To_Player(members Member, book Book);
void Remove_Player_From_Book(book Book, members Member);

book Find_Book_By_Name(book Head_next, char book_name[MAX_LINE]);
members Find_Member_By_Name(members Head_next, char member_name[MAX_LINE]);

int Count_Taken_Books(book Book);
int Count_Member_Books(members Member);

int Search_Book_By_Year(book Head_next, int year);
int Search_Book_By_Author(book Head_next, char author[MAX_LINE]);

book Allocate_Book();
members Allocate_Member();

int Save_Library(members Head_Members_next, book Head_Books_next);
int Load_Library(members Head_Members, book Head_Books);

void Free_Books(book Head);
void Free_Members(members Head);

///////////////////////////////////////////////
//////////////////////////////////////////////


int main() {
    _Members Head_Members = { .name = {0}, .members_next = NULL};
    _Book Head_Books = { .name = {0}, .author = {0}, .copies = 0, .book_next = NULL, .year_of_release = 0 };

    Load_Library(&Head_Members,&Head_Books);

    while (1) {
        printf("\n  Menu:  \n");
        printf("1 - Add member\n");
        printf("2 - Print members\n");
        printf("3 - Add books\n");
        printf("4 - Print books\n");
        printf("5 - Find book\n");
        printf("6 - Find member\n");
        printf("7 - Choose member\n");
        printf("8 - Search books by year\n");
        printf("9 - Search books by author\n");
        printf("10 - Remove member\n");
        printf("11 - Save\n");
        printf("12 - Exit\n");




        char choice[10] = { 0 };
        printf("Enter your choice: ");
        scanf("%s", choice);

        if (strcmp(choice, "1") == 0) {
            char name[MAX_LINE] = { 0 };
            printf("\nEnter name of the member in this format: NAME_SURNAME: ");
            scanf("%s", name);
            Add_Member(&Head_Members, name);

        }
        else if (strcmp(choice, "2") == 0) {
            Print_Members(Head_Members.members_next);
        }

        else if (strcmp(choice, "3") == 0) {
            char name[MAX_LINE] = { 0 };
            char author[MAX_LINE] = { 0 };
            int year = 0;
            int copies = 0;
            printf("\nType the name of the book: ");
            scanf("%s", name);
            printf("Type the author name: ");
            scanf("%s", author);
            printf("Type year of creation: ");
            scanf("%d", &year);
            printf("Type number of copies: ");
            scanf("%d", &copies);
            if (year >= 0 && copies >= 0)
                Add_Book(&Head_Books, name, author, copies, year);
            else
                printf("Number of copies and year of creation musst be positive numbers");
        }
        else if (strcmp(choice, "4") == 0) {
            Print_Books(Head_Books.book_next);
        }
        else if (strcmp(choice, "5") == 0) {
            char book_name[MAX_LINE] = { 0 };
            printf("Type name of the book: ");
            scanf("%s", book_name);
            book Target = Find_Book_By_Name(Head_Books.book_next, book_name);
            if (!Target) {
                printf("\nBook not found!\n");
                continue;
            }
            int quantity = Count_Taken_Books(Target);
            printf("\nName: %s\nAuthor: %s\nAvailable: %d/%d\nYear: %d\nMembers that have it: \n", book_name, Target->author, Target->copies - quantity, Target->copies, Target->year_of_release);
            int count = Count_Taken_Books(Target);
            for (int i = 0; i < count; i++) {
                printf("%d -- %s\n", i + 1, Target->members[i]->name);
            }
        }

        else if (strcmp(choice, "6") == 0) {
            char member_name[MAX_LINE] = { 0 };
            printf("Type the name of the member: ");
            scanf("%s", member_name);
            members Target = Find_Member_By_Name(Head_Members.members_next, member_name);
            if (!Target) {
                printf("\nMember not found!\n");
                continue;
            }
            else {
                int quantity = Count_Member_Books(Target);
                printf("\nMember: %s\nBooks taken: %d\n", member_name, quantity);
                for (int i = 0; i < quantity; i++) {
                    printf("%s\n", Target->books[i]->name);
                }
                printf("\n");
            }
        }
        else if (strcmp(choice, "7") == 0) {
            char member_name[MAX_LINE] = { 0 };
            printf("Type the name of the member: ");
            scanf("%s", member_name);
            members Target = Find_Member_By_Name(Head_Members.members_next, member_name);
            if (!Target) {
                printf("\nMember not found!\n");
                continue;
            }
            else {
                while (1) {
                    printf("\nMember: %s \n", member_name);
                    printf("1 - Borrow the book\n");
                    printf("2 - Return the book\n");
                    printf("3 - Print player books\n");
                    printf("4 - Exit\n");

                    char choice2[10] = { 0 };
                    printf("Enter your choice: ");
                    scanf("%s", choice2);

                    if (strcmp(choice2, "1") == 0) {
                        char book_name[MAX_LINE] = {0};
                        printf("Type name of the the book:");
                        scanf("%s", book_name);
                        int qua = 0;
                        printf("Type number of copies:");
                        scanf("%d", &qua);
                        book Book_target = Find_Book_By_Name(Head_Books.book_next, book_name);
                        if (Book_target != NULL) {
                            Borrow_Book(Target, Head_Books.book_next, book_name, qua,Book_target);
                        }
                        else
                            printf("Book not found\n");
                    }
                    else if (strcmp(choice2, "2") == 0) {
                        char book_name[MAX_LINE] = {0};
                        printf("Choose book to return: ");
                        scanf("%s", book_name);
                        Return_Book(Target, book_name);
                    }
                    else if (strcmp(choice2, "3") == 0) {
                        int quantity = Count_Member_Books(Target);
                        if (quantity > 0)
                            printf("Books[%d]:\n",quantity);
                        else
                            printf("No books borrowed \n");
                        for (int i = 0; i < quantity; i++) {
                            printf("%s\n", Target->books[i]->name);
                        }
                        printf("\n");
                    }
                    else if (strcmp(choice2, "4") == 0) {
                        break;
                    }
                }
            }
        }
        else if (strcmp(choice, "8") == 0) {
            int num = 0;
            printf("Choose year to search: ");
            scanf("%d", &num);
            Search_Book_By_Year(Head_Books.book_next, num);
        }
        else if (strcmp(choice, "9") == 0) {
            char author[MAX_LINE] = { 0 };
            printf("Choose author to search: ");
            scanf("%s", author);
            Search_Book_By_Author(Head_Books.book_next, author);
        }
        else if (strcmp(choice, "10") == 0) {
            char member_name[MAX_LINE] = { 0 };
            printf("Choose member to remove: ");
            scanf("%s", member_name);
            Remove_Member(&Head_Members, member_name);
        }
        else if (strcmp(choice, "11") == 0) {
            Save_Library(Head_Members.members_next, Head_Books.book_next);
        }
        else if (strcmp(choice, "12") == 0) {
            Save_Library(Head_Members.members_next, Head_Books.book_next);
            Free_Members(&Head_Members);
            Free_Books(&Head_Books);
            return 0;
            }
        else {
            printf("\033[0;31mInvalid choice. Please enter a valid option.\033[0m\n");
        }
    }
}

int Add_Member(members Head, char name[MAX_LINE]) {
    members New_Member = Allocate_Member();
    if (!New_Member)
        return -1;
    strcpy(New_Member->name, name);

    if (Head->members_next == NULL || strcmp(name, Head->members_next->name) < 0) {
        New_Member->members_next = Head->members_next;
        Head->members_next = New_Member;
        return 0;
    }

    Head = Head->members_next;
    while (Head->members_next != NULL && strcmp(name, Head->members_next->name) > 0) {
        Head = Head->members_next;
    }

    New_Member->members_next = Head->members_next;
    Head->members_next = New_Member;

    return 0;

}

int Remove_Member(members Head, char member_name[MAX_LINE]) {
    members Target = Find_Member_By_Name(Head->members_next, member_name);
    if (Target == NULL) {
        printf("\nMember not found!\n");
        return -1;
    }

    int num = Count_Member_Books(Target);
    for (int i = 0; i < num; i++) {
        Return_Book(Target, Target->books[0]->name);
    }

    members prev = Head;
    while (prev->members_next != NULL && prev->members_next != Target) {
        prev = prev->members_next;
    }

    if (prev->members_next == Target) {
        prev->members_next = Target->members_next;
        free(Target);
        return 0;
    }
    else {
        return -1;
    }
}

void Print_Members(members Head_next) {
    if (Head_next == NULL) {
        printf("The list is empty.\n");
        return;
    }
    while (Head_next != NULL) {
        printf("\nMember: %s\nBorrowed books [%d]: \n", Head_next->name, Count_Member_Books(Head_next));
        int count = Count_Member_Books(Head_next);
        for (int i = 0; i < count; i++) {
            printf("%d -- %s\n", i + 1, Head_next->books[i]->name);
        }
        Head_next = Head_next->members_next;
    }
}

void Print_Books(book Head_next) {
    if (Head_next == NULL) {
        printf("The list is empty.\n");
        return;
    }

    while (Head_next != NULL) {
        printf("\nName: %s\nAuthor: %s\nYear: %d\nCopies: %d/%d\nMembers that have it [%d]:\n", Head_next->name, Head_next->author, Head_next->year_of_release, Head_next->copies- Count_Taken_Books(Head_next),Head_next->copies, Count_Taken_Books(Head_next));
        int count = Count_Taken_Books(Head_next);
        for (int i = 0; i < count; i++) {
            printf("%d -- %s\n", i + 1, Head_next->members[i]->name);
        }
        Head_next = Head_next->book_next;
    }
}

int Add_Book(book Head, char name[MAX_LINE], char author[MAX_LINE], int copies, int year) {
    book New_Book = Allocate_Book();
    if (!New_Book)
        return -1;
    strcpy(New_Book->name, name);
    strcpy(New_Book->author, author);
    New_Book->copies = copies;
    New_Book->year_of_release = year;

    if (Head->book_next == NULL || strcmp(name, Head->book_next->name) < 0) {
        New_Book->book_next = Head->book_next;
        Head->book_next = New_Book;
        return 0;
    }
    while (Head->book_next != NULL && strcmp(name, Head->book_next->name) > 0) {
        Head = Head->book_next;
    }
    New_Book->book_next = Head->book_next;
    Head->book_next = New_Book;

    return 0;
}

int Return_Book(members Member, char book_name[MAX_LINE]) {
    int counter = 0;

    while (Member->books[counter] != NULL && strcmp(Member->books[counter]->name, book_name) != 0)
        counter++;

    if (Member->books[counter] != NULL) {
        book Book = Member->books[counter];
        Remove_Player_From_Book(Book, Member);

        while (Member->books[counter + 1] != NULL) {
            Member->books[counter] = Member->books[counter + 1];
            counter++;
        }
        Member->books[counter] = NULL;
        printf("\nBook '%s' returned successfully.\n", book_name);
        return 0;
    }
    else {
        printf("\nBook '%s' not found\n", book_name);
        return -1;
    }
}

int Borrow_Book(members Member, book Head_next, char book_name[MAX_LINE], int quantity, book Target) {
    if (!Member || !Head_next) {
        printf("Incorrect Member");
        return -1;
    }

    if (Target == NULL)
        return -1;

    int borrowed = Count_Member_Books(Member);
    int maxtotake = Target->copies - Count_Taken_Books(Target);

    if ((borrowed + quantity) > 5) {
        printf("\nYou can only borrow %d more books\n", 5 - borrowed);
        return -1;
    }
    else if (quantity > maxtotake) {
        printf("\nYou are trying to take more books than there are available copies, if you want to take the maximum, enter 1, if you want to cancel enter 2:\n");

        int choice = 0;
        scanf("%d", &choice);

        if (choice == 1) {
            for (int i = 0; i < maxtotake; i++) {
                if (Add_Book_To_Player(Member, Target) != 0) {
                    printf("\nError adding book to player.\n");
                    return -1;
                }
            }
            printf("\nBooks successfully borrowed.\n");
        }
        else if (choice == 2) {
            return -1;
        }
        else {
            printf("\nIncorrect input. Returning to the menu.\n");
            return -1;
        }
    }
    else if (quantity <= maxtotake) {
        for (int i = 0; i < quantity; i++) {
            if (Add_Book_To_Player(Member, Target) != 0) {
                printf("\nError adding book to player.\n");
                return -1;
            }
        }
    }

    return 0;
}

int Add_Book_To_Player(members Member, book Book) {
    int count = 0;
    while (Member->books[count] != NULL)
        count++;
    Member->books[count] = Book;
    count = 0;
    while (Book->members[count] != NULL)
        count++;
    Book->members[count] = Member;
    return 0;
}

void Remove_Player_From_Book(book Book, members Member) {
    int counter = 0;

    while (Book->members[counter] != NULL && Book->members[counter] != Member)
        counter++;

    if (Book->members[counter] == Member) {
        while (Book->members[counter + 1] != NULL) {
            Book->members[counter] = Book->members[counter + 1];
            counter++;
        }
        Book->members[counter] = NULL;
    }
}

book Find_Book_By_Name(book Head_next, char book_name[MAX_LINE]) {
    while (Head_next != NULL && strcmp(book_name, Head_next->name) != 0)
        Head_next = Head_next->book_next;

    if (Head_next == NULL) {
        return ERROR_FINDING_BOOK;
    }

    return Head_next;
}

members Find_Member_By_Name(members Head_next, char member_name[MAX_LINE]) {
    while (Head_next != NULL && strcmp(member_name, Head_next->name) != 0)
        Head_next = Head_next->members_next;

    if (Head_next == NULL)
        return ERROR_FINDING_BOOK;

    return Head_next;
}

int Count_Taken_Books(book Book) {
    int count = 0;
    while (Book->members[count] != NULL) {
        count++;
    }
    return count;
}

int Count_Member_Books(members Member) {
    int count = 0;
    while (Member->books[count] != NULL) {
        count++;
    }
    return count;
}


int Search_Book_By_Author(book Head_next, char author[MAX_LINE]) {
    int count = 0;
    printf("\nBooks that are written by %s:\n", author);
    while (Head_next != NULL) {
        if (strcmp(author, Head_next->author) == 0) {
            printf("%d -- %s (%d/%d)\n", count + 1, Head_next->name, Head_next->copies - Count_Taken_Books(Head_next), Head_next->copies);
            count++;
        }
        Head_next = Head_next->book_next;
    }
    printf("Found %d book written by that author\n", count);
    return 0;
}

int Search_Book_By_Year(book Head_next, int year) {
    int count = 0;
    printf("\nBooks that are from year %d:\n", year);
    while (Head_next != NULL) {
        if (Head_next->year_of_release == year) {
            printf("%d -- %s (%d/%d)\n", count + 1, Head_next->name, Head_next->copies-Count_Taken_Books(Head_next), Head_next->copies);
            count++;
        }
        Head_next = Head_next->book_next;
    }
    printf("Found %d books with that year\n", count);
    return 0;
}

book Allocate_Book() {
    book To_Allocate = NULL;
    To_Allocate = (book)malloc(sizeof(_Book));
    if (!To_Allocate)
        return ALLOCATION_ERROR;
    strcpy(To_Allocate->name, "");
    strcpy(To_Allocate->author, "");
    To_Allocate->copies = 0;
    To_Allocate->year_of_release = 0;
    To_Allocate->book_next = NULL;

    for (int i = 0; i < MAX_COPY; ++i) {
        To_Allocate->members[i] = NULL;
    }

    return To_Allocate;
}
members Allocate_Member() {
    members To_Allocate = NULL;
    To_Allocate = (members)malloc(sizeof(_Members));
    if (!To_Allocate)
        return ALLOCATION_ERROR;
    strcpy(To_Allocate->name, "");
    To_Allocate->members_next = NULL;

    for (int i = 0; i < MAX_COPY; ++i) {
        To_Allocate->books[i] = NULL;
    }

    return To_Allocate;
}

int Save_Library(members Head_Members_next, book Head_Books_next) {
    FILE* file_members = fopen("Members.txt", "w");
    FILE* file_books = fopen("Books.txt", "w");

    if (file_members == NULL || file_books == NULL) {
        printf("Error opening file for writing.\n");
        return -1;
    }

    while (Head_Members_next != NULL) {
        fprintf(file_members, "#MEMBER\n%s\n", Head_Members_next->name);

        int Books = Count_Member_Books(Head_Members_next);
        for (int i = 0; i < Books; i++) {
            fprintf(file_members, "#BOOK\n%s\n", Head_Members_next->books[i]->name);
        }

        fprintf(file_members, "#ENDMEMBER\n");
        Head_Members_next = Head_Members_next->members_next;
    }

    while (Head_Books_next != NULL) {
        fprintf(file_books, "#BOOK\n%s\n%s\n%d\n%d\n\n", Head_Books_next->name, Head_Books_next->author, Head_Books_next->year_of_release, Head_Books_next->copies);
        Head_Books_next = Head_Books_next->book_next;
    }

    fclose(file_books);
    fclose(file_members);
    printf("Library saved successfully.\n");
    return 0;
}

int Load_Library(members Head_Members, book Head_Books) {
    FILE* file_members = fopen("Members.txt", "r");
    FILE* file_books = fopen("Books.txt", "r");

    if (file_members == NULL || file_books == NULL) {
        printf("Error opening file for reading.\n");
        return -1;
    }

    char marker[MAX_LINE] = {0};
    char member_name[MAX_LINE] = {0};

    while (fscanf(file_books, "%s", marker) == 1 && strcmp(marker, "") != 0) {
        if (strcmp(marker, "#BOOK") == 0) {
            char book_name[MAX_LINE] = {0};
            char author[MAX_LINE] = {0};
            int year = 0;
            int copies = 0;

            fscanf(file_books, "%s", book_name);
            fscanf(file_books, "%s", author);
            fscanf(file_books, "%d", &year);
            fscanf(file_books, "%d", &copies);

            Add_Book(Head_Books, book_name, author, copies, year);
        }
    }

    while (fscanf(file_members, "%s", marker) == 1 && strcmp(marker, "") != 0) {
        if (strcmp(marker, "#MEMBER") == 0) {
            fscanf(file_members, "%s", member_name);
            Add_Member(Head_Members, member_name);

            char book_name[MAX_LINE] = {0};
            while (fscanf(file_members, "%s", marker) == 1 && strcmp(marker, "#BOOK") == 0) {
                fscanf(file_members, "%s", book_name);
                book Book_target = Find_Book_By_Name(Head_Books, book_name);
                if (Book_target != NULL) {
                    members Member_target = Find_Member_By_Name(Head_Members, member_name);
                    Borrow_Book(Member_target, Head_Books, book_name, 1, Book_target);
                }
            }
        }
        else if (strcmp(marker, "#ENDMEMBER") == 0) {
        }
    }

    fclose(file_books);
    fclose(file_members);
    return 0;
}

void Free_Members(members Head) {
    members current = Head->members_next;
    members next;

    while (current != NULL) {
        next = current->members_next;
        free(current);
        current = next;
    }
}

void Free_Books(book Head) {
    book current = Head->book_next;
    book next;

    while (current != NULL) {
        next = current->book_next;
        free(current);
        current = next;
    }
}
