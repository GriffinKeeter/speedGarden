#pragma once
#ifndef PLANT_H
#define PLANT_H

#include <iostream>
#include "CImg.h"
#include "rando.h"

using namespace cimg_library;

double q = 3.14 / 2;


class Node {
public:
	double x;
	double y;
	Node* left;
	Node* right;

	Node(double x_pos, double y_pos) { //constructor //type- 0 - root, 1 - joint, 2 - leaf
		x = x_pos;
		y = y_pos;
		left = nullptr;
		right = nullptr;
	}

	//methods
	bool branchOrNot(int pos, double* genome) {
		int branch;
		branch = sin(genome[3] *5* pos+cos(pos*genome[4])) + 1;
		return(branch);
	}

	double angleFunc(int pos, double* genome) {
		double angle;
		angle = (cos(genome[0] * pos + sin(genome[1] * pos))) * (genome[2] * 0.9) + (genome[3] * 0.8);
		return(angle);
	}

	double growthRate(int pos, double* genome, int direction) {//direction - right or left
		double growth = 0.5;
		if (direction == 0) {
			growth = sin(genome[6] * 5*pos)*0.1+1 *0.8;
		}
		else if (direction == 1) {
			growth = sin(genome[7] * 5*pos+(genome[3]*3))*0.2+1 * 0.7;
		}
		return(growth);
	}
};


#endif