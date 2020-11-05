#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <locale.h>

#define TRUE 1
#define FALSE 0

int gameOver = FALSE;
int wight = 20;
int x = 0, y = 0, fruitX = 0, fruitY = 0, score = 0;
int tailX[100], tailY[100];
int nTail = 0;
//тип перечисление (enum), задающий набор всех возможных целочисленных значений переменной этого типа. Синтаксис перечисления
enum eDirection {STOP=0, LEFT , RIGHT, UP, DOWN};
enum eDirection dir;
//eDirection dir;
//настройка параметров
void gotoxy(int column, int row)
{
	HANDLE hCons;
	COORD crd;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);  
	crd.X = (short)column;
	crd.Y = (short)row;
	SetConsoleCursorPosition(hCons, crd);
}
void Setup() {
	gameOver = FALSE;
	dir = STOP;
	x = wight / 2;
	y = wight / 2;
	do {
		fruitX = rand() % wight;
		fruitY = rand() % wight;
	} while (fruitX <= 1 || fruitX >= wight-1 || fruitY <= 1 || fruitY >= wight-1);
	score = 0;
 }
//
void Draw() {
	//system("cls");
	gotoxy(0, 0);
	for (int i = 0; i <= wight; i++) {
		for (int j = 0; j <= wight; j++) {
			if (i == 0 || j == 0 || i == wight || j == wight) {
				printf("#");
			}
			else if (i == x && j == y) {
				printf("0");
			}
			else if (i == fruitX && j == fruitY) {
				printf("@");
			}
			else {
				int print = FALSE;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] ==i && tailY[k] == j) {
						print = TRUE;
						printf("o");
					}
				}
				if (!print) {
					printf(" ");
				}
			}
		}
		printf("\n");
	}
	printf("\n");
	printf("Score: %d", score);
}
//получеие нажатий 
void Input() {
	if (_kbhit()) {
		switch (_getch())
		{ 
		case 'w':
			dir = UP; //up
			break;
		case 's':
			dir = DOWN; //down
			break;
		case 'a':
			dir = LEFT; //left
			break;
		case 'd':
			dir = RIGHT; // right
			break;
		case 'W':
			dir = UP; //up
			break;
		case 'S':
			dir = DOWN; //down
			break;
		case 'A':
			dir = LEFT; //left
			break;
		case 'D':
			dir = RIGHT; // right
			break;
		//русские маленькие 
		case 230:
			dir = UP; //up
			break;
		case 235:
			dir = DOWN; //down
			break;
		case 228:
			dir = LEFT; //left
			break;
		case 162:
			dir = RIGHT; // right
			break;
		// русские большие 
		case 150:
			dir = UP; //up
			break;
		case 155:
			dir = DOWN; //down
			break;
		case 148:
			dir = LEFT; //left
			break;
		case 130:
			dir = RIGHT; // right
			break;
		// стрелки 
		case 72:
			dir = UP; //up
			break;
		case 80 :
			dir = DOWN; //down
			break;
		case 75:
			dir = LEFT; //left
			break;
		case 77:
			dir = RIGHT; // right
			break;
		case 'x':
			gameOver = TRUE;
			break;
	
		}
	}


}
// 
void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X = 0, prev2Y = 0;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++ ) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case UP:
		x--;
		break;
	case DOWN:
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	}
	/*if (x > wight||x < 0||y > wight||y < 0) {
		gameOver = TRUE;
 
	}*/
	if (x >= wight) {
		x = 0;
	}
	else if(x<0) {
		x = wight - 1;
	}
	if (y >= wight) {
		y = 0;
	}
	else if (y < 0) {
		y = wight - 1;
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i]==y ) {
			gameOver = TRUE;
			system("cls");
			printf("столкнулись с собой  \n");
		}
	}
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % wight;
		fruitY = rand() % wight;
		nTail++;
	}
	
}
int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	Setup();
	//Draw();
	while (!gameOver) {
		Sleep(200);
		Draw();
		Input();
		Logic();

	}
	return(0);
}  