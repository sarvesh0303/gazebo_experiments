#ifndef LIGHTPAIR_H
#define LIGHTPAIR_H

#include "common.hh"
#include "gz_req.hh"
#include "light.hh"

class LightPair {
public:
	Light* lpair[2];
	std::string name;
	std::vector<double> pos;
	std::vector<double> dir;
	bool (*script)(double);

	LightPair(std::string,double newpos[], double newdir[], std::string rpath, std::string gpath);
	void set_script(bool (*script)(double));
	std::vector<std::string> load(void);
	void update(double t, gazebo::physics::WorldPtr world);

};



#endif