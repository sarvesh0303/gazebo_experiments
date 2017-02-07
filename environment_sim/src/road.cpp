#include "../lib/road.hh"


void refine(double& a) {
  a = (a > 0) ? (a-0.5):(a+0.5);
}


Road::Road(std::string init) {
	this->path = init;
  	this->list = std::vector<Point>();
}

void Road::create(double a, double b) {
  	refine(a);
 	refine(b);
  	Point p(a,b);
 	list.push_back(p);
}

void Road::remove(double a, double b) {
	refine(a);
	refine(b);
  	Point compare(a,b);
  	for (int i = 0; i < list.size(); i++) {
	if (list[i].equals(compare))
	  list.erase(list.begin()+i);
  	}
}

std::vector<Point> Road::get_list(void) {
	return list;
}

void Road::set_list(std::vector<Point> newlist) {
	list = newlist;
}

std::string Road::get_path(void) {
	return path;
}

void Road::set_path(std::string newpath) {
	path = newpath;
}

std::vector<std::string> Road::load(void) {
	std::vector<std::string> answer;
	std::ifstream ifs(path.c_str());
	std::stringstream commonbuf;
	std::string parser;
	commonbuf << ifs.rdbuf();
	for (int i = 0; i < list.size(); i++) {
		double three[] = {list[i].x,list[i].y,0};
		std::vector<double> v(three,three+3);
		parser = replace('@',v,commonbuf.str());
		answer.push_back(parser);
	}
	return answer;
}


/*std::string create_road(double x, double y, double z) {
  refine(x);
  refine(y);
  std::ifstream ifs("templates/signal.sdf");
  std::stringstream buffer;
  char c;
  int flag = 0;
  int iter = 0;
  while (ifs.get(c)) {
	iter++;
	if (c=='@') {
	  switch(flag) {
	  case 0:
		   buffer<<x;
		   flag++;
		   break;
	  case 1:
		   buffer<<y;
		   flag++;
		   break;
	  default:
		   buffer<<z;
		 flag++;
		   break;
	  }
	}
	else
	  buffer << c;
  }
  return buffer.str();
}

*/