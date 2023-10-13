#include "grep.h"

int main(int argc, char *argv[]){
    struct short_flags flag = {0};
    char buf[BUFFSIZE] = "";
    if (argc == 1){
        printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
    }
    else{
        if (usedFlags(argc, argv, &flag, buf) == 0){
            printf("\ne i v c l n h s f o\n");
            printf("%d %d %d %d %d %d %d %d %d %d\n", flag.e, flag.i, flag.v, flag.c, flag.l, flag.n, flag.h, flag.s, flag.f, flag.o);
            openFile(argc, argv, flag, buf);
        }
    }
}


int usedFlags(int argc, char *argv[], struct short_flags *flag, char *buf){
    int err = 0;
    char opt; 

    while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1){
        switch (opt)
        {
        case 'e':
            flag->e += 1;
            use_e(buf);
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
            use_f(argv, *flag, buf);
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

void use_e(char *buf){
    if (strcmp(buf, "") != 0)
        strcat(buf, "|");
    strcat(buf, optarg);
}   

void use_f(char *argv[], struct short_flags flag, char *buf){
    if (strcmp(buf, "") != 0){
        strcat(buf, "|");
    }
    FILE *fl = fopen(optarg, "r");
    if (fl == NULL) {
        if (flag.s == 0){
            printf("%s : %s No such file or directory\n", argv[0], optarg);
        } 
    }
    char symb[1] = "";
    char c; 
    while((c = fgetc(fl)) != EOF){
        if (c != 10){
            symb[0] = c;
            strcat(buf, symb);
        }
        else
            strcat(buf, "|");
    }
    fclose(fl);
}

void openFile(int argc, char* argv[], struct short_flags flag, char *buf){
    if (flag.e == 0 && flag.f == 0){
        strcat(buf, argv[optind]);
        optind++;
    }
    int mod;
    if (flag.i == 1){
        mod = REG_EXTENDED | REG_ICASE;
    }
    else{
        mod = REG_EXTENDED;
    }
    
    printf("BUFFER %s\n", buf);
    regex_t template;
    regcomp(&template, buf, mod);
    
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
    int suit_line = 0;
    int count_line = 0;
    while(fgets(line, BUFFSIZE, fp) != NULL){
        match = regexec(&template, line, 0, NULL, 0);
        count_line++;
        suit_line = output(match, flag, line, suit_line, count_line);

    }
    if (flag.c == 1){
        printf("%d\n", suit_line);
    }
}

int output(int match, struct short_flags flag, char *line, int suit_line, int count_line){
    if (flag.v == 1){
            if (match != 0){
                printing(flag, line, suit_line, count_line);     
            }
    }
    else{
        if (match == 0){
           suit_line = printing(flag, line, suit_line, count_line);
        }       
    }
    return suit_line;
}


int printing(struct short_flags flag, char *line, int suit_line, int count_line){
    if (flag.c == 1){
                suit_line++;
    }else{
        if (flag.n == 1)
            printf("%d:", count_line);
    printf("%s", line);
    }
    return suit_line;
}