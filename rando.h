#pragma once
//rando.h

#ifndef RANDO_H
#define RANDO_H

#include <random>
#include <math.h>
#include <stdlib.h>

double randomf() {

	std::random_device rd;  //Will be used to obtain a seed for the random number engine

	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

	std::uniform_int_distribution<> dis(0, 99);



	double t = ((double)dis(gen)) / 100;

	return(t);

}

double randomi(int upper) {

	std::random_device rd;  //Will be used to obtain a seed for the random number engine

	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

	std::uniform_int_distribution<> dis(0, upper);



	int t = dis(gen);

	return(t);

}

#endif
