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
#define SPEED 0.2;

using namespace cimg_library;


int main()
{
	double y_change = 0;
	double x_change = 0;

	CImg<unsigned char> img(640, 400, 1, 3);
	unsigned char ground[] = {50,150,80};
	CImgDisplay main_disp(img, "this is a window");

	//genome
	int num_trees = 100;


	Tree** trees = new Tree* [num_trees];
	for (int i = 0; i < num_trees; i++) {
		trees[i] = new Tree(randomf()*640, randomf()*400, 1.0);
	}

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
		img.fill(100);
		
		unsigned char white[] = { 255, 255, 255 };
		img.draw_arrow(320 - 5, 200 + 5, 320-4, 200+4, white, 1.0, 3.8,10.0, 5);//use a 7x7 box to select
		img.draw_arrow(320 - 5, 200 - 5, 320-4, 200-4, white, 1.0, 3.8, 10.0, 2);
		img.draw_arrow(320 + 5, 200 + 5, 320+4, 200+4, white, 1.0, 3.8, 10.0, 2);
		img.draw_arrow(320 + 5, 200 - 5, 320+4, 200-4, white, 1.0, 3.8, 10.0, 2);
		for (int i = 0; i < num_trees; i++) {
			trees[i]->growth();
			trees[i]->moveAndGrowCaller(x_change, y_change);
			trees[i]->drawTree(trees[i]->root, img);
		}

		//std::cout << tree1.maturity<<"\n";
		img.display(main_disp);

	}
	
	return 0;
}