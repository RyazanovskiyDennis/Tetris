#pragma once
#include "stdafx.h"

struct ColorF
{
	float r, g, b;
	ColorF() : r(0), g(0), b(0) {};
	ColorF(float x, float y, float z) : r(x), g(y), b(z){};
};

class Drawer
{

	int Size;
	double TSK_FrameCount, TSK_SyncTime;
	Point LeftCornerOfField, Window_Size, Field_Size;
	ColorF Current_color, Predict_color;
	friend class Game;
protected:
	Drawer(int);
	void Draw_Tetromino(Tetromino* Current, ColorF Color);
	void Draw_Border();
	void Draw_Field(bool **Field);
	void onReshape(int Width, int Height);
	void FPS_Count();
	void Draw_Score(Point , unsigned char* );
public:
	Point Get_Window_Size(){ return Window_Size; }
};