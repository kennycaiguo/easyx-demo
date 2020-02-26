#pragma once
#include <graphics.h>

// 按钮类
class CButton
{
public:
	CButton();								// 构造函数
	~CButton();								// 构析函数

	void set_X_Y(int x, int y);				// 设置坐标
	void set_Image(IMAGE image);			// 设置外表
	int get_X() const; int get_Y() const;	// 获取坐标
	IMAGE get_Image() const;				// 获取外表
	void draw_Button() const;				// 绘制按钮
	bool if_Mouse_On(MOUSEMSG &m) const;	// 按钮获焦

private:
	int x, y;								// 按钮坐标
	IMAGE image;							// 按钮外表
};
// 按钮类