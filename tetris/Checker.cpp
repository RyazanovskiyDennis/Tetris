#include "stdafx.h"
using namespace std;

Checker::Checker()
{
	for (int i(0); i < 4; i++) rows_to_remove[i] = 0;
	rows_count = 0;
}
bool Checker::Check_collision_with_Field(Tetromino* Current, bool **Field,  const Point &Field_Size, const Point &V)
{
	bool res = 0;
	int i(0);
	while(!res && i < 4)
	{
		int dx = Current->pts[i].x + V.x;
		int dy = Current->pts[i].y + V.y;
		if (0 < dx && dx < Field_Size.x && 0 < dy && dy < Field_Size.y) res = Field[dx][dy];
		i++;
	}
	return res;
}
bool Checker::Check_collision_with_side_borders(Tetromino* Current, const Point &V, const Point &Field_Size)
{
	for (int i(0); i < 4; i++) if (Current->pts[i].x + V.x < 0 || Current->pts[i].x + V.x > Field_Size.x - 1) return 1;
	return 0;
}
int Checker::Check_collision_with_borders_after_rotate(Tetromino* Current,  const Point &Field_Size)
{
	int dx(0);
	if (Current->pts[0].x < 0 || Current->pts[3].x < 0 || Current->pts[1].x < 0)
	{
		dx = Current->pts[0].x;
		if (dx > Current->pts[1].x) dx = Current->pts[1].x;
		if (dx > Current->pts[3].x) dx = Current->pts[3].x;
		dx *= -1;
	}
	else if (Current->pts[0].x > Field_Size.x - 1 || Current->pts[3].x > Field_Size.x - 1 || Current->pts[1].x > Field_Size.x - 1)
	{
		dx = Current->pts[0].x;
		if (dx < Current->pts[1].x) dx = Current->pts[1].x;
		if (dx < Current->pts[3].x) dx = Current->pts[3].x;
		dx = Field_Size.x - 1 - dx;
	}
	return dx;
}
/*0 - tetromino didnt stop 1 - tetromino stoped*/
bool Checker::Check_after_move(Tetromino* Current, bool **Field, const Point &Field_Size)
{
	bool t(0);
	int i(0);
	while (!t && i < 4)
	{
		if (Current->pts[i].y == 0) t = 1;
		else if (Current->pts[i].y < Field_Size.y && Field[Current->pts[i].x][Current->pts[i].y - 1])	t = 1;
		i++;
	}
	return t;
}

bool greater(int a, int b)
{
	return a > b; 
}

bool Checker::Check_rows(Tetromino* Current, bool **Field, const Point &Field_Size)
{
	int y[4], different_count(0);
	for (int i(0); i < 4; i++) y[i] = rows_to_remove[i] = -1;
	// записываем в у[i] разные у из Current'a, и считаем их кол-во 
	for (int i(0); i < 4; i++)
	{
		bool not_equal(1);
		for (int j(0);not_equal && j < i; j++) if (y[j] == Current->pts[i].y) not_equal = 0;
		if (not_equal) y[different_count++] = Current->pts[i].y;
	}
	sort(y, y + different_count, greater);
	//проверяем каждую строку с у = у[i]
	rows_count = 0;
	for (int i(0); i < different_count; i++)
	{
		int j(0);
		bool all_points_in_line(1);
		while (all_points_in_line && j< Field_Size.x) all_points_in_line = Field[j++][y[i]];
		if (all_points_in_line) rows_to_remove[rows_count++] = y[i];
	}
	return rows_count;
}

bool Checker::Check_game_over(Tetromino* Current, const Point &Field_Size)
{
	for (int i(0); i < 4; i++) if (Current->pts[i].y >= Field_Size.y) return 1;
	return 0;
}

bool Checker::Check_collision_with_Field_on_rotate(Tetromino *Current, bool **Field,const Point &Field_Size)
{ 
	Current->rotate();
	int dx = this->Check_collision_with_borders_after_rotate(Current, Field_Size);
	if (dx) Current->move(Point(dx, 0));
	for (int i(0); i < 4; i++)
	{
		if (Current->pts[i].y < Field_Size.y - 1 && Field[Current->pts[i].x][Current->pts[i].y]) return 1;
	}
	return 0;
}
