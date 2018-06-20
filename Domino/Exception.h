#pragma once
#define MAX_STRING_SIZE 100

class Exception {
	char msg[MAX_STRING_SIZE];
public:
	Exception();
	~Exception();
	Exception(char * str);
	void what();
};