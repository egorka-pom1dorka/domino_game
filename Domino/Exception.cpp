#pragma once
#include <string.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <errno.h>
#include <iostream>
#include "Exception.h"
using namespace std;

Exception::Exception() {
	strcpy_s(msg, "Throwed new exception");
}

Exception::Exception(char * str) {
	strcpy_s(msg, str);
}

Exception::~Exception() {

}

void Exception::what() {
	cout << msg << endl;
}