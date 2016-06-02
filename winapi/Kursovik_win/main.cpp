#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include <Windowsx.h>

#include "model.h"

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Win32 Guided Tour Application");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#define PI (double)3.1415
#define WINDOW_WIDTH 800
TLcastle Lcastle;
TRcastle Rcastle;
TShot Shot;
Tmap Map;
void DoPhysics(ULONGLONG dT);
void StartGame();
FILE *F;
double filevalue;
			int n=0;
double filemas[7];
char filename[] = "file.bin ";
/*!
*Main function which performs the window-creation action and calls main processing function called doPhysics
*@return hInstance, hPrevInstance, lpCmdLine, nCmdShow
*/
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable

	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	ULONGLONG prevTime = -1, curTime, deltaT;

	StartGame();
	// Enter the infinite message loop
	while (TRUE)
	{
		// Check to see if any messages are waiting in the queue
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Translate the message and dispatch it to WindowProc()
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If the message is WM_QUIT, exit the while loop
		if (msg.message == WM_QUIT)
			break;

		curTime = GetTickCount64();
		if (prevTime == -1)
			deltaT = 0;
		else deltaT = curTime - prevTime;
		prevTime = curTime;

		DoPhysics(deltaT);

		InvalidateRect(hWnd, NULL, 1);
	}

	return (int)msg.wParam;
}

/*!
*Initialization function which is called at the start and every restart of the game.
*Sets the default parametres for the game objects.
*/
void StartGame()
{
	if(Map.saved==0)
	{
	srand(GetTickCount());
	RECT r = { 100, 100, 700, 400 };
	Lcastle.x = 55;
	Lcastle.y = 500;
	Lcastle.x1 = 80;
	Lcastle.y1 = 475;
	Rcastle.x = 715;
	Rcastle.y = 485;
	Rcastle.x1 = 690;
	Rcastle.y1 = 475;
	Shot.r = 10;
	Shot.x = 20;
	Shot.y = 20;
	Shot.t = 0;
	Shot.vnx = 140;
	Shot.vny = 140;
	Shot.a = 0.1;
	Shot.y1 = Lcastle.y1;
	Shot.x1 = Lcastle.x1;
	Shot.changed = 0;
	Shot.G = 35;
	Shot.draw = 0;
	Map.x = 60;
	Map.y = 600;
	Map.xp = 60;
	Map.yp = 600;
	Map.xl1 = 20;
	Map.yl1 = 520;
	Map.xl2 = 180;
	Map.yl2 = 480;
	Map.xl3 = 250;
	Map.yl3 = 480;
	Map.xl4 = 370;
	Map.yl4 = 300;
	Map.xl5 = 420;
	Map.yl5 = 310;
	Map.xl6 = 520;
	Map.yl6 = 460;
	Map.xl7 = 590;
	Map.yl7 = 500;
	Map.xl8 = 750;
	Map.yl8 = 500;
	Map.info=0;
		Lcastle.angle = 10;
		Rcastle.angle = 170;
		Lcastle.health = 30;
	Rcastle.health = 30;
		Shot.switched=0;//1-левый 0-правый замки
			Map.gameover = 0;//0-игра идет, 1-лицо сломалось у левого, 2-лицо сломалось у правого
			Map.saved=1;
	}
	else
	{
		srand(GetTickCount());
	RECT r = { 100, 100, 700, 400 };
	Lcastle.x = 55;
	Lcastle.y = 500;
	Lcastle.x1 = 80;
	Lcastle.y1 = 475;
	Rcastle.x = 715;
	Rcastle.y = 485;
	Rcastle.x1 = 690;
	Rcastle.y1 = 475;
	Shot.r = 10;
	Shot.x = 20;
	Shot.y = 20;
	Shot.t = 0;
	Shot.vnx = 140;
	Shot.vny = 140;
	Shot.a = 0.1;
	Shot.y1 = Lcastle.y1;
	Shot.x1 = Lcastle.x1;
	Shot.changed = 0;
	Shot.G = 35;
	Shot.draw = 0;
	Map.x = 60;
	Map.y = 600;
	Map.xp = 60;
	Map.yp = 600;
	Map.xl1 = 20;
	Map.yl1 = 520;
	Map.xl2 = 180;
	Map.yl2 = 480;
	Map.xl3 = 250;
	Map.yl3 = 480;
	Map.xl4 = 370;
	Map.yl4 = 300;
	Map.xl5 = 420;
	Map.yl5 = 310;
	Map.xl6 = 520;
	Map.yl6 = 460;
	Map.xl7 = 590;
	Map.yl7 = 500;
	Map.xl8 = 750;
	Map.yl8 = 500;
	Map.info=0;
	}
}
/*!
*The function that makes objects move and change statements.
*Here we make all changes to coords and control of movements.
*Repeated every timer tick.
*/
void DoPhysics(ULONGLONG dT)
{
	RECT r = { 100, 100, 700, 400 };



	//process ship model

	Lcastle.sinus = sin(Lcastle.angle * PI / 180.0); //синус угла альфа
	Lcastle.cosin = cos(Lcastle.angle*PI / 180.0);//косинус альфа
	Lcastle.tangens = Lcastle.sinus / Lcastle.cosin;
	Lcastle.toright = 25 * Lcastle.cosin;
	Lcastle.upstairs = 25 * Lcastle.sinus;
	Lcastle.x1 = Lcastle.x + Lcastle.toright;
	Lcastle.y1 = Lcastle.y - Lcastle.upstairs;

	Rcastle.sinus = sin(Rcastle.angle * PI / 180.0); //синус угла альфа
	Rcastle.cosin = cos(Rcastle.angle*PI / 180.0);//косинус альфа
	Rcastle.tangens = Rcastle.sinus / Rcastle.cosin;
	Rcastle.toright = 25 * Rcastle.cosin;
	Rcastle.upstairs = 25 * Rcastle.sinus;
	Rcastle.x1 = Rcastle.x + Rcastle.toright;
	Rcastle.y1 = Rcastle.y - Rcastle.upstairs;


	if (Shot.draw != 0)

	{
		if (Shot.switched == 0)
		{
			if (Shot.changed == 0)
			{
				Shot.x = Lcastle.x1;
				Shot.y = Lcastle.y1;
				Shot.vy = Shot.vnx*(-1.10);
				Shot.changed = 1;
			}
			Shot.x += (Shot.vnx - 0)*((double)dT / 1000)*cos(Lcastle.angle*PI / 180);
			Shot.vy += ((double)dT / 1000)*Shot.G;
			Shot.y += Shot.vy*((double)dT / 1000)*sin(Lcastle.angle*PI / 180);
		}
		else
		{
			if (Shot.changed == 0)
			{
				Shot.x = Rcastle.x1;
				Shot.y = Rcastle.y1;
				Shot.vy = Shot.vnx*(-1.10);
				Shot.changed = 1;
			}
			Shot.x += (Shot.vnx - 0)*((double)dT / 1000)*cos(Rcastle.angle*PI / 180);
			Shot.vy += ((double)dT / 1000)*Shot.G;
			Shot.y += Shot.vy*((double)dT / 1000)*sin(Rcastle.angle*PI / 180);
		}
	}
	else
	{
		Shot.changed = 0;
	}

	//полет при углах от 0 до 180 градусов

	//processing cannon


	double dx = Lcastle.x - 10 - Shot.x;
	double dy = Lcastle.y - Shot.y;
	if (sqrt(dx*dx + dy*dy) <= 15 + Shot.r)
	{
		Shot.draw = 0;
		Shot.x = 100;
		Shot.y = 100;
		Lcastle.health -= 10;
		if (Lcastle.health == 0)
		{
			Map.gameover = 1;
		}
		Lcastle.angle = 0;
		Rcastle.angle = 180;
	}
	double dxR = Rcastle.x + 10 - Shot.x;
	double dyR = Rcastle.y - Shot.y;
	if (sqrt(dxR*dxR + dyR*dyR) <= 15 + Shot.r)
	{
		Shot.draw = 0;
		Shot.x = 100;
		Shot.y = 100;
		Rcastle.health -= 10;
		if (Rcastle.health == 0)
		{
			Map.gameover = 2;
		}
		Lcastle.angle = 0;
		Rcastle.angle = 180;
	}
	Map.xp = Map.xl1;
	for (int i = 0; i<160; i++)
	{
		Map.yp = (Map.xp + 300) / 4;
		Map.yp = 600 - Map.yp;
		if (Shot.x <= 180 && Shot.x >= Map.xp&&Shot.y + Shot.r >= Map.yp)
		{
			Shot.draw = 0;
			Shot.x = 100;
			Shot.y = 100;
			Lcastle.angle = 0;
			Rcastle.angle = 180;
		}
		Map.xp++;
	}
	Map.xp = Map.xl2;//180-250
	for (int i = 0; i<70; i++)
	{
		Map.yp = 480;
		if (Shot.x <= 250 && Shot.x >= Map.xp&&Shot.y + Shot.r >= Map.yp)
		{
			Shot.draw = 0;
			Shot.x = 100;
			Shot.y = 100;
			Lcastle.angle = 0;
			Rcastle.angle = 180;
		}
		Map.xp++;
	}
	Map.xp = Map.xl3;//Map.xl3=250;Map.yl3=480;Map.xl4=370;Map.yl4=300;
	for (int i = 0; i<120; i++)
	{
		Map.yp = (3 * Map.xp - 510) / 2;
		Map.yp = 600 - Map.yp;
		if (Shot.x <= 370 && Shot.x >= Map.xp&&Shot.y + Shot.r >= Map.yp)
		{
			Shot.draw = 0;
			Shot.x = 100;
			Shot.y = 100;
			Lcastle.angle = 0;
			Rcastle.angle = 180;
		}
		Map.xp++;
	}
	Map.xp = Map.xl4;//Map.xl4=370;Map.yl4=300;Map.xl5=420;Map.yl5=310;
	for (int i = 0; i<50; i++)
	{
		Map.yp = (1870 - Map.xp) / 5;
		Map.yp = 600 - Map.yp;
		if (Shot.x <= 420 && Shot.x >= Map.xp&&Shot.y + Shot.r >= Map.yp)
		{
			Shot.draw = 0;
			Shot.x = 100;
			Shot.y = 100;
			Lcastle.angle = 0;
			Rcastle.angle = 180;
		}
		Map.xp++;
	}

	Map.xp = Map.xl5;//Map.xl5=420;Map.yl5=310;Map.xl6=520;Map.yl6=460;
	for (int i = 0; i<100; i++)
	{
		Map.yp = (-15 * Map.xp + 9200) / 10;
		Map.yp = 600 - Map.yp;
		if (Shot.x >= 420 && Shot.x <= Map.xp&&Shot.y + Shot.r >= Map.yp)
		{
			Shot.draw = 0;
			Shot.x = 100;
			Shot.y = 100;
			Lcastle.angle = 0;
			Rcastle.angle = 180;
		}
		Map.xp++;
	}

	Map.xp = Map.xl6;//Map.xl6=520;Map.yl6=460;Map.xl7=590;Map.yl7=500;
	for (int i = 0; i<70; i++)
	{
		Map.yp = (-4 * Map.xp + 3060) / 7;
		Map.yp = 600 - Map.yp;
		if (Shot.x >= 520 && Shot.x <= Map.xp&&Shot.y + Shot.r >= Map.yp)
		{
			Shot.draw = 0;
			Shot.x = 100;
			Shot.y = 100;
			Lcastle.angle = 0;
			Rcastle.angle = 180;
		}
		Map.xp++;
	}

	Map.xp = Map.xl7;//Map.xl7=590;Map.yl7=500;Map.xl8=750;Map.yl8=500;
	for (int i = 0; i<160; i++)
	{
		Map.yp = 500;
		if (Shot.x >= 520 && Shot.x <= Map.xp&&Shot.y + Shot.r >= Map.yp)
		{
			Shot.draw = 0;
			Shot.x = 100;
			Shot.y = 100;
			Lcastle.angle = 0;
			Rcastle.angle = 180;
		}
		Map.xp++;
	}


	if ((Shot.x < 0) || (Shot.x > 800) || (Shot.y < 0) || (Shot.y > 600))
	{
		Shot.draw = 0;
		Shot.x = 100;
		Shot.y = 100;
		Lcastle.angle = 0;
		Rcastle.angle = 180;
	}
	else
	{

	}
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
/*!
*The function in which we set all the controls for player.
*It also contains all the drawing parametres for objects.
*@return hWnd, message, wParam, lParam
*/
HBITMAP hBitmap = NULL;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	   int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	int savedDC;
	HDC backbuffDC;
	int width, height;
	HBITMAP backbuffer;
	HBRUSH hBrush;
	TCHAR greeting[] = _T("Hello, World!");
	int xPos, yPos;
	double dx, dy;
	HPEN hPen, hOldPen;
	double alpha, pieX, pieY;
	int r;
	/*!
*This switch allows to create background and to assign control keys
*/
	switch (message)
	{
	 case WM_CREATE:
    	hBitmap = (HBITMAP)LoadImage(hInst, L"C:\\Users/asus/Documents/Visual Studio 2010/Projects/Kursovik_win/Kursovik_win/test.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    	break;
	case WM_KEYUP:
		switch (wParam)
		{
		case 'S':
			break;
		case 'W':
			break;
		}
		break;
	case WM_KEYDOWN:

		switch (wParam)
		{
		case 'U'://загрузка
			Map.displayloaded=1;
			F = fopen(filename, "rb");
			for (int i=0; i<6; i++)
			{
				fread(&filevalue, sizeof(double), 1, F);
				switch(i)
				{
				case 0:
					Lcastle.angle=filevalue;
					break;
					case 1:
			Rcastle.angle=filevalue;
			break;
					case 2:
			Lcastle.health=filevalue;
			break;
					case 3:
			Rcastle.health=filevalue;
			break;
					case 4:
			Map.gameover=filevalue;
			break;
					case 5:
			Shot.switched=filevalue;
			break;
				}
			}			
			fclose(F);
			StartGame();
			break;    

		case 'Y'://сохранение
			Map.displaysaved=1;
			F = fopen(filename, "w+"); 
			n=0;
			filemas[0] = Lcastle.angle;
			filemas[1]=Rcastle.angle;
			filemas[2]=Lcastle.health;
			filemas[3]=Rcastle.health;
			filemas[4]=Map.gameover;
			filemas[5]=Shot.switched;
			for(int i=0; i<6; i++)
			{
				fwrite(&filemas[i], sizeof(double), 1, F);
			}
			fclose(F);
			Map.saved=1;
			break;

		case 'R':
			Map.displayloaded=0;
			Map.displaysaved=0;
			Map.saved=0;
			StartGame();
			break;
		case 'I':
			Map.displayloaded=0;
			Map.displaysaved=0;
			if(Map.info==0)
			{
				Map.info=1;
			}
			else
			{
				Map.info=0;
			}
			break;
		case 'S':
			Map.displayloaded=0;
			Map.displaysaved=0;
			if (Map.gameover != 0)
			{
			}
			else
			{

				if (Shot.switched == 1)
				{
					Lcastle.angle -= 2;
				}
				else
				{
					Rcastle.angle += 2;
				}
			}
			break;
		case 'W':
			Map.displayloaded=0;
			Map.displaysaved=0;
			if (Map.gameover != 0)
			{
			}
			else
			{
				if (Shot.switched == 1)
				{
					Lcastle.angle += 2;
				}
				else
				{
					Rcastle.angle -= 2;
				}
			}
			break;
		case ' ':
			Map.displayloaded=0;
			Map.displaysaved=0;
			if (Map.gameover != 0)
			{
			}
			else
			{
				if (Shot.draw == 1)
				{

				}
				else
				{
					if (Shot.switched == 0)
					{
						Shot.switched = 1;
					}
					else
					{
						Shot.switched = 0;
					}
					Shot.draw = 1;
				}
			}
			break;
		
	}
		InvalidateRect(hWnd, NULL, 1);
		break;
	case WM_PAINT:

		PAINTSTRUCT 	ps;
    	HDC 			hdc;
    	BITMAP 			bitmap;
    	HDC 			hdcMem;
        HGDIOBJ 		oldBitmap;
		hdc = BeginPaint(hWnd, &ps);
		RECT rect;
		GetClientRect(hWnd, &rect);
		width = rect.right;
		height = rect.bottom;

		backbuffDC = CreateCompatibleDC(hdc);

		backbuffer = CreateCompatibleBitmap(hdc, width, height);

		savedDC = SaveDC(backbuffDC);

		SelectObject(backbuffDC, backbuffer);
			

		// Draw HERE

		//clear window
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		FillRect(backbuffDC, &rect, hBrush);
		DeleteObject(hBrush);
			hdcMem = CreateCompatibleDC(hdc);
        oldBitmap = SelectObject(hdcMem, hBitmap);
 GetObject(hBitmap, sizeof(bitmap), &bitmap);
        BitBlt(backbuffDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
		//draw asteroids
		hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));//!
   hOldPen = (HPEN)SelectObject(backbuffDC, hPen);//!
		//Lcastle.d=sqrt((Lcastle.width*Lcastle.width)+(Lcastle.height*Lcastle.height));
		Rectangle(backbuffDC, Lcastle.x - 25, Lcastle.y - 15, Lcastle.x + 5, Lcastle.y + 15);
		MoveToEx(backbuffDC, Lcastle.x, Lcastle.y, NULL);
		LineTo(backbuffDC, Lcastle.x1, Lcastle.y1);
		Rectangle(backbuffDC, Rcastle.x - 5, Rcastle.y - 15, Rcastle.x + 25, Rcastle.y + 15);
		MoveToEx(backbuffDC, Rcastle.x, Rcastle.y, NULL);
		LineTo(backbuffDC, Rcastle.x1, Rcastle.y1);

		MoveToEx(backbuffDC, Map.xl1, Map.yl1, NULL);
		LineTo(backbuffDC, Map.xl2, Map.yl2);
		MoveToEx(backbuffDC, Map.xl2, Map.yl2, NULL);
		LineTo(backbuffDC, Map.xl3, Map.yl3);
		MoveToEx(backbuffDC, Map.xl3, Map.yl3, NULL);
		LineTo(backbuffDC, Map.xl4, Map.yl4);
		MoveToEx(backbuffDC, Map.xl4, Map.yl4, NULL);
		LineTo(backbuffDC, Map.xl5, Map.yl5);
		MoveToEx(backbuffDC, Map.xl5, Map.yl5, NULL);
		LineTo(backbuffDC, Map.xl6, Map.yl6);
		MoveToEx(backbuffDC, Map.xl6, Map.yl6, NULL);
		LineTo(backbuffDC, Map.xl7, Map.yl7);
		MoveToEx(backbuffDC, Map.xl7, Map.yl7, NULL);
		LineTo(backbuffDC, Map.xl8, Map.yl8);

		//draw shot

		if (Shot.draw != 0)
		{
			Ellipse(backbuffDC, Shot.x - Shot.r, Shot.y - Shot.r, Shot.x + Shot.r, Shot.y + Shot.r);
		}
		SelectObject(backbuffDC, hOldPen);
   DeleteObject(hPen);
   //print text
		WCHAR s[100];
		wsprintf(s, _T("%d"), (int)Lcastle.health);
		TextOut(backbuffDC, Lcastle.x - 20, Lcastle.y - 5, s, wcslen(s));
		wsprintf(s, _T("%d"), (int)Rcastle.health);
		TextOut(backbuffDC, Rcastle.x + 5, Rcastle.y - 5, s, wcslen(s));
		wsprintf(s, _T("Press I to check the instructions"));
		TextOut(backbuffDC, 25, 20, s, wcslen(s));
		if(Map.displayloaded==1)
		{
			wsprintf(s, _T("The game was loaded!"));
			TextOut(backbuffDC, 320, 75, s, wcslen(s));
		}
		if(Map.displaysaved==1)
		{
			wsprintf(s, _T("The game was saved!"));
			TextOut(backbuffDC, 320, 75, s, wcslen(s));
		}
		if(Map.info==0)
		{

		}
		else
		{
			wsprintf(s, _T("To increase gun's height press and hold W"));
			TextOut(backbuffDC, 25, 45, s, wcslen(s));
			wsprintf(s, _T("To decrease gun's height press and hold S"));
			TextOut(backbuffDC, 25, 60, s, wcslen(s));
			wsprintf(s, _T("To shoot press space"));
			TextOut(backbuffDC, 25, 75, s, wcslen(s));
			wsprintf(s, _T("To restart press R"));
			TextOut(backbuffDC, 25, 90, s, wcslen(s));
			wsprintf(s, _T("To save the game press Y"));
			TextOut(backbuffDC, 25, 105, s, wcslen(s));
			wsprintf(s, _T("To load saved game press U"));
			TextOut(backbuffDC, 25, 120, s, wcslen(s));
		}
		if (Shot.switched == 0)
		{
			wsprintf(s, _T("Right castle's turn!"));
			TextOut(backbuffDC, 600, 10, s, wcslen(s));
		}
		if (Shot.switched == 1)
		{
			wsprintf(s, _T("Left castle's turn!"));
			TextOut(backbuffDC, 600, 10, s, wcslen(s));
		}
		if (Map.gameover == 1)
		{
			wsprintf(s, _T("Game over!"));
			TextOut(backbuffDC, 600, 35, s, wcslen(s));
			wsprintf(s, _T("Right castle won!"));
			TextOut(backbuffDC, 600, 50, s, wcslen(s));
			wsprintf(s, _T("GAME OVER!"));
			TextOut(backbuffDC, 350, 25, s, wcslen(s));
			wsprintf(s, _T("PRESS 'R' TO RESTART!"));
			TextOut(backbuffDC, 320, 50, s, wcslen(s));
		}
		if (Map.gameover == 2)
		{
			wsprintf(s, _T("Game over!"));
			TextOut(backbuffDC, 600, 35, s, wcslen(s));
			wsprintf(s, _T("Left castle won!"));
			TextOut(backbuffDC, 600, 50, s, wcslen(s));
			wsprintf(s, _T("GAME OVER!"));
			TextOut(backbuffDC, 350, 25, s, wcslen(s));
			wsprintf(s, _T("PRESS 'R' TO RESTART!"));
			TextOut(backbuffDC, 320, 50, s, wcslen(s));
		}

		// End application-specific layout section.
		BitBlt(hdc, 0, 0, width, height, backbuffDC, 0, 0, SRCCOPY);
		RestoreDC(backbuffDC, savedDC);
		
        SelectObject(hdcMem, oldBitmap);
        DeleteDC(hdcMem);
		DeleteObject(backbuffer);
		DeleteDC(backbuffDC);

		EndPaint(hWnd, &ps);
		break;
	case WM_ERASEBKGND:
		return 1;
	case WM_DESTROY:
		DeleteObject(hBitmap);
    	PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}