// GraphAlgWeightedText.cpp : Defines the entry point for the console application.

//Graph Data Structure created using an Adjacency List. 
//Undirected weighted graph
//Algorithms include BFS and shortest path 
//Program reads in a text file from user
//Could use vectors instead of dynamically allocated arrays in graph implementation to be up to dat C++11

#include "stdafx.h"
#include <iostream>
#include "GraphWeighted.h"
#include "RouteOptimization.h"

int main()
{
	std::ifstream inFile;
	inFile.open("test.txt");
	RouteOptimization rt(inFile);
	//rt.printTest();
	rt.createGraph();
	rt.print();
	rt.breadthFirstSearch(0);
	rt.dijkstraAlg(0);

	return 0;
}
