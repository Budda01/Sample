#include "cat.h"

int main(int argc, char *argv[]){
    struct short_flags flag = {0};
    if (argc == 1){
        noArgs();
    }
    else{
        if (usedFlags(argc, argv, &flag) == 0){
            printf("\nb e n s t v \n");
            printf("%d %d %d %d %d %d \n", flag.b, flag.e, flag.n, flag.s, flag.t, flag.v);
            openFile(argc, argv);
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
    //printf("%d", optind);
    return err;
}



void openFile(int argc, char* path[]){
    for (int i = optind; i < argc; i++){
        FILE * fp;
        fp = fopen(path[i], "r");
        if (fp!= NULL){
        char buff[BUFFSIZE];
        while(fgets(buff, sizeof(buff), fp)!= NULL){
            printf("%s", buff);
        }
        fclose(fp);
        }
        else
            printf("s21_cat: %s: No such file or directory\n", path[i]);
    }
}

