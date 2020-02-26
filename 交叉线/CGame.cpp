#include "CGame.h"

extern MOUSEMSG msg; //  Û±Íœ˚œ¢

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::clear_Board()
{
	setbkcolor(BKCOLOR);
	cleardevice();
}
