#include <graphics.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#define ROW 9
#define COL 9
#define CELL_WIDTH 40
#define MAX_MINE 20

int mine[ROW+2][COL+2];
IMAGE images[12];
MOUSEMSG msg;
int currentX, currentY;

void GameInit();	// 初始化扫雷数据
void GameDraw();	// 画界面
void print();		// 打印数据
void GameMouse();	// 获取鼠标消息
void Jude();		// 判断是否点到雷了
void OpenNull(int x, int y);	// 打开周围的空格子


int main()
{
	initgraph(ROW*CELL_WIDTH, COL*CELL_WIDTH, 1);
	
	GameInit();
	print();

	while (1)
	{
		
		GameMouse();

		GameDraw();

		Jude();
	}
	
	
	getchar();
	return 0;
}

void print()
{
	for (int i = 0; i < ROW+2; i++) {
		for (int j = 0; j < COL+2; j++) {
			printf("%5d", mine[i][j]);
		}
		printf("\n");
	}
}

void GameInit()
{
	// 随机生成雷
	srand((unsigned)time(NULL));
	int x, y;
	for (int i = 0; i < MAX_MINE; i++) {
		x = rand() % 8 + 1;
		y = rand() % 8 + 1;
		if (mine[x][y] == 0) {
			mine[x][y] = -1;
		}
	}
	// 遍历数组，对雷九宫格进行+1操作
	for (int i = 1; i < ROW+2; i++) {
		for (int j = 1; j < COL+2; j++) {
			if (mine[i][j] == -1)
			{
				for (int k = i-1; k <= i+1; k++) {
					for (int q = j-1; q <= j+1; q++) {
						if (mine[k][q] != -1)
						{
							mine[k][q]++;
						}
						
					}
				}
			}
		}
	}
	// 解密格子
	for (int i = 1; i <= ROW; i++) {
		for (int j = 1; j <= COL; j++) {
			mine[i][j] += 20;
		}
	}
	char tmp[20] = " ";
	for (int i = 0; i < 12; i++) {
		sprintf_s(tmp, "./images/%d.bmp", i);
		loadimage(&images[i], tmp, CELL_WIDTH, CELL_WIDTH);
	}

	
}

void GameDraw()
{
	for (int i = 1; i <= ROW; i++) {
		for (int j = 1; j <= COL; j++) {
			int x = (j-1) * CELL_WIDTH;
			int y = (i-1) * CELL_WIDTH;

			if (mine[i][j] >= 0 && mine[i][j] <= 8) {
				putimage(x, y, &images[mine[i][j]]);
			}
			else if (mine[i][j] == -1) {
				putimage(x, y, &images[9]);
			}
			else if (mine[i][j] >= 19 && mine[i][j] <= 28)
			{
				putimage(x, y, &images[10]);
			}
			else if (mine[i][j] > 30)
			{
				putimage(x, y, &images[11]);
			}
		}
	}
}

void GameMouse()
{
	if (MouseHit())
	{
		msg = GetMouseMsg();
		currentX = msg.y/ CELL_WIDTH + 1;
		currentY = msg.x / CELL_WIDTH + 1;
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			// 鼠标左键按下
			mine[currentX][currentY] -= 20;
			OpenNull(currentX, currentY);
		}
		else if (msg.uMsg == WM_RBUTTONDOWN)
		{
			// 鼠标右键按下, 标记一个格子
			if (mine[currentX][currentY] < 30)
			{
				mine[currentX][currentY] += 20;
			}
			else {
				mine[currentX][currentY] -= 20;
			}
		}
	}
}

void Jude()
{
	if (mine[currentX][currentY] == -1)
	{
		HWND hWnd = GetHWnd();
		int isok = MessageBox(hWnd, "点到雷了，是否继续？", "Game Over!", MB_YESNO);
		if (isok == IDYES)
		{
			mine[currentX][currentY] += 20;
		}
		else if (isok == IDNO)
		{
			exit(0);
		}
	}
	
}

void OpenNull(int x, int y)
{
	if (mine[x][y] == 0)
	{
		for (int i = x - 1; i <= x + 1; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				if (mine[i][j] == 20)
				{
					mine[i][j] -= 20;
					OpenNull(i, j);
				}
			}
		}
	}
}