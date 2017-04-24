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
#define PI 3.14159265 

int myRand(int a, int b)
{
	return (rand() % (b - a) + a);
}

void CompareX(int &left, int &right, int x1, int x2){
	if(x1<x2){
			left=x1;
			right=x2;
		}
		else{
			left=x2;
			right=x1;
		}
}

void CompareY(int &left, int &right, int y1, int y2){
	if(y1<=y2){
			left=y1;
			right=y2;
		}
		else
		{
			left=y2;
			right=y1;
		}
}


bool PixelCheck(Mat img,int x1, int y1, int x2, int y2){
	double k,b;				//y=kx+b
	int leftX,rightX;
	int leftY,rightY;
	int y;
	if(x1!=x2){
		CompareX(leftX,rightX,x1,x2);
		k=(double)(y1-y2)/(double)(rightX-leftX);
		b=y1-k*x1;
		for(int x=leftX; x<=rightX; x++){
			y=k*x+b;
			if(x>=500 || x<=0 || y>=500 || y<=0 || img.at<Vec3b>(y,x).val[0]==255)
				return false;
		}
	}
	else
		CompareY(leftY,rightY,y1,y2);
		for(int y=y1; y<=y2; y++){
			if(x1>=500 || x1<=0 || y>=500 || y<=0 || img.at<Vec3b>(y,x1).val[0]==255)
				return false;
		}
	return true;

}

void drawLine(Mat img, int x, int y, int angle,int length,int constLength,int iter, int IterNum)
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
		line(img,cvPoint(x1,y1),cvPoint(x2,y2),CV_RGB(255,255,255),int(pow(iter-IterNum,1.0/1.5)));
		drawLine(img,x2,y2,alpha,len,constLength,iter,IterNum);

	}
	else
	{
		IterNum++;
		len = myRand(constLength-(IterNum-1)*koef,constLength-(IterNum)*koef);
		alpha = myRand(angle-22,angle+22);
		x2 = x1+len*cos(alpha*CV_PI/180);
		y2 = y1+len*sin(alpha*CV_PI/180);
		line(img,cvPoint(x1,y1),cvPoint(x2,y2),CV_RGB(255,255,255),int(pow(iter-IterNum,1.0/1.5)));
		drawLine(img,x2,y2,alpha,len,constLength,iter,IterNum);

		len = myRand(constLength-(IterNum-1)*koef,constLength-(IterNum)*koef);
		alpha = myRand(angle-22,angle+22);
		x3 = x1+len*cos(alpha*CV_PI/180);
		y3 = y1+len*sin(alpha*CV_PI/180);
		line(img,cvPoint(x1,y1),cvPoint(x3,y3),CV_RGB(255,255,255),int(pow(iter-IterNum,1.0/1.5)));
		drawLine(img,x3,y3,alpha,len,constLength,iter,IterNum);

	}
}

void drawLine2(Mat img, int x, int y, int angle,int length, int IterNum)
{
	int x1 = x, y1 = y;
	int x2 = 0, y2 = 0;
	int x3 = 0, y3 = 0;
	int rd=0;
	double alpha, alpha2;
	int len = length;

	alpha = myRand(angle-22,angle+22);
	alpha2 = myRand(angle-22,angle+22);
	
	x2 = x1+len*cos(alpha*CV_PI/180);
	y2 = y1+len*sin(alpha*CV_PI/180);

	x3 = x1+len*cos(alpha2*CV_PI/180);
	y3 = y1+len*sin(alpha2*CV_PI/180);

	if(PixelCheck(img,x1,y1,x2,y2))
	{
		rd = rand()%5;
		if(rd==8){
			IterNum++;
			line(img,cvPoint(x1,y1),cvPoint(x2,y2),CV_RGB(200,200,200),1);
			alpha = myRand(angle-22,angle+22);
			drawLine2(img,x2,y2,alpha,len,IterNum);
		}
		else{
			IterNum++;
			line(img,cvPoint(x1,y1),cvPoint(x2,y2),CV_RGB(200,200,200),1);
			alpha = myRand(angle-22,angle+22);
			drawLine2(img,x2,y2,alpha,len,IterNum);

			line(img,cvPoint(x1,y1),cvPoint(x3,y3),CV_RGB(200,200,200),1);
			alpha2 = myRand(angle-22,angle+22);
			//drawLine2(img,x3,y3,alpha2,len,IterNum);
			
		}
	}

}

void drawVoronoi(Mat src,Vertices *ver, Vertices *dir)
{
	edg = v->GetEdges(ver,w,w);

	for(Vertices::iterator i = ver->begin(); i != ver->end(); i++)
		circle(src,cvPoint((*i)->x,(*i)->y),2,CV_RGB(254,254,254),2);

	for(Edges::iterator i = edg->begin(); i != edg->end(); i++)
		line(src,cvPoint((*i)->start->x,(*i)->start->y),cvPoint((*i)->end->x,(*i)->end->y),CV_RGB(255,255,255),2);
}

int main(int argc, char** argv)
{
	Mat img;
	img = imread("img.jpg");
	v = new Voronoi();
	ver = new Vertices();
	dir = new Vertices();
	
	int x,y;
	int length = 15;
	for(int i=0; i<10; i++){
		x= myRand(0,500);
		y= myRand(0,500);
		ver->push_back(new VPoint(x, y));
		dir->push_back(new VPoint((double)x/(double)RAND_MAX-0.5,(double)y/(double)RAND_MAX-0.5));
	}

	drawVoronoi(img, ver, dir);
	x=281 , y=327;
	//for(Vertices::iterator j = ver->begin(); j != ver->end(); j++)
	//	for(int i=1; i<360; i+=45)
	//		drawLine2(img,(*j)->x,(*j)->y,i,length,0);

	for(int i=0; i<360; i+=45)
		drawLine2(img,x,y,i,length,0);

	imshow("Astrocytes",img);
	waitKey(0); 
}


/*

41 467		++
334 0		--
169 224		++
478 358		++
462 464		+-
205 145		+-
281 327		++
461 491		+-
495 442		++
327 436		+-

*/