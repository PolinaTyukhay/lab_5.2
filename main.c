#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <locale.h>

#define TRUE 1
#define FALSE 0

char newGameChoice = 0;
int gameOver = FALSE;
int wight = 16;
int Speed = 0;
int modeGame = 0;
int x = 0, y = 0, fruitX = 0, fruitY = 0, score = 0;
int tailX[100], tailY[100];
int nTail = 1;
//int dir = 0;
//тип перечисление (enum), задающий набор всех возможных целочисленных значений переменной этого типа. Синтаксис перечисления
enum eDirection {STOP=0, LEFT , RIGHT, UP, DOWN};
enum eDirection dir;

void hidecursor()
{
	HANDLE hCons;
	CONSOLE_CURSOR_INFO cci;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	cci.dwSize = 1;
	cci.bVisible = 0;
	SetConsoleCursorInfo(hCons, &cci);
}
void get_fruit() {
	do {
		fruitX = rand() % wight;
		fruitY = rand() % wight;
	} while (fruitX <= 1 || fruitX >= wight - 1 || fruitY <= 1 || fruitY >= wight - 1);
}
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
	get_fruit();
	score = 0;
 }
//
void Draw() {
	//system("cls");
	gotoxy(0, 0);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i <= wight; i++) {
		for (int j = 0; j <= wight; j++) {
			if (i == 0 || j == 0 || i == wight || j == wight) {
				SetConsoleTextAttribute(hConsole,(0 | 14));
				printf("#");
			}
			else if (i == x && j == y) {
				SetConsoleTextAttribute(hConsole, (0  | 2));
				printf("0");
			}
			else if (i == fruitX && j == fruitY) {
				SetConsoleTextAttribute(hConsole, (0  | 12));
				printf("@");
			}
			else {
				int print = FALSE;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] ==i && tailY[k] == j) {
						print = TRUE;
						SetConsoleTextAttribute(hConsole, (0  | 2));
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
	SetConsoleTextAttribute(hConsole, (0  | 7));
	printf("Score: %d", score);
	//dir = 1;
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
		case 'X':
			gameOver = TRUE;
			break;
		case 231:
			gameOver = TRUE;
			break;
		case 151:
			gameOver = TRUE;
			break;
	
		}
	}


}
// 
void Logic() {
	
	
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
	if (modeGame == 2) {
		if (x >= wight || x <= 0 || y >= wight || y <= 0) {
			gameOver = TRUE;
			system("cls");
			printf("GAME OWER\n");
		}
	}
	else {
		if (x >= wight) {
			x = 1;
		}
		else if(x<1) {
			x = wight - 1;
		}
		if (y >= wight) {
			y = 1;
		}
		else if (y <1) {
			y = wight - 1;
		}
	}
	for (int i = nTail-1; i > 0; i-- ) {
		
		tailX[i] = tailX[i - 1];
		tailY[i] = tailY[i - 1];
	}
	tailX[0] = x;
	tailY[0] = y;


	for (int i = 1; i < nTail; i++) {
		if (tailX[i] == x && tailY[i]==y ) {
			gameOver = TRUE;
			system("cls");
			printf("GAME OWER \n");
		}
	}
	if (x == fruitX && y == fruitY) {
		score += 10;
		get_fruit();
		nTail++;
	}
	
}
int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	//while (1) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (0  | 7));
	while (1)
	{
		printf("Game window size (16 - 25)\n");
		scanf_s("%d", &wight);
		if (!(wight < 16 || wight > 25)) break;

	}
	while (1)
	{
		
		printf("During the game- 'x' to exit!\nSpeed level: (1-40)\n");
		scanf_s("%d", &Speed);
		if (!(Speed < 1 || Speed > 40)) break;

	}
	while (1)
	{

		printf("Game mode:1)without bordes 2)with borders \n");
		scanf_s("%d", &modeGame);
		if (modeGame == 1 || modeGame ==2) break;

	}
	system("cls");
	hidecursor();
	    Setup();
	    Draw();
	
		while (!gameOver) {
			Sleep(1000 / Speed);
			//Draw();
			Input();
			Logic();
			Draw();
		}
	
			
	
	return(0);
}  