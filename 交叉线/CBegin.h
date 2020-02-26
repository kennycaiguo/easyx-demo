#pragma once
#include "CGame.h"

class CBegin :public CGame
{
public:
	CBegin();
	~CBegin();
	void inter_Face_Running(); // 初始界面
private:
	void draw_Title(); // 绘制标题
};