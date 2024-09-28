#include "string_vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

void my_errno(int error) {
	switch (error) {
		case (INV_PTR) :
			printf("Invalid Pointer \n");
			break;
		case (INV_DATA) :
			printf("Invalid Data \n");
			break;
		case (INIT_FAIL) :
			printf("Initalization is failed \n");
			break;
		case (BAD_CAP) :
			printf("Bad capacity \n");
			break;
		case (BAD_RANGE) :
			printf("Bad range \n");
			break;
		case (BAD_VAL) :
			printf("Bad value \n");
			break;
		case (INV_LENGTH) :
			printf("Bad length \n");
			break;
		case (SAM_DATA) :
			printf("Datas is same \n");
			break;
		case (INV_IND) : {
			printf("Invalid index");
			break;
		}
        case (INV_POS) : {
            printf("Invalid position \n");
        }
	}
}

void resize(char **data, size_t newCap, size_t size) {
	char *tmpMem = (char*)calloc(newCap + 1, sizeof(char));    

	for (int i = 0; i < size; ++i) {
		tmpMem[i] = (*data)[i];
	}

	free(*data);
	*data = tmpMem;
}

//Constructors, Destructor and Assignment Operator:

int string_init(String *this) {
	if (this == NULL) {
		my_errno(INV_PTR);
		return -1;
	}
	
	this->capacity = 0;
	this->length = 0;
	this->data = NULL;
	return 0;
}

int string_init_size(String *this, size_t new_cap) {
	if (this == NULL) {
		my_errno(INV_PTR);
		return -1;
	}
	if (!new_cap) {
		my_errno(BAD_CAP);
		return -1;
	}
	if (this->data == NULL) {
		my_errno(INV_DATA);
		return -1;
	}

	this->capacity = new_cap + 1;
	this->length = 0;
	this->data = (char*)calloc(this->capacity, sizeof(char));
	
	return 0;
}

int string_init_fill(String *this, size_t new_size, char value) {
	if (this == NULL) {
		my_errno(INV_PTR);
		return -1;
	}
	if (value < 0) {
		my_errno(BAD_VAL);
		return -1;
	}

	if (!new_size) {
		my_errno(BAD_SIZE);
		return -1;
	}
	this->capacity = new_size + 1;
	this->length = new_size;
	this->data = (char*)calloc(this->capacity, sizeof(char));
	
	for (int i = 0; i < this->length; ++i) {
		this->data[i] = value;
	}

	return 0;
}

int string_copy(String *this, const String *other) {
	if (other == NULL) {
		my_errno(INV_PTR);
		return -1;
	}
	if (other->data) {
		my_errno(INV_DATA);
		return -1;
	}

	string_init(this);
	this->capacity = other->capacity;
	this->length = other->length;
	this->data = (char*)calloc(this->capacity, sizeof(char));
	
	for (int i = 0; i <= this->length; ++i) {
		this->data[i] = other->data[i];
	}

	return 0;
}

int create_string(String *this, const char *str) {
	if (this == NULL || str == NULL) {
		my_errno(INV_DATA);
		return -1;
	}

	const char *ptr = str;
	int strLength = 0;

	while (*ptr++) {
		++strLength;
	}

	string_init_size(this, strLength);
	this->length = strLength;
	
	for (int i = 0; i < strLength; ++i) {
		this->data[i] = str[i];
	}
	
	return 0;
}

String *string_assign(String *this, const String *other) {
	if (this == NULL || other == NULL) {
		my_errno(INV_PTR);
		return NULL;
	}
	if (this->data == other->data) {
		my_errno(SAM_DATA);
		return this;
	}
	if (this->data != NULL) {
		free(this->data);
	}
	
	this->capacity = other->capacity;
	this->length = other->length;
	this->data = (char*)calloc(this->capacity, sizeof(char));
	
	for (int i = 0; i < this->length; ++i) {
		this->data[i] = other->data[i];
	}

	return this;	
}

int string_destroy(String *this) {
	if (this == NULL) {
		my_errno(INV_PTR);
		return -1;
	}

	free(this->data);
	this->data = NULL;

	return 0;
}

// Element access

char *at(const String *this, size_t index) {
	if (this == NULL) {
		return NULL;
	}
	if (index > this->length) {
		my_errno(INV_IND);
		return NULL;
	}
	if (this->data == NULL) {
		my_errno(INV_PTR);
		return NULL;
	}
 	if (!this->length) {
		my_errno(INV_LENGTH);
		return NULL;
	}
	return &this->data[index];
}

char *string_front(String *this) {
	if (this == NULL) {
		my_errno(INV_PTR);
		return NULL;
	}
	if (!this->length) {
		my_errno(INV_LENGTH);
		return NULL;
	}
	
	return &this->data[0];
}

char *string_back(String *this) {
	if (this == NULL) {
		my_errno(INV_PTR);
		return NULL;
	}
	if (!this->length) {
		my_errno(INV_LENGTH);
		return NULL;
	}
	return &this->data[this->length]; 
}

int empty(String *this) {
	if (this == NULL) {
		my_errno(INV_PTR);
		return -1;
	}
	if (this->length) {
		my_errno(SIZE_HAVE);
		return -1;
	}

	return !this->length;
}

// Modifiers

int append(String *this, const String *other) {
	if (this == NULL ) {
        my_errno(INV_PTR);
        return -1;
    }

    if (this->data == other->data) {
        my_errno(SAM_DATA);
        return -1;
	}

	if ((this->length + other->length) > this->capacity || this->data == NULL) {
		resize(&this->data, this->length + other->length, this->length);
	}	
	
	(this->data) += this->length;
    this->capacity += 1;
	int i = 0;

	while (*(this->data)) {
		*(this->data) = other->data[i++];
		this->data++;
	}

	return 0;
}

int string_push_back(String *this, char value) {
	if (this == NULL) {
        my_errno(INV_PTR);
        return -1;
	}
	if (this->data == NULL) {
		string_init_size(this, 1);
		this->data[0] = value;
		return 0;		
	}
	if (this->length == (this->capacity - 1)) {
		resize(&this->data, this->capacity, this->length);
	}

	this->data[this->length++] = value;
    this->capacity += 1;
	return 0;
}

int string_pop_back(String* this) {
	if (this == NULL) {
        my_errno(INV_PTR);
        return -1;
	}
	if (this->data == NULL) {
        my_errno(INV_DATA);
        return -1;
	}
	if (!this->length) {
		my_errno(INV_LENGTH);
		return -1;
	}

	resize(&this->data, this->capacity - 1, this->length - 1);
    this->capacity -= 1;
    this->length -= 1;
	return 0;
}

int clear(String *this) {
	if (this == NULL) {
        my_errno(INV_PTR);
        return -1;
	}
	if (this->data == NULL) {
        my_errno(INV_DATA);
		return -1;
	}
	
	this->capacity = 0;
	this->length = 0;
	free(this->data);
	return 0;	
}

int insert(String *this, const String *other, size_t pos) {
    if (this == NULL || other == NULL) {
        my_errno(INV_PTR);
        return -1;
    }
    if (other->data == NULL) {
        my_errno(INV_DATA);
        return -1;
    }
    if (this->length < pos) {
        my_errno(INV_POS);
        return -1;
    }

    if (this->length + other->length >= this->capacity) {
        resize(&this->data, this->length + other->length, this->length);
    }

    this->capacity = this->length + other->length + 1;
   
    if (pos <= this->length) {
        for (int i = this->length - 1, j = this->capacity - 2; i >= pos; --i, --j) {
            this->data[j] = this->data[i];
        }
    }
    for (int i = pos, j = 0; j < other->length; ++i, ++j) {
        this->data[i] = other->data[j];
    }

    this->length += other->length;

    return 0;
}

int erase(String *this, size_t pos) {
    if (this == NULL) {
        my_errno(INV_PTR);
        return -1;
    }
    if (pos >= this->length) {
        my_errno(INV_POS);
        return -1;
    }
    if (pos == this->length - 1) {
        string_pop_back(this);
        return 0;
    }

    for (int i = pos; i < this->length - 1; ++i) {
        this->data[i] = this->data[i + 1];
    }
    this->length -= 1;
    this->data[this->length] = '\0';

    return 0;
}

int trim(String *this) {
    if (this == NULL) {
        my_errno(INV_PTR);
    }

    int leftSpaces = 0;
    int rightSpaces = 0;

    for (int i = 0; this->data[i] == ' ' || this->data[i] == '\t' || this->data[i] == '\n'; ++i) {
        ++leftSpaces;
    }
    for (int i = this->length - 1; this->data[i] == ' ' || this->data[i] == '\t' || this->data[i] == '\n'; --i) {
        ++rightSpaces;
    }

    this->capacity -= leftSpaces + rightSpaces + 1;
    this->length = this->capacity - 1;
    
    for (int i = 0; i < this->length; ++i) {
        this->data[i] = this->data[i + leftSpaces];
    }
    
    resize(&this->data, this->capacity - 1, this->length);

    return 0;
}

int compare(const String *this, const String *other) {
    if (this == NULL || other == NULL) {
        my_errno(INV_PTR);
        return INV_PTR;
    }
    if (this->data == NULL || other->data == NULL) {
        return 0;
    }

    int cycleCnt = (this->length <= other->length) ? this->length : other->length;

    for (int i = 0; i < cycleCnt; ++i) {
        if ((this->data[i] - other->data[i]) > 0) {
            return 1;
        }
        if ((this->data[i] - other->data[i]) < 0) {
            return -1;
        }
    }
    return 0;
}

int find(const String *this, const char *substr) {
    if (this == NULL || substr == NULL) {
        my_errno(INV_PTR);
        return INV_PTR;
    }
    if (this->data == NULL) {
        my_errno(INV_DATA);
        return INV_DATA;
    }

    int substrLen = strlen(substr);
    int back = 0;

    for (int i = 0; i < substrLen; ++i) {
        if (this->data[i] == *substr) {
            ++back;
            ++substr;
        } else {
            substr -= back;
            back = 0;
        }
        if (back == substrLen) {
            return ++i - back;
        }
    }

    return -1;
}

int to_string(String *this, int val) {
    if (this == NULL) {
        my_errno(INV_PTR);
        return -1;
    }
    
    int size = 0;
    int tmp = val;

    while (tmp) {
        tmp /= 10;
        ++size;
    }

    if (this->data == NULL) {
        string_init_size(this, size);
    }
    if (this->data != NULL) {
        clear(this);
        this->capacity = size + 1;
        this->data = (char*)calloc(this->capacity, sizeof(char));
    }

    this->length = size;

    while (val) {
        tmp = val % 10;
        val /= 10;
        this->data[--size] = tmp + 48;
    }
    
    return 0;
}

int to_int(String *this) {
    if (this == NULL) {
        my_errno(INV_PTR);
        return -1;
    }
    if (this->data == NULL) {
        my_errno(INV_DATA);
        return -1;
    }
    
    char *tmpPtr = this->data;
    int tmp = 0;

    while (*tmpPtr) {
        if (*tmpPtr < '0' || *tmpPtr > '9') {
            ++tmpPtr;
            continue;
        }
        tmp = tmp * 10 + (*tmpPtr - 48);
        ++tmpPtr;
    }

    return tmp;    
}
