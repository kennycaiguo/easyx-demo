#include "Calc.h"

int main() {
	GCount count;
	while (1) {
		count.Run();
		Sleep(20);
	}
	_getch();
	closegraph();
	return 0;
}