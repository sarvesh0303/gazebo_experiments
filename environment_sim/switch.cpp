//Plugin Template

#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/math/gzmath.hh>
#include <iostream>
#include <string>
#include <fstream>

namespace gazebo {
	class Switch : public WorldPlugin {
		public: void Load(physics::WorldPtr _parent, sdf::ElementPtr _sdf) {
				this->world = _parent;
				l_green = world->Light("l_green");
				l_red = world->Light("l_red");
				flag = 0;
				//Update call
				this->updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&Switch::OnUpdate,this,_1));
		}

		public: void	OnUpdate(const common::UpdateInfo& _info) {
				double t = this->world->GetSimTime().Double();
				if (t > 5 && flag==0) {
					flag = 1;
					l_red->SetRelativePose(math::Pose(0,0,10,0,0,0));
				}
				if (t > 10 && flag==1) {
					flag = 2;
					l_red->SetRelativePose(math::Pose(0,0,0.5,0,0,0));
					l_green->SetRelativePose(math::Pose(0,0,10,0,0,0));
				}
		}

		private: int flag;
		private: physics::LightPtr l_green;
		private: physics::LightPtr l_red;
		private: physics::WorldPtr world;
		private: event::ConnectionPtr updateConnection;
};
	GZ_REGISTER_WORLD_PLUGIN(Switch)
}
