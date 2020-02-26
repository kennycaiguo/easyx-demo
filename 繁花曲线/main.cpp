#include <stdio.h>
#include <easyx.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <tchar.h>
#define PI 3.1415926

int fgbs(int n1, int n2) {
	int hcf, temp, lcm;


	hcf = n1;
	temp = n2;

	while (hcf != temp)
	{
		if (hcf > temp)
			hcf -= temp;
		else
			temp -= hcf;
	}

	lcm = (n1 * n2) / hcf;

	return lcm;
}

inline void calcDrawingPoint(long & resX, long & resY, long cenX, long centY, float angleRotation, float angleRevolution, float radiusInner, float radiusDraw) {
	long innerCenterX = sin(angleRevolution) * radiusInner;
	long innerCenterY = cos(angleRevolution) * radiusInner;

	long drawX = innerCenterX + sin(angleRotation) * radiusDraw;
	long drawY = innerCenterY + cos(angleRotation) * radiusDraw;

	resX = cenX + drawX;
	resY = centY + drawY;

}

void initRand() {
	srand((int)time(0));
}

void swapInteger(int * a, int * b) {
	*a += *b;
	*b = *a - *b;
	*a = *a - *b;;
}

int getNextRandomInteger(int min, int max) {
	if (min > max) {
		swapInteger(&min, &max);
	}
	return (rand() % (max - min)) + min;
}

void drawSth() {
	float radiusBig = 400;//外轮半径
	initgraph(radiusBig * 2, radiusBig * 2);	// 创建绘图窗口，大小为 640x480 像素

	for (int t = 0; t < 5; t++) {
		//float radiusSmall = 105;//内轮半径
		float radiusSmall = getNextRandomInteger(40, radiusBig - 20);
		//float toSide = 20;//内轮画点边距
		float toSide = getNextRandomInteger(3, radiusSmall - 20);
		long radiusScale = 10;//角度放大倍数
		long stepRadiusScaled = 1;//画图步长

		//每圈自传角度 大元等于小圆时,无转动角度,两动抵消,余量为小圆转动圈数,乘以360即为角度(小圆为反向转动)
		float innerSelfRadiusPerRound = 0.0 - ((radiusBig - radiusSmall) * 2 * PI / radiusSmall);
		//每圈公转角度
		float innerPublicRadiusPerRound = 2 * PI;

		float toCenter = radiusSmall - toSide;//内轮花点偏心距


		//circle(200, 200, 100);	// 画圆，圆心(200, 200)，半径 100
		//circle(radiusBig, radiusBig, radiusBig);
		int cr = getNextRandomInteger(10, 255);
		int cg = getNextRandomInteger(10, 255);
		int cb = getNextRandomInteger(10, 255);
		setlinecolor(RGB(cr, cg, cb));

		//linerel(10, 10);
		//lineto(20, 15);
		//lineto(25, 30);

		//计算外轮原点
		float outCx = radiusBig;
		float outCy = radiusBig;

		//计算内轮初始原点
		//float innerC0x = outCx - radiusBig + radiusSmall;
		//float innerC0y = outCy;

		float ric = 0;//内轮圆心位置角度
		float rid = 0;//内轮画芯位置角度

		int gbs = fgbs(radiusBig, radiusSmall);

		int pass = gbs / radiusBig;//总共要绕外圈转多少圈

		printf("%d\n", pass);

		if (pass > 120) {//圈数过大,重来
			t--;
			continue;
		}

		//double passed = 0;
		long roundStepNum = 360 * radiusScale; //每圆步数
		long totalStepNum = roundStepNum * pass;
		long currentStepIdx = 0; //当前步数游标
		while (currentStepIdx < totalStepNum) {
			long dx = 0;
			long dy = 0;
			ric = (currentStepIdx / (360.0 * radiusScale)) * innerPublicRadiusPerRound;
			rid = (currentStepIdx / (360.0 * radiusScale)) * innerSelfRadiusPerRound;
			calcDrawingPoint(dx, dy, outCx, outCy, rid, ric, radiusBig - radiusSmall, toCenter);

			//printf_s("currentStepIdx:%ld,rid:%f,ric:%f,X:%ld,Y:%ld\n", currentStepIdx,rid,ric, dx, dy);

			if (currentStepIdx) {//非第一个点
				lineto(dx, dy);
			}
			else {
				printf("moverel\n");
				moveto(dx, dy);
				lineto(dx, dy);
			}

			currentStepIdx += stepRadiusScaled;
		}
	}

	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
}

int main()
{
	initRand();
	drawSth();
	return 0;
}

