#pragma once
#include "Exception.h"
#include "Bone.h"
#include <vector>

class Vector : public vector<Bone> {
public:
	void print();
	Bone getBone(int);
	void remove(int);
	void unshift(Bone);
};