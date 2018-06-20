#pragma once
#include "Exception.h"
#include <iostream>
using namespace std;

class Bone {
public:
	static const int MIN_NUMBER = 0;
	static const int MAX_NUMBER = 6;
	static const int VALUES_AMOUNT = 2;
	int left;
	int right;
	Bone * next;
	Bone * prev;
	Bone();
	~Bone();
	Bone(int, int);
	bool compareData(int, int);
	void swapData();
	friend ostream & operator << (ostream & out, const Bone bone);
};