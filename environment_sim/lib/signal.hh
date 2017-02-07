#include "common.hh"
#include "lightpair.hh"
#include "helper.hh"

class Signal {
public:
	LightPair* cart[4];
	std::string name;
	std::vector<double> pos;
	std::string path;


	Signal(std::string, double newpos[], std::string rpath, std::string gpath, std::string spath);
	void set_script(int a, bool(*script)(double));
	std::vector<std::string> load(void);
	void update(double t, gazebo::physics::WorldPtr world);


};