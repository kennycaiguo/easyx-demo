#pragma once

// 线类
class CLine
{
public:
	CLine(int a = 0, int b = 0);				// 构造函数
	~CLine();									// 构析函数

	double vector_Mult(int a, int b, int c);	// 向量叉乘
	bool line_Cross(CLine l);					// 判断线段是否交叉

	int a, b;									// 编号
};
// 线类
