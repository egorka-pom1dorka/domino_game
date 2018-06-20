#pragma once
#include "Bone.h"
#include <iostream>
using namespace std;

Bone::Bone() : left(0), right(0), prev(nullptr), next(nullptr){
	
}

Bone::Bone(int num1, int num2) {
	if (num1 < Bone::MIN_NUMBER || num1 > Bone::MAX_NUMBER) {
		throw Exception("Incorrect first number");
	}
	else if (num2 < Bone::MIN_NUMBER || num2 > Bone::MAX_NUMBER) {
		throw Exception("Incorrect second number");
	}
	else {
		left = num1;
		right = num2;
		prev = nullptr;
		next = nullptr;
	}
}

Bone::~Bone() {

}

bool Bone::compareData(int n1, int n2) {
	return (this->left == n1 && this->right == n2);
}

ostream & operator << (ostream & out, const Bone bone) {
	out << " --- --- \n| " << bone.left << " | " << bone.right << " | \n --- --- " << endl;
	return out;
}

void Bone::swapData() {
	int i = this->left;
	this->left = this->right;
	this->right = i;
}