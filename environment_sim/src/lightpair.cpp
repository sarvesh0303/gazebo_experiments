#include "lightpair.hh"

LightPair::LightPair(std::string newname, double newpos[], double newdir[], std::string rpath, std::string gpath) {
	lpair[0] = new Light(newname+"_red",newpos,newdir,rpath);
	lpair[1] = new Light(newname+"_green",newpos,newdir,gpath);
	for (int i = 0; i < 3; i++)
		pos.push_back(newpos[i]);
	for (int i = 0; i < 3; i++)
		dir.push_back(newdir[i]);
	script = NULL;
}

std::vector<std::string> LightPair::load(void) {
	std::vector<std::string> ans;
	ans.push_back(lpair[0]->load());
	ans.push_back(lpair[1]->load());
	return ans;
}

void LightPair::set_script(bool (*newscript)(double)) {
	script = newscript;
}

void LightPair::update(double t, gazebo::physics::WorldPtr world) {
	if (script(t)) {
		world->Light(lpair[0]->get_name())->SetRelativePose(gazebo::math::Pose(pos[0],pos[1],10,0,0,0));
		world->Light(lpair[1]->get_name())->SetRelativePose(gazebo::math::Pose(pos[0],pos[1],pos[2],0,0,0));
	}
	else {
		world->Light(lpair[0]->get_name())->SetRelativePose(gazebo::math::Pose(pos[0],pos[1],pos[2],0,0,0));
		world->Light(lpair[1]->get_name())->SetRelativePose(gazebo::math::Pose(pos[0],pos[1],10,0,0,0));
	}
}