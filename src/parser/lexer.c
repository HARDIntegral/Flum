#include "lexer.h"
#include "file_io.h"
#include <stddef.h>

#define MIN_LEX 32

_lexeme_t* gen_lexemes(const char * filename) {
    _lexeme_t* lexemes = (_lexeme_t*)malloc(sizeof(_lexeme_t)*MIN_LEX);

    size_t num_lines;
    char** raw_file = get_raw_lines(filename, &num_lines);

    for (size_t i = 0; i < num_lines; i++) 
        printf("%s", raw_file[i]);
    printf("\n");

    return lexemes;
}