#include "pch.h"
#include "Tail.h"


Tail::Tail()
{
}

Tail::Tail(int radius)
{
	this->radius = radius;
	x = 0;
	y = 0;
	dx = 0;
	dy = 0;
	Next = NULL;
	Prev = NULL;
}


Tail::~Tail()
{
}
