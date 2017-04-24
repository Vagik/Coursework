#pragma once
#include "VPoint.h"
	/*
	Класс, отвечающий за ребра диаграммы Вороного

	start		: указатель на начальную точку
	end			: указатель на конечную точку
	left		: указатель на область(или точку) левее от ребра
	right		: указатель на область(или точку) правее от ребра

	neighbour	: некоторые ребра состоят из двух частей, поэтому мы добавляем указатель на другую часть, чтобы соединить их в конце алгоритма

	direction	: направляющий вектор от "start" до "end",  normal of |left, right|
	f, g		: направляющие коэффициенты, удовлетворяющие уравнению y = f*x + g (ребро лежит на этой линии)
*/
class VEdge
{
public:
	VPoint *start;
	VPoint *end;
	VPoint *direction;
	VPoint *left;
	VPoint *right;

	double f;
	double g;

	VEdge *neighbour;

	VEdge (VPoint *s, VPoint *l, VPoint *r)
	{
		start = s;
		left = l;
		right = r;
		neighbour = 0;
		end = 0;
		f=(r->x - l->x)/(l->y - r->y);
		g = s->y - f*s->x;
		direction = new VPoint (r->y - l->y,l->x - r->x);
	}

	~VEdge()
	{
		delete direction;
	}
};