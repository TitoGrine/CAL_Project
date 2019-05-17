/*
 * Edge.h
 */
#ifndef EDGE_H_
#define EDGE_H_

#include "Graph.h"
#include "Vertex.h"

/********************** Edge  ****************************/

class Vertex;
class Graph;


class Edge {
	Vertex *orig; 	// Fp07
	Vertex * dest;      // destination vertex
	double weight;         // edge weight

	bool selected; // Fp07

public:
	Edge(Vertex *o, Vertex *d, double w);
	friend class Graph;
	friend class Vertex;

	// Fp07
	double getWeight() const;

	bool operator<(const Edge & e2) const;
	bool operator==(const Edge & e2 ) const;

	Vertex *  getOrig() const { return orig; };
	Vertex *  getDest() const { return dest; };
	
};

#endif
