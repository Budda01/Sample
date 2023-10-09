// #include <stdio.h>

// int main() {
//     FILE *file = fopen("filename.txt", "r");
//     if (file == NULL) { 
//         printf("Failed to open file\n");
//         return 1;
//     }

//     char buffer[256];
//     int last_line = 0; 
//     while (fgets(buffer, sizeof(buffer), file)) { 
//         if (!last_line) { 
//             printf("%s", buffer); 
//         } else { 
//             printf("%s\n", buffer); 
//         }
//         if (feof(file)) { 
//             last_line = 1; 
//         }
//     }

//     fclose(file); 
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <getopt.h>

// int main(int argc, char *argv[]) {
//     int c;
//     int width = 0;
//     char *filename = NULL;

//     while ((c = getopt(argc, argv, "w:f:")) != -1) {
//         switch (c) {
//             case 'w':
//                 width = atoi(optarg);
//                 break;
//             case 'f':
//                 filename = optarg;
//                 break;
//             default:
//                 printf("Unknown option: %c\n", c);
//                 return 1;
//         }
//     }

//     printf("Width: %d\n", width);
//     printf("Filename: %s\n", filename);

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;
    char *arg1 = NULL, *arg2 = NULL, *arg3 = NULL;

    while ((opt = getopt(argc, argv, "a:b:c:")) != -1) {
        switch (opt) {
            case 'a':
                arg1 = optarg;
                break;
            case 'b':
                arg2 = optarg;
                break;
            case 'c':
                arg3 = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -a arg1 -b arg2 -c arg3\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (arg1) {
        printf("-a: %s\n", arg1);
    }
    if (arg2) {
        printf("-b: %s\n", arg2);
    }
    if (arg3) {
        printf("-c: %s\n", arg3);
    }

    return 0;
}