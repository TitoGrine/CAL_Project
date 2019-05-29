/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>

#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include "Vertex.h"
 #include "Edge.h"

template <class T> class Edge;
template <class T> class Vertex;
template <class T> class Graph;

#define INF std::numeric_limits<double>::max()


/*************************** Graph  **************************/

/**
 * @brief Class graph used to store vertexex and edges, and aplly methods to the stored values.
 * Adapted from the class given to us.
 * 
 */
template <class T>
class Graph {
	// Set of the vertexed that compose this graph
	vector<Vertex<T> *> vertexSet;    

	//Bounds of the graph
	double rightBound, leftBound, topBound, bottomBound;	

	// Matrix of distances between vertex, used in Floyd-Warshall Algorithm
	vector<vector<double>>  W;   

	// Matrix of paths between vertex, used in Floyd-Warshall Algorithm
	vector<vector<int>> P;   

	// Used in some methods
	priority_queue<Edge<T>> buildHeap();

public:
	/**
	 * @brief Finds the index in the vertex set of the vertex with the info received in the parameter
	 * @param in Info of the vertex 
	 * @return Index in the verex set of the vertex
	 * 
	 */
	int findVertexIdx(const T &in) const;
	
	/**
	 * @brief Finds the vertex in the vertex with the info received in the parameter
	 * @param in Info of the vertex
	 * @return Pointer to the vertes
	 * 
	 */
	Vertex<T> *findVertex(const T &in) const;

	/**
	 * @brief Adds a new Vertex to the vertex set
	 * @param in Info of the vertex
	 * @param x X Coord of the vertex
	 * @param y Y Coord of the vertex
	 * @return True if the addition was successful, 
	 * False otherwise
	 * 
	 */
	bool addVertex(const T &in, double x, double y);
	
	/**
	 * @brief Adds a new Edge to the graph
	 * @param sourc Info of the source vertex of the edge
	 * @param dest Info of the destination vertex of the edge
	 * @param w Weight of the edge
	 * @return True if the addition was successful, 
	 * False otherwise
	 * 
	 */
	bool addEdge(const T &sourc, const T &dest, double w);

	/**
	 * @brief Return the current size of the vertex set
	 * @return Size of the vertex set
	 * 
	 */
	int getNumVertex() const;
	
	/**
	 * @brief Return the current vertex set
	 * @return The vertex set
	 * 
	 */
	vector<Vertex<T> *> getVertexSet() const;

	/**
	 * @brief Returns the distance in the vertex matrix between vertex width indexes i and j
	 * @param i Index in the vertex matrix of the source vertex
	 * @param j Index in the vertex matrix of the destination vertex
	 * @return Distance between the vertexes
	 * 
	 */
	double getW(int i, int j) const;

	/**
	 * @brief Sets the distance in the vertex matrix between the vertex with indexes i and j
	 * @param i Index in the vertex matrix of the source vertex
	 * @param j Index in the vertex matrix of the destination vertex
	 * @param value Distance between the two vertexes
	 * 
	 */
	void setW(int i, int j, double value);
	
	/**
	 * @brief Returns the index of the following vertex in the shortest path between i and j	 
	 * @param i Index in the path matrix of the source vertex
	 * @param j Index in the path matrix of the destination vertex 
	 * @return Index of the following vertex in the shortest path between in and j
	 * 
	 */
	int getP(int i, int j) const;

	/**
	 * @brief Sets the index of the following vertex in the shortest path between i and j	 
	 * @param i Index in the path matrix of the source vertex
	 * @param j Index in the path matrix of the destination vertex 
	 * @param index of the following vertex in the shortest path between in and j
	 * 
	 */
	void setP(int i, int j, int index);

	/**
	 * @brief Initializes single source shortest path data (path, dist).
 	 * Receives the content of the source vertex and returns a pointer to the source vertex.
 	 * Used by all single-source shortest path algorithms.
	 * @param orig Origin vertex info
	 * @return Pointer to the origin vertex in the vertex set
	 * 
	 */
	Vertex<T> * initSingleSource(const T &orig);

	/**
	 * @brief Return the previously calculated path between two vertexes
	 * @param origin Info of the origin vertex
	 * @param dest Info of the destination vertex
	 * @return Path between the two vertexes
	 * 
	 */
	vector<Vertex<T> *> getPath(const T &origin, const T &dest) const;

	/**
	 * @brief Return the previously Floyd-Warshall calculated path between two vertexes
	 * @param origin Info of the origin vertex
	 * @param dest Info of the destination vertex
	 * @return Path between the two vertexes
	 * 
	 */
	vector<T> getFloydWarshallPath(const T &origin, const T &dest) const;

	/**
	 * @brief Returns the weight of the edge that connecets the two vertexes with indexes i and j in the vertex set
	 * @param i Index of the source vertex in the vertex set
	 * @param j Index of the destination vertex in the vertex set
	 * @return Wight of the edge
	 * 
	 */
	double edgeWeight(int i, int j);
	
	/**
	 * @brief Return the next vertex on the shortest path between i and j
	 * @param i Index of the source vertex in the path matrix
	 * @param j Index of the detination vertex in the path matrix
	 * @return Return j if it is adjacent to i, otherwise returns -1
	 */
	int nextVertex(int i, int j);

	/**
	 * @brief Resets the matrix of distances
	 * @param n Size of the matrix
	 * 
	 */
	void resetMatrixW(int n);
	
	/**
	 * @brief Resets the matrix of paths
	 * @param n Size of the matrix
	 * 
	 */
	void resetMatrixP(int n);

	/**
	 * @brief Deletes this graph, freeing all previously allocated memory
	 * 
	 */
	~Graph();
	
	/**
	 * @brief Return the Right bound of this graph
	 * @return Right bound
	 */
	double getRightBound() const { return this->rightBound; };

	/**
	 * @brief Return the left bound of this graph
	 * @return left bound
	 */
	double getLeftBound() const { return this->leftBound; };

	/**
	 * @brief Return the top bound of this graph
	 * @return top bound
	 */
	double getTopBound() const { return this->topBound; };

	/**
	 * @brief Return the bottom bound of this graph
	 * @return bottom bound
	 */
	double getBottomBound() const { return this->bottomBound; };

	/**
	 * @brief Inverts this graph
	 * @return Inverted graph
	 * 
	 */
	Graph<T> invert();
	
	/**
	 * @brief Creates a copy of this graph
	 * @return Copy of this graph
	 * 
	 */
	Graph<T> duplicate();
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
double Graph<T>::getW(int i, int j) const{
	return W.at(i).at(j);
}

template <class T>
void Graph<T>::setW(int i, int j, double value){
	W.at(i).at(j) = value;
}

template <class T>
int Graph<T>::getP(int i, int j) const{
	return P.at(i).at(j);
}

template <class T>
void Graph<T>::setP(int i, int j, int index){
	P.at(i).at(j) = index;
}

template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return nullptr;
}

template <class T>
int Graph<T>::findVertexIdx(const T &in) const {
	for (unsigned i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == in)
			return i;
	return -1;
}

template <class T>
bool Graph<T>::addVertex(const T &in, double x, double y) {
	if (findVertex(in) != nullptr)
		return false;

	if(vertexSet.size() == 0){
		this->rightBound = x;		
		this->leftBound = x;
		this->topBound = y;
		this->bottomBound = y;
	}
	else{
		if (x > this->rightBound) 
			this->rightBound = x;
		else if(this->leftBound > x)
			this->leftBound = x;
		if(y > this->topBound)
			this->topBound = y;
		else if(this->bottomBound > y)
			this->bottomBound = y;
	}
	
	vertexSet.push_back(new Vertex<T>(in, x, y));
	return true;
}

template <class T>
Graph<T> Graph<T>::invert(){
	Graph<T> newGraph = Graph();
	for(auto v: this->vertexSet)
		newGraph.addVertex( *(v->getInfo()), v->getX(), v->getY());
	
	for(auto v: this->vertexSet)
		for(size_t j = 0; j < v->getAdj()->size(); j++)
			newGraph.addEdge( *(v->getAdj()->at(j).getDest()->getInfo()), *(v->getAdj()->at(j).getOrig()->getInfo()), v->getAdj()->at(j).getWeight());
	return newGraph;
}


template <class T>
Graph<T> Graph<T>::duplicate(){
	Graph<T> newGraph = Graph();
	for(auto v: this->vertexSet)
		newGraph.addVertex( *(v->getInfo()), v->getX(), v->getY());
	
	for(auto v: this->vertexSet)
		for(size_t j = 0; j < v->getAdj()->size(); j++)
			newGraph.addEdge( *(v->getAdj()->at(j).getOrig()->getInfo()), *(v->getAdj()->at(j).getDest()->getInfo()), v->getAdj()->at(j).getWeight());
	return newGraph;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == nullptr || v2 == nullptr)
		return false;
	v1->addEdge(v2, w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/
template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origin) {
	for(auto v : vertexSet) {
		v->dist = INF;
		v->path = nullptr;
	}
	auto s = findVertex(origin);
	s->dist = 0;
	return s;
}


template<class T>
vector<Vertex<T> *> Graph<T>::getPath(const T &origin, const T &dest) const{
	vector<Vertex<T> *> res;
	auto o = findVertex(origin);
	auto v = findVertex(dest);
	if (v == nullptr || v->dist == INF) // missing or disconnected
		return res;
	for ( ; v != o && v != nullptr; v = v->path)
		res.push_back(v);
	res.push_back(o);
	reverse(res.begin(), res.end());

	return res;
}

/**************** All Pairs Shortest Path  ***************/

template <class T>
double Graph<T>::edgeWeight(int i, int j){
	if(i == j) return 0;

	for(Edge<T> edge : *(vertexSet.at(i)->getAdj())){
		if(edge.dest == vertexSet.at(j))
			return edge.getWeight();
	}

	return INF;
}

template <class T>
int Graph<T>::nextVertex(int i, int j){
	for(Edge<T> edge : *(vertexSet.at(i)->getAdj())){
		if(edge.dest == vertexSet.at(j))
			return j;
	}

	return -1;
}

template <class T>
void Graph<T>::resetMatrixW(int n) {
	W = vector<vector<double>> (n, vector<double> (n));
}

template <class T>
void Graph<T>::resetMatrixP(int n) {
	P = vector<vector<int>> (n, vector<int> (n));
}

template <class T>
Graph<T>::~Graph() {
	W.erase(W.begin(), W.end());
	P.erase(P.begin(), P.end());
}

template<class T>
vector<T> Graph<T>::getFloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	int i = findVertexIdx(orig);
	int j = findVertexIdx(dest);
	cout << "Initial point: " << i << endl;
	cout << "Final point: " << j << endl;
	if (i == -1 || j == -1 || getW(i, j) == INF)  // missing or disconnected
		return res;
	
	res.push_back(vertexSet[i]->info);

	while(i != j){
		i = getP(i, j);

		if(i < 0)
			break;
		
		res.push_back(vertexSet[i]->info);
	}

	return res;
}


#endif /* GRAPH_H_ */
