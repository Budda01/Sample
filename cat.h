#ifndef S21_CAT_HEAD
#define S21_CAT_HEAD


#include <stdio.h>
#include <getopt.h>

#define BUFFSIZE 4096


struct short_flags
{
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
};


static struct option long_flags[]={{"number-nonblank", no_argument, NULL, 'b'}, {"number", no_argument , NULL, 'n'}, {"squeeze-blank", no_argument , NULL, 's'}, {NULL, no_argument , NULL, 0}};


void openFile(int argc, char* path[], struct short_flags flag);
void noArgs();
int usedFlags(int argc, char *argv[], struct short_flags *flag);
void use_E(char c);
void use_v(int *c);

#endif