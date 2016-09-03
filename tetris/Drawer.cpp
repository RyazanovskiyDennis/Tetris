#include "stdafx.h"


Drawer::Drawer(int s)
{
	Window_Size = Point(800,600);
	Field_Size = Point(10, 20);
	Size = 0;
	TSK_FrameCount = 0;
	TSK_SyncTime = 0;
	LeftCornerOfField = Point(30, 30);
	Size = s;
	Current_color = ColorF(1.f, 0.25f, 0.f);
	Predict_color = ColorF(0.f, 0.25f, 1.f);
}

void Drawer::FPS_Count()
{
	long Time;
	static long OldTime = -1, StartTime;
	static char Buf[100];
	if (OldTime == -1) StartTime = OldTime = clock();
	else
	{
		Time = clock();
		TSK_SyncTime = (double)(Time - StartTime) / CLOCKS_PER_SEC;
		Time = Time - OldTime;
		if (Time > CLOCKS_PER_SEC)
		{
			OldTime = clock();
			sprintf_s(Buf, "%s FPS: %.3f","Tetris",TSK_FrameCount / ((double)Time / CLOCKS_PER_SEC));
			TSK_FrameCount = 0;
			glutSetWindowTitle(Buf);
		}
	}
}

void Drawer::onReshape(int Width, int Height)
{
	glViewport(0, 0, Window_Size.x = Width, Window_Size.y = Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, Window_Size.x, 0, Window_Size.y);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void Drawer::Draw_Border()
{

	glColor3d(1, 1, 1);

	glRecti(-1 * Size + LeftCornerOfField.x, -1 * Size + LeftCornerOfField.y,
			 0 + LeftCornerOfField.x, Field_Size.y * Size + LeftCornerOfField.y);
	glRecti( 0 + LeftCornerOfField.x, -1 * Size + LeftCornerOfField.y,
			 Field_Size.x * Size + LeftCornerOfField.x, 0 + LeftCornerOfField.y);
	glRecti( Field_Size.x * Size + LeftCornerOfField.x, -1 * Size + LeftCornerOfField.y,
			(Field_Size.x + 1) * Size + LeftCornerOfField.x, Field_Size.y * Size + LeftCornerOfField.y);
	glColor3d(0, 0, 0);

}
void Drawer::Draw_Field(bool **Field)
{
	for (int i = 0; i < Field_Size.x; i ++)
		for (int j = 0; j < Field_Size.y; j++)
			if (Field[i][j])
			{
				glColor3f(1.f, 0.25f, 0.5f);
				glRecti((i) * Size + LeftCornerOfField.x,
					(j) * Size + LeftCornerOfField.y,
					(i + 1) * Size + LeftCornerOfField.x,
					(j + 1) * Size + LeftCornerOfField.y);
			}
	glutPostRedisplay();
}
void Drawer::Draw_Tetromino(Tetromino* Current, ColorF Color)
{
	for (int i(0); i < 4; i++)
	{
		glColor3f(Color.r, Color.g * i, Color.b);
		glRecti((Current->pts[i].x) * Size + LeftCornerOfField.x,
				(Current->pts[i].y) * Size + LeftCornerOfField.y,
				(Current->pts[i].x + 1) * Size + LeftCornerOfField.x,
				(Current->pts[i].y + 1) * Size + LeftCornerOfField.y);
	}
	glutPostRedisplay();
}


void Drawer::Draw_Score(Point Pos,unsigned char* str)
{
	glRasterPos2i(Pos.x, Pos.y);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, str);
}


