#pragma once
#include "VPoint.h"
	/*
	�����, ���������� �� ����� ��������� ��������

	start		: ��������� �� ��������� �����
	end			: ��������� �� �������� �����
	left		: ��������� �� �������(��� �����) ����� �� �����
	right		: ��������� �� �������(��� �����) ������ �� �����

	neighbour	: ��������� ����� ������� �� ���� ������, ������� �� ��������� ��������� �� ������ �����, ����� ��������� �� � ����� ���������

	direction	: ������������ ������ �� "start" �� "end",  normal of |left, right|
	f, g		: ������������ ������������, ��������������� ��������� y = f*x + g (����� ����� �� ���� �����)
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