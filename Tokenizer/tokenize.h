#ifndef TOKENIZE_H
#define TOKENIZE_H

#define FALSE (0)
#define TRUE (1)

char** tokenize_malloc(const char* str, const char* delim);
int is_delimiter(const char letter, const char* delim);
#endif /* TOKENIZE_H */
