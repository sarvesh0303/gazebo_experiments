#ifndef LIGHT_H
#define LIGHT_H
#include "common.hh"
#include "helper.hh"

class Light {
private:
	std::string path;
	std::vector<double> pos;
	std::vector<double> dir;
	std::string name;
public:
	Light(std::string init_name, double init_pos[], double init_dir[], std::string mewpath);
	std::string get_name(void);
	std::string load(void);
};

#endif