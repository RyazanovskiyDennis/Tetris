#pragma once
#include "stdafx.h"
#include <algorithm>

class Checker
{
	int rows_to_remove[4], rows_count;
	friend class Game;
	Checker();
	int  Check_collision_with_borders_after_rotate(Tetromino* Current, const Point &Field_Size);
	bool Check_collision_with_side_borders(Tetromino* Current, const Point &V, const Point &Field_Size);
	bool Check_collision_with_Field(Tetromino* Current, bool **Field, const Point &Field_Size, const Point &V);
	bool Check_collision_with_Field_on_rotate(Tetromino *Current, bool **Field,const Point &Field_Size);
	bool Check_after_move(Tetromino* Current, bool **Field, const Point &Field_Size);
	bool Check_rows(Tetromino* Current, bool **Field, const Point &Field_Size);
	bool Check_game_over(Tetromino* Current, const Point &Field_Size);
};
