/*
 * Vertex.h
 */
#ifndef VERTEX_H_
#define VERTEX_H_
/************************* Vertex  **************************/

#include <vector>
#include <cmath>
#include "../Utilities/MutablePriorityQueue.h"

template <class T> class Edge;
template <class T> class Vertex;
template <class T> class Graph;

/**
 * @brief Class Vertex used in graph, adapted from the given to us
 * 
 */
template <class T>
class Vertex {
	// contents
	T info;       

	// outgoing edges

	vector<Edge<T> > adj;  

	// auxiliary field
	bool visited;     

	//distance used in short paths algorithms
	double dist = 0; 
	
	//Pointer to the previous vertex in a calculated path
	Vertex<T> *path = nullptr;

	// required by MutablePriorityQueue
	int queueIndex = 0; 		

	//Indicates if the vertex is being processed
	bool processing = false;   

	//Coords read from given map file
	double vertexX, vertexY;  

	//adds an adjacent edge to the vertex
	void addEdge(Vertex<T> *dest, double w);

public:
	/**
	* @brief Constructor - creates a new Vertex
	* @param in Info of the new vertex
	* @param x X coord of the new vertex
	* @param y Y coord of the new vertex
	*
	*/
	Vertex(T in, double x, double y);

	/**
	* @brief quired by MutablePriorityQueue to orden Vertexes
	* @param Vertex being compared to this object
	*
	*/
	bool operator<(Vertex<T> & vertex) const; 

	/**
	* @brief returns the vertex info
	* @return Info of this vertex 
	*/
	T * getInfo();

	/**
	 * @brief return the current distance of this vertex
	 * @return current distance
	 */
	double getDist() const;

	/**
	 * @brief return the atribute path
	 * @return Previous vertex in calculated path
	 * 
	 */
	Vertex *getPath() const;

	/**
	 * @brief returns the adjacent edges of the current vertex
	 * @return Adjacent edges
	 * 
	 */
	vector<Edge<T>> * getAdj() { return &adj; };

	/**
	 * @brief sets the distance of this vertex
	 * @param New distance
	 * 
	 */
	void setDist(double dist) { this->dist = dist; };

	/**
	 * @brief Sets a new value to the atribute path
	 * @param v Pointer to the previous vertex in the calculated path
	 *
	 */
	void setPath(Vertex * v) { this->path = v; };

	/**
	 * @brief Sets the atribute visited
	 * @param visited New value to be set
	 *
	 */
	void setVisited(bool visited) { this->visited = visited; };

	/**
	 * @brief Indicates if the vertex has been visited
	 * @return True if the vertex was previously visited,
	 * False otherwise
	 * 
	 */
	bool getVisited() const { return this->visited; };

	/**
	 * @brief Returns the x Coord of this vertex
	 * @return The current X coord of this vertex
	 * 
	 */
	double getX() const { return this->vertexX; };

	/**
	 * @brief Returns the y Coord of this vertex
	 * @return The current y coord of this vertex
	 * 
	 */
	double getY() const { return this->vertexY; };

	/**
	 * @brief Calculates the euclidean distance between this vertex and the vertex in its parameter
	 * @oaram vertex2 Vertex to which the euclidian distance in being calulated
	 * @return The euclidean distance
	 * 
	 */
	double getEuclideanDist(const Vertex<T> *  vertex2) const;

	/**
	 * @brief Calculates the manattan distance between this vertex and the vertex in its parameter
	 * @oaram vertex2 Vertex to which the manattan distance in being calulated
	 * @return The manattan distance
	 * 
	 */
	double getManhattanDist(const Vertex<T> * vertex2) const;

	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};

template <class T>
Vertex<T>::Vertex(T in, double x, double y): info(in), vertexX(x), vertexY(y) {}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(this, d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T * Vertex<T>::getInfo() {
	return &(this->info);
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

template <class T>
double Vertex<T>::getEuclideanDist(const Vertex<T> *  vertex2) const{
	return sqrt(pow(vertex2->vertexX - this->vertexY, 2) + pow(vertex2->vertexX - this->vertexY, 2));
}

template <class T>
double Vertex<T>::getManhattanDist(const Vertex<T> * vertex2) const{
	return abs(this->vertexX - vertex2->vertexX) + abs(this->vertexY - vertex2->vertexY);
}



#endif
