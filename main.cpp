#include <iostream>
#include <cstring>
#include "input.h"
#include "port.h"
#include "ip.h"

/* In the main function we should split each rule into it's type
	and it's data. It also takes care of port and IP related rules */
int main(int argc, char** argv)
{
	if (check_args(argc,argv))
		return 1;
	String main_str = String(argv[1]);
	String *sub_str = NULL;
	size_t length = 0;
	main_str.split("=",&sub_str,&length);
	if ((sub_str[0].trim().equals("dst-port")) ||
		(sub_str[0].trim().equals("src-port"))) {
		Port main_port = Port (sub_str[0].trim());
		main_port.set_value(sub_str[1].trim());
		parse_input (main_port);

	}
	if ((sub_str[0].trim().equals("dst-ip")) ||
		(sub_str[0].trim().equals("src-ip"))) {
		Ip ip_main = Ip (sub_str[0].trim());
		ip_main.set_value(sub_str[1].trim());
		parse_input (ip_main);

	}
	delete[] sub_str;
	return 0;
}