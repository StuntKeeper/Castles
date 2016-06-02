#ifndef __MODEL__
#define __MODEL__

#include <Windows.h>

struct Tmap
{
	double x, y, xp, yp;
	double xl1, yl1, xl2, yl2, xl3, yl3, xl4, yl4, xl5, yl5, xl6, yl6, xl7, yl7, xl8, yl8;
	double gameover, info;
	double saved, displaysaved, displayloaded;
};
struct TShot
{
	double x, y, x1, y1, vnx, vny, vx, vy;
	double r, CD, h, t, a, changed, G, switched, draw;
};
struct TLcastle
{
	double up, down, v, d;
	double width, height;
	double x, y, x1, y1;
	double sinus, cosin, tangens, angle;
	double toright, upstairs;//сдвиги для координат пушки
	double health;
};
struct TRcastle
{
	double up, down, v, d;
	double width, height;
	double x, y, x1, y1;
	double sinus, cosin, tangens, angle;
	double toright, upstairs;//сдвиги для координат пушки
	double health;
};

#endif