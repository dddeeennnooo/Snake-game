#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <time.h>

//funkcia na nastavenie hry 
void Setup(int* height, int* width, int* score, int* x, int* y, int* fruitX, int* fruitY) {
    srand((unsigned int)time(NULL));

    *x = *height / 2;           //bod kde zaèína hadík
    *y = *width / 2;
    *score = 0;

    //spownovanie fruitu
    while (1) {
        *fruitX = 1 + rand() % *width;
        *fruitY = 1 + rand() % *height;

        if (*fruitX > 0 && *fruitY > 0 && *fruitX != *x && *fruitY != *y && *fruitX <= *height && *fruitY <= *width) {
            break;
        }
    }
}
//funkcia na vykreslenie 
void Draw(int* height, int* width, int* score, int* fruitX, int* fruitY, int* tailX, int* tailY, int* x, int* y, int* totalTail) {
    system("cls");

    for (int i = 0; i < *height; i++) {                                                 //vykreslenie arénky pre hada
        for (int j = 0; j < *width; j++) {
            if (i == 0 || j == 0 || i == *width - 1 || j == *height - 1) {
                printf("#");
            }
            else if (i == *x && j == *y) {
                printf("O");                                                            //vykreslenie hada
            }
            else if (*fruitX == i && *fruitY == j) {
                printf("F");                                                            //vykreslenie fruitu
            }
            else {
                int print = 0;                                                          //vykreslenie chvostika
                for (int k = 0; k < *totalTail; k++) {
                    if (tailX[k] == i && tailY[k] == j) {
                        printf("o");
                        print = 1;
                    }
                }
                if (print == 0) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", *score);                                                        //priebezne score
}

//ovladanie pomocou sipok
void Input1(int* s) {
    if (_kbhit()) {
        int key = _getch();
        switch (key) {
        case 72:
            *s = 1;
            break;
        case 80:
            *s = 2;
            break;
        case 75:
            *s = 3;
            break;
        case 77:
            *s = 4;
            break;
        }
    }
}

//ovladanie wasd
void Input2(int* s) {
    if (_kbhit()) {
        int key = _getch();
        switch (key) {
        case 'w':
            *s = 1;
            break;
        case 's':
            *s = 2;
            break;
        case 'a':
            *s = 3;
            break;
        case 'd':
            *s = 4;
            break;
        }
    }
}

//hlavna logika gamesky
void Logic(int* height, int* width, int* score, int* fruitX, int* fruitY, int* tailX, int* tailY, int* x, int* y, int* totalTail, int* s, int* gameOver) {
    int prevX = tailX[0];                                                   //pohyb hada s chvostikov
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = *x;
    tailY[0] = *y;
    for (int i = 1; i < *totalTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (*s) {                                                            //smer hada
    case 1:
        (*x)--;
        break;
    case 2:
        (*x)++;
        break;
    case 3:
        (*y)--;
        break;
    case 4:
        (*y)++;
        break;
    default:
        break;
    }

    //ukoncenie hry ked narazis do steny
    if (*x >= *width - 1 || *x <= 0 || *y >= *height - 1 || *y <= 0) {
        *gameOver = 1;
    }

    //ukoncenie hry ked narazis do seba 
    for (int i = 0; i < *totalTail; i++) {
        if (tailX[i] == *x && tailY[i] == *y) {
            *gameOver = 1;
        }
    }

    //podmienka aby sa fruit spownoval vzdy niekde inde 
    if (*x == *fruitX && *y == *fruitY) {
        *score += 1;
        (*totalTail)++;
    start2:
        *fruitX = 1 + rand() % (*width - 2);
        *fruitY = 1 + rand() % (*height - 2);

        if (*fruitX <= 0 || *fruitY <= 0 || *fruitX == *x || *fruitY == *y || *fruitX > *height || *fruitY > *width) {
            goto start2;
        }
    }
}