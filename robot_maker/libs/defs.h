enum JOINT {FIXED=0,REVOLUTE=1}

class URDF_String {

private:
	std::vector<std::string> adder;

public:
	URDF_String(std::string model_name);
	void add_box(std::string name, double mass, double pos[], double dim[]);
	void add_sphere(std::string name, double mass, double pos[], double rad);
	void create_joint(std::string parent_link, std::string child_link,JOINT j,double pos[]);
	void load();

}