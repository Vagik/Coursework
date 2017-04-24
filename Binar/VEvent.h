#pragma once
#include "VParabola.h"
#include <iostream>

/*
	Класс будет хранить событие точки/круга в очереди событий
	
	point:  точка, в которой данное событие происходит
	pe:     определяет, это событие точки или нет
	y:      координата "Y" точки "point". События сортируются по этой "y"
	arch:   если "pe"==true, то это арка, выше которой происходит событие
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