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

void use_l(char *file_name, int suit_line){
    if (suit_line > 0){
        printf("%s\n", file_name);
    }
}

void openFile(int argc, char* argv[], struct short_flags flag, char *buf){
 
    if (flag.e == 0 && flag.f == 0){
        strcat(buf, argv[optind]);
        optind++;
    }

    int count_file = argc - optind;
    
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
            char *file_name = argv[i];
            grepWorks(fp, flag, template, count_file, file_name);
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

void grepWorks(FILE * fp, struct short_flags flag, regex_t template, int count_file, char *file_name){
    regmatch_t matches[MAXMATCHES];
    char line[BUFFSIZE];
    int match;
    int suit_line = 0;
    int count_line = 0;
    while(fgets(line, BUFFSIZE, fp) != NULL){
        if (flag.o == 1){
            line[strcspn(line, "\n")] = 0;
            match = regexec(&template, line, MAXMATCHES, matches, 0);
        }
        else
            match = regexec(&template, line, 0, NULL, 0);
        count_line++;
        suit_line = output(fp, match, flag, line, suit_line, count_line, count_file, file_name, matches);
    }
    if (flag.c == 1 && flag.l == 0){
        if (flag.h == 0 && count_file > 1){
            printf("%s:", file_name);
        }
        printf("%d\n", suit_line);
    }
    if (flag.l == 1){
        use_l(file_name, suit_line);
    }
}

int output(FILE * fp, int match, struct short_flags flag, char *line, int suit_line, int count_line, int count_file, char *file_name, regmatch_t matches[]){
    if (flag.v == 1 && match != 0 && flag.o == 0){
        suit_line = printing(flag, line, suit_line, count_line, count_file, file_name, matches);
        if (feof(fp) && strcmp(line, "") != 0 && flag.c == 0 && flag.l == 0){
            printf("\n");
        }     
    }
    else if (flag.v == 0 && match == 0){
        suit_line = printing(flag, line, suit_line, count_line, count_file, file_name, matches);
        if (feof(fp) && strcmp(line, "") != 0 && flag.c == 0 && flag.l == 0 && flag.o == 0){
            printf("\n");
        }
    }
    return suit_line;
}


int printing(struct short_flags flag, char *line, int suit_line, int count_line, int count_file, char *file_name, regmatch_t matches[]){
    if (flag.h == 0 && count_file > 1 && flag.c == 0 && flag.l == 0){
        printf("%s:", file_name);
    }
    if (flag.c == 1 || flag.l == 1){
            suit_line++;
    }else{
        if (flag.n == 1)
            printf("%d:", count_line);
        if (flag.o == 1){
            printf("%.*s\n", (int)(matches[0].rm_eo - matches[0].rm_so), line + matches[0].rm_so);
        }
        else
            printf("%s", line);
    }
    return suit_line;
}