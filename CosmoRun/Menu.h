#pragma once

class Menu
{
public:
	Menu();
	~Menu();
	void Set(int wid, int len);	
	void Show();	
	void Hide();	
	void Text(int x, int y, char *text, int font_size = 25, int font_bold = 600, COLORREF font_color = BLACK);	// ÷¶¿Ì¿ïÙµ
	void sleep();
private:
	const int MENU_SPEED;
	int wid;
	int len;
	COLORREF menu_color;
	IMAGE background;
};

