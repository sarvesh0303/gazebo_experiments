#include "../lib/point.hh"

Point::Point(double a, double b) {
	this->x = a;
	this->y = b;
}

void Point::print(void) {
	std::cout << "( "<<this->x<<" , "<<this->y<<" )\n";
}

bool Point::equals(Point c) {
	return ((abs(this->x - c.x)<0.001) && (abs(this->y - c.y)<0.001))? true:false;
}