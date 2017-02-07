#include "../lib/light.hh"

Light::Light(std::string init_name,double init_pos[], double init_dir[], std::string newpath) {
	name = init_name;
	for (int i = 0; i < 3; i++)
		pos.push_back(init_pos[i]);
	for (int i = 0; i < 3; i++)
		dir.push_back(init_dir[i]);
	path = newpath;
}

std::string Light::get_name(void) {
	return name;
}

std::string Light::load(void) {
	std::ifstream ifs(path.c_str());
	std::stringstream buffer;
	buffer << ifs.rdbuf();
	std::string parser = buffer.str();
	std::vector<std::string> list;
	list.push_back(name);
	parser = replace('$', list, parser);
	parser = replace('@', pos, parser);
	parser = replace('#', dir, parser);
	return parser; 
}