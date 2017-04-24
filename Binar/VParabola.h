#pragma once
#include "VEdge.h"


//Параболы и события имеют указатели друг на друга, поэтому мы объявляем класс VEvent, который будет определен позже
class VEvent;

/*
	Класс будет хранить информацию об элементах "береговой линии" последовательно. Он может представлять дугу
	параболы или пересечение между двумя арками, которое определяет ребро.
	В данной реализации построено бинарное дерево с этими элементами
	(внутренние узлы - ребра, листья - арки)
*/

class VParabola
{
private:
	VParabola *leftP;
	VParabola *rightP;

public:
	/*
		isLeaf		: флаг, определяющий: лист или внутренний узел
		site		: указатель на фокус параболы
		edge		: указатель на ребро
		cEvent		: указатель на событие круга
		parent		: указатель на родителя в дереве
	*/
	bool	   isLeaf;
	VPoint     *site;
	VEdge      *edge;
	VEvent     *cEvent;
	VParabola  *parent;

	VParabola ()
	{
		site = 0;
		isLeaf = false;
		cEvent = 0;
		edge = 0;
		parent = 0;
	}
	VParabola(VPoint *s)
	{
		site = s;
		isLeaf = true;
		cEvent = 0;
		edge = 0;
		parent = 0;
	}
	void SetLeft  (VParabola *p) {leftP = p; p->parent = this;}
	void SetRight (VParabola *p) {rightP = p; p->parent = this;}
	VParabola *Left()  {return leftP;}
	VParabola *Right() {return rightP;}

	static VParabola *GetLeft (VParabola *p)  {return GetLeftChild(GetLeftParent(p));}
	static VParabola *GetRight (VParabola *p) {return GetRightChild(GetRightParent(p));}
	static VParabola *GetLeftParent (VParabola *p)
	{
		VParabola *par = p->parent;
		VParabola *pLast = p;
		while (par->Left() == pLast)
		{
			if(!par->parent)
				return 0;
			pLast = par;
			par = par->parent;
		}
		return par;
	}
	static VParabola *GetRightParent (VParabola *p)
	{
		VParabola *par = p->parent;
		VParabola *pLast = p;
		while (par->Right() == pLast)
		{
			if(!par->parent)
				return 0;
			pLast = par;
			par = par->parent;
		}
		return par;
	}
	static VParabola *GetLeftChild (VParabola *p)
	{
		if(!p)
			return 0;
		VParabola *par = p->Left();
		while(!par->isLeaf)
			par = par->Right();
		return par;
	}
	static VParabola *GetRightChild (VParabola *p)
	{
		if(!p)
			return 0;
		VParabola *par = p->Right();
		while(!par->isLeaf)
			par = par->Left();
		return par;
	}
};