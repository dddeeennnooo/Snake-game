#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include "hra.h"


// funkcia na nastavovanie farbičiek
void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
FILE* inputFile, * outputFile;

void loadLeaderboard(int lb[]) {
    FILE* inputFile = fopen("leaderboard.txt", "r");

    if (inputFile == NULL) {
        printf("Nelze najst vystupni soubor.\n");
        return;
    }

    for (int i = 0; i < 5; i++) {
        if (fscanf(inputFile, "%d", &lb[i]) != 1) {
            printf("Chyba pri citani zo suboru.\n");
            break;
        }
    }

    fclose(inputFile);
}

int main() {
    int gameOver = 0, width = 25, height = 25, x, y, fruitX, fruitY, score = 1;
    int s = 0;
    int totalTail = 0;
    int tailX[1000], tailY[1000];
    char cmd;
    int ovladanie = 1;
    int obtiaznost = 200;
    int lb[5] = {};

    loadLeaderboard(lb);


    do {
        system("cls");     
       //meneneie farbičiek
        if (obtiaznost == 200) {
            SetConsoleColor(10);
        }
        else if (obtiaznost == 150) {
            SetConsoleColor(14);
        }
        else if (obtiaznost == 100) {
            SetConsoleColor(12);
        }
        else if (obtiaznost == 50) {
            SetConsoleColor(15);
        }

        //menu
        printf("H: Zacat hru     ");
        printf("L: Leaderboard     ");
        printf("O: Vyber si ovladanie   ");
        printf("B: Vyber si obtiaznost   ");
        printf("Q: Konec\n\n");

    
        printf("Zakladne nastavenia su ovaladanie sipkami a obtiaznost pomala.\n\n");
        

        cmd = tolower(getchar());
        while (getchar() != '\n');

        switch (cmd) {
        case 'b':
            //case na obtaiznosti
            printf("200 = Snaek ide pomaly\n");
            printf("150 = Sneak ide trosky rychlejsie\n");
            printf("100 = Sneak ide dost rychlo\n");
            printf("50 = Sneak ide tak rýchlo ze z toho obcas padne hra\n");
            if (scanf("%d", &obtiaznost) != 100 || (obtiaznost != 100 && obtiaznost != 200 && obtiaznost != 150 && obtiaznost != 50)) {
                printf("Neplatna volba. Zvolte 100, 200, 150 alebo 50.\n");             //ošetrenie na zadavanie 
            }

            break;
        case 'o':
            //case na ovladanie
            printf("1 = Hra sa ovlada sipkami\n");
            printf("2 = Hra sa ovlada W(hore) A(vlavo) S(dole) D(vpravo)\n\n");
            if (scanf("%d", &ovladanie) != 1 || (ovladanie != 1 && ovladanie != 2)) {
                printf("Neplatna volba. Zvolte 1 alebo 2.\n");                          //ošetrenie na zadavanie 
            }

            break;
        case 'l':
            outputFile = fopen("leaderboard.txt", "w");
            if (outputFile == NULL) {
                printf("Nelze najst vystupni soubor.\n");
                return 1;
            }
            for (size_t i = 0; i < 5; i++)
            {
                fprintf(outputFile, "%d\n", lb[i]);
            }
            fclose(outputFile);
            
            printf("Tabulka sa zobrazi na 5s\n");
            printf("Top 5 score v tejto hre je:\n");
            inputFile = fopen("leaderboard.txt", "r");
            if (inputFile == NULL) {
                printf("Nelze najst vystupni soubor.\n");
                return 1;
            }
            char txt[50];
            while (fgets(txt, sizeof(txt), inputFile) != NULL) {
                printf("%s", txt);
            }
            fclose(inputFile);
            
            
            Sleep(5000);
            break;
            
        case 'h':
            // Hlavná hra funkcie 
            Setup(&height, &width, &score, &x, &y, &fruitX, &fruitY);

            while (gameOver != 1) {
                Draw(&height, &width, &score, &fruitX, &fruitY, tailX, tailY, &x, &y, &totalTail);
                Logic(&height, &width, &score, &fruitX, &fruitY, tailX, tailY, &x, &y, &totalTail, &s, &gameOver);
                if (ovladanie == 1)
                {
                    Input1(&s);
                }
                else if (ovladanie == 2)
                {
                    Input2(&s);
                }
                Sleep(obtiaznost);             
            }
            for (size_t i = 0; i < 5; i++) {
                if (score >= lb[i]) {
                    for (size_t j = 4; j > i; j--) {
                        lb[j] = lb[j - 1];
                    }
                    lb[i] = score;
                    break;
                }
            }
            break;
        case 'q':
            //koniec pomocný case
            break;

        default:
            //ošetrenie na zadavanie 
            printf("Neplatny vyber. Skuste znovu.\n");
            break;
        }
        
    } while (cmd != 'q');

    return 0;
   }

    
