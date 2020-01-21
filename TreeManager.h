#pragma once
#ifndef TREE_MANAGER_H
#define TREE_MANAGER_H

#include "CImg.h"
#include "Tree.h"

using namespace cimg_library;

class TreeManager {
public:
	Tree* selectedTree = nullptr;

	double y_change = 0;
	double x_change = 0;

	bool holdingFruit = false;
	
	void drawUser(CImg<unsigned char>& img) {
		unsigned char white[] = { 255, 255, 255 };
		img.draw_arrow(320 - 5, 200 + 5, 320 - 4, 200 + 4, white, 1.0, 3.8, 10.0, 5);//use a 7x7 box to select
		img.draw_arrow(320 - 5, 200 - 5, 320 - 4, 200 - 4, white, 1.0, 3.8, 10.0, 2);
		img.draw_arrow(320 + 5, 200 + 5, 320 + 4, 200 + 4, white, 1.0, 3.8, 10.0, 2);
		img.draw_arrow(320 + 5, 200 - 5, 320 + 4, 200 - 4, white, 1.0, 3.8, 10.0, 2);
		if (holdingFruit == true) {
			drawFruit(img);
		}
	}

	void drawText(CImg<unsigned char>& img) {
		img.draw_text(20, 20, "WASD to move", white);
		img.draw_text(20, 40, "ENTER to pick", white);
		img.draw_text(20, 60, "SPACE to plant", white);
	}

	void drawFruit(CImg<unsigned char>& img) {//s_tree - SelectedTree
		if (selectedTree!= nullptr) {
			unsigned char fruit[] = { selectedTree->genome[6] * 255, selectedTree->genome[5] * 255, selectedTree->genome[4] * 255 };
			img.draw_circle(320, 200, 2, fruit, 1.0);
		}
	}

	Tree** plantTree(Tree** trees, int& numTrees, double x_change, double y_change) {
		Tree** new_trees = new Tree*[numTrees+1];
		for (int i = 0; i < numTrees; i ++) {
			new_trees[i] = trees[i];
		}
		delete trees;
		new_trees[numTrees] = new Tree(320.0-x_change,200.0-y_change,1.0);

		for (int i = 0; i < new_trees[0]->GENOME_SIZE; i ++) {
			new_trees[numTrees]->genome[i] = selectedTree->genome[i];
		} //need to delete old genome and trees
		new_trees[numTrees]->mutateGenome();
		numTrees++;
		selectedTree = nullptr;
		return(new_trees);
	}


};

#endif
