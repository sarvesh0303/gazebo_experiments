#include <sstream>
#include <fstream>
#include <string>
#include <cmath>

template <class T> std::string replace(char d, std::vector<T> list, std::string red) {
	int flag = 0;
	char c;
	std::stringstream buffer;
	for (int i = 0; i < red.size(); i++) {
		c = red[i];
		if (c=='#')
			i++;
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

template <class T> std::vector vec_from_arr(T arr[], int size) {
	return std::vector<T>(arr,arr+size);
}

template <class T> std::vector vec_from_single(T arr) {
	std::vector<T> v; v.push_back(arr); return v;
}

std::string load_input(std::string path) {
	std::ifstream ifs(path.c_str());
	std::stringstream buffer;
	buffer << ifs.rdbuf();
	return buffer.str();
}