#include <stdio.h>
#include <string.h>

#define MAX_ARG_LENGTH 100
#define MAX_NAME_LENGTH 100
#define MAX_PHONE_LENGTH 100
#define MAX_CONTACTS 42

bool is_numeric(char string[]);

int main(int argc, char *argv[]) {
    // check if the number of arguments is less than 2
    if (argc > 2) {
        fprintf(stderr, "Invalid number of arguments. 0-1 arguments allowed.\n");
        return 1;
    }

    char *search_pattern = nullptr;
    if (argc == 2) {
        search_pattern = argv[1];

        //check if the first arguments is not empty
        if (search_pattern[0] == '\0') {
            fprintf(stderr, "The first argument cannot be empty.\n");
            return 1;
        }

        //check if the first argument is numeric
        if (!is_numeric(search_pattern)) {
            fprintf(stderr, "The first argument must be numeric.\n");
            return 1;
        }

        //check if the argument length does not exceed the limit
        if (strlen(search_pattern) > MAX_ARG_LENGTH) {
            fprintf(stderr, "Argument is too long. 1-100 numbers allowed.\n");
            return 1;
        }
    }

    char name[MAX_NAME_LENGTH + 1];
    char phone[MAX_PHONE_LENGTH + 1];
    char loaded_char;
    bool loading_name = true;

    //TODO: vnorit do cyklu pro nacteni vice kontaktu
    for (int contact_n = 0; contact_n < MAX_CONTACTS; contact_n++) {
        for (int idx = 0; (loaded_char = getchar()) != -1; idx++) {
            printf("IDX: %d\n", idx);
            if (idx > MAX_NAME_LENGTH) {
                fprintf(stderr, "Name and phone must be 1-100 characters long.\n");
                return 1;
            }

            //loading name
            if (loading_name) {
                if (loaded_char == '\n') {
                    name[idx] = '\0';
                    idx = -1;
                    loading_name = false;
                    continue;
                }

                name[idx] = loaded_char;
                continue;
            }

            //loading phone
            if (loaded_char == '\n') {
                phone[idx] = '\0';
                loading_name = true;
                break;
            }
            phone[idx] = loaded_char;
        }

        //TODO: kontrolovat jestli je soubor ve spravnem formatu
        if (strlen(name) && strlen(phone)) {
            printf("%s, %s\n", name, phone);
        }
    }

    /*for (int idx = 0; (loaded_char = getchar()) != EOF; idx++) {
        if (idx > MAX_NAME_LENGTH) {
            fprintf(stderr, "Name and phone must be 1-100 characters long.\n");
            return 1;
        }

        //loading name
        if (loading_name) {
            if (loaded_char == '\n') {
                name[idx] = '\0';
                idx = -1;
                loading_name = false;
                continue;
            }

            name[idx] = loaded_char;
            continue;
        }

        //loading phone
        if (loaded_char == '\n') {
            phone[idx] = '\0';
            loading_name = true;
            break;
        }
        phone[idx] = loaded_char;
    }*/

    //TODO: kontrolovat jestli je soubor ve spravnem formatu
    /*if (strlen(name) && strlen(phone)) {
        printf("%s, %s\n", name, phone);
    }*/

    return 0;
}


bool is_numeric(char string[]) {
    for (int idx = 0; string[idx] != '\0'; idx++) {
        if (string[idx] < '0' || string[idx] > '9') {
            return false;
        }
    }
    return true;
}
