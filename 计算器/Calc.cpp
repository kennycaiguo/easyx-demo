#include "Calc.h"

GButton::GButton()
{
	x = 0;
	y = 0;
	cx = 0;
	cy = 0;
	String = "0";
}

void GButton::GButtonX(int x1, int y1, int cx1, int cy1, char* str, COLORREF colors)
{
	x = x1;
	y = y1;
	cx = cx1;
	cy = cy1;
	String = str;
	color = colors;
	PaintButton();
}

void GButton::GButtonX(int x1, int y1, int cx1, int cy1, char c, COLORREF colors)
{
	x = x1;
	y = y1;
	cx = cx1;
	cy = cy1;
	String = c;
	color = colors;
	PaintButton();
}

// 绘制按钮
void GButton::PaintButton()
{
	setbkmode(TRANSPARENT);
	Retangle(x, y, x + cx, y + cy, color);
	if (String.length() < 3) {
		outtextxy(x + cx / 2 - 5, y + cy / 2 - 5, String.c_str());
	}
	else if (String.length() == 3) {
		outtextxy(x + cx / 2 - 15, y + cy / 2 - 5, String.c_str());
	}
	else {
		outtextxy(x + cx / 2 - 20, y + cy / 2 - 5, String.c_str());
	}
	PainButtonWall(LIGHTGRAY);
}

void GButton::PainButtonWall(COLORREF color)
{
	setcolor(color);
	rectangle(x, y, x + cx, y + cy);
	setcolor(WNDCOLOR);
}

string GButton::ReturnButtonString()
{
	return String;
}

GEdit::GEdit()
{
	x = 0;
	y = 0;
	cx = 0;
	cy = 0;
	String = "";
}

void GEdit::GEditX(int x1, int y1, int size)
{
	x = x1;
	y = y1;
	maxsize = size;
	PaintEdit();
}

void GEdit::PaintEdit()
{
	Retangle(x, y, x + 380, y + 40, BKCOLOR);
	setcolor(LIGHTGRAY);
	rectangle(x, y, x + 380, y + 40);
	setcolor(WNDCOLOR);
}

void GEdit::ShowEdit()
{
	if (String.length() > maxsize) {
		String = String.substr(0, 44);
	}
	outtextxy(25, 35, String.c_str());
}

void GEdit::SetEditString(string Strings)
{
	String = Strings;
}

// 绘制填充矩形
void Retangle(int x1, int y1, int x2, int y2, COLORREF color)
{
	int points[] = { x1, y1,x1, y2,x2, y2,x2,y1 };
	setlinestyle(PS_SOLID, 5);
	setfillcolor(color);
	fillpoly(4, points);
}

GCount::GCount()
{
	int x1 = 20;
	int y1 = 100;
	xPre = 0;
	yPre = 0;
	xNow = 0;
	yNow = 0;
	String = "";
	left = "";
	right = "";
	oper = '0';
	flag = false;
	number1 = number2 = 0.0;

	CreateCount();
	settextstyle(16, 0, _T("Fixedsys"));

	// 第 0 行
	button[0][0].GButtonX(20, 100, 80, 50, '1', COLOR1);
	button[0][1].GButtonX(120, 100, 80, 50, '2', COLOR1);
	button[0][2].GButtonX(220, 100, 80, 50, '3', COLOR1);
	button[0][3].GButtonX(320, 100, 80, 50, '0', COLOR1);

	// 第 1 行
	button[1][0].GButtonX(20, 170, 80, 50, '4', COLOR1);
	button[1][1].GButtonX(120, 170, 80, 50, '5', COLOR1);
	button[1][2].GButtonX(220, 170, 80, 50, '6', COLOR1);
	button[1][3].GButtonX(320, 170, 80, 50, '.', COLOR1);

	// 第 2 行
	button[2][0].GButtonX(20, 240, 80, 50, '7', COLOR1);
	button[2][1].GButtonX(120, 240, 80, 50, '8', COLOR1);
	button[2][2].GButtonX(220, 240, 80, 50, '9', COLOR1);
	button[2][3].GButtonX(320, 240, 80, 50, '%', COLOR2);

	// 第 3 行
	button[3][0].GButtonX(20, 310, 80, 50, '+', COLOR2);
	button[3][1].GButtonX(120, 310, 80, 50, '-', COLOR2);
	button[3][2].GButtonX(220, 310, 80, 50, '*', COLOR2);
	button[3][3].GButtonX(320, 310, 80, 50, '/', COLOR2);

	// 第 4 行
	button[4][0].GButtonX(20, 380, 80, 50, _T("+/-"), COLOR2);
	button[4][1].GButtonX(120, 380, 80, 50, _T("rec"), COLOR2);
	button[4][2].GButtonX(220, 380, 80, 50, _T("x^2"), COLOR2);
	button[4][3].GButtonX(320, 380, 80, 50, _T("exp"), COLOR2);

	// 第 5 行
	button[5][0].GButtonX(20, 450, 80, 50, _T("sqrt"), COLOR2);
	button[5][1].GButtonX(120, 450, 80, 50, _T("<--"), COLOR3);
	button[5][2].GButtonX(220, 450, 180, 50, _T("Clear"), COLOR3);
	button[5][3].GButtonX(20, 520, 380, 50, _T("==="), COLOR2);

	edit.GEditX(20, 20, 45);
}

void GCount::Run()
{
	ProcessMsg();
	edit.ShowEdit();
}

void GCount::CreateCount()
{
	initgraph(WIDTH, HEIGHT);
	setbkcolor(BKCOLOR);
	cleardevice();
	Retangle(0, 0, WIDTH, HEIGHT, WNDCOLOR);
	setcolor(COLOR2);
	line(10, 90, 410, 90);
	line(10, 90, 10, 580);
	line(410, 90, 410, 580);
	line(110, 510, 410, 510);
	line(10, 580, 410, 580);
	line(10, 300, 310, 300);
	line(310, 230, 310, 300);
	line(310, 230, 410, 230);
	line(110, 440, 410, 440);
	line(110, 440, 110, 510);
	setcolor(WNDCOLOR);
}

void GCount::ProcessMsg()
{
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;
	while (MouseHit()) {						// 如果有鼠标消息
		msg = GetMouseMsg();					// 获取鼠标事件
		OnMouseMoveButton(msg.x, msg.y);		// 鼠标移动到按钮上
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:
			OnLeftButtonDown(msg.x, msg.y);		// 鼠标左键按下
			edit.PaintEdit();					// 重绘编辑框
			break;
		default:
			break;
		}
		if (String.length() == 0) {
			flag = false;
		}
	}
}

bool GCount::OnLocate(int x, int y)
{
	int n1 = 0, n2 = 0;
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

	// 定位鼠标
	if (x >= 20 && x <= 540) {
		if ((y >= 100 && y <= 430) || (x <= 200 && y >= 450 && y <= 500)) {
			x1 = (x - 20) / 100;
			y1 = (y - 100) / 70;
			x2 = floor((x - 100) / 100.0);
			y2 = floor((y - 150) / 70.0);
		}

		// 成功定位i再按钮上
		if (x1 != x2 && y1 != y2 && (y >= 100)) {
			// 修改当前按钮
			xNow = x1;
			yNow = y1;
			return true;
		}
	}

	// 位于 Clear 按钮内部
	if ((x > 220 && x <= 540) && (y >= 450 && y <= 500)) {
		xNow = 2;
		yNow = 5;
		return true;
	}

	// 位于 == 按钮内部
	if ((x >= 20 && x <= 540) && (y >= 520 && y <= 570)) {
		xNow = 3;
		yNow = 5;
		return true;
	}
	// 定位失败
	return false;
}

void GCount::OnMouseMoveButton(int x, int y)
{
	bool isLocate = OnLocate(x, y);
	if (isLocate) {
		// 恢复前一个按钮的边框颜色
		button[yPre][xPre].PainButtonWall(LIGHTGRAY);

		// 重置前一次按钮的值
		xPre = xNow;
		yPre = yNow;

		// 绘制当前按钮的边框颜色
		button[yNow][xNow].PainButtonWall(LIGHTGREEN);
	}
}

// 鼠标左键按下
void GCount::OnLeftButtonDown(int x, int y)
{
	bool isLocate = OnLocate(x, y);
	//printf("%d\n", isLocate);
	if (isLocate) {
		// 按钮上第一个字母
		switch (button[yNow][xNow].ReturnButtonString()[0]) {
			// 清楚编辑器
		case 'C':
			String = "";
			OnSetData();
			break;
			// 这里有两个操作符使用了 '+' 号, 一个是正负号, 一个是真的加号
		case '+':
			if (button[yNow][xNow].ReturnButtonString()[1] == '/') {
				if (String[0] != '-') {
					String = '-' + String;
				}
				else {
					String = String.substr(1, String.length());
				}
				left = String;
			}
			// 这里加上或操作可使操作连续进行, 如果第一个字符为-，也可以进行+操作
			else if (!flag || oper == '=' || String[0] == '-') {
				flag = true;
				oper = '+';
				left = String;
				String += button[yNow][xNow].ReturnButtonString();
			}
			break;
		case '-':
		case '/':
		case '%':
		case '*':
			// 加上或操作的原因同上
			if (!flag || oper == '=')
			{
				flag = true;
				oper = button[yNow][xNow].ReturnButtonString()[0];
				left = String;
				String += button[yNow][xNow].ReturnButtonString();
			}
			break;
		// 后退一个字符
		case '<':
			String = String.substr(0, String.length() - 1);
			break;
		// 计算
		case '=':
			OnCompute();
			break;
		// 求平方
		case 'x':
			if (!flag || oper == '=') {
				flag = true;
				OnSqu();
			}
			break;
		// 指数计算
		case 'e':
			if (!flag || oper == '=') {
				flag = true;
				OnExp();
			}
			break;
		// 求倒数
		case 'r':
			if (!flag || oper == '=') {
				flag = true;
				OnRec();
			}
			break;
		// 求平方根
		case 's':
		{
			if (flag == false || oper == '=')
			{
				flag = true;
				OnSqr();											// 开平方
			}
			break;
		}
		// 小数点
		case '.':
			// 检查现在的String有没有小数点
			if (count(String.begin(), String.end(), '.') == 0) {
				String += '.';
			}
			else if (count(String.begin(), String.end(), '.') == 1) {
				if (left != "" && oper != '0') {
					String += '.';
				}
			}
			else if (flag == true && oper == '=') {
				String = "";
				flag = false;
			}

			break;
		// 点击0的情况
		case '0':
			// 如果第一个字符是0，并且总长度为1
			if (String.length() > 1 && (String[0] != '0' || String[1] != 0)) {
				String += '0';
			}
			else if (String.length() == 0) {
				String += '0';
			}
			break;
		default:
			if (flag && oper == '=') {
				String = "";
				flag = false;
			}
			String += button[yNow][xNow].ReturnButtonString();
			break;
		}
	}
	// 更新编辑框的数据
	edit.SetEditString(String);
}

// 用于完成一次计算任务后, 一些数据的重置
void GCount::OnSetData()
{
	int length = 0;
	left = "";
	right = "";
	number1 = number2 = 0.0;
	oper = '=';

	// 将String后多余的0去掉
	for (int i = String.length() - 1; i > 0; --i) {
		if (String[i] == '0' || String[i] == 46) {
			++length;
		}
		else {
			break;
		}
	}
	String = String.substr(0, String.length() - length);
}

void GCount::OnCompute()
{
	// 如果字符串非空
	if (!String.empty()) {
		right = String.substr(left.length() + 1, String.length());
	}
	// 如果左右操作数都不为空
	if (!left.empty() && !right.empty()) {
		switch (oper)
		{
		case '+':
			OnAdd();			// 加法操作
			break;
		case '-':
			OnSub();			// 减法操作
			break;
		case '*':
			OnMul();			// 乘法操作
			break;
		case '/':
			OnDiv();			// 除法操作
			break;
		case '%':
			OnMod();			// 取模操作
			break;
		default:

			break;
		}
		oper = '=';
	}
}

void GCount::OnAdd()
{
	// 设置左右操作数
	number1 = atof(left.c_str());
	number2 = atof(right.c_str());
	number1 += number2;

	// 更新时间
	sprintf_s(str1, "%lf", number1);
	String = str1;
	OnSetData();
}

void GCount::OnSub()
{
	// 设置左右操作数
	number1 = atof(left.c_str());
	number2 = atof(right.c_str());
	number1 -= number2;

	// 更新时间
	sprintf_s(str1, "%lf", number1);
	String = str1;
	OnSetData();
}

void GCount::OnMul()
{
	// 设置左右操作数
	number1 = atof(left.c_str());
	number2 = atof(right.c_str());
	number1 *= number2;

	// 更新数据
	sprintf_s(str1, "%lf", number1);
	String = str1;

	OnSetData();
}

void GCount::OnDiv()
{
	// 设置左右操作数
	number1 = atof(left.c_str());
	number2 = atof(right.c_str());

	// 右操作数不能为 0 
	if (number2 != 0)
	{
		number1 /= number2;
		sprintf_s(str1, "%lf", number1);
		String = str1;
	}
	else
	{
		String = _T("错误! 除数为0");
	}

	OnSetData();
}

void GCount::OnMod()
{
	// 设置左右操作数
	number1 = atof(left.c_str());
	number2 = atof(right.c_str());

	// 右操作数不能为 0
	if (number2 != 0)
	{
		number1 = fmod(number1, number2);
		sprintf_s(str1, "%lf", number1);
		String = str1;
	}
	else
	{
		String = _T("错误! 模数为0");
	}

	OnSetData();
}

void GCount::OnSqu()
{
	// 设置左操作数
	left = String;
	number1 = atof(left.c_str());
	number1 = number1 * number1;

	// 更新数据
	sprintf_s(str1, "%lf", number1);
	String = str1;

	OnSetData();
}

void GCount::OnExp()
{
	// 设置左操作数
	left = String;
	number1 = atof(left.c_str());
	number1 = exp(number1);

	// 更新数据
	sprintf_s(str1, "%lf", number1);
	String = str1;

	OnSetData();
}

void GCount::OnRec()
{
	// 设置左操作数
	left = String;
	number1 = atof(left.c_str());
	if (number1 != 0) {
		number1 = 1 / number1;

		// 更新数据
		sprintf_s(str1, "%lf", number1);
		String = str1;
	}
	else {
		String = _T("错误! 0不能求倒数");
	}


	OnSetData();
}

void GCount::OnSqr()
{
	// 设置左操作数
	left = String;
	number1 = atof(left.c_str());

	// 操作数不能为小于 0 
	if (number1 >= 0)
	{
		number1 = sqrt(number1);
		sprintf_s(str1, "%lf", number1);
		String = str1;
	}
	else
	{
		String = _T("负数! 不能开平方");
	}

	OnSetData();
}
