#pragma once
#include "VParabola.h"
#include <iostream>

/*
	����� ����� ������� ������� �����/����� � ������� �������
	
	point:  �����, � ������� ������ ������� ����������
	pe:     ����������, ��� ������� ����� ��� ���
	y:      ���������� "Y" ����� "point". ������� ����������� �� ���� "y"
	arch:   ���� "pe"==true, �� ��� ����, ���� ������� ���������� �������
*/

class VEvent
{
public:
	VPoint *point;
	bool pe;
	double y;
	VParabola *arch;

	VEvent(VPoint *p, bool pev)
	{
		point = p;
		pe = pev;
		y = p->y;
		arch = 0;
	}

	struct CompareEvent : public std::binary_function<VEvent*, VEvent*, bool>
	{
		bool operator() (const VEvent* l, const VEvent *r) const
		{
			return (l->y < r->y);
		}
	};
};