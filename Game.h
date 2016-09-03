#pragma once
#include "stdafx.h"
#include "Drawer.h"
#include "Checker.h"

class Game
{
public:
	enum status { start, game, pause, end };
	enum Buttons { Restart = 'r', Sandbox = 's', Exit = 27, Rotate = 32, Pause = 'p', Force_Down = 'f', Easy_mode = 'e' };
private:
	int  score, speed, size, lines, tick, current_difficulty, difficulty_scale, need_lines_to_lvl_up, max_difficulty;
	Tetromino *Current, *Predict;
	bool **Field, easy_mode, sandbox, ended;
	status Current_status;
	Drawer *drawer;
	Checker *checker;
	Point Field_Size;
public:
	Game(); 
	status GameStatus(){return Current_status;}
	void GameLoop();
	Point Get_Window_Size(){ return drawer->Get_Window_Size(); }
	void Draw();
	void onKey(unsigned char);
	void onReshape(int W, int H){ drawer->onReshape(W, H); }
	void onSpecKey(int);
private:
	void Change_score();
	void Remove_lines();
	void Press_left();
	void Press_right();
	void Press_down();
	void Press_up();
	void Press_rotate();
	void Press_exit();
	void Press_restart();
	void Press_Force_Down();
	void Press_sandbox();
	void Press_pause();
	void Press_easy_mode();
	void Calculate_Predict();
	void add_to_field() { for (int i(0); i < 4; i++) Field[Current->pts[i].x][Current->pts[i].y] = 1; };
	bool move_tetromino(Point V);
	bool analys_after_move();
	void Create_new();
	void Force_down(Tetromino *T);
	void onStart();
	void onEnd();
	void Help();
};

