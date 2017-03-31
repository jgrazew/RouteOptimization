#include "stdafx.h"
#include <iostream>
#include "RouteOptimization.h"

//constructor will put file into dynamically allocated pointer- since not sharing across another class
//we could just use a regualar vector. Dont need pointer to dynamically allocated vector but I am going to
//leave as is Incase I decide to expand program
RouteOptimization::RouteOptimization(std::ifstream &is) : m_file(new std::vector<InputData>), 
				m_vectorCount(0)
{
	std::string line;
	std::string number;

	while (std::getline(is, line))
	{
		InputData tempdata;
		//bind record(just created) to line
		std::istringstream record(line);	
		//split the string into a series of ints
		//while (record >> number)		//cplusplus.com/reference   std::istringstream shows you can 
		for(int i = 0; i !=3; i++)		//convert a istringstream to an int. 3 per line. I PRINTED THIS OUT 
		{
			record >> tempdata.src;
			record >> tempdata.dest;
			record >> tempdata.weight;

			//set only takes unique values- therefore count of our set will be number of unique vectors
			m_vectorSet.insert(tempdata.src);
			m_vectorSet.insert(tempdata.dest);
			m_vectorCount = m_vectorSet.size();
		}
		//append this record to file
		m_file->push_back(tempdata);		
		
	}
}

void RouteOptimization::createGraph()
{
	m_theGraph = new GraphWeighted(m_vectorCount);
	//iterate through a pointer to a vector
	for (int i = 0; i != m_file->size(); ++i)
		m_theGraph->addEdge(m_file->at(i).src, m_file->at(i).dest, m_file->at(i).weight);
}

void RouteOptimization::print()
{
	m_theGraph->printGraph();
}

void RouteOptimization::dijkstraAlg(int src)
{
	m_theGraph->shortestPath(src); 

}

void RouteOptimization::breadthFirstSearch(int src)
{
	m_theGraph->bfs(src);
}
