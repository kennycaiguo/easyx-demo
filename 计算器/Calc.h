#pragma once
#include <graphics.h>
#include <string>
#include <conio.h>
#include <cmath>
#include <algorithm>

using namespace std;

// 宏定义
#define _CRT_SECURE_NO_WARNINGS
#define WIDTH		420													// 窗口宽度
#define HEIGHT		600													// 窗口高度
#define BKCOLOR		RGB(LIGHTRED, LIGHTGREEN, 0)						// 背景颜色
#define WNDCOLOR    RGB(238, 224, 229)									// 窗口颜色
#define COLOR1		RGB(244, 36, 198)									// 按钮颜色 1
#define COLOR2		RGB(116, 47, 250)									// 按钮颜色 2
#define COLOR3		RGB(255, 128, 0)									// 按钮颜色 3

// 按钮类
class GButton
{
private:
	int x;
	int y;
	int cx;
	int cy;
	string String;
	COLORREF color;
public:
	GButton();
	void GButtonX(int x1, int y1, int cx1, int cy1, char *str, COLORREF colors);
	void GButtonX(int x1, int y1, int cx1, int cy1, char c, COLORREF colors);
	void PaintButton();
	void PainButtonWall(COLORREF color);
	string ReturnButtonString();
};

// 编辑框类
class GEdit {
private:
	int x;
	int y;
	int cx;
	int cy;
	int maxsize;
	string String;
public:
	GEdit();
	void GEditX(int x1, int y1, int size);
	void PaintEdit();
	void ShowEdit();
	void SetEditString(string Strings);
};

class GCount {
private:
	string String;
	GEdit edit;
	GButton button[6][4];
	MOUSEMSG msg;
	int xNow;			// 当前按钮
	int yNow;			// 当前按钮
	int xPre;			// 上一次按钮
	int yPre;			// 上一次按钮
	bool flag;
	string left;
	string right;
	char oper;
	double number1;
	double number2;
	char str1[100]; 
public:
	GCount();
	void Run();
	void CreateCount(); 
	void ProcessMsg();
	bool OnLocate(int x, int y);				// 定位
	void OnMouseMoveButton(int x, int y);		// 鼠标移动到按钮上
	void OnLeftButtonDown(int x, int y);		// 鼠标左键按下
	void OnSetData();
	void OnCompute();							// 计算
	void OnAdd();								// 加法操作
	void OnSub();								// 减法操作
	void OnMul();								// 乘法操作
	void OnDiv();								// 除法操作
	void OnMod();								// 取模操作
	void OnSqu();								// 求平方
	void OnExp();								// 指数计算
	void OnRec();								// 求倒数
	void OnSqr();								// 开平方
};

extern void Retangle(int x1, int y1, int x2, int y2, COLORREF color);