#pragma once
class Game
{
	friend class Floor;
	friend class Ball;

public:
	Game();
	~Game();

	void start(); // 进入游戏
	bool run;
	bool exit;   // 退出游戏时为true
	bool restart; // 重新开始

	void Draw();
	void Move();
	void Act(double x0, double y0);
private:
	float FloorColor; 
	double speed;
	const double BASE_SPEED;
	const double SPEED;
	const double FLOOR_AFTER;
	const double FLOOR_BEFORE;

	void Init(); // 初始化
	void Option();
	void addFloor(); 
	void DrawCosmo();
	void DrawFloor();
	void FloorColorChange();
	void deleteHeadFloor();
	void deleteAllFloor();
	void deleteCosmo();
	void Speed();
	bool JudgeNext();
	void JudgeDie();
	bool JudgeOut();

	void ChangeDirect();
	
	void PrintScore();
	bool $return();
	bool $restart();

	bool wait;
	void End();
	void Wait();
	void Play();
	void GetCommand();

	Floor* GetLastFloor();
	int score;
	Floor* headfloor;
	Ball* cosmo;
	void bkcolorgrad(COLORREF bkcolor);

	void sleep();
};

extern Game *game;
// 线程用于绘制图形
DWORD WINAPI Thread_MoveAndDraw(PVOID pMyPara);

