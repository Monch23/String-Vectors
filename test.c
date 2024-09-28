#include <stdio.h>
#include <string.h>
#include "string_vector.h"

void print_string(const String *str) {
    if (str && str->data) {
        printf("String: %s, Length: %zu, Capacity: %zu\n", str->data, str->length, str->capacity);
    } else {
        printf("String is empty or uninitialized.\n");
    }
}

int main() {
    String str1, str2, str3;

    // Test constructor without parameters
    string_init(&str1);
    printf("Initialized str1.\n");
    print_string(&str1);

    // Test constructor with size and capacity
    string_init_size(&str2, 10);
    
	printf("Initialized str2 with capacity 10.\n");
    print_string(&str2);

    // Test constructor with fill
    string_init_fill(&str3, 5, 'A');
    
	printf("Initialized str3 with 'AAAAA'.\n");
    print_string(&str3);

    // Test string assignment
    if (string_assign(&str1, &str3) == NULL) {
        printf("Failed to assign str3 to str1.\n");
    } else {
        printf("Assigned str3 to str1.\n");
        print_string(&str1);
    }

    // Test push back
    if (string_push_back(&str1, 'B') == INIT_FAIL) {
        printf("Failed to push back 'B' to str1.\n");
    } else {
        printf("Pushed 'B' to str1.\n");
        print_string(&str1);
    }

    // Test pop back
    if (string_pop_back(&str1) == INIT_FAIL) {
        printf("Failed to pop back from str1.\n");
    } else {
        printf("Popped back from str1.\n");
        print_string(&str1);
    }
	
    insert(&str3, &str2, 1);
    printf("%s \n", str3.data);

	/*
    // Test reverse
    if (string_reverse(&str1) == INIT_FAIL) {
        printf("Failed to reverse str1.\n");
    } else {
        printf("Reversed str1.\n");
        print_string(&str1);
    }

    // Test substring extraction
    String substr;
    if (substring(&str1, &substr, 1, 3) == INIT_FAIL) {
        printf("Failed to extract substring from str1.\n");
    } else {
        printf("Extracted substring from str1.\n");
        print_string(&substr);
        destroyString(&substr);
    }

    // Test destroy function
    if (destroyString(&str1) == INIT_FAIL) {
        printf("Failed to destroy str1.\n");
    } else {
        printf("Destroyed str1.\n");
    }

    // Clean up remaining strings
    destroyString(&str2);
    destroyString(&str3);
	*/
    return 0;
}
