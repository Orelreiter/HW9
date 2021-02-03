#include <cstdlib>
#include "port.h"

Port::Port(String pattern) : Field(pattern,PORT) {
	range[0] = 0;
	range [1] = 0;
}
// This function basically splits the port's range into max and min while checking correct variables.
bool Port::set_value(String val) {
	size_t size = 0;
	String *arr_of_str = NULL;
	val.split("-",&arr_of_str,&size);
	if (size == 0) {
		delete[] arr_of_str;
		return false;
	}
	if ((range[0] < 0 || range[1] < 0) || (range[0] > range[1])) {
		delete[] arr_of_str;
		return false;
	}
	if (range[0] > range[1]) {
		delete[] arr_of_str;
		return false;
	}
	range[0] = arr_of_str[0].trim().to_integer();
	range[1] = arr_of_str[1].trim().to_integer();
	delete[] arr_of_str;
	return true;
}

bool Port::match_value(String val) const {
	int port = val.trim().to_integer();
	if ((port >= range[0]) && (port <= range[1]))
		return true;
	return false;
}
