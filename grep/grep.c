#include "grep.h"

int main(int argc, char *argv[]){
    struct short_flags flag = {0};
    char buf[BUFFSIZE] = "";
    if (argc == 1){
        printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
    }
    else{
        if (usedFlags(argc, argv, &flag) == 0){
            printf("\ne i v c l n h s f o\n");
            printf("%d %d %d %d %d %d %d %d %d %d\n", flag.e, flag.i, flag.v, flag.c, flag.l, flag.n, flag.h, flag.s, flag.f, flag.o);
            openFile(argc, argv, flag, buf);
        }
    }
}


int usedFlags(int argc, char *argv[], struct short_flags *flag){
    int err = 0;
    char opt;
    char *arg= NULL; 
    while ((opt = getopt(argc, argv, "eivclnhsfo")) != -1){
        switch (opt)
        {
        case 'e':
            flag->e += 1;
            arg = optarg;
            printf("%s", arg);
            break;
        case 'i':
            flag->i = 1;
            break;
        case 'v':
            flag->v = 1;
            break;
        case 'c':
            flag->c = 1;
            break;
        case 'l':
            flag->l = 1;
            break;
        case 'n':
            flag->n = 1;
            break;
        case 'h':
            flag->h = 1;
            break;
        case 's':
            flag->s = 1;
            break;
        case 'f':
            flag->f += 1;

            break;
        case 'o':
            flag->o = 1;
            break;
        default:
            err = 1;
            break;
        }
    }
    
    return err;
}


void openFile(int argc, char* argv[], struct short_flags flag, char *buf){
    if (flag.e == 0 && flag.f == 0){
        strcat(buf, argv[optind]);
    }
    optind++;
    regex_t template;
    regcomp(&template, buf, 0);
    
    for (int i = optind; i < argc; i++){
        FILE * fp = NULL;
        fp = fopen(argv[i], "r");
        if (fp != NULL){
            grepWorks(fp, flag, template);
            fclose(fp);
        }
        else{
            if (flag.s == 0){
                printf("%s : %s No such file or directory\n", argv[0], argv[i]);
            }
        }
    }
   regfree(&template);  
}

void grepWorks(FILE * fp, struct short_flags flag, regex_t template){
    char line[BUFFSIZE];
    int match;
    while(fgets(line, BUFFSIZE, fp)){
        match = regexec(&template, line, 0, NULL, 0);
        if (flag.v == 1){
            if (match != 0){
                printf("%s", line);
            }
        }
        else{
            if (match == 0){
                printf("%s", line);
            }
        } 
    }
}