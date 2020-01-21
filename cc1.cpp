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
#include "TreeManager.h"

#define SPEED 0.2;

using namespace cimg_library;


int main()
{
	FreeConsole();
	double y_change = 0;
	double x_change = 0;

	CImg<unsigned char> img(640, 400, 1, 3);
	CImgDisplay main_disp(img, "TreeBreeder");


	TreeManager tManager1;


	//genome
	int num_trees = 3;


	Tree** trees = new Tree* [num_trees];
	for (int i = 0; i < num_trees; i++) {
		trees[i] = new Tree(randomf()*640, randomf()*400, 1.0);
	}
	
	
	bool planted = false;

	while (!main_disp.is_closed() && !main_disp.is_keyESC()) {
		//main_disp.wait();

		if (main_disp.is_keyW()) {
			y_change += SPEED;
		}
		if (main_disp.is_keyS()) {
			y_change -= SPEED;
		}
		if (main_disp.is_keyD()) {
			x_change -= SPEED;
		}
		if (main_disp.is_keyA()) {
			x_change += SPEED;
		}

		if (main_disp.is_keySPACE() && planted == false && tManager1.selectedTree != nullptr) {
			planted = true;
			trees = tManager1.plantTree(trees, num_trees, x_change, y_change);
			tManager1.holdingFruit = false;
		}
		if (main_disp.released_key() == cimg::keySPACE) {
			planted = false;
		}
		img.fill(100);


		//growth
		for (int i = 0; i < num_trees; i++) {
			trees[i]->growth();
			trees[i]->moveAndGrowCaller(x_change, y_change);
			trees[i]->drawTree(trees[i]->root, img);
			if (trees[i]->selected==true && main_disp.is_keyENTER()) { //SELECTING A FRUIT
				tManager1.selectedTree = trees[i];
				tManager1.holdingFruit = true;
			}
		}

		tManager1.drawUser(img);
		if (num_trees < 10) {
			tManager1.drawText(img);
		}
		//std::cout << trees[0]->selected << "\n";
		img.display(main_disp);

	}
	
	return 0;
}