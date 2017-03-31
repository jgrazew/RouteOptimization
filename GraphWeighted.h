#pragma once

#ifndef GRAPHWEIGHTED_H
#define GRAPHWEIGHTED_H

#include "stdafx.h"
#include <iostream>
#include <queue>

// Adjacency List Node- linked list
struct AdjListNode
{
	int dest;
	int weight;
	AdjListNode* next;
};

// Adjacency List; these pointers will point to a head of a linked list 
struct AdjList
{
	AdjListNode *head;
};

class GraphWeighted
{
private:
	int m_V;
	//array for number of head nodes
	AdjList *m_array;


public:
	//constructor
	GraphWeighted(int);
	// Creating New Adjacency List Node
	AdjListNode* newAdjListNode(int, int);
	// Adding undirected Edge to Graph
	void addEdge(int, int, int);						
														
	void bfs(int);
	//Shortest Path of an unweighted graph- start at int and create a path to all other vertices
	void shortestPath(int);
	void printGraph();

	//destructor
	~GraphWeighted()
	{
		AdjListNode *current;
		for (int i = 0; i != m_V; ++i)
		{
			current = m_array[i].head;
			while (current->next != NULL)
			{
				AdjListNode *next = current->next;
				delete current;
				current = next;

			}
		}
		current = 0;

		delete[] m_array;
	}

};

#endif // !GRAPHWEIGHTED_H
