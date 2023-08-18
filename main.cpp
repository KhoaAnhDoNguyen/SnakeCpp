#include <iostream>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
//#include <dir.h>
#include <cstdlib>
#include <time.h>
#define MAX 100
using namespace std;

int toa_do_x[MAX];
int toa_do_y[MAX];
int dot=4;
int x_ban_dau = 60;
int y_ban_dau = 15;
int xqua;
int yqua;
int Score=0;
int Speed = 150;
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void SetColor(int ForgC)
{
     int Word ,wColor;
      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
 }

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}

void Drawgameboard()
{
	char ch1(220), ch3 (222);
	SetColor(14);
	for (float x=10.5; x<112.5; x++)
	{
		gotoxy(x,3.5);
		cout << ch1;
		gotoxy(x,25);
		cout << ch1;
	}
	
	for (float y=4; y<26; y++)
	{
		gotoxy(10,y);
		cout << ch3;
		gotoxy(111,y);
		cout << ch3;
	}
}

void DrawSnake()
{
	
	for (int i=0; i<dot ; i++)
	{
		toa_do_x[i] = x_ban_dau;
		toa_do_y[i] = y_ban_dau;
		x_ban_dau -- ;
	}
}

void Snake()
{
	for (int i=0; i<dot ; i++)
	{
		SetColor(10);
		gotoxy (toa_do_x[i], toa_do_y[i]);
		if (i==0)
		cout << "O";
		else 
		cout << "o";
	}
}

int GameOver()
{
	if ( toa_do_x[0] == 10 || toa_do_x[0] == 111 || toa_do_y[0] == 3 || toa_do_y[0] ==25)
	return 0;
	else
	return 1;
}

int SnakeEatSnake()
{
	for (int i=1; i<dot ; i++)
	{
		if ( toa_do_x[0] == toa_do_x[i] && toa_do_y[0] == toa_do_y[i])
		return 3;
	}
}

void MoveSnake(int x, int y)
{
	for (int i=dot; i>0 ; i--)
	{
		toa_do_x[i] = toa_do_x[i-1];
		toa_do_y[i] = toa_do_y[i-1];
	}
	toa_do_x[0] =x;
	toa_do_y[0] =y;
}

void MakeFruit()
{
	xqua = rand() % (100-15+1)+15;
	yqua = rand() % (22-7+1)+7;
}

int FruitInSnake()
{
	for (int i=0 ; i<dot ; i++)
	{
		if (toa_do_x[i] == xqua && toa_do_y[i] == yqua)
		{
			return 2;
		}
	}
}

void DrawFruit()
{
	char Fruit(3);
	do
	{
		gotoxy (xqua,yqua);
		SetColor(9);
		cout << Fruit;
	} while ( FruitInSnake() == 2);
		
	
}


void SnakeEatFruit()
{
	if ( toa_do_x[0] == xqua && toa_do_y[0] == yqua)
	{
		dot +=1;
		Score +=1;
		gotoxy(100,1);
		SetColor(12);
		cout << "Score: " << Score;
		if (Score >= 5 && Score <=10)
		{
			Speed = 100;
		}
		else if (Score > 10 && Score <15)
		{
			Speed = 50;
		}
		else if (Score >=15)
		{
			Speed = 30;
		}
		MakeFruit();
		DrawFruit();
	}
	
}


int main()
{
	int x = x_ban_dau;
	int y = y_ban_dau;
	char button;
	int check =1;
	gotoxy(100,1);
	{
		SetColor(12);
		cout << "Score: 0";
	}
	srand(time(0));
	Drawgameboard();
	DrawSnake();
	MakeFruit();
	DrawFruit();
	while (true)
	{
		// Quy uoc 0: di len
		//			1: qua phai
		//			2: di xuong
		//			3: qua trai
		ShowCur(0);
		gotoxy( toa_do_x[dot], toa_do_y[dot]);
		cout << " ";
		Snake();
		if (kbhit())
		{
			button = getch();
			if (button == 72 && check != 2)
			{
				check =0;
			}
			else if (button == 80 && check != 0)
			{
				check =2;
			}
			else if (button == 75 && check !=1)
			{
				check =3;
			}
			else if (button == 77 && check !=3)
			{
				check =1;
			}
		}
				if (check ==0)
					{
						y--;
					}
					else if (check == 1)
						{
						x++;
						}
						else if (check == 2)
							{
							y++;
							}
							else if (check == 3)
								{
								x--;
								}
		
		if ( GameOver() == 0 )
		{
			gotoxy(100,1);
			cout << "\t\t\t";	
			break;
		}
		if ( SnakeEatSnake() == 3)
		{
			gotoxy(100,1);
			cout << "\t\t\t";
			break;
		}
		MoveSnake(x,y);
		SnakeEatFruit();
		Sleep(Speed);
	}
	gotoxy(50,10);
	SetColor(13);
	cout << "DIE !!!! :))) - Score: " << Score;
	getch();
	system("cls");
	return 0;
}
