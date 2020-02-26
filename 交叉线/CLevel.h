#pragma once
#include "CGame.h"

// 关卡界面类
class CLevel : public CGame
{
public:
	CLevel();					// 构造函数
	~CLevel();					// 构析函数

	void inter_Face_Running();	// 关卡界面

private:
	int stat();					// 统计关卡
};
// 关卡界面类

