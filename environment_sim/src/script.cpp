#include "../lib/environ.hh"
	
bool scr(double t) {
	if ((int)t % 2 ==0)
		return true;
	return false;
}

bool alt(double t) {
	return !scr(t);
}

void Environ::makescript(void) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			insert_road(i,j);
	}
	insert_signal("first",2,3);
	for (int i = 1; i < 5; i+=2)
		access_signal("first")->set_script(i,&scr);
	for (int i = 2; i < 5; i+=2)
		access_signal("first")->set_script(i,&alt);
}
