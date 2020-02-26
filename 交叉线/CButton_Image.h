#pragma once
#include "Head.h"
#include <graphics.h>

// 按钮图形类
class CButton_Image
{
public:
	CButton_Image();																// 构造函数
	~CButton_Image();																// 构析函数

	IMAGE start_Button(COLORREF color);												// 开始按钮图形
	IMAGE help_Button(COLORREF color);												// 帮助按钮图形
	IMAGE close_Button(COLORREF color);												// 关闭按钮图形
	IMAGE level_Button(const wchar_t num[], const wchar_t tim[], COLORREF color);	// 关卡按钮图形
	IMAGE return_Button(COLORREF color);											// 返回按钮图形
	IMAGE again_Button(COLORREF color);												// 重来按钮图形
	IMAGE next_Button(COLORREF color);												// 下一关按钮图形
	IMAGE ok_Button(COLORREF color);												// O K 按钮图形
};
// 按钮图形类
