#include<iostream>
#include<conio.h>
#include"windows.h"
using namespace std;
bool gameover;
const int width = 20;
const int height = 20;
int x, y, fruitx, fruity;
int ntail=1,xlast=1,ylast=1;
int tailx[200], taily[200];
enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
direction dir;
int score;
void setup() {
	gameover = false;
	dir = STOP;
	tailx[0]=x = width / 2;
	taily[0]=y = width / 2;
	fruitx = rand() % 20;
	fruity = rand() % 20;
	score = 0;
}
void draw() {
	system("cls");
	//cout << endl;
	for (int i = 0; i < width; i++)  cout << "#";
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == width - 1 || j == 0)  cout << "#";
			else if (j == fruitx && i == fruity)  cout << "F";
			else if (j == x && i == y)  cout << "A";
			else{
				bool print = false;
					for (int k = 1; k < ntail; k++) {
						if (i == taily[k] && j == tailx[k])
						{
							cout << "O";
							print = true;
						}
					}
				if(!print)
				cout << " ";
			}
			
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++)  cout << "#";
	cout << endl;
	cout << "score: " << score;
}
void input() {
	if (_kbhit())
	{
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 'z':
			dir = DOWN;
			break;
		}
	}
}
void logic() {
	int prex = x, prey = y;
	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	ntail = (score / 10) + 1;
	if (fruitx == x && fruity == y) {
		score = score + 10;
		fruitx = rand() % 20;
		fruity = rand() % 20;

		ntail = (score / 10) + 1;
		if (ntail > 1) {
			tailx[0] = prex;  taily[0] = prey;
			for (int k = ntail - 1; k >=1; k--) {
				//int t = tailx[k];  int m = taily[k];    
				tailx[k] = tailx[k - 1];
				taily[k] = taily[k - 1];

			}

		}
	}
	if (ntail > 1 && (fruitx != x || fruity != y)) {
		tailx[0] = prex; taily[0] = prey;
		for (int k = ntail-1; k >= 1; k--) {

			tailx[k] = tailx[k - 1];
			taily[k] = taily[k - 1];
		}
	}
	if (x > width || x<0 || y>height || y < 0)  gameover = true;
	for (int i = 1; i < ntail; i++) {
		if (tailx[i] == x && taily[i] == y)
			gameover = true;
	}
}
int main() {
	setup();
	while (!gameover) {
		draw();
		input();
		logic();
		Sleep(300);
	}
	return 0;

}



