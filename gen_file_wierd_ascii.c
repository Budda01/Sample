#include <stdio.h>

int main() {
    int ascii_code;
    // Открываем файл для записи
    FILE* file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return 1;
    }
     for (ascii_code = 0; ascii_code< ; ascii_code++){
        fprintf(file, "%d", ascii_code);
        fputc(' ', file);
        fputc(ascii_code, file);
        fputc('\n', file);
    }

    // Закрываем файл
    fclose(file);

    printf("Символ записан в файл\n");
    
    return 0;
}




