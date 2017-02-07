#include "../lib/environ.hh"

Environ::Environ(void) {
	signalpath = "templates/signal.sdf";
	roadpath = "templates/road.sdf";
	greenpath = "templates/green.sdf";
	redpath = "templates/red.sdf";
	roads = new Road(roadpath);
}

void Environ::insert_road(double x, double y) {
	roads->create(x,y);
}

void Environ::remove_road(double x, double y) {
	roads->remove(x,y);
}

void Environ::insert_signal(std::string name, double x, double y) {
	double pos2[] = {x,y};
	sig_list.push_back(Signal(name,pos2,redpath,greenpath,signalpath));
}

Signal* Environ::access_signal(std::string findname) {
	for (int i = 0; i < sig_list.size(); i++) {
		if (sig_list[i].name == findname)
			return &(sig_list[i]);
	}
	return NULL;
}

void Environ::load(gazebo::physics::WorldPtr world) {
	std::vector<std::string> addsdf = roads->load();
	std::vector<std::string> sigsdf;
	for (int i = 0; i < sig_list.size(); i++) {
		sigsdf = sig_list[i].load();
		addsdf.insert(addsdf.end(),sigsdf.begin(),sigsdf.end());
	}
	for (int i = 0; i < addsdf.size(); i++) {
		world->InsertModelString(addsdf[i]);
	}
}

void Environ::update(double t, gazebo::physics::WorldPtr world) {
	for (int i = 0; i < sig_list.size(); i++) {
		sig_list[i].update(t,world);
	}	
}