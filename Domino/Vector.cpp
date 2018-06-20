#pragma once
#include "Vector.h"
#include <iostream>
using namespace std;

void Vector::print() {
	int len = this->size();
	for (int i = 0; i < len; i++) {
		cout << this->at(i);
	}
}

Bone Vector::getBone(int _i) {
	return this->at(_i);
}

void Vector::remove(int i) {
	this->erase(begin() + i);
}

void Vector::unshift(Bone b) {
	this->insert(begin(), b);
}