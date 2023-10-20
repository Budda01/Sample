#include "grep.h"

int main(int argc, char *argv[]){
    struct short_flags flag = {0};
    char buf[BUFFSIZE] = "";
    if (argc == 1){
        printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
    }
    else{
        usedFlags(argc, argv, &flag, buf);
        if (flag.err == 0){
            // printf("\ne i v c l n h s f o err\n");
            // printf("%d %d %d %d %d %d %d %d %d %d %d\n", flag.e, flag.i, flag.v, flag.c, flag.l, flag.n, flag.h, flag.s, flag.f, flag.o, flag.err);
            openFile(argc, argv, flag, buf);
        }
    }
}


void usedFlags(int argc, char *argv[], struct short_flags *flag, char *buf){
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
            use_f(argv, flag, buf);
            break;
        case 'o':
            flag->o = 1;
            break;
        default:
            flag->err = 1;
            break;
        }
    }
}

void use_e(char *buf){
    if (strcmp(buf, "") != 0)
        strcat(buf, "|");
    strcat(buf, optarg);
}   

void use_f(char *argv[], struct short_flags *flag, char *buf){
    if (strcmp(buf, "") != 0){
        strcat(buf, "|");
    }
    FILE *fl = fopen(optarg, "r");
    if (fl == NULL){
        if ((*flag).err < 1){
            if ((*flag).s == 0)
                fprintf(stderr, "%s: %s: No such file or derectory\n", argv[0], argv[optind]);
        (*flag).err++;  
        }
    }
    else{
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
}

void use_l(char *file_name, int suit_line){
    if (suit_line > 0){
        printf("%s\n", file_name);
    }
}

void use_o(struct short_flags flag, regmatch_t matches, regex_t template, char *line, int count_line, int count_file, char *file_name){
    int now_char = 0;
    line[strcspn(line, "\n")] = 0;
    while (regexec(&template, line + now_char, 1, &matches, 0) == 0){
        if (flag.h == 0 && count_file > 1)
            printf("%s:", file_name);
        if (flag.n == 1)
            printf("%d:", count_line);
        int len_line = matches.rm_eo - matches.rm_so;
        printf("%.*s\n", len_line, line + now_char + matches.rm_so);
        now_char += matches.rm_eo;
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
    
    //printf("BUFFER %s\n", buf);
    regex_t template;
    regmatch_t matches;
    regcomp(&template, buf, mod);
    
    for (int i = optind; i < argc; i++){
        FILE * fp = NULL;
        fp = fopen(argv[i], "r");
        if (fp != NULL){
            char *file_name = argv[i];
            staticOutput(fp, flag, template, count_file, file_name, matches);
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

void staticOutput(FILE * fp, struct short_flags flag, regex_t template, int count_file, char *file_name, regmatch_t matches){
    char line[BUFFSIZE];
    int match;
    int suit_line = 0;
    int count_line = 0;
    while(fgets(line, BUFFSIZE, fp) != NULL){
        match = regexec(&template, line, 0, NULL, 0);
        count_line++;
        suit_line = dynamicOutput(fp, match, flag, line, suit_line, count_line, count_file, file_name);
        if (flag.o == 1 && flag.c == 0 && flag.v == 0 && flag.l == 0){
            use_o(flag, matches, template, line, count_line, count_file, file_name);
        }
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

int dynamicOutput(FILE * fp, int match, struct short_flags flag, char *line, int suit_line, int count_line, int count_file, char *file_name){
    if (flag.v == 1 && match != 0){
        suit_line = printing(flag, line, suit_line, count_line, count_file, file_name);
        if (feof(fp) && strcmp(line, "") != 0 && flag.c == 0 && flag.l == 0 && flag.o == 0){
            printf("\n");
        }     
    }
    else if (flag.v == 0 && match == 0){
        suit_line = printing(flag, line, suit_line, count_line, count_file, file_name);
        if (feof(fp) && strcmp(line, "") != 0 && flag.c == 0 && flag.l == 0 && flag.o == 0){
            printf("\n");
        }
    }
    return suit_line;
}


int printing(struct short_flags flag, char *line, int suit_line, int count_line, int count_file, char *file_name){
    if (flag.h == 0 && count_file > 1 && flag.c == 0 && flag.l == 0 && flag.o == 0){
        printf("%s:", file_name);
    }
    if (flag.c == 1 || flag.l == 1){
            suit_line++;
    }else{
        if (flag.n == 1 && flag.o == 0)
            printf("%d:", count_line);
        if (flag.o == 0){
            printf("%s", line);
        }
    }
    return suit_line;
}