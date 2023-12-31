#ifndef S21_GREP_HEAD
#define S21_GREP_HEAD


#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <regex.h>

#define BUFFSIZE 4096
#define FILENAMESIZE 256
#define MAXMATCHES 4096


struct short_flags
{
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
    int err;
};

void usedFlags(int argc, char *argv[], struct short_flags *flag, char *buf);
void openFile(int argc, char* path[], struct short_flags flag, char *buf);
void staticOutput(FILE * fp, struct short_flags flag, regex_t template, int count_file, char *file_name, regmatch_t matches);
void use_e(char *buf);
void use_f(char *argv[], struct short_flags *flag, char *buf);
void use_o(struct short_flags flag, regmatch_t matches, regex_t template, char *line, int count_line, int count_file, char *file_name);
int dynamicOutput(FILE * fp, int match, struct short_flags flag, char *line, int suit_line, int count_line, int count_file, char *file_name);
int printing(struct short_flags flag, char *line, int suit_line, int count_line, int count_file, char *file_name);
#endif