#include "tokenize.h"
#include <string.h>
#include <stdlib.h>

char** tokenize_malloc(const char* str, const char* delim)
{
    const char* ptr_str = str;
    const char* ptr_pre_str = str;
    int is_delim = FALSE;
    size_t n = 0;
    size_t size = strlen(str);
    char** result;
    char* ptr_temp;
    if (str == NULL || size == 0) {
        result = (char**)malloc(sizeof(char*));
        result[0] = NULL;
        return result;
    }
    if (delim == NULL || *delim == '\0') {
        result = (char**)malloc(sizeof(char*) * 2);
        result[0] = (char*)malloc(sizeof(char) * (size + 1));
        memcpy(result[0], str, (size + 1));
        result[1] = NULL;
        return result;
    }
    result = (char**)malloc(sizeof(char*) * size);
    while (*ptr_str != '\0') {
        if (is_delimiter(*ptr_str, delim) == TRUE) {
            if (is_delim == TRUE) {
                result[n] = (char*)malloc(sizeof(char) * (ptr_str - ptr_pre_str + 1));
                ptr_temp = result[n];
                while (ptr_str > ptr_pre_str) {
                    *ptr_temp++ = *ptr_pre_str++;
                }
                *ptr_temp = '\0';
                n++;
                is_delim = FALSE;
                ptr_pre_str++;
            } else {
                ptr_pre_str++;
            }
        } else {
            is_delim = TRUE;
        }
        ptr_str++;
    }
    if (n == 0) {
        result[n] = (char*)malloc(sizeof(char) * (size + 1));
        memcpy(result[n], str, (size + 1));
        n++;
    }
    result[n] = NULL;
    return result;
}

int is_delimiter(const char letter, const char* delim)
{
    while (*delim != '\0') {
        if (letter == *delim) {
            return TRUE;
        }
        delim++;
    }
    return FALSE;
}
