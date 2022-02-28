#ifndef __LEXER_H__
#define __LEXER_H__

#include <malloc.h>
#include "file_io.h"

typedef struct lexeme {
    int type;
    char *contents;
}_lexeme_t;

_lexeme_t* gen_lexemes(const char * filename);

#endif /* __LEXER_H__ */