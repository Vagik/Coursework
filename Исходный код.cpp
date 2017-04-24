#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdlib.h>
#include <cmath>
#include <conio.h>
#include <iostream>
#include <clocale>
#include "Voronoi.h"

using namespace std;
using namespace cv;
using namespace vor;

Voronoi *v;
Vertices *ver;
Vertices *dir;
Edges *edg;
double w = 500;


int myRand(int a, int b)
{
	return (rand() % (b - a) + a);
}

void drawPoint(IplImage *img, int x, int y)
{
	cvCircle(img,cvPoint(x,y),3,CV_RGB(255,255,255),3);
}

void drawLine(IplImage *img, int x, int y, int angle,int length,int constLength,int iter, int IterNum)
{
	int x1 = x, y1 = y;
	int x2 = 0, y2 = 0;
	int x3 = 0, y3 = 0;
	int rd=0;
	int alpha = 0;
	int len = length;
	int koef = constLength/iter;

	if(IterNum == iter)
		return;
	rd = rand()%5;
	if(rd == 0)
	{
		IterNum++;
		len = myRand(constLength-(IterNum-1)*koef,constLength-(IterNum)*koef);
		alpha = myRand(angle-22,angle+22);
		x2 = x1+len*cos(alpha*CV_PI/180);
		y2 = y1+len*sin(alpha*CV_PI/180);
		cvLine(img,cvPoint(x1,y1),cvPoint(x2,y2),CV_RGB(255,255,255),int(pow(iter-IterNum,1.0/1.5)));
		drawLine(img,x2,y2,alpha,len,constLength,iter,IterNum);

	}
	else
	{
		IterNum++;
		len = myRand(constLength-(IterNum-1)*koef,constLength-(IterNum)*koef);
		alpha = myRand(angle-22,angle+22);
		x2 = x1+len*cos(alpha*CV_PI/180);
		y2 = y1+len*sin(alpha*CV_PI/180);
		cvLine(img,cvPoint(x1,y1),cvPoint(x2,y2),CV_RGB(255,255,255),int(pow(iter-IterNum,1.0/1.5)));
		drawLine(img,x2,y2,alpha,len,constLength,iter,IterNum);

		len = myRand(constLength-(IterNum-1)*koef,constLength-(IterNum)*koef);
		alpha = myRand(angle-22,angle+22);
		x3 = x1+len*cos(alpha*CV_PI/180);
		y3 = y1+len*sin(alpha*CV_PI/180);
		cvLine(img,cvPoint(x1,y1),cvPoint(x3,y3),CV_RGB(255,255,255),int(pow(iter-IterNum,1.0/1.5)));
		drawLine(img,x3,y3,alpha,len,constLength,iter,IterNum);

	}
}

void drawVoronoi(IplImage *src,Vertices *ver, Vertices *dir)
{
	cvSetZero(src);
	edg = v->GetEdges(ver,w,w);

	for(Vertices::iterator i = ver->begin(); i != ver->end(); i++)
		cvCircle(src,cvPoint((*i)->x,(*i)->y),2,CV_RGB(255,255,255),2);

	for(Edges::iterator i = edg->begin(); i != edg->end(); i++)
		cvLine(src,cvPoint((*i)->start->x,(*i)->start->y),cvPoint((*i)->end->x,(*i)->end->y),CV_RGB(255,255,255));

}

void MouseClick( int event, int x, int y, int flags, void* param )
{
	int iter=6;
	int length=25;
        IplImage* img = (IplImage*) param;
        switch( event ){
                case CV_EVENT_MOUSEMOVE: 
                        break;

                case CV_EVENT_LBUTTONDOWN:
						drawPoint(img, x, y);
						for(int i=0; i<16; i++)
							drawLine(img,x,y,22.5*i,length,length,iter,0);

                        break;

                case CV_EVENT_LBUTTONUP:
                        break;

				case CV_EVENT_RBUTTONDOWN:
						ver->push_back(new VPoint(x, y));
						dir->push_back(new VPoint((double)rand()/(double)RAND_MAX-0.5,(double)rand()/(double)RAND_MAX-0.5));
						drawVoronoi(img, ver, dir);

						break;
        }
}

int main(int argc, char** argv)
{
	IplImage *img;
	img = cvLoadImage("img.jpg");
	cvSetZero(img);
	v = new Voronoi();
	ver = new Vertices();
	dir = new Vertices();

	cvNamedWindow("My_Project",CV_WINDOW_AUTOSIZE);
	cvSetMouseCallback( "My_Project",MouseClick,(void*) img);

	while(1)
	{
		cvShowImage( "My_Project", img );
		char c = cvWaitKey(33);
		if (c == 27)												// если нажата ESC - выходим
				break;
	}
	system("pause");
}

