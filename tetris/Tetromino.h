#pragma once
#include "stdafx.h"

struct Point
{
	int x, y;
	Point() : x(0), y(0) {};
	Point(int a, int b) : x(a), y(b){};
	void operator += (Point p) { x += p.x;	y += p.y; }
};

class Tetromino
{
public:
	Point pts[4];
	virtual void move(Point Speed){ for (int i(0); i < 4; i++) pts[i] += Speed; }
	virtual void rotate();
	virtual Tetromino* clone(){ return new Tetromino(*this); };
};
class Tetromino_I : public Tetromino
{
public:
	Tetromino_I();
};
class Tetromino_J : public Tetromino
{

public:
	Tetromino_J();
};
class Tetromino_L : public Tetromino
{

public:
	Tetromino_L();
};
class Tetromino_O : public Tetromino
{
public:
	Tetromino_O();
	void rotate(){ return; }
};
class Tetromino_S : public Tetromino
{

public:
	Tetromino_S();
};
class Tetromino_T : public Tetromino
{

public:
	Tetromino_T();
};
class Tetromino_Z : public Tetromino
{

public:
	Tetromino_Z();
};



