#include <stdio.h>
#include <string.h>

#define MAX_ARG_LENGTH 100
#define MAX_NAME_LENGTH 100
#define MAX_PHONE_LENGTH 100
#define MAX_CONTACTS 42

bool is_numeric_string(char string[]);

bool is_valid_name_char(char c);

int load_contact(char *name, char *phone, int name_length, int phone_length);

bool is_number(char c);

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
        if (!is_numeric_string(search_pattern)) {
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
    if (load_contact(name, phone, MAX_NAME_LENGTH, MAX_PHONE_LENGTH) == -1) {
        fprintf(stderr, "Failed to load contact.\n");
        return 1;
    }


    return 0;
}


bool is_numeric_string(char string[]) {
    for (int idx = 0; string[idx] != '\0'; idx++) {
        if (!is_number(string[idx])) {
            return false;
        }
    }
    return true;
}

bool is_alpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool is_number(char c) {
    return c >= '0' && c <= '9';
}


bool is_valid_name_char(char c) {
    if (!is_alpha(c) && !is_number(c)) {
        return c == ' ' || c == '.' || c == ',' || c == '-';
    }
    return true;
}

bool is_valid_phone_char(char c) {
    if (!is_number(c)) {
        return c == '+';
    }
    return true;
}

int load_contact(char *name, char *phone, int name_length, int phone_length) {
    char loaded_char;
    bool loading_name = true;
    for (int idx = 0; (loaded_char = getchar()) != EOF; idx++) {
        //loading name
        if (loading_name) {
            if (idx > name_length) {
                return -1;
            }

            if (loaded_char == '\n') {
                name[idx] = '\0';
                loading_name = false;
                //reset counter for phone loading
                idx = -1;
                continue;
            }

            if (!is_valid_name_char(loaded_char)) {
                return -1;
            }

            name[idx] = loaded_char;
            continue;
        }

        //loading phone
        if (idx > phone_length) {
            return -1;
        }

        if (loaded_char == '\n') {
            printf("test");
            phone[idx] = '\0';
            break;
        }

        if (is_valid_phone_char(loaded_char)) {
            if (loaded_char == '+' && idx != 0) {
                return -1;
            }
            phone[idx] = loaded_char;
            continue;
        }
        return -1;
    }
    return 0;
}
