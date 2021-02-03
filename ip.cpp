#include <cstring>
#include <iostream>
#include "ip.h"

enum {oct_1st = 3 , oct_2nd = 2 , oct_3rd = 1 , oct_4th = 0};

enum {packet_max_size = 255 ,packet_min_size = 0 ,one_byte = 8 , two_bytes = 16,
		three_bytes = 24 ,four_bytes = 32 };

Ip::Ip(String pattern) : Field(pattern,IP) 
{
	this->low = 0;
	this->high = 0;
}

/**
 * @brief convert the string to ip num
 * @return the ip num and if was success we change the value of error to 0
 * @if the range is incorrect  we change the value of error to 1
 */
unsigned int convert_given_ip_to_num (String Ip, int *error){
	size_t length = 0;
	String *array_of_str = NULL;
	Ip.split(".",&array_of_str,&length);
	
	/* we check if the range of IP byte is correct*/      
	for (size_t counter = 0; counter < length ; counter++) 
	{
		if ( (array_of_str[counter].to_integer() < packet_min_size)||
			(array_of_str[counter].to_integer() > packet_max_size))     
		{
			delete[] array_of_str;
			*error = 1;
			return 0;
		}
	}
	unsigned int res = 0;
	/* now we compose, by the ip bytes, the complete ip num */
	res = array_of_str[oct_1st].to_integer() 
		  | array_of_str[oct_2nd].to_integer()  <<  one_byte
		  | array_of_str[oct_3rd].to_integer() << two_bytes
		  | array_of_str[oct_4th].to_integer() << three_bytes ;  
	delete[] array_of_str;
	*error = 0;
	return res;
}

bool Ip::set_value(String val){
	int err;
	unsigned int mask = 0;
	size_t help_size = 0;
	String *help_string = NULL;
	val.split("/",&help_string,&help_size);  // now we split to ip and cidr
	int cidr = help_string[1].trim().to_integer();
	
	/* we check if the range of cidr is correct*/
	if(four_bytes < cidr|| 0 > cidr ) {      
		delete[] help_string;
		return false;
	}
	for(int counter = 0; counter < cidr; counter++) {
		mask = mask + (1 << (four_bytes-1-counter)); 
	}
	unsigned int number_of_ip = convert_given_ip_to_num (help_string[0].trim() , &err);
	if (err) {
		delete[] help_string;
		return false;
	}
	this->low =  (number_of_ip) & (mask);
	this->high = number_of_ip | (~mask);
	delete[] help_string;
	return true;
}

bool Ip::match_value(String val) const{
	int err;
	unsigned int ip = convert_given_ip_to_num(val ,&err);
	if(err) 
		return false;
	if((ip >= this->low) && (ip <= this->high))
		return true;
	return false;
}
