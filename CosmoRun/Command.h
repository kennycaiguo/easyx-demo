#pragma once
class Command
{
public:
	Command();
	~Command();
	bool getClick();
	void setClick(bool state);
	bool getLBdown();
	void setLBdown(bool state);
	MOUSEMSG msg;
private:
	bool click;
	bool LBdown;
	
};

// 线程用于获取键盘鼠标消息
DWORD WINAPI Thread_GetMouseMsg(PVOID pMypara);
