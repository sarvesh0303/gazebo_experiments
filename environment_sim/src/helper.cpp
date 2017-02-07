#include "../lib/helper.hh"

std::string replace(char d, std::vector<double> list, std::string red) {
	int flag = 0;
	char c;
	std::stringstream buffer;
	for (int i = 0; i < red.size(); i++) {
		c = red[i];
		if (c==d) {
			if (flag < list.size())
				buffer << list[flag++];
			else {
				buffer << c;
				std::cout<<"Warning: Something seems to have exceeded\n Additional placeholder left as is\n"; 
			}
		}
		else 
			buffer << c;
	}
	return buffer.str();}

std::string replace(char d, std::vector<std::string> list, std::string red) {
	int flag = 0;
	char c;
	std::stringstream buffer;
	for (int i = 0; i < red.size(); i++) {
		c = red[i];
		if (c==d) {
			if (flag < list.size())
				buffer << list[flag++];
			else {
				buffer << c;
				std::cout<<"Warning: Something seems to have exceeded\n Additional placeholder left as is\n"; 
			}
		}
		else 
			buffer << c;
	}
	return buffer.str();
}
