#include "pch.h"
#include "Floor.h"


Floor::Floor():LENOFSIDE(34)
{
	start_gap = 40;
	on_gap = 0;
	end_gap = 0;
	Next = NULL;
	Prev = NULL;
	create_bug = false;
	CosmoOnColor = 0;
	dx = 0;
	dy = 0;
	dz = 0;
}


Floor::~Floor()
{
}

// 初始化板块
bool Floor::Set()
{
	do {
		// 板块初始化出错
		if (create_bug) return false;
		mode = (int)pow(double(2), rand() % 3 + 2) + rand() % 4;

		// 根据板块类型获得坐标
		GetLocation(); 
	} while (!FitRule() || !JudgeCoincidence()); // 检查板块是否符合规则

	return true;
}

void Floor::draw(float FloorColor)
{
	setlinecolor(0x444444);
	setfillcolor(0x444444);
	if (mode & F1) {
		x1 = x - 2 * LENOFSIDE*d, y1 = y;
		x2 = x, y2 = y + LENOFSIDE * d;
		x3 = x + 2 * LENOFSIDE*d, y3 = y;
		x4 = x, y4 = y - LENOFSIDE * d;
		setfillcolor(HSLtoRGB(FloorColor, 0.8f + 2 * CosmoOnColor, 0.5f + CosmoOnColor));
		draw_f(x1, y1, x2, y2, x3, y3, x4, y4);
	}
	else if (mode & F2) {
		x1 = x - LENOFSIDE * d, y1 = y - LENOFSIDE * 2 * 0.75*d;
		x2 = x + LENOFSIDE * d, y2 = y - LENOFSIDE * 2 * 0.25*d;
		x3 = x + LENOFSIDE * d, y3 = y + LENOFSIDE * 2 * 0.75*d;
		x4 = x - LENOFSIDE * d, y4 = y + LENOFSIDE * 2 * 0.25*d;
		setfillcolor(HSLtoRGB(FloorColor, 0.8f + 2 * CosmoOnColor, 0.38f + CosmoOnColor));
		draw_f(x1, y1, x2, y2, x3, y3, x4, y4);
	}
	else if (mode & F3) {
		x1 = x - LENOFSIDE * d, y1 = y - LENOFSIDE * 2 * 0.25*d;
		x2 = x + LENOFSIDE * d, y2 = y - LENOFSIDE * 2 * 0.75*d;
		x3 = x + LENOFSIDE * d, y3 = y + LENOFSIDE * 2 * 0.25*d;
		x4 = x - LENOFSIDE * d, y4 = y + LENOFSIDE * 2 * 0.75*d;
		setfillcolor(HSLtoRGB(FloorColor, 0.8f + 2 * CosmoOnColor, 0.26f + CosmoOnColor));
		draw_f(x1, y1, x2, y2, x3, y3, x4, y4);
	}
}

void Floor::drawshadow()
{
	setlinecolor(0x444444);
	setfillcolor(0x444444);
	if (mode & F1) {
		x1 = x - 2 * LENOFSIDE*d, y1 = y;
		x2 = x, y2 = y + LENOFSIDE * d;
		x3 = x + 2 * LENOFSIDE*d, y3 = y;
		x4 = x, y4 = y - LENOFSIDE * d;
		draw_f(x1, y1 + 4, x2, y2 + 4, x3, y3 + 4, x4, y4 + 4);
	}
	else if (mode & F2) {
		x1 = x - LENOFSIDE * d, y1 = y - LENOFSIDE * 2 * 0.75*d;
		x2 = x + LENOFSIDE * d, y2 = y - LENOFSIDE * 2 * 0.25*d;
		x3 = x + LENOFSIDE * d, y3 = y + LENOFSIDE * 2 * 0.75*d;
		x4 = x - LENOFSIDE * d, y4 = y + LENOFSIDE * 2 * 0.25*d;
		draw_f(x1 + 4, y1 + 4, x2 + 4, y2 + 4, x3 + 4, y3 + 4, x4 + 4, y4 + 4);
	}
	else if (mode & F3) {
		x1 = x - LENOFSIDE * d, y1 = y - LENOFSIDE * 2 * 0.25*d;
		x2 = x + LENOFSIDE * d, y2 = y - LENOFSIDE * 2 * 0.75*d;
		x3 = x + LENOFSIDE * d, y3 = y + LENOFSIDE * 2 * 0.25*d;
		x4 = x - LENOFSIDE * d, y4 = y + LENOFSIDE * 2 * 0.75*d;
		draw_f(x1 - 4, y1 + 4, x2 - 4, y2 + 4, x3 - 4, y3 + 4, x4 - 4, y4 + 4);
	}
}

void Floor::gap(double speed)
{
	if (start_gap) start_gap--;		// 动画效果
	if (end_gap >= 1) end_gap++;	// 动画效果
	if (on_gap) {
		on_gap--;
		CosmoOnColor += 0.005f;
	}
	d = (40 - start_gap) / 40.0 * ((int)(20.0 / speed) - end_gap) / (int)(20.0 / speed);	// 动画效果

}

void Floor::lightup()
{
	on_gap = 20;
}

void Floor::end()
{
	end_gap = 1;
}

bool Floor::end(double speed)
{
	if ((int)(20.0 / speed) == end_gap)
		return true;
	return false;
}

bool Floor::FitRule()	// 初步 检查板块类型是否符合规则
{
	// 第一类板块初始化
	if (mode & F1) {
		if (Prev->mode == F2_LEFT_UP ||
			Prev->mode == F2_RIGHT_DOWN ||
			Prev->mode == F3_LEFT_DOWN ||
			Prev->mode == F3_RIGHT_UP)
			return false;
		else if (mode == F1_LEFT_UP) {
			if (Prev->mode & F1) {
				if (Prev->mode == F1_RIGHT_DOWN)		// 防止板块折回
					return false;
				else if (Prev->Prev != NULL && Prev->Prev->mode == F1_RIGHT_DOWN && (Prev->mode == F1_RIGHT_UP || Prev->mode == F1_LEFT_DOWN))	// 防止板块迂回
					return false;
				// else 
			}
			else if (Prev->mode == F3_DOWN)	// 防止板块折回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_UP && Prev->Prev->mode == F2_RIGHT_DOWN)	// 防止板块迂回
				return false;
			// else
		}
		else if (mode == F1_LEFT_DOWN) {
			if (Prev->mode & F1) {
				if (Prev->mode == F1_RIGHT_UP) 	// 防止板块折回
					return false;
				else if (Prev->Prev != NULL && Prev->Prev->mode == F1_RIGHT_UP && (Prev->mode == F1_LEFT_UP || Prev->mode == F1_RIGHT_DOWN))	// 防止板块迂回
					return false;
				// else 
			}
			else if (Prev->mode == F2_UP) 	// 防止板块折回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_DOWN && Prev->Prev->mode == F3_RIGHT_UP)	// 防止板块迂回
				return false;
			// else
		}
		else if (mode == F1_RIGHT_UP) {
			if (Prev->mode & F1) {
				if (Prev->mode == F1_LEFT_DOWN) 	// 防止板块折回
					return false;
				else if (Prev->Prev != NULL && Prev->Prev->mode == F1_LEFT_DOWN && (Prev->mode == F1_RIGHT_DOWN || Prev->mode == F1_LEFT_UP))	// 防止板块迂回
					return false;
				// else 
			}
			else if (Prev->mode == F2_DOWN) 	// 防止板块折回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_UP && Prev->Prev->mode == F3_LEFT_DOWN)	// 防止板块迂回
				return false;
			// else
		}
		else if (mode == F1_RIGHT_DOWN) {
			if (Prev->mode & F1) {
				if (Prev->mode == F1_LEFT_UP) 	// 防止板块折回
					return false;
				else if (Prev->Prev != NULL && Prev->Prev->mode == F1_LEFT_UP && (Prev->mode == F1_RIGHT_UP || Prev->mode == F1_LEFT_DOWN))	// 防止板块迂回
					return false;
			}
			else if (Prev->mode == F3_UP) 	// 防止板块折回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_DOWN && Prev->Prev->mode == F2_LEFT_UP)	// 防止板块迂回
				return false;
			// else
		}
	}

	// 第二类板块初始化
	else if (mode & F2) {
		if (Prev->mode == F1_LEFT_UP ||
			Prev->mode == F1_RIGHT_DOWN ||
			Prev->mode == F3_UP ||
			Prev->mode == F3_DOWN)
			return false;
		else if (Prev->Prev != NULL && Prev->mode == F1_RIGHT_UP && Prev->Prev->mode == F3_DOWN)	// 防止板块迂回
			return false;
		else if (Prev->Prev != NULL && Prev->mode == F1_LEFT_DOWN && Prev->Prev->mode == F3_UP)	// 防止板块迂回
			return false;
		else if (mode == F2_UP) {
			if (Prev->mode == F1_LEFT_DOWN || Prev->mode == F2_DOWN) // 防止板块错位
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F3_DOWN && (Prev->mode == F3_RIGHT_UP || Prev->mode == F3_LEFT_DOWN))	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_RIGHT_UP && Prev->Prev->mode == F1_LEFT_UP)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_LEFT_DOWN && Prev->Prev->mode == F1_RIGHT_DOWN)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_RIGHT_DOWN && Prev->Prev->mode == F1_LEFT_DOWN)	// 防止板块迂回
				return false;
		}
		else if (mode == F2_DOWN) {
			if (Prev->mode == F1_RIGHT_UP || Prev->mode == F2_UP) // 防止板块错位
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F3_UP && (Prev->mode == F3_RIGHT_UP || Prev->mode == F3_LEFT_DOWN))	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_RIGHT_UP && Prev->Prev->mode == F1_LEFT_UP)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_LEFT_DOWN && Prev->Prev->mode == F1_RIGHT_DOWN)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_LEFT_UP && Prev->Prev->mode == F1_RIGHT_UP)	// 防止板块迂回
				return false;
		}
		else if (mode == F2_LEFT_UP) {
			if (Prev->mode == F2_RIGHT_DOWN || Prev->mode == F3_RIGHT_UP) // 防止板块错位
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_LEFT_DOWN && Prev->Prev->mode == F1_RIGHT_DOWN)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F1_RIGHT_UP && Prev->Prev->mode == F1_RIGHT_DOWN)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F1_RIGHT_DOWN && (Prev->mode == F1_RIGHT_UP || Prev->mode == F1_LEFT_DOWN))	// 防止板块迂回
				return false;
		}
		else if (mode == F2_RIGHT_DOWN) {
			if (Prev->mode == F3_LEFT_DOWN || Prev->mode == F2_LEFT_UP) // 防止板块错位
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_RIGHT_UP && Prev->Prev->mode == F1_LEFT_UP)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F1_LEFT_DOWN && Prev->Prev->mode == F1_LEFT_UP)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F1_LEFT_UP && (Prev->mode == F1_RIGHT_UP || Prev->mode == F1_LEFT_DOWN))	// 防止板块迂回
				return false;
		}
	}

	// 第三类板块初始化
	else if (mode & F3) {
		if (Prev->mode == F1_LEFT_DOWN ||
			Prev->mode == F1_RIGHT_UP ||
			Prev->mode == F2_UP ||
			Prev->mode == F2_DOWN)
			return false;
		else if (Prev->Prev != NULL && Prev->mode == F1_RIGHT_DOWN && Prev->Prev->mode == F2_UP)	// 防止板块迂回
			return false;
		else if (Prev->Prev != NULL && Prev->mode == F1_LEFT_UP && Prev->Prev->mode == F2_DOWN)	// 防止板块迂回
			return false;
		else if (mode == F3_UP) {
			if (Prev->mode == F1_RIGHT_DOWN || Prev->mode == F3_DOWN) // 防止板块错位
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F2_DOWN && (Prev->mode == F2_RIGHT_DOWN || Prev->mode == F2_LEFT_UP))	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_RIGHT_DOWN && Prev->Prev->mode == F1_LEFT_UP)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_LEFT_UP && Prev->Prev->mode == F1_RIGHT_UP)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_LEFT_DOWN && Prev->Prev->mode == F1_RIGHT_DOWN)	// 防止板块迂回
				return false;
		}
		else if (mode == F3_DOWN) {
			if (Prev->mode == F1_LEFT_UP || Prev->mode == F3_UP) // 防止板块错位
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F2_UP && (Prev->mode == F2_RIGHT_DOWN || Prev->mode == F2_LEFT_UP))	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_RIGHT_DOWN && Prev->Prev->mode == F1_LEFT_DOWN)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_LEFT_UP && Prev->Prev->mode == F1_RIGHT_UP)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_RIGHT_UP && Prev->Prev->mode == F1_LEFT_UP)	// 防止板块迂回
				return false;
		}
		else if (mode == F3_LEFT_DOWN) {
			if (Prev->mode == F2_RIGHT_DOWN || Prev->mode == F3_RIGHT_UP) // 防止板块错位
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_LEFT_UP && Prev->Prev->mode == F1_RIGHT_UP)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F1_RIGHT_DOWN && Prev->Prev->mode == F1_RIGHT_UP)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F1_RIGHT_UP && (Prev->mode == F1_RIGHT_DOWN || Prev->mode == F1_LEFT_UP))	// 防止板块迂回
				return false;
		}
		else if (mode == F3_RIGHT_UP) {
			if (Prev->mode == F2_LEFT_UP || Prev->mode == F3_LEFT_DOWN) // 防止板块错位
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_RIGHT_DOWN && Prev->Prev->mode == F1_LEFT_DOWN)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F1_LEFT_UP && Prev->Prev->mode == F1_LEFT_DOWN)	// 防止板块迂回
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F1_LEFT_DOWN && (Prev->mode == F1_RIGHT_DOWN || Prev->mode == F1_LEFT_UP))	// 防止板块迂回
				return false;
		}
	}
	/*   进一步判断 板块坐标是否符合规则   */
	if (mode == F1_RIGHT_UP || mode == F2_UP) {
		dx = 1;
		dy = 0;
		dz = 0;
	}
	else if (mode == F1_LEFT_DOWN || mode == F2_DOWN) {
		dx = -1;
		dy = 0;
		dz = 0;
	}
	else if (mode == F1_LEFT_UP || mode == F3_UP) {
		dx = 0;
		dy = -1;
		dz = 0;
	}
	else if (mode == F1_RIGHT_DOWN || mode == F3_DOWN) {
		dx = 0;
		dy = 1;
		dz = 0;
	}
	else if (mode == F2_RIGHT_DOWN || mode == F3_RIGHT_UP) {
		dx = 0;
		dy = 0;
		dz = 1;
	}
	else if (mode == F2_LEFT_UP || mode == F3_LEFT_DOWN) {
		dx = 0;
		dy = 0;
		dz = -1;
	}

	// 检查板块是否迂回
	int dx0 = 0, dy0 = 0, dz0 = 0;
	if (this->Prev != NULL && this->Prev->Prev != NULL) {
		dx0 = dx + this->Prev->dx + this->Prev->Prev->dx;
		dy0 = dy + this->Prev->dy + this->Prev->Prev->dy;
		dz0 = dz + this->Prev->dz + this->Prev->Prev->dz;
		if ((dx0 == 0 && dy0 == 0 && (dz0 == 1 || dz0 == -1)) ||
			(dx0 == 0 && dz0 == 0 && (dy0 == 1 || dy0 == -1)) ||
			(dz0 == 0 && dy0 == 0 && (dx0 == 1 || dx0 == -1)))
			return false;
		if ((dx0 == -1 && dz0 == 1 && (dy0 == 1 || dy0 == -1)) ||
			(dx0 == 1 && dz0 == -1 && (dy0 == 1 || dy0 == -1)) ||
			(dx0 == -1 && dy0 == 1 && (dz0 == 1 || dz0 == -1)) ||
			(dx0 == 1 && dy0 == -1 && (dz0 == 1 || dz0 == -1)) ||
			(dz0 == 1 && dy0 == -1 && (dx0 == 1 || dx0 == -1)) ||
			(dz0 == -1 && dy0 == 1 && (dx0 == 1 || dx0 == -1)))
			return false;
		if ((dx0 == 1 && dy0 == 1 && dz0 == -1) ||
			(dx0 == -1 && dy0 == -1 && dz0 == 1))
			return false;
	}
	return true;
}

bool Floor::JudgeCoincidence()
{
	POINT vertex[5];
	if (mode & F1) {
		vertex[0].x = (int)x - LENOFSIDE;
		vertex[0].y = (int)y - LENOFSIDE / 2;
		vertex[1].x = (int)x + LENOFSIDE;
		vertex[1].y = (int)y - LENOFSIDE / 2;
		vertex[2].x = (int)x - LENOFSIDE;
		vertex[2].y = (int)y + LENOFSIDE / 2;
		vertex[3].x = (int)x + LENOFSIDE;
		vertex[3].y = (int)y + LENOFSIDE / 2;
		vertex[4].x = (int)x;
		vertex[4].y = (int)y;
	}
	else if (mode & F2 || mode & F3) {
		vertex[0].x = (int)x - LENOFSIDE;
		vertex[0].y = (int)y;
		vertex[1].x = (int)x + LENOFSIDE;
		vertex[1].y = (int)y;
		vertex[2].x = (int)x;
		vertex[2].y = (int)y + LENOFSIDE;
		vertex[3].x = (int)x;
		vertex[3].y = (int)y - LENOFSIDE;
		vertex[4].x = (int)x;
		vertex[4].y = (int)y;
	}

	Floor* p = Prev;
	while (p->Prev != NULL) {
		p = p->Prev;
		for (int i = 0; i < 5; i++) {
			if (p->mode & F1) {
				if (fabs((vertex[i].y - (int)p->y) + 0.5*((int)p->x - vertex[i].x)) <= LENOFSIDE + 1 &&
					fabs((vertex[i].y - (int)p->y) - 0.5*((int)p->x - vertex[i].x)) <= LENOFSIDE + 1) {
					create_bug = true;
					return false;
				}
			}
			else if (p->mode & F2) {
				if (fabs((vertex[i].y - (int)p->y) + 0.5*((int)p->x - vertex[i].x)) <= LENOFSIDE + 1 &&
					fabs(p->x - vertex[i].x) <= LENOFSIDE + 1) {
					create_bug = true;
					return false;
				}
			}
			else if (p->mode & F3) {
				if (fabs((vertex[i].y - (int)p->y) - 0.5*((int)p->x - vertex[i].x)) <= LENOFSIDE + 1 &&
					fabs(p->x - vertex[i].x) <= LENOFSIDE + 1) {
					create_bug = true;
					return false;
				}
			}
		}
	}
	return true;
}

void Floor::GetLocation()
{
	// 第一类板块坐标
	if (mode & F1) {
		if (Prev->mode & F1) {
			if (Prev->mode == F1_LEFT_UP) {
				x = Prev->x - (2 * LENOFSIDE);
				y = Prev->y - (LENOFSIDE);
			}
			else if (Prev->mode == F1_LEFT_DOWN) {
				x = Prev->x - (2 * LENOFSIDE);
				y = Prev->y + (LENOFSIDE);
			}
			else if (Prev->mode == F1_RIGHT_UP) {
				x = Prev->x + (2 * LENOFSIDE);
				y = Prev->y - (LENOFSIDE);
			}
			else if (Prev->mode == F1_RIGHT_DOWN) {
				x = Prev->x + (2 * LENOFSIDE);
				y = Prev->y + (LENOFSIDE);
			}
		}
		else if (Prev->mode == F2_DOWN) {
			x = Prev->x - (2 * LENOFSIDE / 2);
			y = Prev->y + (int)(LENOFSIDE*1.5);
		}
		else if (Prev->mode == F2_UP) {
			x = Prev->x + (2 * LENOFSIDE / 2);
			y = Prev->y - (int)(LENOFSIDE*1.5);
		}
		else if (Prev->mode == F3_DOWN) {
			x = Prev->x + (2 * LENOFSIDE / 2);
			y = Prev->y + (int)(LENOFSIDE*1.5);
		}
		else if (Prev->mode == F3_UP) {
			x = Prev->x - (2 * LENOFSIDE / 2);
			y = Prev->y - (int)(LENOFSIDE*1.5);
		}
	}

	// 第二类板块坐标
	else if (mode & F2) {
		if (Prev->mode & F1) {
			if (Prev->mode == F1_RIGHT_UP) {
				x = Prev->x + (2 * LENOFSIDE / 2);
				y = Prev->y - (int)(1.5*LENOFSIDE);
			}
			else if (Prev->mode == F1_LEFT_DOWN) {
				x = Prev->x - (2 * LENOFSIDE / 2);
				y = Prev->y + (int)(1.5*LENOFSIDE);
			}
		}
		else if (Prev->mode & F2) {
			if (Prev->mode == F2_UP) {
				x = Prev->x;
				y = Prev->y - (2 * LENOFSIDE);
			}
			else if (Prev->mode == F2_DOWN) {
				x = Prev->x;
				y = Prev->y + (2 * LENOFSIDE);
			}
			else if (Prev->mode == F2_LEFT_UP) {
				x = Prev->x - (2 * LENOFSIDE);
				y = Prev->y - (LENOFSIDE);
			}
			else if (Prev->mode == F2_RIGHT_DOWN) {
				x = Prev->x + (2 * LENOFSIDE);
				y = Prev->y + (LENOFSIDE);
			}
		}
		else if (Prev->mode & F3) {
			if (Prev->mode == F3_RIGHT_UP) {
				x = Prev->x + (2 * LENOFSIDE);
				y = Prev->y;
			}
			else if (Prev->mode == F3_LEFT_DOWN) {
				x = Prev->x - (2 * LENOFSIDE);
				y = Prev->y;
			}
		}
	}

	// 第三类板块坐标
	else if (mode & F3) {
		if (Prev->mode & F1) {
			if (Prev->mode == F1_RIGHT_DOWN) {
				x = Prev->x + (2 * LENOFSIDE / 2);
				y = Prev->y + (int)(1.5*LENOFSIDE);
			}
			else if (Prev->mode == F1_LEFT_UP) {
				x = Prev->x - (2 * LENOFSIDE / 2);
				y = Prev->y - (int)(1.5*LENOFSIDE);
			}
		}
		else if (Prev->mode & F2) {
			if (Prev->mode == F2_LEFT_UP) {
				x = Prev->x - (2 * LENOFSIDE);
				y = Prev->y;
			}
			else if (Prev->mode == F2_RIGHT_DOWN) {
				x = Prev->x + (2 * LENOFSIDE);
				y = Prev->y;
			}
		}
		else if (Prev->mode & F3) {
			if (Prev->mode == F3_UP) {
				x = Prev->x;
				y = Prev->y - (2 * LENOFSIDE);
			}
			else if (Prev->mode == F3_DOWN) {
				x = Prev->x;
				y = Prev->y + (2 * LENOFSIDE);
			}
			else if (Prev->mode == F3_RIGHT_UP) {
				x = Prev->x + (2 * LENOFSIDE);
				y = Prev->y - (LENOFSIDE);
			}
			else if (Prev->mode == F3_LEFT_DOWN) {
				x = Prev->x - (2 * LENOFSIDE);
				y = Prev->y + (LENOFSIDE);
			}
		}
	}
}

void Floor::draw_f(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	// 根据顶点坐标画四边形
	POINT pts[] = { { (int)x1,(int)y1 },{ (int)x2,(int)y2 },{ (int)x3,(int)y3 },{ (int)x4,(int)y4 } };
	fillpolygon(pts, 4);
}
