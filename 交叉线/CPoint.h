#pragma once
// 点类
class CPoint
{
public:
	CPoint(int x = 0, int y = 0,
		bool move = 1, bool moving = 0);	// 构造函数
	~CPoint();									// 构析函数

	int x, y;									// 坐标
	bool move;									// 是否可移动、是否正在移动
};
// 点类

