#include <stdio.h>

int main() {
    
    FILE* file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return 1;
    }
     for (int i = 0; i < 600; i++){
        fprintf(file, "%d", i);
        fputc(' ', file);
        fputc('1', file);
        fputc('\n', file);
    }

    // Закрываем файл
    fclose(file);

    printf("Символ записан в файл\n");
    
    return 0;
}

