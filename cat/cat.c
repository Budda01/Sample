#include "cat.h"

int main(int argc, char *argv[]){
    struct short_flags flag = {0};
    if (argc == 1){
        noArgs();
    }
    else{
        if (usedFlags(argc, argv, &flag) == 0){
            // printf("\nb e n s t v \n");
            // printf("%d %d %d %d %d %d \n", flag.b, flag.e, flag.n, flag.s, flag.t, flag.v);
            openFile(argc, argv, flag);
        }
    }
}

void noArgs(){
    char str[BUFFSIZE];
    int count = 0;
    while (count < BUFFSIZE){
        scanf("%s", str);
        printf("%s\n", str);
        count++;
    }  
}
void use_v(int *c){
    int check = 0;  
    if (*c > 127){
        check = 1;
        *c = (*c % 128);
        printf("M-");
    }
    if (check == 0){
        if(((*c % 128)>=0 && (*c % 128) <=31 && (*c % 128)!= 9 && (*c % 128)!= 10) || (*c % 128) == 127){
            if ((*c + 64) > 127){
                *c = (*c + 64) % 128;
            }
            else
                *c += 64;
            printf("^");
        }
    }
    else{
        if(((*c % 128)>=0 && (*c % 128) <=31) || (*c % 128) == 127){
            if ((*c + 64) > 127){
                *c = (*c + 64) % 128;
            }
            else
                *c += 64;
            printf("^");
        }    
    }  
}

void use_t(int *c){
    if (*c == 9){
        *c = *c + 64;
        printf("^");
    }
}

void use_E(char c){
    if (c == 10){
        printf("$");
    }
}

int usedFlags(int argc, char *argv[], struct short_flags *flag){
    int err = 0;
    char opt;
    while ((opt = getopt_long(argc, argv, "benstvET", long_flags, NULL)) != -1){
        switch (opt)
        {
        case 'b':
            flag->b = 1;
            break;
        case 'e':
            flag->e = 1;
            flag->v = 1;
            break;
        case 'n':
            flag->n = 1;
            break;
        case 's':
            flag->s = 1;
            break;
        case 't':
            flag->t = 1;
            flag->v = 1;
            break;
        case 'v':
            flag->v = 1;
            break;
        case 'E':
            flag->e = 1;
            break;
        case 'T':
            flag->t = 1;
            break;
        default:
            err = 1;
            break;
        }
    }
   
    return err;
}


void openFile(int argc, char* path[], struct short_flags flag){
    int lin_num = 1;
    int count_s = 1;
    int count_bn = 0;
    for (int i = optind; i < argc; i++){
        FILE * fp = NULL;
        fp = fopen(path[i], "r");
        if (fp != NULL){
            int c;
            while((c = fgetc(fp)) != EOF){

                if (flag.s == 1){
                    if (c == 10){ count_s++; }
                    else {count_s = 0;}
                }
                if (count_s <= 2){
                    
                    if (flag.b == 1){
                        if (count_bn == 0 && c != 10){ printf("%6d\t", lin_num++); }
                        if (c != 10){ count_bn++; }
                        else { count_bn = 0; }
                    }
                    if (flag.n == 1 && flag.b == 0){
                        if (count_bn == 0) { printf("%6d\t", lin_num++); }
                        if (c != 10) { count_bn++; }
                        else { count_bn = 0; }
                    }
                    if (flag.e == 1){use_E(c);}
                    if (flag.v == 1){use_v(&c);}
                    if (flag.t == 1){use_t(&c);}
                    printf("%c", c);
                }
            }
            fclose(fp);
        }
        else
            fprintf(stderr, "%s: %s: No such file or derectory", path[0], path[i]);
    }
}


