#include <stddef.h>
#include <iostream>
#include <cstring>
#include "string.h"

using namespace std; //Namespace is useful

String::String() {
	length = 0;
	data = NULL;
}

String::String(const String &str) {
	length = str.length; 
	data = new char [length + 1];
	if ((length == 0) || (str.data == NULL)) {   
		delete[] data;
		data = NULL;
	}
	else
	{
		strcpy (data ,str.data);
	}	
}

String::String(const char *str) {
	if (str == NULL) {
		length = 0;
		data = NULL;  ///
		   
	}
	else
	{
		data = new char [strlen(str) + 1];
		strcpy (data ,str);
		length = strlen(str);

	}
}

String::~String() {
	if (data != NULL) 
		delete[] data;
}

//	These functions frees the memory created. (Allocated)

String& String::operator=(const String &rhs) {
	if (data != NULL) 
		delete[] data;
	length = rhs.length;
	if (length == 0){
		data = NULL;
		return *this;
	}
	else {
		data = new char [length + 1];
		strcpy (data ,rhs.data);
		return *this;
	}
	
}

String& String::operator=(const char *str) {
	if (data != NULL) 
		delete[] data;
	if (str == NULL) {
		length = 0;
		data = NULL;
		return *this;
	}
	length = strlen(str) ;  
	data = new char [length + 1];
	strcpy(data,str);
	return *this;
	
}

bool String::equals(const String &rhs) const {
	if (length != rhs.length) 
		return false;
	if (strcmp(data,rhs.data))
		return false;
	return true;
}

bool String::equals(const char *rhs) const {
	if ((data == NULL) && (rhs == NULL)) 
		return true;
	else 
		if (rhs == NULL) 
			return false;
	if (strcmp(data,rhs)) 
	{
		return false;
	}
	return true;
}

/* The indexes of the arr (It contains data) points to the start to each sub string
	also, this function makes new strings and copies the data given to it.
	Moreover, it searches for delimiters in the strings and changes it to 
	the right chars. It updates the delimiter according to the actions and data
	being given in the function and the output should contain all the sub strings */

void String::split(const char *delimiters,String **output,size_t *size) const {
	char tmp[length + 1];
	int counter_of_delimiters = 0;	
	int delimiters_number = strlen(delimiters);
	int starting_index = 1;
	size_t starting_string [length] = {0};
	if(data == NULL)
	{
		*size = 0;
		return;
	}
	strcpy (tmp,data);
	for (size_t counter = 0; counter < length; counter++) {
		for (int sec_counter = 0; sec_counter < delimiters_number; sec_counter++) {
			if (tmp[counter] == delimiters[sec_counter])
			{
				if(((counter + 1) < length) && (tmp[counter + 1] == '\0')) 
				{
					counter_of_delimiters--;
					break;
				}
				if ((starting_string[starting_index - 1] == counter) 
					&& (tmp[counter + 1]!= '\0')) 
				{
					starting_string[starting_index - 1] = counter + 1;
					tmp[counter] = '\0';
					continue;
				}
				tmp[counter] = '\0';
				counter_of_delimiters++;
				if (((counter + 1) < length) && (tmp[counter + 1]!= '\0')) 
				{
					starting_string[starting_index] = counter + 1;
					starting_index++;
					break;
					}
				}
			}
	}
	*size = counter_of_delimiters + 1;
	if (output == NULL) 
		return;
		
	*output = new String [counter_of_delimiters + 1];
	for (int counter = 0; counter < counter_of_delimiters + 1; counter++) {
		String output_string = &(tmp[starting_string[counter]]);
		(*output)[counter] = output_string;
	}
}


int String::to_integer() const {
	return atoi(this->data);
}

/* It skips the spaces all around the strings and copies the right chars 
	to the a created new string */

String String::trim() const {
	int running_cursor = 0;
	int stoppage = this->length-1;
	if (data == NULL) 
		return *this;
	if(this->length == 0)
	return *this;
	while ((running_cursor < stoppage) && (this->data[running_cursor]==' '))
	{
		running_cursor++;
	}
	while ((running_cursor != stoppage) && (this->data[stoppage] == ' ')) {
		stoppage--;
	}
	if (running_cursor > stoppage) {
		char emp_str[1] ;
		emp_str[0] = '\0';
		return String(emp_str);
	}
	int created_length = 2+stoppage-running_cursor;   
	char op_str[created_length]; //Bias needed
	op_str[created_length - 1] ='\0';
	for (int counter = 0 ;counter <created_length - 1 ;counter++) { 
		op_str[counter] = this->data[running_cursor + counter];
	}
	return String(op_str);
}
