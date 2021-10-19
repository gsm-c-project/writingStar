#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#pragma warning(disable : 4996)warning pragma

typedef struct point {
	double x;
	double y;

}D2point;

typedef struct line {
	D2point p2;
	D2point p1;
}D2line;


typedef struct D3point {
	double x;
	double y;
	double z;
}D3point;

typedef struct D3line {
	D3point p1;
	D3point p2;
}D3line;




int key2code(int key) {
	switch (key) {
	case 119:
		return 0;
	case 97:
		return 1;
	case 115:
		return 2;
	case 100:
		return 3;
	case 113:
		return 4;
	case 101:
		return 5;
	case 27:
		return 27;
	}
}
void gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void remove_scrollbar()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size = {
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}
//그래픽(별)을 보여주는 함수
void show_graphic(char** graphic) {
	system("cls");
	for (int i = 0; i < 60; ++i) {
		for (int k = 0; k < 120; ++k) {
			printf("%c", graphic[i][k]);
		}
		printf("\n");
	}
	return;

}
void show_custom(char** graphic) {
	system("cls");
	for (int i = 0; i < 60; ++i) {
		for (int k = 0; k < 150; ++k) {
			printf("%c", graphic[i][k]);
		}
		printf("\n");
	}
	return;
}
void show_pos() {
	gotoxy(25, 40);
	printf("00");
	gotoxy(35, 40);
	printf("01");
	gotoxy(45, 40);
	printf("02");
	gotoxy(55, 40);
	printf("03");
	gotoxy(65, 40);
	printf("04");
	gotoxy(25, 35);
	printf("05");
	gotoxy(35, 35);
	printf("06");
	gotoxy(45, 35);
	printf("07");
	gotoxy(55, 35);
	printf("08");
	gotoxy(65, 35);
	printf("09");
	gotoxy(25, 30);
	printf("10");
	gotoxy(35, 30);
	printf("11");
	gotoxy(45, 30);
	printf("12");
	gotoxy(55, 30);
	printf("13");
	gotoxy(65, 30);
	printf("14");
	gotoxy(25, 25);
	printf("15");
	gotoxy(35, 25);
	printf("16");
	gotoxy(45, 25);
	printf("17");
	gotoxy(55, 25);
	printf("18");
	gotoxy(65, 25);
	printf("19");
	gotoxy(25, 20);
	printf("20");
	gotoxy(35, 20);
	printf("21");
	gotoxy(45, 20);
	printf("22");
	gotoxy(55, 20);
	printf("23");
	gotoxy(65, 20);
	printf("24");
	gotoxy(18, 19);
	printf("45:~");
	gotoxy(18, 14);
	printf("70:~");
	gotoxy(18, 9);
	printf("95:~");
	gotoxy(18, 4);
	printf("120:~");
	//gotoxy()
	gotoxy(0, 0);
}
//그래픽(별)을 제거하는 함수
void clear_graphic(char** graphic) {
	system("cls");
	for (int i = 0; i < 60; ++i) {
		for (int k = 0; k < 120; ++k) {
			graphic[i][k] = ' ';
		}
	}
}
void clear_custom(char** graphic) {
	system("cls");
	for (int i = 0; i < 60; ++i) {
		for (int k = 0; k < 150; ++k) {
			graphic[i][k] = ' ';
		}
	}
}
void colrow2(double x, double y, int* rowcol, int isCustom) {//좌표를　행렬로　바꿔준다
	if (isCustom == 0) {
		rowcol[0] = (int)(59 - floor(y));
		rowcol[1] = (int)(floor(2 * x));
	}
	else {
		rowcol[0] = (int)(59 - floor(y));
		rowcol[1] = (int)(floor(2 * x));
	}
}


double inclination(D2line* p) {//직선　입력시에　기울기를　리턴
	return (((p->p1.y) - (p->p2.y)) / ((p->p1.x) - (p->p2.x)));
}


//ｘ좌표를　시작점부터　일정하게　키우면서　ｙ값을　찾고　그　값을　반올림하면　행， 열에　해당하는　정수를　얻을　수　있음
//한 열에 별이 최대 하나밖에 찍히지 않으므로, 기울기가 큰 직선은 y값을 키우며 접근하도록 한다
void put_graphic(char** graphic, D2line* straight, int* rowcol) { // 직선　입력시　직선을　그래픽에　찍는　함수
	double start;
	double end;
	double inc;
	double i;
	inc = inclination(straight);
	if (inc<2 && inc>-2) {
		start = (straight->p1.x > straight->p2.x) ? straight->p2.x : straight->p1.x;
		end = straight->p2.x + straight->p1.x - start;
		for (i = start; !(i > end); i += 0.5) {
			colrow2(i, inc * (i - straight->p1.x) + straight->p1.y, rowcol, 0);
			graphic[rowcol[0]][rowcol[1]] = '*';
		}

	}
	else {
		start = (straight->p1.y > straight->p2.y) ? straight->p2.y : straight->p1.y;
		end = straight->p2.y + straight->p1.y - start;
		for (i = start; !(i > end); i += 1) {
			colrow2((i - straight->p1.y) / inc + straight->p1.x, i, rowcol, 0);
			graphic[rowcol[0]][rowcol[1]] = '*';
		}
	}

	return;
}


void put_custom(char** graphic, D2line* straight, int* rowcol) { // 직선　입력시　직선을　그래픽에　찍는　함수
	double start;
	double end;
	double inc;
	double i;
	inc = inclination(straight);
	if (inc<6 && inc>-6) {
		start = (straight->p1.x > straight->p2.x) ? straight->p2.x : straight->p1.x;
		end = straight->p2.x + straight->p1.x - start;
		for (i = start; !(i > end); i += 0.5) {
			colrow2(i, inc * (i - straight->p1.x) + straight->p1.y, rowcol, 1);
			graphic[rowcol[0]][rowcol[1]] = '*';
		}
		/*printf("%d %d", rowcol[0], rowcol[1]);
		exit(0);*/
	}
	else {
		start = (straight->p1.y > straight->p2.y) ? straight->p2.y : straight->p1.y;
		end = straight->p2.y + straight->p1.y - start;
		for (i = start; !(i > end); i += 1) {
			colrow2((i - straight->p1.y) / inc + straight->p1.x, i, rowcol, 1);
			graphic[rowcol[0]][rowcol[1]] = '*';

		}
		/*printf("%d %d", rowcol[0], rowcol[1]);
		exit(0);*/
	}

	return;
}

//3차원에서 직선을 받으면 직선을 평행이동 시키는 함수
void parallel_model(D3line* D3, int n) { //n = 1 +=30 / n = -1 -=30
	if (n > 0) {
		D3->p1.x += 30;
		D3->p1.y += 30;
		D3->p1.z += 30;
		D3->p2.x += 30;
		D3->p2.y += 30;
		D3->p2.z += 30;
	}
	else {
		D3->p1.x -= 30;
		D3->p1.y -= 30;
		D3->p1.z -= 30;
		D3->p2.x -= 30;
		D3->p2.y -= 30;
		D3->p2.z -= 30;
	}
}



//3차원에서 직선 회전
/*
어떤 점  p (x,y,z)에 대하여
x축 기준 회전하면
x' = x
y' = y cosθ - z sinθ
z' = y sinθ + z cosθ

y축 기준 회전
x' = z sinθ + x cosθ
y' = y
z' = z cosθ - x sinθ

z축 기준 회전
x' = x cosθ + - y sinθ
y' = x sinθ + y cosθ
z' = z
*/
void spin_model(D3line* LP, int axis, double theta) {//1:x 2:y 3:z
	double xpos, ypos, zpos;
	if (axis == 1) {
		xpos = LP->p1.x;
		ypos = LP->p1.y;
		zpos = LP->p1.z;
		LP->p1.x = xpos;
		LP->p1.y = ypos * cos(theta) - zpos * sin(theta);
		LP->p1.z = ypos * sin(theta) + zpos * cos(theta);
		xpos = LP->p2.x;
		ypos = LP->p2.y;
		zpos = LP->p2.z;
		LP->p2.x = xpos;
		LP->p2.y = ypos * cos(theta) - zpos * sin(theta);
		LP->p2.z = ypos * sin(theta) + zpos * cos(theta);
	}
	else if (axis == 2) {
		xpos = LP->p1.x;
		ypos = LP->p1.y;
		zpos = LP->p1.z;
		LP->p1.x = zpos * sin(theta) + xpos * cos(theta);
		LP->p1.y = ypos;
		LP->p1.z = zpos * cos(theta) - xpos * sin(theta);
		xpos = LP->p2.x;
		ypos = LP->p2.y;
		zpos = LP->p2.z;
		LP->p2.x = zpos * sin(theta) + xpos * cos(theta);
		LP->p2.y = ypos;
		LP->p2.z = zpos * cos(theta) - xpos * sin(theta);
	}
	else {
		xpos = LP->p1.x;
		ypos = LP->p1.y;
		zpos = LP->p1.z;
		LP->p1.x = xpos * cos(theta) - ypos * sin(theta);
		LP->p1.y = xpos * sin(theta) + ypos * cos(theta);
		LP->p1.z = zpos;
		xpos = LP->p2.x;
		ypos = LP->p2.y;
		zpos = LP->p2.z;
		LP->p2.x = xpos * cos(theta) - ypos * sin(theta);
		LP->p2.y = xpos * sin(theta) + ypos * cos(theta);
		LP->p2.z = zpos;
	}
}



//3차원 직선을 2차원에서 볼 수 있게
void orthogonal_projetion(D3line* D3, D2line* D2) {
	D2->p1.x = D3->p1.x;
	D2->p1.y = D3->p1.z;
	D2->p2.x = D3->p2.x;
	D2->p2.y = D3->p2.z;
}

void controll(D3line* dot, int pos, double theta, D2line D2li, int* rowcol, char** graphic, int count) {

	for (int i = 0; i < count; ++i) {
		parallel_model(&dot[i], -1);
		spin_model(&dot[i], pos, theta);
		parallel_model(&dot[i], 1);
	}
	clear_graphic(graphic);
	for (int i = 0; i < count; ++i) {
		orthogonal_projetion(&dot[i], &D2li);
		put_graphic(graphic, &D2li, rowcol);
	}
	show_graphic(graphic);
}
void controll_custom(D3line* dot, int pos, double theta, D2line D2li, int* rowcol, char** graphic, int count) {

	for (int i = 0; i < count; ++i) {
		parallel_model(&dot[i], -1);
		spin_model(&dot[i], pos, theta);
		parallel_model(&dot[i], 1);
	}
	clear_custom(graphic);
	for (int i = 0; i < count; ++i) {
		orthogonal_projetion(&dot[i], &D2li);
		put_custom(graphic, &D2li, rowcol);
	}
	show_custom(graphic);
}





int main() {
	remove_scrollbar();
	srand(time(NULL));
	int N;
	D2line D2l1; //줄을 긋기 위한 2차원 직선
	int model;
	D3point* points;

	D3line* line;


	points = (D3point*)malloc(sizeof(D3point) * 8); //초기화

	char** graphic; //화면의 그래픽
	int* rowcol; //2차원 좌표를 행렬로 바꿀때 쓸 배열
	rowcol = (int*)malloc(sizeof(int) * 2);


	//그래픽　배열　초기화
	graphic = (char**)malloc(sizeof(char*) * 60);
	for (int i = 0; i < 60; ++i) graphic[i] = (char*)malloc(sizeof(char) * 120);
	for (int i = 0; i < 60; ++i) {
		for (int k = 0; k < 120; ++k) {
			graphic[i][k] = ' ';
		}
	}

SELC:
	system("cls");
	printf("삼각뿔 : 1		정육면체 : 2			커스텀 : 3\n");
	scanf("%d", &model);









	Sleep(10);

	//사각형
	//3차원 큐브배열에 12개의 선을 저장
	if (model == 2) {
		N = 0;
		for (int i = 15; i <= 45; i += 30) {
			for (int k = 15; k <= 45; k += 30) {
				for (int m = 15; m <= 45; m += 30) {
					points[N].x = m;
					points[N].y = k;
					points[N].z = i;
					N++;
				}
			}
		}
		graphic = (char**)malloc(sizeof(char*) * 60);
		for (int i = 0; i < 60; ++i) graphic[i] = (char*)malloc(sizeof(char) * 120);
		for (int i = 0; i < 60; ++i) {
			for (int k = 0; k < 120; ++k) {
				graphic[i][k] = ' ';
			}
		}
		line = (D3line*)malloc(sizeof(D3line) * 12);
		line[0].p1 = points[0];
		line[0].p2 = points[1];
		line[1].p1 = points[3];
		line[1].p2 = points[1];
		line[2].p1 = points[2];
		line[2].p2 = points[3];
		line[3].p1 = points[0];
		line[3].p2 = points[2];
		line[4].p1 = points[4];
		line[4].p2 = points[0];
		line[5].p1 = points[5];
		line[5].p2 = points[1];
		line[6].p1 = points[7];
		line[6].p2 = points[3];
		line[7].p1 = points[6];
		line[7].p2 = points[2];
		line[8].p1 = points[5];
		line[8].p2 = points[4];
		line[9].p1 = points[7];
		line[9].p2 = points[5];
		line[10].p1 = points[6];
		line[10].p2 = points[7];
		line[11].p1 = points[6];
		line[11].p2 = points[4];





		for (int i = 0; i < 12; ++i) {
			parallel_model(&line[i], -1);
			spin_model(&line[i], 3, 3.14 / 10);
			spin_model(&line[i], 1, 3.14 / 10);
			parallel_model(&line[i], 1);
		}
		for (int i = 0; i < 12; ++i) {
			orthogonal_projetion(&line[i], &D2l1);
			put_graphic(graphic, &D2l1, rowcol);
		}
		show_graphic(graphic);

		int key;
		while (1) {
			N = 0;
			for (int i = 15; i <= 45; i += 30) {
				for (int k = 15; k <= 45; k += 30) {
					for (int m = 15; m <= 45; m += 30) {
						points[N].x = m;
						points[N].y = k;
						points[N].z = i;
						N++;
					}
				}
			}
			key = getch();
			key = key2code(key);
			switch (key) {
			case 27:
				system("cls");
				clear_graphic(graphic);
				goto SELC;
				break;
			case 0:
				controll(line, 1, -(3.14 / 80), D2l1, rowcol, graphic, 12);
				break;
			case 1:
				controll(line, 3, -(3.14 / 80), D2l1, rowcol, graphic, 12);
				break;
			case 2:
				controll(line, 1, (3.14 / 80), D2l1, rowcol, graphic, 12);
				break;
			case 3:
				controll(line, 3, (3.14 / 80), D2l1, rowcol, graphic, 12);
				break;
			case 4:
				controll(line, 2, -(3.14 / 80), D2l1, rowcol, graphic, 12);
				break;
			case 5:
				controll(line, 2, (3.14 / 80), D2l1, rowcol, graphic, 12);
				break;
			}
		}
	}
	else if (model == 1) {
		graphic = (char**)malloc(sizeof(char*) * 60);
		for (int i = 0; i < 60; ++i) graphic[i] = (char*)malloc(sizeof(char) * 120);
		for (int i = 0; i < 60; ++i) {
			for (int k = 0; k < 120; ++k) {
				graphic[i][k] = ' ';
			}
		}
		N = 0;
		for (int i = 15; i <= 45; i += 30) {
			for (int k = 15; k <= 45; k += 30) {
				for (int m = 15; m <= 45; m += 30) {
					points[N].x = m;
					points[N].y = k;
					points[N].z = i;
					N++;
				}
			}
		}
		line = (D3line*)malloc(sizeof(D3line) * 6);
		points[7].x = (points[3].x + points[1].x + points[0].x) / 3;
		points[7].y = (points[3].y + points[1].y + points[0].y) / 3;
		points[7].z = 35;
		points[3].x = points[3].x - 5;
		points[7].x = points[7].x - 10;
		points[7].z = points[7].z - 3;

		line[0].p1 = points[0];
		line[0].p2 = points[1];
		line[1].p1 = points[0];
		line[1].p2 = points[3];
		line[2].p1 = points[1];
		line[2].p2 = points[3];
		line[3].p1 = points[0];
		line[3].p2 = points[7];
		line[4].p1 = points[1];
		line[4].p2 = points[7];
		line[5].p1 = points[3];
		line[5].p2 = points[7];
		for (int i = 0; i < 6; ++i) {
			parallel_model(&line[i], -1);
			spin_model(&line[i], 3, 3.14 / 10);
			spin_model(&line[i], 2, 3.14 / 10);
			spin_model(&line[i], 1, 3.14 / 10);
			parallel_model(&line[i], 1);
		}
		for (int i = 0; i < 6; ++i) {
			orthogonal_projetion(&line[i], &D2l1);
			put_graphic(graphic, &D2l1, rowcol);
		}
		show_graphic(graphic);
		int key;
		while (1) {

			key = getch();
			key = key2code(key);
			switch (key) {
			case 27:
				system("cls");
				clear_graphic(graphic);
				goto SELC;
				break;
			case 0:
				controll(line, 1, -(3.14 / 80), D2l1, rowcol, graphic, 6);
				break;
			case 1:
				controll(line, 3, -(3.14 / 80), D2l1, rowcol, graphic, 6);
				break;
			case 2:
				controll(line, 1, (3.14 / 80), D2l1, rowcol, graphic, 6);
				break;
			case 3:
				controll(line, 3, (3.14 / 80), D2l1, rowcol, graphic, 6);
				break;
			case 4:
				controll(line, 2, -(3.14 / 80), D2l1, rowcol, graphic, 6);
				break;
			case 5:
				controll(line, 2, (3.14 / 80), D2l1, rowcol, graphic, 6);
				break;
			}
		}
	}
	//xpfvh

	else if (model == 3) { //Custom
		system("cls");
		graphic = (char**)malloc(sizeof(char*) * 60);
		for (int i = 0; i < 60; ++i) graphic[i] = (char*)malloc(sizeof(char) * 150);
		for (int i = 0; i < 60; ++i) {
			for (int k = 0; k < 150; ++k) {
				graphic[i][k] = ' ';
			}
		}
		points = (D3point*)malloc(sizeof(D3point) * 125);

		int M = 0;
		for (int i = 15; i <= 55; i += 10) {
			for (int k = 15; k <= 55; k += 10) {
				for (int m = 15; m <= 55; m += 10) {
					points[M].x = m;
					points[M].y = k;
					points[M].z = i;
					M++;
				}
			}
		}

		int linenum;
		printf("선의 개수 : ");
		scanf("%d", &linenum);

		line = (D3line*)malloc(sizeof(D3line) * linenum);


		int Dot = 0;

		system("cls");

		while (1) {
			int Apos, Bpos;
			if (Dot == linenum)
				break;
			show_pos();
			gotoxy(0, 0);
			printf("0을 2번 입력시 종료\n");
			printf("연결할 1번 점 : ");
			scanf("%d", &Apos);
			printf("연결할 2번 점 : ");
			scanf("%d", &Bpos);

			if (Apos == 0 && Bpos == 0)
				break;
			line[Dot].p1 = points[Apos];
			line[Dot].p2 = points[Bpos];
			Dot++;



			Sleep(200);
			system("cls");

		}
		int key;
		clear_custom(graphic);
		for (int i = 0; i < linenum; ++i) {
			parallel_model(&line[i], -1);
			spin_model(&line[i], 3, 3.14 / 10);
			spin_model(&line[i], 1, 3.14 / 10);
			parallel_model(&line[i], 1);
		}
		for (int i = 0; i < linenum; ++i) {
			orthogonal_projetion(&line[i], &D2l1);
			put_graphic(graphic, &D2l1, rowcol);
		}
		show_custom(graphic);

		while (1) {
			key = getch();
			key = key2code(key);
			switch (key) {
			case 27:
				system("cls");
				clear_graphic(graphic);
				goto SELC;
				break;
			case 0:
				controll(line, 1, -(3.14 / 80), D2l1, rowcol, graphic, Dot);
				break;
			case 1:
				controll(line, 3, -(3.14 / 80), D2l1, rowcol, graphic, Dot);
				break;
			case 2:
				controll(line, 1, (3.14 / 80), D2l1, rowcol, graphic, Dot);
				break;
			case 3:
				controll(line, 3, (3.14 / 80), D2l1, rowcol, graphic, Dot);
				break;
			case 4:
				controll(line, 2, -(3.14 / 80), D2l1, rowcol, graphic, Dot);
				break;
			case 5:
				controll(line, 2, (3.14 / 80), D2l1, rowcol, graphic, Dot);
				break;
			}
		}



	}
}