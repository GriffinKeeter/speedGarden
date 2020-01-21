#pragma once
#ifndef TREE_H
#define TREE_H

#include "plant.h"
#include <cmath>
#include "rando.h"
#include "Colors.h"


class Tree {
public:
	int GENOME_SIZE = 20;
	double MUTATION_STEP = 0.05;
	double x = 0;
	double y = 0;
	double* genome = nullptr;
	double maturity = 15.0;
	Node* root = nullptr;
	bool selected = false;
	Tree(double p_x, double p_y, double p_maturity) {//maturity is the length of the first branch
		x = p_x;
		y = p_y;
		root = new Node(x, y, 0, 0);
		maturity = p_maturity;
		genome = new double[20];
		for (int i = 0; i < GENOME_SIZE; i ++) {
			genome[i] = randomf();
		}

	}

	void growth() {//maturity increment , deals with max height and growth rate
		if (maturity < genome[15]*150) {
			maturity += 0.05*genome[14];
		}
	}

	void moveAndGrowCaller(double x_change, double y_change) {//there has to be a better way to do this - how to start a recursive function with no parameters
		selected = false; //sets selected = false every time the tree is updated
		moveAndGrow(root, x+x_change, y+y_change, maturity);
	}

	void moveAndGrow(Node* root, double x, double y, double prev_length) { 


		//you need these whether you are updating positions or creating new nodes - formulas using position in the tree as input as well as genome
		double angle = 3.14/4 * (sin((root->pos) * (genome[13]-0.5)*10*root->depth +sin(root->pos * genome[12]))*genome[13]+1);
		double left_length = prev_length *0.8 - (sin(root->pos* (genome[10] - 0.5) *10+sin(root->depth * genome[11]*5))-1)*0.4;
		double right_length = prev_length *0.8 - (sin(root->pos * (genome[11]-0.5) * 10 + sin(root->depth * genome[10] * 5)) - 1) * 0.4;


		//new coordinates for the following nodes
		double new_x_left = x - (cos(angle) * left_length);
		double new_y_left = y - (sin(angle) * left_length);
		double new_x_right = x + (cos(angle) * right_length);
		double new_y_right = y - (sin(angle) * right_length);

		int branch = sin(root->pos * (genome[7]-0.5) * 3.14 * 14 / 5)+1+(genome[8]-0.5);
		if (root->depth == 0) {
			branch = 1;//makes sure the tree always branches on the first level
		}


		if (root->left == nullptr && root->right == nullptr) { //node is a leaf and the branch before it was longer than 10
			if (prev_length > 20. && branch != 0) {
				root->left = new Node(new_x_left, new_y_left, (root->pos)-1, (root->depth)+1);

				root->right = new Node(new_x_right, new_y_right, (root->pos) + 1, (root->depth) + 1);
			}
			else {
				root->x = x;
				root->y = y;
			}
		}
		else if(root->left != nullptr && root->right != nullptr){ //node is inside the tree
			root->x = x;
			root->y = y;

			moveAndGrow(root->left, new_x_left, new_y_left, left_length);
			moveAndGrow(root->right, new_x_right, new_y_right, right_length);
		}
		return;
	}

	void drawTree(Node* root, CImg<unsigned char>& img) {
		unsigned char leaf[] = { genome[6]*255, genome[5]*255, genome[4]*255 };
		unsigned char branch[] = { genome[3]*255, genome[2]*255, genome[1]*255 };
		if (root->left == nullptr && root->right == nullptr) {
			int radius = 2;
			int mid_x = 320;
			int mid_y = 200;
			if (root->x < mid_x + 7 && root->x > mid_x - 7 && root->y > mid_y - 7 && root->y < mid_y + 7) {//a fruit from this tree is selected //doesn't select anyone other than first layer?
				img.draw_circle(root->x, root->y, radius+3, white, 1.0);
				selected = true;
			}
	
			img.draw_circle(root->x, root->y, radius, leaf, 1.0);
			return;
		}
		//drawTree()
		if (root->left != nullptr) {
			img.draw_line(root->x, root->y, root->left->x, root->left->y, branch, 1.0, ~0U, true);
			drawTree(root->left, img);
		}
		if (root->right != nullptr) {
			img.draw_line(root->x, root->y, root->right->x, root->right->y, branch, 1.0, ~0U, true);
			drawTree(root->right, img);
		}
		return;
	}

	void mutateGenome() {
		for (int i = 0; i < GENOME_SIZE; i ++) {
			if (genome[i]+MUTATION_STEP>=1.0) {
				genome[i] -= MUTATION_STEP;
			}
			else if (genome[i] - MUTATION_STEP < 0.0) {
				genome[i] += MUTATION_STEP;
			}
			else {//could increment or decrement
				double dir = (randomi(1)-0.5)*2*MUTATION_STEP;//give either + or - mutation step
				genome[i] += dir;
			}
		}
	}
};

#endif