#ifndef ENVIRON_H
#define ENVIRON_H

#include "common.hh"
#include "signal.hh"
#include "road.hh"

class Environ {
public:
	std::string roadpath;
	std::string signalpath;
	std::string greenpath;
	std::string redpath;
	Road *roads;
	std::vector<Signal> sig_list;

	Environ(void);
	void insert_road(double x, double y);
	void remove_road(double x, double y);
	void insert_signal(std::string name,double x, double y);
	Signal* access_signal(std::string findname);
	void makescript(void);
	void load(gazebo::physics::WorldPtr world);
	void update(double t, gazebo::physics::WorldPtr world);
};


#endif