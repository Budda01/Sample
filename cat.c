#include <stdio.h>
#define BUFFSIZE 4096

void openFile(char* path);
void noArgs();


int main(int argc, char *argv[]){
    if (argc == 1){
        noArgs();
    }
    else{
        for (int i = 1; i < argc; i++){
        openFile(argv[i]);
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

void openFile(char* path){
    FILE * fp;
    fp = fopen(path, "r");
    if (fp!= NULL){
        char buff[BUFFSIZE];
        while(fgets(buff, sizeof(buff), fp)!= NULL){
            printf("%s", buff);
        }
    fclose(fp);
    }
    else
        printf("No such file or directory");
}

