#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"

#define FILE_EXT_LEN    4
#define FILE_EXT        "flum"

static int validate_file_type(const char* filename);
static size_t get_line_num(FILE *f);
static char* sub_str(const char* str, size_t pos, size_t len);

char** get_raw_lines(const char* filename, size_t* num_lines) {
    if (!validate_file_type(filename)) {
        printf("File inputs require .flum extension\n");
        exit(EXIT_FAILURE);
    }
    
    FILE *f = fopen(filename, "r");
    *num_lines = get_line_num(f);
    char** raw_lines = (char**)malloc(sizeof(char*)*(*num_lines));

    char* line_buffer;
    size_t buffer_len = 0;
    for (size_t i=0; getline(&line_buffer, &buffer_len, f) != -1; i++) {
        char* tmp_buffer = (char*)malloc(sizeof(char)*strlen(line_buffer));
        strcpy(tmp_buffer, line_buffer);       
        raw_lines[i] = tmp_buffer;       
        line_buffer = NULL;
    }
    fclose(f);
    (*num_lines)--;

    return raw_lines;
}

static int validate_file_type(const char* filename) {
    int validation = 1;
    char* ext = sub_str(filename, strlen(filename)-FILE_EXT_LEN+1, FILE_EXT_LEN);
    if (strcmp(ext, FILE_EXT))
        validation = 0;
    free(ext);
    return validation;
}

static size_t get_line_num(FILE *f) {
    size_t lines = 0;
    char c;
    while((c=fgetc(f))!=EOF) 
        if (c=='\n')  lines++;
    fseek(f, 0, SEEK_SET);
    return lines+=2;
}

static char* sub_str(const char* str, size_t pos, size_t len) {
    char* sub_str = (char*)malloc(sizeof(char)*(len+1));
    size_t i;
    for (i=0; i<len; i++) 
        sub_str[i] = str++[pos-1];
    sub_str[i] = '\0';
    return sub_str;
}