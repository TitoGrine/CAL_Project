/*
 * Vertex.h
 */
#ifndef VERTEX_H_
#define VERTEX_H_
/************************* Vertex  **************************/

#include <vector>
#include "Edge.h"
#include "Vertex.h"
#include "../Utilities/MutablePriorityQueue.h"

class Edge;

class Vertex {
	long info;                // contents
	vector<Edge> adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;
	double x, y;
	Vertex *path = nullptr;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	// Deposite and garage identifiers
	bool initial = false;
	bool last = false;

	void addEdge(Vertex *dest, double w);


public:
	Vertex(long in, double x, double y);
	Vertex(long in);
	bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
	long getInfo() const;
	double getX() const { return x; };
	double getY() const { return y; };
	double getDist() const;

	bool getVisited() const { return this->visited; };
	double getEuclideanDist(const Vertex *  vertex2) const;
	void setInitial() { this->initial = true; };
	void setFinal() { this->last = true; };
	void setDist(double dist) { this->dist = dist; };
	void setPath(Vertex * v) { this->path = v; };
	void setVisited(bool visited) { this->visited = visited; };
	void removeInitial() { this->initial = false; };
	void removeFinal() { this->last = false; };

	Vertex *getPath() const;
	vector<Edge> * getAdj() { return &adj; };
	friend class Graph;
	friend class MutablePriorityQueue<Vertex>;
};

#endif
