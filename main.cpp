#include "stdafx.h"


Game game;



void Reshape(int Width, int Height){game.onReshape(Width, Height);}

void Idle(){ game.GameLoop(); }

void Draw(){ game.Draw(); }

void Keyboard( unsigned char Key, int X, int Y ){ game.onKey(Key); }

void SpecialKeyboard( int Key, int MouseX, int MouseY ){ game.onSpecKey(Key); }

int _tmain( int argc, _TCHAR *argv[] )
{
	srand(time(0));
	glutInit(&argc,(char**) argv);
	SetConsoleTitle(L"Title");
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	Point WSize = game.Get_Window_Size();
	glutInitWindowSize(WSize.x, WSize.y);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Title");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutMainLoop();
	return 0;
}
