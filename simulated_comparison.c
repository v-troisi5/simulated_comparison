#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_LEN 64

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <file1> <file2> <ritardo_ms>\n", argv[0]);
        return 1;
    }

    char *file1 = argv[1];
    char *file2 = argv[2];
    int delay = atoi(argv[3]);  

    FILE *fp1 = fopen(file1, "r");
    if (!fp1) {
        perror("Errore apertura file 1");
        return 1;
    }

    FILE *fp2;
    char word1[MAX_LEN], word2[MAX_LEN];

    //Avvio timer
    LARGE_INTEGER t_start, t_end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&t_start);

    while (fgets(word1, MAX_LEN, fp1)) {
        word1[strcspn(word1, "\r\n")] = 0;

        fp2 = fopen(file2, "r");
        if (!fp2) {
            perror("Errore apertura file 2");
            fclose(fp1);
            return 1;
        }

        while (fgets(word2, MAX_LEN, fp2)) {
            word2[strcspn(word2, "\r\n")] = 0;

            printf("Confronto: %s con %s\n", word1, word2);
            Sleep(delay);
        }

        fclose(fp2);
    }

    //Terminazione timer
    QueryPerformanceCounter(&t_end);

    //Calcolo tempo totale
    double ms = (double)(t_end.QuadPart - t_start.QuadPart) * 1000.0 / (double)freq.QuadPart;
    printf("Tempo totale: %.3f ms (%.3f secondi)\n", ms, ms / 1000.0);

    fclose(fp1);
    return 0;
}
