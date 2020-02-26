#pragma once
#include "CGame.h"

// 游戏界面类
class CPlay : public CGame
{
public:
	CPlay();						// 构造函数
	~CPlay();						// 构析函数

	void inter_Face_Running();		// 游戏界面
	void read_Level();				// 读取关卡
	void draw_Title();				// 绘制标题
	void draw_Paper();				// 绘制纸盘
	void draw_Graph();				// 绘制图
	void point_Move(int point_id);	// 移动点
	void clear();					// 清空
	bool if_Win();					// 胜利判定

	static int point_num, line_num;	// 点数、线数
};
// 游戏界面类