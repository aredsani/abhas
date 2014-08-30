#include <iostream>
#include <math.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#ifndef _MAYAnk_
#define _MAYAnk_


using namespace std;
using namespace cv;

float dist(Point p1, Point p2);
float ang(Point p1, Point p2, Point p3);
void *gestureREC(void * argument);

#endif
