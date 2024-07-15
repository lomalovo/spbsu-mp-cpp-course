#include <stddef.h>
size_t my_strlen(const char *s){
    size_t count = 0;

    while (*s++) {
        count++;
    }

    return count;
};

char *my_strcat(char *dst, const char *src){
    char *pointer = dst;
    while (*pointer) {
        pointer++;
    }

    while (*src) {
        *pointer++ = *src++;
    };

    *pointer = 0; 

    return dst;
};

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {

        if (*s1 != *s2) {
            if (*s1 > *s2) {
                return 1;
            }

            else {
                return -1;
            }
        }
        else {
            s1++;
            s2++;
        }
    }
    
    if (!*s1 && !*s2) {
        return 0;
    }
    else {
        if (!*s1 && *s2) {
            return -1;
        }
    }
    
    return 1;
};

char *my_strcpy(char *dst, const char *src){
    char *pointer = dst;
    while (*src) {
        *pointer++ = *src++;
    };
    *pointer = 0; 

    return dst;
};