#pragma once
#include "Head.h"

class CGame
{
public:
	CGame();
	~CGame();
	virtual void inter_Face_Running() = 0; // 界面接口
protected:
	void clear_Board(); // 绘制背景
};

