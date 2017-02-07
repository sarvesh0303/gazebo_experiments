//Plugin Template

#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/math/gzmath.hh>
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

namespace gazebo {


double max(double a, double b) {
	return (a>b)?a:b;
}

double min(double a, double b) {
	return (a<b)?a:b;
}

void Print_Vec(math::Vector3 vect) {
	std::cout << vect.x<<", "<<vect.y<<", "<<vect.z<<"\n";
}

class Push : public ModelPlugin {
	public: void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf) {

		//Getting model pointer
		this->model = _parent;
		
		//Getting links
		body = this->model->GetLink("link_0");
		lb_wheel = this->model->GetLink("link_1_clone_clone");
		rb_wheel = this->model->GetLink("link_1_clone_clone_0");
		lf_wheel = this->model->GetLink("link_1_clone");
		rf_wheel = this->model->GetLink("link_1");
		
		//Getting joints	
		lb_drive = this->model->GetJoint("lb_drive");
		rf_drive = this->model->GetJoint("rf_drive");
		lf_drive = this->model->GetJoint("lf_drive");
		rb_drive = this->model->GetJoint("rb_drive");
		lf_steer = this->model->GetJoint("lf_steer");
		rf_steer = this->model->GetJoint("rf_steer");
		
		//Initializing Joint Controller
		this->j_con = this->model->GetJointController();
		
		//Joint Pointer Vectors -> Drive and Steer
		std::vector<physics::JointPtr> j_drive;
		std::vector<physics::JointPtr> j_steer;

		j_drive.push_back(lb_drive);
		j_drive.push_back(rb_drive);
		j_drive.push_back(rf_drive);
		j_drive.push_back(lf_drive);

		j_steer.push_back(lf_steer);
		j_steer.push_back(rf_steer);

		//Initializing PID Controllers
		this->pidrive = common::PID(10000,0,0);
		this->pisteer1 = common::PID(10000,0,0);
		this->pisteer2 = common::PID(10000,0,0);

		//Assigning PID controllers to Joints
		for (int i = 0 ; i < j_drive.size(); i++) {
			j_con->SetPositionPID(j_drive[i]->GetScopedName(),pidrive);
		}
		j_con->SetPositionPID(lf_steer->GetScopedName(),pisteer1);
		j_con->SetPositionPID(rf_steer->GetScopedName(),pisteer2);
		
		//A couple of state flags, for future use	
		flag = 0;
		state = 0;
		
		radius = 20*(lb_wheel->GetWorldCoGPose().pos.x);

		//Getting front wheels' parameters for ackermann
		lfd = math::Vector3(-radius*.95,0,0);
		lfd = (lf_wheel->GetWorldCoGPose().pos - lb_wheel->GetWorldCoGPose().pos)+lfd;
		rfd = math::Vector3(-radius*1.05,0,0);
		rfd = (rf_wheel->GetWorldCoGPose().pos - rb_wheel->GetWorldCoGPose().pos)+rfd;


		//Radius Setting with test output		
		std::cout << "Radius of trajectory is "<<radius<<std::endl;
		//Update Call
		this->updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&Push::OnUpdate,this,_1));


	}

	public: void  OnUpdate(const common::UpdateInfo& _info) {
		//Getting Time 
		common::Time T_curr = this->model->GetWorld()->GetSimTime();
		double t = T_curr.Double();

		//driver value for wheels
		double driver = 3*max(0,t-1);

		//Control of rear wheels' drive
		j_con->SetPositionTarget(rb_drive->GetScopedName(), 1.05*driver);
		j_con->SetPositionTarget(lb_drive->GetScopedName(), 0.95*driver);

		//Control of front wheels' drive
		std::cout << lfd.GetLength() << " | "<< rfd.GetLength()<<std::endl;
		j_con->SetPositionTarget(lf_drive->GetScopedName(), driver*lfd.GetLength()/-radius);
		j_con->SetPositionTarget(rf_drive->GetScopedName(), driver*rfd.GetLength()/-radius);

		//Getting steering angles
		double l_angle = lf_steer->GetAngle(0).Radian();
		double r_angle = rf_steer->GetAngle(0).Radian();

		//Left Ackermann Check
		math::Vector3 v1(radius,lb_wheel->GetWorldCoGPose().pos.y,lb_wheel->GetWorldCoGPose().pos.z);
		v1 = lf_wheel->GetWorldCoGPose().pos - v1;
		math::Vector3 v2(-sin(l_angle),cos(l_angle),0);
		if ((1000*std::abs(v1.Normalize().Dot(v2)) < 1) && (flag == 0)) {
			final_l = l_angle;
			std::cout << "final_l is "<<final_l<<std::endl;
			flag = 1;
			Print_Vec(v1.Normalize());
			Print_Vec(v2);
			std::cout << std::abs(v1.Normalize().Dot(v2)) << std::endl;
		}
		

		//Right Ackermann Check
		math::Vector3 v3(radius, rb_wheel->GetWorldCoGPose().pos.y, rb_wheel->GetWorldCoGPose().pos.z);
		v3 = rf_wheel->GetWorldCoGPose().pos - v3;
		math::Vector3 v4(-sin(r_angle),cos(r_angle),0);
		if ((1000*std::abs(v3.Normalize().Dot(v4)) < 1) && (state == 0)) {
			final_r = r_angle;
			std::cout << "final_r is "<<final_r<<std::endl;
			state = 1;
			Print_Vec(v3.Normalize());
			Print_Vec(v4);
			std::cout << std::abs(v3.Normalize().Dot(v4)) << std::endl;
		}

		//Steer Updates wrt Ackermann
		if (flag == 0)
			j_con->SetPositionTarget(lf_steer->GetScopedName(), t);
		else
			j_con->SetPositionTarget(lf_steer->GetScopedName(), final_l);

		if (state == 0)
			j_con->SetPositionTarget(rf_steer->GetScopedName(), t);
		else
			j_con->SetPositionTarget(rf_steer->GetScopedName(), final_r);

		//Debugging print statement
		if (t > 1)
			std::cout << final_l << " | "<<final_r<<" | "<<l_angle<<" | "<<r_angle<<"\n";

	
	}

	public: math::Vector3 lfd,rfd;
	public: double radius, final_l, final_r;
	private: int flag;
	private: int state;
	private: double max_y;
	private: double min_y;
	private: common::PID pisteer1;
	private: common::PID pisteer2;
	private: common::PID pidrive;
	private: common::Time T_prev;
	private: physics::LinkPtr body, lb_wheel, rb_wheel, lf_wheel, rf_wheel;
	private: physics::JointControllerPtr j_con;
	private: physics::JointPtr lb_drive,rb_drive,lf_drive,rf_drive,lf_steer,rf_steer;
	private: physics::ModelPtr model;
	private: event::ConnectionPtr updateConnection;
};
	GZ_REGISTER_MODEL_PLUGIN(Push)
}

