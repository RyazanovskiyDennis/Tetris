#include "stdafx.h"
#include "Game.h"
#include <ctime>
using namespace std;
int tbegin; 
Game::Game()
{
	Current_status = start;
	max_difficulty = 10;
	min_delay = 200;
	difficulty_scale = 0;
	need_lines_to_lvl_up = 10;
	speed = 1;
	size = 10;
	drawer = new Drawer(size);
	checker = new Checker;
	Field_Size = drawer->Field_Size;
	Current = new Tetromino_O;
	Predict = new Tetromino_O;
	Field = new bool*[Field_Size.x];
	for (int i(0); i < Field_Size.x; i++) Field[i] = new bool[Field_Size.y];
	tbegin = clock();
}



void Game::onStart()
{
	/* возможно, здесь будет меню, а не инит, пока что, по сути status = start - бесполезен */
	Help();
	Current_status = game;
	tick = 0;
	current_difficulty = 1;
	Create_new();
	for (int j = 0; j < Field_Size.x; j++)
		for (int i = 0; i < Field_Size.y; i++)
			Field[j][i] = 0;
	lines = 0;
	score = 0;
	easy_mode = 1;
	if (easy_mode) Calculate_Predict();
	sandbox = 0;
}
void Game::onEnd()
{
	exit(0);
}
void Game::GameLoop()
{
	if (Current_status == start) onStart();
	else if (Current_status == pause) //!!!!
	{
		char str[100];
		sprintf_s(str, "Pause\nYour score is %d", score);
		drawer->Draw_Score(Point(300, 300), (unsigned char*)str);
	}
	else if (Current_status == game)
	{
		tick++;
		drawer->FPS_Count();
		if ((tick == (max_difficulty - current_difficulty) * difficulty_scale + min_delay )&&  !sandbox)
		{
			Press_down();
			tick = 0;
			cout << tbegin - clock();
			tbegin = clock();
		}
	}
	else if (Current_status == end) onEnd();
}

bool Game::move_tetromino(Point V)
{

	if (checker->Check_collision_with_Field(Current, Field, Field_Size, V)) return false;
	if (!checker->Check_collision_with_side_borders(Current, V, Field_Size)) Current->move(V);
	if (easy_mode && V.x) Calculate_Predict();
	return analys_after_move();
}

void Game::Remove_lines()
{
	for (int i(0); i <checker->rows_count; i++)
	{
		for (int j(0); j < Field_Size.x; j++)
			for (int k(checker->rows_to_remove[i]); k < Field_Size.y - 1; k++)
				Field[j][k] = Field[j][k + 1];
		//	cout << "line '" << res[i] << "' removed" << endl;
	}
}


bool Game::analys_after_move()
{
	if (checker->Check_after_move(Current, Field, Field_Size))
	{
		if (checker->Check_game_over(Current, Field_Size))	Current_status = end;
		add_to_field();
		if (checker->Check_rows(Current, Field, Field_Size))
		{
			Remove_lines();
			Change_score();
		}
		Create_new();
		if (easy_mode) Calculate_Predict();
		return 1;
	}
	else return 0;
}

void Game::Draw()
{
	
	
	if (Current_status == game)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		if (easy_mode) drawer->Draw_Tetromino(Predict, drawer->Predict_color);
		drawer->Draw_Tetromino(Current, drawer->Current_color);
		drawer->Draw_Field(Field);
		drawer->Draw_Border();
		glFlush();
		glutSwapBuffers();
	}
	/*
	else if ((Current_status == end) && !ended)
	{
		char str[100];
		sprintf_s(str, "Your score is %d", score);
		drawer->Draw_Score(Point(300, 300), (unsigned char*)str);
		ended = 1;
	}
	*/
	drawer->TSK_FrameCount++;
}
void Game::onKey(unsigned char Key)
{
	switch (Key)
	{
	case Restart:
		Press_restart();
		break;
	case Sandbox:
		Press_sandbox();
		break;
	case Easy_mode:
		Press_easy_mode();
		break;
	case Force_Down:
		Press_Force_Down();
		break;
	case Pause:
		Press_pause();
		break;
	case Rotate:
		Press_rotate();
		break;
	case Exit:
		Press_exit();
		break;
	}
}
void Game::onSpecKey(int Key)
{
	switch (Key)
	{
	case GLUT_KEY_LEFT:
		Press_left();
		break;
	case GLUT_KEY_RIGHT:
		Press_right();
		break;
	case GLUT_KEY_UP:
		Press_up();
		break;
	case GLUT_KEY_DOWN:
		Press_down();
		break;
	}
}

void Game::Change_score()
{
	lines += checker->rows_count;
	score += checker->rows_count * current_difficulty;
	cout << "your score now : " << score << endl;
	if (lines >= current_difficulty * need_lines_to_lvl_up && current_difficulty < max_difficulty) current_difficulty++;
}
void Game::Create_new()
{
	int r = rand() % 7;
	delete Current;
	switch (r)
	{
	case 0:
		Current = new Tetromino_I;
		break;
	case 1:
		Current = new Tetromino_J;
		break;
	case 2:
		Current = new Tetromino_L;
		break;
	case 3:
		Current = new Tetromino_O;
		break;
	case 4:
		Current = new Tetromino_S;
		break;
	case 5:
		Current = new Tetromino_T;
		break;
	case 6:
		Current = new Tetromino_Z;
		break;
	}
	for (int i(0); i < 4; i++) Current->pts[i] += Point(Field_Size.x / 2, Field_Size.y);
}
void Game::Force_down(Tetromino *T)
{
	bool tmp = !checker->Check_after_move(T, Field, Field_Size);
	do
	{
		T->move(Point(0, -1));
		tmp = !checker->Check_after_move(T, Field, Field_Size);
	} while (tmp);
}
void Game::Calculate_Predict()
{
	Predict = Current->clone();
	Force_down(Predict);
}
void Game::Help()
{
	cout << "use arrows to move Tetromino" << endl
		<< "use spacebar to rotate Tetromino" << endl
		<< "use 'r' to restart game" << endl
		<< "use 'f' to force down Tetromino" << endl
		<< "use ESC to exit the game" << endl;
}

void Game::Press_left()
{
	if (Current_status == game) move_tetromino(Point(-1, 0));
}
void Game::Press_right(){
	if (Current_status == game) move_tetromino(Point(1, 0));
}
void Game::Press_down()	{
	if (Current_status == game) move_tetromino(Point(0, -1));
}
void Game::Press_up()	{
	if (Current_status == game) move_tetromino(Point(0, 1));
}
void Game::Press_exit()
{
	Current_status = end;
	//exit(0);
}
void Game::Press_rotate()
{
	if (!checker->Check_collision_with_Field_on_rotate(Current->clone(), Field, Field_Size)) Current->rotate();
	int dx = checker->Check_collision_with_borders_after_rotate(Current, Field_Size);
	if (dx) Current->move(Point(dx, 0));
	if (easy_mode) Calculate_Predict();
}
void Game::Press_restart()
{
	Current_status = start;
}
void Game::Press_Force_Down()
{
	Force_down(Current);
	analys_after_move();
}
void Game::Press_sandbox()
{
	sandbox = !sandbox;
}
void Game::Press_pause()
{
	if (Current_status == pause) Current_status = game;
	else if (Current_status == game) Current_status = pause;
}
void Game::Press_easy_mode()
{
	easy_mode = !easy_mode;
	if (easy_mode) Calculate_Predict();
}
