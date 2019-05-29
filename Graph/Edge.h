/*
 * Edge.h
 */
#ifndef EDGE_H_
#define EDGE_H_

//#include "Graph.h"
#include "Vertex.h"

/********************** Edge  ****************************/

template <class T> class Graph;
template <class T> class Vertex;

/**
 * @brief Edge class used to structure a graph
 * 
 */
template <class T>
class Edge {
	//Origin vertex
	Vertex<T> * orig;

	//destination vertex 	
	Vertex<T> * dest;

	// Edge weight
	double weight;         

	//Indicates if the edge was selected
	bool selected; 

public:
	/**
	 * @brief Constructor - creates new Edge
	 * @param o Pointer to the origin vertex
	 * @param d Pointer to the destination vertex
	 * @param w Weifht of the new edge
	 * 
	 */
	Edge(Vertex<T> *o, Vertex<T> *d, double w);

	friend class Graph<T>;
	friend class Vertex<T>;

	/**
	 * @brief Return this weight of this edge
	 * @return Value of the weight of this edge
	 * 
	 */
	double getWeight() const;

	/**
	 * @brief Used to compare to edges
	 * @param e2 Edge being compared to this edge
	 * @return True if this edge has less weight than the edge e2,
	 * False otherwise
	 * 
	 */
	bool operator<(const Edge<T> & e2) const;

	/**
	 * @brief Used to compare the equality of this edge with another edge
	 * @param e2 Edge being compared to this edge
	 * @return True if this edge has the same origin and destination as of the other edge
	 * False otherwise
	 * 
	 */
	bool operator==(const Edge<T> & e2 ) const;

	/**
	 * @brief Returns the origin atribute
	 * @return Pointer to the oirign vertex of this edge
	 * 
	 */
	Vertex<T> *  getOrig() const { return this->orig; };

	/**
	 * @brief Return the destination atribute
	 * @return Poninter to the destination vertex of this edge
	 * 
	 */
	Vertex<T> *  getDest() const { return this->dest; };
};


template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w): orig(o), dest(d), weight(w) {}

template <class T>
double Edge<T>::getWeight() const {
	return weight;
}

template <class T>
bool Edge<T>::operator<(const Edge<T> & e2 ) const {
	return this->getWeight() > e2.getWeight();
}

template <class T>
bool Edge<T>::operator==(const Edge<T> & e2 ) const {
	return this->getDest() == e2.getDest() && this->getOrig() == e2.getOrig();
}

#endif
