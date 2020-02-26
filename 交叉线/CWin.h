#pragma once
#include "CGame.h"

// 过关界面类
class CWin : public CGame
{
public:
	CWin();						// 构造函数
	~CWin();					// 构析函数

	void inter_Face_Running();	// 过关界面

private:
	void change_Best_Time();	// 修改最佳时间
	void draw_Title();			// 绘制标题
};
// 过关界面类
