#pragma once

#ifndef ROUTEOPTIMIZATION_H
#define ROUTEOPTIMIZATION_H

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include "GraphWeighted.h"

struct InputData
{
	int src;
	int dest;
	int weight;
};


class RouteOptimization
{
private:
	//will store file in vector of struct- could add another memeber to the struct such as "cityName"
	std::vector<InputData> *m_file;	
	
	//set will be used to hold unique vectors therefore we can get a count to plug into graph algorithm
	std::set<int> m_vectorSet;
	//count of vector (or nodes)
	int m_vectorCount;
	//graph object
	GraphWeighted *m_theGraph; 

public:
	//constructor
	RouteOptimization(std::ifstream&);
	//void printTest();
	void createGraph();
	void breadthFirstSearch(int);
	//shortest distance algorithm
	void dijkstraAlg(int);
	void print();

	//destructor- for a vector delete calls the destructor before de-allocationg memory. This will clear its
	//contents- no reason to call .clear
	~RouteOptimization()
	{
		delete(m_theGraph);
		delete(m_file);

	}
};


#endif // !ROUTEOPTIMIZATION_H
