#pragma once
#ifndef PLANT_H
#define PLANT_H

#include <iostream>
#include "CImg.h"
#include "rando.h"
#include <cmath>

using namespace cimg_library;

double q = 3.14 / 2;


class Node {
public:
	double x;
	double y;
	int pos = 0;//distance from center
	int depth = 0;//distance from root
	bool selected = false;
	Node* left = nullptr;
	Node* right = nullptr;

	Node(double x_pos, double y_pos, int p_pos, int p_depth) { //constructor //type- 0 - root, 1 - joint, 2 - leaf
		x = x_pos;
		y = y_pos;
		pos = p_pos;
		depth = p_depth;
	}
};


#endif