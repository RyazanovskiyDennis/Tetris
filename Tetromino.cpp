#include "stdafx.h"
#include "Tetromino.h"

using namespace std;					// x = x0 + (y0-y);
										// y = y0 + (x0-x);

void Tetromino::rotate()
{
	for (int i = 0; i < 4; i++)
	{
		int dx = pts[2].x + (pts[2].y - pts[i].y);
		pts[i].y = pts[2].y + (pts[i].x - pts[2].x);
		pts[i].x = dx;
	}
}

Tetromino_I::Tetromino_I()
{
	pts[0] = Point(0, 0);
	pts[1] = Point(0, 1);
	pts[2] = Point(0, 2);
	pts[3] = Point(0, 3);
}
Tetromino_J::Tetromino_J ()
{
	
	pts[0] = Point(0, 0);
	pts[1] = Point(1, 0);
	pts[2] = Point(1, 1);
	pts[3] = Point(1, 2);
}
Tetromino_L::Tetromino_L()
{
	pts[0] = Point(1, 0);
	pts[1] = Point(0, 0);
	pts[2] = Point(0, 1);
	pts[3] = Point(0, 2);
}
Tetromino_O::Tetromino_O()
{
	pts[0] = Point(0, 0);
	pts[1] = Point(1, 0);
	pts[2] = Point(0, 1);
	pts[3] = Point(1, 1);
}
Tetromino_S::Tetromino_S()
{
	pts[0] = Point(0, 0);
	pts[1] = Point(1, 0);
	pts[2] = Point(1, 1);
	pts[3] = Point(2, 1);
}
Tetromino_T::Tetromino_T()
{
	pts[0] = Point(0, 1);
	pts[1] = Point(1, 0);
	pts[2] = Point(1, 1);
	pts[3] = Point(2, 1);
}
Tetromino_Z::Tetromino_Z()
{
	pts[0] = Point(0, 1);
	pts[1] = Point(1, 1);
	pts[2] = Point(1, 0);
	pts[3] = Point(2, 0);
}


