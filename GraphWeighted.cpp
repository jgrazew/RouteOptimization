#include "stdafx.h"
#include <iostream>
#include <functional> //for std::greater in the shortestPath() function
#include "GraphWeighted.h"

GraphWeighted::GraphWeighted(int V) : m_V(V)
{
	//Create a array for the number of vertex and initially set each head to NULL
	m_array = new AdjList[V];
	for (int i = 0; i < V; ++i)
		m_array[i].head = NULL;
}

AdjListNode* GraphWeighted::newAdjListNode(int dest, int weight)
{
	AdjListNode* newNode = new AdjListNode;
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

//undirected Edge to Graph- for directed would get rid of last 3 lines of code
void GraphWeighted::addEdge(int src, int dest, int weight)
{
	//dynamically allocates a new node; node equal do dest and pointing next to NULL
	AdjListNode* newNode = newAdjListNode(dest, weight);
	//src head created in constructor; MAKES CONNECTION
	newNode->next = m_array[src].head;
	//source head now pointing to new node
	m_array[src].head = newNode;
	//dynamically allocate a newNode
	newNode = newAdjListNode(src, weight); 
	newNode->next = m_array[dest].head;
	m_array[dest].head = newNode;
}

//s will be starting node of traversal- bfs prints in levels: 0 dist away; 1 dist away; 2 dist away, etc
void GraphWeighted::bfs(int s)
{
	//mark all vertices as not visited 
	bool *visited = new bool[m_V];
	for (int i = 0; i != m_V; ++i)
		visited[i] = false;

	//queue cpntainer adaptor
	std::queue<int> queue;

	//mark the current node as visited and enqueue it
	visited[s] = true;
	queue.push(s);

	std::cout << "The BFS traversal for " << s << " is: ";

	while (!queue.empty())
	{
		int temp = queue.front();
		std::cout << temp << " ";
		queue.pop();

		//get all nodes adjacent to dequeued vertex temp
		for (AdjListNode *i = m_array[temp].head; i != NULL; i = i->next)
		{
			if (visited[i->dest] == false)
			{
				visited[i->dest] = true;
				queue.push(i->dest);
			}
		}
	}
	std::cout << std::endl;
}

void GraphWeighted::shortestPath(int s)
{
	//set distance from s to each vector initially as 20k; no distance will reach 20k; s/ do INFINITY (float) if weights larger
	int *distance = new int[m_V];
	for (int i = 0; i != m_V; ++i)
		distance[i] = 20000; 

	//by default priority_queue is max (top element is largest) this makes priority queue min (top element smallest)
	//priority queue used for weighted shortest path where regular queue is used for unweighted graph
	std::priority_queue<int, std::vector<int>, std::greater<int> > queue;

	//distance of s to itself is 0
	distance[s] = 0;
	queue.push(s);

	//loop until queue is empty 
	while (!queue.empty())
	{
		int temp = queue.top();
		queue.pop();

		//get all nodes adjacent to temp (remember head is a pointer); iterate until i->next points to NULL
		for (AdjListNode *i = m_array[temp].head; i != NULL; i = i->next)
		{
			//if distance[temp] + i->weight is shorter enter conditional
			if (distance[i->dest] > distance[temp] + i->weight) 
			{
				//update distance
				distance[i->dest] = distance[temp] + i->weight;
				queue.push(i->dest);
			}
		}
	}

	for (int i = 0; i != m_V; ++i)
		std::cout << "the distance from " << s << " to " << i << " is " << distance[i] << std::endl;

}

void GraphWeighted::printGraph()
{
	for (int v = 0; v < m_V; ++v)
	{
		AdjListNode* current = m_array[v].head;
		std::cout << "Adjacency list of vertex " << v << std::endl;
		std::cout << "Head ";
		while (current)
		{
			std::cout << "-> " << current->dest << " (weight of " << current->weight << ") ";
			current = current->next;
		}
		std::cout << std::endl;
	}
}
