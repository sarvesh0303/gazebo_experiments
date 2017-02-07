#include "../lib/signal.hh"

Signal::Signal(std::string newname, double newpos[], std::string rpath, std::string gpath, std::string spath) {
	name = newname;
	for (int i = 0; i < 3; i++)
		pos.push_back(newpos[i]);
	double a1[] = {pos[0]+2,pos[1],1.4};
	double a2[] = {pos[0],pos[1]+2,1.4};
	double a3[] = {pos[0]-2,pos[1],1.4};
	double a4[] = {pos[0],pos[1]-2,1.4};
	double d1[] = {-1,0,0};
	double d2[] = {0,-1,0};
	double d3[] = {1,0,0};
	double d4[] = {0,1,0};
	cart[0] = new LightPair(name+"_xp",a1,d1,rpath,gpath);
	cart[1] = new LightPair(name+"_yp",a2,d2,rpath,gpath);
	cart[2] = new LightPair(name+"_xn",a3,d3,rpath,gpath);
	cart[3] = new LightPair(name+"_yn",a4,d4,rpath,gpath);
	path = spath;
}

void Signal::set_script(int a, bool (*script)(double)) {
	cart[a-1]->set_script(script);
}

std::vector<std::string> Signal::load(void) {
	std::vector<std::string> ans;
	std::ifstream ifs(path.c_str());
	std::stringstream buffer;
	buffer << ifs.rdbuf();
	std::string parser = replace('@',pos,buffer.str());
	ans.push_back(parser);
	std::vector<std::string> v[4];
	for (int i = 0; i < 4; i++)
		v[i] = cart[i]->load();
	for (int i = 0; i < 4; i++)
		ans.insert(ans.end(),v[i].begin(),v[i].end());
	return ans;
}

void Signal::update(double t, gazebo::physics::WorldPtr world) {
	for (int i = 0; i < 4; i++) {
		cart[i]->update(t,world);
	}
}