#include <iostream>
#include <cstring>
#include "field.h"
#include "port.h"
#include "ip.h"

Field::Field(String pattern, field_type type ) : pattern(pattern), type(type)
{}

Field::Field(String pattern)  {
	this->type = GENERIC;
	this->pattern = pattern;
}

Field::~Field() 
{}

field_type Field::get_type() const {
	return this->type;
}

bool Field::match_value(String val) const {
	if(this->type == PORT)
		return ((Port*)this)->match_value(val);
	if (this->type == IP)
		return ((Ip*)this)->match_value(val);
	return false;
}

bool Field::set_value(String val) {
	if(this->type == PORT)
		return ((Port*)this)->set_value(val);
	if (this->type == IP)
		return ((Ip*)this)->set_value(val);
	return false;
}

/* This function places each packet's subfields in the arr and it also
	checks whether the sub fields is the same as the rule. */

bool Field::match(String packet) {
	String *array_of_string = NULL;
	size_t counter_of_fields = 0; 
	packet.split(",=",&array_of_string,&counter_of_fields);
	if(counter_of_fields == 0)
	{
		delete[] array_of_string;
		return false;
	}
	for(size_t counter = 0; counter < counter_of_fields; counter++){
		if(array_of_string[counter].trim().equals(this->pattern.trim()))
		{
			bool res = this->match_value(array_of_string[counter+1].trim());
			delete[] array_of_string;
			return res;
		}
	}
	delete[] array_of_string;
	return false;
}
