#ifndef POINT_H
#define POINT_H
#include "common.hh"


class Point {
public:
	//Members
	double x;
	double y;
	//Functions
	Point(double a, double b);
	void print(void);
	bool equals(Point p);
};

#endif