//Plugin Template

#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/math/gzmath.hh>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "lib/road.hh"
#include "lib/environ.hh"

namespace gazebo {
	class Insert : public WorldPlugin {
		public: void Load(physics::WorldPtr _parent, sdf::ElementPtr _sdf) {
				this->world = _parent;

				env = Environ();
				env.makescript();

				env.load(world);

				//Update call
				this->updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&Insert::OnUpdate,this,_1));
		}

		public: void  OnUpdate(const common::UpdateInfo& _info) {
			/*
			Update Code
			*/
			double t = world->GetSimTime().Double();

			env.update(t,world);


		}



		public: Environ env;
		private: physics::WorldPtr world;
		private: event::ConnectionPtr updateConnection;
	};
	GZ_REGISTER_WORLD_PLUGIN(Insert)
}
