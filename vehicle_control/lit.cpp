//Plugin Template

#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/math/gzmath.hh>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace gazebo {
	class Lit : public WorldPlugin {
		public: void Load(physics::WorldPtr _parent, sdf::ElementPtr _sdf) {
			this->world = _parent;
			double xt,yt,t;
			std::stringstream acc;
			for (int i = 0; i < 25; i++) {
				acc.str("light");
				t = 0.25*i;
				xt = 9*(cos(t)-1);
				yt = 9*sin(t)-0.35;
				acc << i;
				InsertLight(acc.str(),xt,yt);
			}


			this->updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&Lit::OnUpdate,this,_1));
		}

		public: void  OnUpdate(const common::UpdateInfo& _info) {
			;
		}

		public: void InsertLight(std::string name, double x, double y) {
			ifs = new std::ifstream("light.sdf");
			char c;
			int flag = 0;
			std::stringstream buffer;
			while (ifs->get(c)) {
				if (c=='$')
					buffer << name;
				else {
				if (c=='@' && flag == 0) {
					buffer << x;
					flag = 1;
				}
				else if (c=='@' && flag == 1) {
					buffer << y;
					flag = 2;
				}
				else
					buffer << c;
				} 
			}
			ifs->close();
			delete ifs;
			world->InsertModelString(buffer.str());
		}

		private: std::ifstream* ifs;
		private: physics::WorldPtr world;
		private: event::ConnectionPtr updateConnection;
};
	GZ_REGISTER_WORLD_PLUGIN(Lit)
}
