#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include "structura.h"

#define file_name "file.bin"

void del_n(char* str) {
    char* pn = strchr(str, '\n');
    if (pn != NULL) {
        *pn = '\0';
    }
}

int check_FIO(char* s) {
    int flag = 0;
    char sim[] = "123457890!@#$%^&*()-_`~/?{}[]|:;',=+\\\t";
    size_t len = strlen(s);
    size_t len_sim = strlen(sim);
    for (int i = 0; i < len_sim; i++) {
        for (int j = 0; j < len; j++) {
            if (sim[i] == s[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            break;
        }
    }
    return flag;
}

int check_main(char* s) {
    int flag = 0;
    char sim[] = "!@#$%^&*()-_`~/?{}[]|:;',=+\\ёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ<>üöäß0§ÜÖÄ\tqwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    size_t len = strlen(s);
    size_t len_sim = strlen(sim);
    for (int i = 0; i < len_sim; i++) {
        for (int j = 0; j < len; j++) {
            if (sim[i] == s[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            break;
        }
    }
    return flag;
}

book_info create_book() {
	book_info new_book;
	printf("---------------------------------------\n");

    printf("Input author's name: ");
    fgets(new_book.author.NAME, 10, stdin);
    
    if (strlen(new_book.author.NAME) == 9) {
        printf("\nThere was an error in the entered data\n");
        exit(1);
    }
    else {
        del_n(new_book.author.NAME);
    }
    printf("Input author's surname: ");
    fgets(new_book.author.surname, 10, stdin);

    if (strlen(new_book.author.surname) == 9) {
        printf("\nThere was an error in the entered data\n");
        exit(1);
    }
    else {
        del_n(new_book.author.surname);
    }
    printf("Input author's otchestvo: ");
    fgets(new_book.author.otch, 10, stdin);

    if (strlen(new_book.author.otch) == 9) {
        printf("\nThere was an error in the entered data\n");
        exit(1);
    }
    else {
        del_n(new_book.author.otch);
    }

    // Input title

	printf("Input title of book: ");
	fgets(new_book.name, 30, stdin);
    if (strlen(new_book.name) == 29) {
        printf("\nThere was an error in the entered data\n");
        exit(1);
    }
    else {
        del_n(new_book.name);
    }

    // Input house

	printf("Input publishing house of book: ");
	fgets(new_book.redaction, 30, stdin);
    if (strlen(new_book.redaction) == 29) {
        printf("\nThere was an error in the entered data\n");
        exit(1);
    }
    else {
        del_n(new_book.redaction);
    }

    // Input year

	printf("Input the year of publishing of book: ");
    fgets(new_book.year, 30, stdin);
    int year = atoi(new_book.year);
    if (strlen(new_book.year) == 29) {
        printf("\nThere was an error in the entered data\n");
        exit(1);
    }
    else {
        
        int flag = check_main(new_book.year);
        if (flag == 1) {
            printf("\nThere was an error in the entered data\n");
            exit(1);
        }
        else {

            if (year == 0 || year > 2024) {
                printf("\nThere was an error in the entered data\n");
                exit(1);
            }
            else {
                del_n(new_book.year);
            }
        } 
    }

    // Input page

    printf("Input number of pages in book: ");
    fgets(new_book.page, 30, stdin);
    int page = atoi(new_book.page);
    if (strlen(new_book.page) == 29) {
        printf("\nThere was an error in the entered data\n");
        exit(1);
    }
    else {
        int flag = check_main(new_book.page);
        if (flag == 1) {
            printf("\nThere was an error in the entered data\n");
            exit(1);
        }
        else {
            if (page == 0) {
                printf("\nThere was an error in the entered data\n");
                exit(1);
            }
            else {
                del_n(new_book.page);
            }
        }
    }
	return new_book;
}

void add_book(book_info book) {
	FILE* f = fopen(file_name, "ab");
	if (!f) {
	    printf("Error when opening a file: %s\n", file_name);
	    return;
	}
	fwrite(&book, sizeof(book_info), 1, f);
	printf("Book added\n");
	fclose(f);
}

void file_out() {
    FILE* f = fopen(file_name, "rb");
    if (!f) {
        printf("Error when opening a file: %s\n", file_name);
        return;
    }


    int flag = 1;
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    book_info book;
    puts("\n------------------------------------------------------------------------------------------------------------------------------------------");
    puts(" # | \tAuthor  \t\t     |\t   Title\t              |\t Publish house                 | Year of publish | Number of pages");

    

    fread(&book, sizeof(book_info), 1, f);
    for (int i = 1; flag && (i * sizeof(book_info) <= file_size); i++) {
        puts("------------------------------------------------------------------------------------------------------------------------------------------");
        printf(" %d |  %-10s%-10s%-10s | %-30s | %-30s |  %-14s |  %3s\n", i, book.author.NAME,book.author.surname,book.author.otch, book.name, book.redaction, book.year, book.page);
        fread(&book, sizeof(book_info), 1, f);
    }
    fclose(f);
    puts("------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void del_book() {

	FILE* f = fopen(file_name, "r+b"); 
	if (!f) {
		printf("Error when opening a file: %s\n", file_name);
		return;
	}
    file_out();
	puts("\nNumber of del book: ");
	char s[100];
	fgets(s, 100, stdin);
    int flag = check_main(s);
    
    if (flag) {
        printf("\nThere was an error in the entered data\n");
        return;
    }
    else {
        int n = atoi(s);
        fseek(f, 0, SEEK_END);
        long file_size = ftell(f);
        rewind(f);

        if (n > file_size / sizeof(book_info) || n <= 0) {
            puts("\nThere's no book by that number");
            fclose(f);
            return;
        }

        fseek(f, (n - 1) * sizeof(book_info), SEEK_SET);
        book_info book;
        while (!feof(f)) {
            printf("I work\n");
            fseek(f, sizeof(book_info), SEEK_CUR);
            if (!fread(&book, sizeof(book), 1, f)) { break; }
            fseek(f, (-2) * (long)sizeof(book_info), SEEK_CUR);
            fwrite(&book, sizeof(book_info), 1, f);
        }

        int desc = _fileno(f);
        _chsize(desc, file_size - sizeof(book_info));
        fclose(f);
        puts("Book deleted");
    }
}

void red_book() {
    FILE* f = fopen(file_name, "r+b");
    if (!f) {
        printf("Error when opening a file: %s\n", file_name);
        return;
    }
    file_out();
    printf("\nEnter number of book: ");
    char s[100];
    fgets(s, 100, stdin);
    int flag_1 = check_main(s);

    if (flag_1) {
        printf("\nThere was an error in the entered data\n");
        return;
    }
    else {
        int n, flag, shift;
        n = atoi(s);
        fseek(f, 0, SEEK_END);
        long file_size = ftell(f);
        rewind(f);
        if (n > file_size / sizeof(book_info) || n <= 0) { 
            puts("\nBook with this number dont exist"); 
            fclose(f); 
            return;
        }
        printf("Choose what to change\n1) Name\n2) Surname\n3) Otchestvo\n4) Title\n5) Publishing house\n6) Year of publishing\n7) Number of pages");
        printf("\nNumber: ");
        char s[100];
        fgets(s, 100, stdin);
        int flag_1 = check_main(s);
        if (flag_1) {
            printf("\nThere was an error in the entered data\n");
            return;
        }
        else {
            flag = atoi(s);
            switch (flag) {
            case 1:
                shift = 0;
                break;
            case 2:
                shift = 10;
                break;
            case 3:
                shift = 20;
                break;
            case 4:
                shift = 30;
                break;
            case 5:
                shift = 60;
                break;
            case 6:
                shift = 90;
                break;
            case 7:
                shift = 120;
                break;
            default:
                puts("Wrong value");
                return;
                break;
            }
            fseek(f, (n - 1) * sizeof(book_info) + shift, SEEK_SET);
            printf("New value: ");
            char new_value[30];
            char fio[10];
            if ((shift - 20) <= 0) {
                fgets(fio, 10, stdin);
                if (strlen(fio) == 9) {
                    printf("\nThere was an error in the entered data\n");
                    del_n(fio);
                    return;
                }
                else {
                    del_n(fio);
                    if (shift == 0 || shift == 10 || shift == 20) {
                        int flag = check_FIO(fio);
                        if (flag) {
                            printf("\nThere was an error in the entered data\n");
                            return;
                        }
                    }
                    fwrite(&fio, sizeof(fio), 1, f);
                    fclose(f);
                    puts("Change saved\n");
                }
            }
            else {
                fgets(new_value, 30, stdin);
                if (strlen(new_value) == 29) {
                    printf("\nThere was an error in the entered data\n");
                    del_n(new_value);
                    return;
                }
                else {
                    del_n(new_value);
                    if (shift == 0 || shift == 10 || shift == 20) {
                        int flag = check_FIO(new_value);
                        if (flag) {
                            printf("\nThere was an error in the entered data\n");
                            return;
                        }
                    }
                    else if (shift == 90) {
                        int flag = check_main(new_value);
                        if (flag) {
                            printf("\nThere was an error in the entered data\n");
                            return;
                        }
                    }
                    else if (shift == 120) {
                        int flag = check_main(new_value);
                        if (flag) {
                            printf("\nThere was an error in the entered data\n");
                            return;
                        }
                    }

                    fwrite(&new_value, sizeof(new_value), 1, f);
                    fclose(f);
                    puts("Change saved\n");
                }
            }
            
            
        }
            
    }
        
    
}

void search_book() {

    puts("\nChoose search criterion:");
    puts("1) Name\n2) Surname\n3) Otchestvo\n4) Title\n5) Publishing house\n6) Year of publishing\n7) Number of pages");

    printf("Number: ");
    int flag, shift;
    char s[100];
    fgets(s, 100, stdin);
    int flag_1 = check_main(s);

    if (flag_1) {
        printf("\nThere was an error in the entered data\n");
        return;
    }
    else {
        flag = atoi(s);
        switch (flag) {
        case 1:
            shift = 0;
            break;
        case 2:
            shift = 10;
            break;
        case 3:
            shift = 20;
            break;
        case 4:
            shift = 30;
            break;
        case 5:
            shift = 60;
            break;
        case 6:
            shift = 90;
            break;
        case 7:
            shift = 120;
            break;
        default:
            puts("Wrong value");
            return;
            break;
        }

        FILE* f = fopen(file_name, "rb");
        if (!f) {
            printf("Error when opening a file: %s\n", file_name);
            return;
        }

        int flag2 = 1;
        printf("The value you're looking for : ");
        char value[30];
        fgets(value, 30, stdin);
        del_n(value);
        puts("\n------------------------------------------------------------------------------------------------------------------------------------------");
        puts("\tAuthor  \t\t |\t   Title\t          |\t Publish house             | Year of publish | Number of pages");

        fseek(f, shift, SEEK_SET);
        char temp[30];
        while (!feof(f)) {
            if (!fread(&temp, 30, 1, f)) { break; }
            if (!strcmp(temp, value)) {
                fseek(f, -1 * (30 + shift), SEEK_CUR);
                book_info book;
                fread(&book, sizeof(book_info), 1, f);
                puts("------------------------------------------------------------------------------------------------------------------------------------------");
                printf("  %-10s%-10s%-10s | %-30s | %-30s |  %-14s |  %3s\n", book.author.NAME, book.author.surname, book.author.otch, book.name, book.redaction, book.year, book.page);
                fseek(f, shift, SEEK_CUR);
                flag2 = 0;
            }
            else { fseek(f, sizeof(book_info) - 30, SEEK_CUR); }
        }
        if (flag2) { 
            puts("\n\t\t\t    Not found");
        }
        fclose(f);
        puts("------------------------------------------------------------------------------------------------------------------------------------------\n");
    }

    
}

#define n 1
#if n == 1

void main() {
    int flag, ch;
	book_info new_book;
	while (1) {
        printf("\nChoose one of five actions:\n1) Add an entry to the file\n2) Delete an entry by entry sequence number\n3) Find a record by structure field\n4) Edit a given entry\n5) Output the file in tabular form\n6) Exit\nAction: ");
        char s[100];
        fgets(s, 100, stdin);
        int flag = check_main(s);
        if (flag) {
            printf("\nThere was an error in the entered data\n");
        }
        else {
                ch = atoi(s);
                switch (ch)
                {
                case 1: // Add book

                    new_book = create_book();
                    add_book(new_book);
                    break;

                case 2: // Delete book
                    del_book();
                    break;

                case 3: // Search book
                    search_book();
                    break;

                case 4: // Redaction
                    red_book();
                    break;

                case 5: // Out file
                    file_out();
                    break;

                case 6: // Exit
                    exit(0);
                default:
                    printf("\nThere was an error in the entered data\n");
                    return;
                    break;
                }
        }
        
	}
}

#elif n==2
void main() {
    FILE* f = fopen(file_name, "wb");
    book_info book_1 = { "Kochetkov","U", "U", "Algebra", "MIEM", "1997", "457" };
    book_info book_2 = { "Romanov", "A", "V","Matan","MIEM","1990", "1012" };
    book_info book_3 = { "Robert", "Grin", " ", "48 laws of power","Company 1", "2000", "630"};
    book_info book_4 = { "Stenli", " ", " ", "Combination", "Company 2", "1984", "239"};
    fwrite(&book_1, sizeof(book_info), 1, f);
    fwrite(&book_2, sizeof(book_info), 1, f);
    fwrite(&book_3, sizeof(book_info), 1, f);
    fwrite(&book_4, sizeof(book_info), 1, f);
    fclose(f);
}
#else
    puts("Неверное значение");
    return 0;
#endif
