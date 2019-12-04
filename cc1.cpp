// cc1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CImg.h"
#include <random>
#include <math.h>
#include <stdlib.h>
#include "rando.h"
#include "plant.h"
#include "Tree.h"
#define SPEED 1;

using namespace cimg_library;

void updateTrees(Tree** trees, CImg<unsigned char>& img, int num_trees, int y_change, int x_change) {
	img.fill(100);
	for (int i = 0; i < num_trees; i++) {
		//trees[i]->updateTree(trees[i]->root, trees[i]->maturity, trees[i]->x+x_change, trees[i]->y + y_change, 0);
		//trees[i]->root = trees[i]->buildtree(trees[i]->maturity, trees[i]->x, trees[i]->y, 0);
		trees[i]->drawTree(trees[i]->root, img);
	}
}

int main()
{
	int y_change = 0;
	int x_change = 0;

	CImg<unsigned char> img(640, 400, 1, 3);
	unsigned char ground[] = {50,150,80};
	CImgDisplay main_disp(img, "this is a window");

	//genome
	int num_trees = 20;

	int genome_size = 20;
	double** genome = new double*[num_trees];

	for (int i = 0; i < num_trees; i ++) {
		genome[i] = new double[genome_size];
		for (int j = 0; j < genome_size; j++) {
			genome[i][j] = randomf();
		}
	}



	Tree** trees = new Tree * [num_trees];
	for (int i = 0; i < num_trees; i ++) {
		trees[i] = new Tree(randomf()*640, randomf()*400, genome[i], 40.);
	}

	Tree tree1(300., 300., genome[0], 40.);
	//tree1.root = tree1.buildtree(tree1.maturity, tree1.x, tree1.y, 0);
	tree1.drawTree(tree1.root, img);

	while (!main_disp.is_closed() && !main_disp.is_keyESC()) {
		//main_disp.wait();

		if (main_disp.is_keyW()) {
			y_change += 1;
		}
		if (main_disp.is_keyS()) {
			y_change -= 1;
		}
		if (main_disp.is_keyD()) {
			x_change -= 1;
		}
		if (main_disp.is_keyA()) {
			x_change += 1;
		}
		img.fill(100);
		tree1.drawTree(tree1.root, img);
		tree1.updateTree(tree1.root, tree1.maturity, tree1.x+x_change, tree1.y + y_change, 0);
		//updateTrees(trees, img, num_trees, y_change, x_change);
		/*for (int i = 0; i < num_trees; i++) {
			trees[i]->buildtree(trees[i]->maturity, trees[i]->x, trees[i]->y, 0);
			trees[i]->drawTree(trees[i]->root, img);
		}*/
		tree1.maturity += 0.05;

		std::cout << tree1.maturity<<"\n";
		img.display(main_disp);

	}
	
	return 0;
}