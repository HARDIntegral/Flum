#include <stdio.h>
#include "parser/parser.h"

int main(int argc, char** argv) {
    parse_file(argv[1], 1);
    return 0;
}