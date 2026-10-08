#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_ARG_LENGTH 100
#define MAX_NAME_LENGTH 102
#define MAX_PHONE_LENGTH 102
#define MAX_CONTACTS 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
} Contact;

// T9 table used for converting lowercase ASCII letters to their corresponding T9 number
// Each index is calculated as the ASCII value of the letter minus the ASCII value of 'a'(97)
char t9_table[] = {
    '2', '2', '2', // a, b, c
    '3', '3', '3', // d, e, f
    '4', '4', '4', // g, h, i
    '5', '5', '5', // j, k, l
    '6', '6', '6', // m, n, o
    '7', '7', '7', '7', // p, q, r, s
    '8', '8', '8', // t, u, v
    '9', '9', '9', '9', // w, x, y, z
};

bool is_numeric_string(char *string) {
    for (int idx = 0; string[idx] != '\0'; idx++) {
        if (!isdigit(string[idx])) {
            return false;
        }
    }
    return true;
}

int load_contact(Contact *contact) {
    char *name = contact->name;
    char *phone = contact->phone;

    if (fgets(name, MAX_NAME_LENGTH, stdin) == NULL) {
        return -1;
    }
    if (fgets(phone, MAX_PHONE_LENGTH, stdin) == NULL) {
        return 1;
    }

    if (name[strlen(name) - 1] != '\n' || phone[strlen(phone) - 1] != '\n') {
        return 1;
    }

    name[strlen(name) - 1] = '\0';
    phone[strlen(phone) - 1] = '\0';

    if (strlen(name) == 0 || strlen(phone) == 0) {
        return 1;
    }

    return 0;
}


bool is_valid_contact(Contact *contact) {
    char *name = contact->name;
    char *phone = contact->phone;

    for (int idx = 0; name[idx] != '\0'; idx++) {
        if (!isprint((unsigned char)name[idx])) {
            return false;
        }
    }

    if (strlen(phone) == 1 && phone[0] == '+') {
        return false;
    }

    for (int idx = 0; phone[idx] != '\0'; idx++) {
        if (phone[idx] == '+' && idx == 0) {
            continue;
        }

        if (!isdigit((unsigned char)phone[idx])) {
            return false;
        }
    }
    return true;
}

void t9_string_to_num(char *string, char *destination) {
    int idx = 0;
    for (; string[idx] != '\0'; idx++) {
        char lowercase_char = tolower(string[idx]);
        if (lowercase_char == '+') {
            destination[idx] = '0';
            continue;
        }
        if (lowercase_char < 'a' || lowercase_char > 'z') {
            destination[idx] = string[idx];
            continue;
        }
        destination[idx] = t9_table[lowercase_char - 'a'];
    }
    destination[idx] = '\0';
}

bool is_match(Contact *contact, char *pattern) {
    if (pattern == nullptr) {
        return true;
    }

    //find in phone
    char *name = contact->name;
    char *phone = contact->phone;
    char check_buffer[MAX_NAME_LENGTH];
    t9_string_to_num(phone, check_buffer);
    if (strstr(check_buffer, pattern) != NULL) {
        return true;
    }
    t9_string_to_num(name, check_buffer);
    if (strstr(check_buffer, pattern) != NULL) {
        return true;
    }
    return false;
}


int main(int argc, char *argv[]) {
    // check if the number of arguments is more than 2
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

    Contact contacts[MAX_CONTACTS];
    int contact_idx = 0;
    int loaded_contacts = 0;
    int return_code;
    while ((return_code = load_contact(&contacts[contact_idx])) != -1) {
        if (return_code == 1) {
            fprintf(stderr, "Error loading contact.\n");
            return 1;
        }

        if (!is_valid_contact(&contacts[contact_idx])) {
            fprintf(stderr, "Invalid contact.\n");
            return 1;
        }

        if (is_match(&contacts[contact_idx], search_pattern)) {
            contact_idx++;
        }

        loaded_contacts++;
        if (loaded_contacts == MAX_CONTACTS && fgetc(stdin) != EOF) {
            fprintf(stderr, "Contact capacity exceeded. 0 - %d contacts supported.\n", MAX_CONTACTS);
            return 1;
        }
    }

    for (int idx = 0; idx < contact_idx; idx++) {
        printf("%s, %s\n", contacts[idx].name, contacts[idx].phone);
    }

    if (contact_idx == 0) {
        printf("Not found\n");
    }

    return 0;
}
