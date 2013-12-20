#ifndef ktrack
#define ktrack 

#include "opencv2/opencv.hpp"
#include <math.h>
#include <ctime>
#include <iostream>

using namespace cv;
//using namespace std;
//void zain(Mat);
void setCenter(int,int);
struct rectval{
	int height;
	int width;
	int x;
	int y;
	double time;
};

static struct prevpara{

	int x;
	int y;
	double time;
	
}pp;
RECT getWindow();
rectval sens();
double distance();
void prevpara(int,int,double tim=0);
Point frame_center();
bool convert(Point);
void sendEvent(int);
void recogreturn();
void lclick();
void dblclick();

#endif