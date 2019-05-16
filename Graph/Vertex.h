/*
 * Vertex.h
 */
#ifndef VERTEX_H_
#define VERTEX_H_
/************************* Vertex  **************************/

#include <vector>
#include "Graph.h"
#include "Vertex.h"
#include "../Utilities/MutablePriorityQueue.h"

class Edge;
class Graph;

class Vertex {
	long info;                // contents
	vector<Edge> adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;
	double x, y;
	Vertex *path = nullptr;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	void addEdge(Vertex *dest, double w);


public:
	Vertex(long in, double x, double y);
	Vertex(long in);
	bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
	long getInfo() const;
	double getX() const { return x; };
	double getY() const { return y; };
	double getDist() const;
	double getEuclideanDist(const Vertex *  vertex2) const;
	Vertex *getPath() const;
	const vector<Edge> * getAdj() const { return &adj; };
	friend class Graph;
	friend class MutablePriorityQueue<Vertex>;
};

#endif
