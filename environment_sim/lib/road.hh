#ifndef ROAD_H
#define ROAD_H
#include "common.hh"
#include "helper.hh"
#include "point.hh"

class Road {
	private:
		std::vector<Point> list;
		std::string path;
	public:
		Road(std::string init);
		void create(double a, double b);
		std::vector<std::string> load(void);
		void remove(double a, double b);
		std::vector<Point> get_list(void);
		void set_list(std::vector<Point> newlist);
		std::string get_path(void);
		void set_path(std::string);
};


#endif
