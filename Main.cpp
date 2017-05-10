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
double width = 1500;
#define PI 3.14159265 

int myRand(int a, int b)
{
    return (rand() % (b - a) + a);
}

void InitXY(int *X, int *Y) {
    X[0] = 281; Y[0] = 327;
    X[1] = 41; Y[1] = 467;
    X[2] = 142; Y[2] = 200;
    X[3] = 478; Y[3] = 358;
    X[4] = 495; Y[4] = 442;
    X[5] = 135; Y[5] = 411;
    X[6] = 246; Y[6] = 155;
    X[7] = 291; Y[7] = 65;
    X[8] = 128; Y[8] = 321;
    X[9] = 350; Y[9] = 256;
    X[10] = 40; Y[10] = 60;
    X[11] = 462; Y[11] = 48;
}

void Compare(int &left, int &right, int num1, int num2) {
    if (num1 < num2) {
        left = num1;
        right = num2;
    }
    else {
        left = num2;
        right = num1;
    }
}

bool PixelCheck(Mat img, int x1, int y1, int x2, int y2) {
    double k, b;
    int leftX, rightX;
    int leftY, rightY;
    int y;
    Compare(leftX, rightX, x1, x2);
    Compare(leftY, rightY, y1, y2);

    k = (double)(y1 - y2) / (double)(x1 - x2);
    b = y1 - k*x1;

    for (int x = leftX; x <= rightX; x++) {
        y = k*x + b;
        if (x >= width || x <= 0 || y >= width || y <= 0 || img.at<Vec3b>(y, x).val[0] == 255)
            return false;
    }
    for (int y = leftY; y <= rightY; y++) {
        if (x2 >= width || x2 <= 0 || y >= width || y <= 0 || img.at<Vec3b>(y, x2).val[0] == 255)
            return false;
    }

    return true;

}

void drawLine(Mat img, int x, int y, int angle, int length, int IterNum)
{
    int x1 = x, y1 = y;
    int x2 = 0, y2 = 0;
    int x3 = 0, y3 = 0;
    int rd = 0;
    double alpha, alpha2;
    int len = length, len2 = length;;
    int wid = 3;
    alpha = myRand(angle - 22, angle + 22);
    alpha2 = myRand(angle - 22, angle + 22);

    x2 = x1 + len*cos(alpha*CV_PI / 180);
    y2 = y1 + len*sin(alpha*CV_PI / 180);

    x3 = x1 + len*cos(alpha2*CV_PI / 180);
    y3 = y1 + len*sin(alpha2*CV_PI / 180);

    if (PixelCheck(img, x1, y1, x2, y2) && PixelCheck(img, x1, y1, x3, y3) && IterNum < 20)
    {
        if (IterNum > 3)
            wid = 2;
        if (IterNum > 6)
            wid = 1;
        rd = rand() % 5;
        if (rd == 0) {
            IterNum++;
            line(img, cvPoint(x1, y1), cvPoint(x2, y2), CV_RGB(250, 250, 250), wid);
            len++;
            drawLine(img, x2, y2, alpha, len, IterNum);
        }
        else {
            IterNum++;
            line(img, cvPoint(x1, y1), cvPoint(x2, y2), CV_RGB(250, 250, 250), wid);
            len++;
            drawLine(img, x2, y2, alpha, len, IterNum);
            len2++;
            line(img, cvPoint(x1, y1), cvPoint(x3, y3), CV_RGB(250, 250, 250), wid);
            drawLine(img, x3, y3, alpha2, len2, IterNum);

        }
    }

}

void drawVoronoi(Mat src, Vertices *ver, Vertices *dir)
{
    edg = v->GetEdges(ver, width, width);

    for (Vertices::iterator i = ver->begin(); i != ver->end(); i++)
        circle(src, cvPoint((*i)->x, (*i)->y), 2, CV_RGB(254, 254, 254), 10);

    for (Edges::iterator i = edg->begin(); i != edg->end(); i++)
        line(src, cvPoint((*i)->start->x, (*i)->start->y), cvPoint((*i)->end->x, (*i)->end->y), CV_RGB(255, 255, 255), 10);
}

int main(int argc, char** argv)
{
    Mat img = Mat::zeros(1500, 1500, CV_8UC3);
    v = new Voronoi();
    ver = new Vertices();
    dir = new Vertices();

    int x, y;
    int length = 33;
    int *X = new int[12];
    int *Y = new int[12];

    InitXY(X, Y);
    for (int i = 0; i < 12; i++) {
        x = 3*X[i];
        y = 3*Y[i];
        ver->push_back(new VPoint(x, y));
        dir->push_back(new VPoint((double)x / (double)RAND_MAX - 0.5, (double)y / (double)RAND_MAX - 0.5));
    }
    drawVoronoi(img, ver, dir);

    for (Vertices::iterator j = ver->begin(); j != ver->end(); j++)
        for (int i = 1; i < 360; i += 45)
            drawLine(img, (*j)->x, (*j)->y, i, length, 0);

    resize(img, img, cvSize(500, 500), 0, 0, 3);
    imshow("Astrocytes", img);
    waitKey(0);
}
