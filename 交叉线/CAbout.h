#pragma once
#include "CGame.h"
#include "CButton.h"
#include "CButton_Image.h"

// 关于界面类
class CAbout : public CGame
{
public:
	CAbout();					// 构造函数
	~CAbout();					// 构析函数

	void inter_Face_Running();	// 关于界面

private:
	void draw_Text();			// 输出文字
};
// 关于界面类
