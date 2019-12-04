#pragma once
#ifndef TREE_H
#define TREE_H

#include "plant.h"

class Tree {
public:
	double x = 0;
	double y = 0;
	double* genome;
	double maturity = 1;
	Node* root;
	Tree(double p_x, double p_y, double* p_genome, double p_maturity) {
		x = p_x;
		y = p_y;
		genome = p_genome;
		maturity = p_maturity;
		root = buildtree(maturity, x, y, 0);
	}

	Node* buildtree(double length, double x, double y, int position) {//position increases to right, decreases to left

		Node* root; //declaring the root, this is a ptr to a node

		root = new Node(x, y);

		if (length < 15) {

			return(root);
		}


		double left_growth = root->growthRate(position, genome, 0);
		double right_growth = root->growthRate(position, genome, 1);

		double angle = root->angleFunc(position, genome);

		bool branch = root->branchOrNot(position, genome);

		if (branch) {
			root->left = buildtree(length * left_growth, x - (cos(90 - angle) * length), y - (sin(90 - angle) * length), position - 1);  //a-> shorthand for (a*).b - accessing the left part of the Node pointed at by root*
			root->right = buildtree(length * right_growth, x + (cos(90 - angle) * length), y - (sin(90 - angle) * length), position + 1);
		}
		else {

			return(root);
		}
		return root;
	}

	void updateTree(Node* root, double length, double x, double y, int position) {//position increases to right, decreases to left

		if (root!= nullptr) {
			root->x = x;
			root->y = y;

			double left_growth = root->growthRate(position, genome, 0);
			double right_growth = root->growthRate(position, genome, 1);

			double angle = root->angleFunc(position, genome);

			bool branch = root->branchOrNot(position, genome);

			if (branch) {
				updateTree(root->left, length * left_growth, x - (cos(90 - angle) * length), y - (sin(90 - angle) * length), position - 1);  //a-> shorthand for (a*).b - accessing the left part of the Node pointed at by root*
				updateTree(root->right, length * right_growth, x + (cos(90 - angle) * length), y - (sin(90 - angle) * length), position + 1);
			}
		}
	}

	void drawTree(Node* root, CImg<unsigned char>& img) {
		unsigned char leaf[] = { genome[10]*255,genome[11] * 255,genome[12] * 255 };
		unsigned char branch[] = { genome[8] * 255,genome[9] * 255,genome[10] * 255 };
		if (root->left == nullptr && root->right == nullptr) {
			img.draw_circle(root->x, root->y, 2, leaf, 1.0);
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
	}
};

#endif