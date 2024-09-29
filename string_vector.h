#ifndef MY_STRING_VECTOR
#define MY_STRING_VECTOR
#include <stddef.h>

typedef struct {
    size_t capacity;
    size_t length;
    char *data;
} String;

enum ERR_ALR {
	INV_PTR,
	INV_DATA,
	INIT_FAIL,
	BAD_CAP,
	BAD_RANGE,
	BAD_VAL,
	BAD_SIZE,
	INV_LENGTH,
	SAM_DATA,
	INV_IND,
	SIZE_HAVE,
    INV_POS
};

//Constructors, Destructor and Assignment Operator:
int string_init(String* this);
int string_init_size(String* this, size_t new_cap);
int string_init_fill(String* this, size_t new_size, char value);
int string_copy(String* this, const String* other);
int create_string(String* this, const char *str);
String* string_assign(String* this, const String* other);
int destroy_string(String *this);

//Element Access
char* at(const String *this, size_t index);
char* string_front(String* this);
char* string_back(String* this);
int empty(String* this);

//Modifiers
int append(String *this, const String *other);
int string_push_back(String* this, char value);
int string_pop_back(String* this);
int clear(String *this);
int insert(String *this, const String *other, size_t pos);
int erase(String *this, size_t pos);
int trim(String *this);

//String Operations
int compare(const String *this, const String *other);
int find(const String *this, const char *substr);
int to_string(String* this, int val);
int to_int(String* this);
int substring(const String *this, String *substr, size_t start, size_t length);
int string_reverse(String* this);
int string_to_lowercase(String* this);
int string_to_uppercase(String* this);

#endif
