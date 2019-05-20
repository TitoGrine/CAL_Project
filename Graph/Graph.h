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

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

	double rightBound, leftBound, topBound, bottomBound;	

	double ** W = nullptr;   // dist
	int **P = nullptr;   // path
	int findVertexIdx(const T &in) const;

	priority_queue<Edge<T>> buildHeap();

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in, double x, double y);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05
	Vertex<T> * initSingleSource(const T &orig);

	// Fp05 - single source
	void unweightedShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;
	~Graph();

	// Fp07 - minimum spanning tree
	vector<Vertex<T>*> calculatePrim();
	vector<Vertex<T>*> calculateKruskal();

	double getRightBound() const { return this->rightBound; };
	double getLeftBound() const { return this->leftBound; };
	double getTopBound() const { return this->topBound; };
	double getBottomBound() const { return this->bottomBound; };

	Graph<T> invert();
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
template <class T>
int Graph<T>::findVertexIdx(const T &in) const {
	for (unsigned i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == in)
			return i;
	return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in, double x, double y) {
	// TODO: confiar que ele n tem indices repetidos??
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

// TODO: meter isto direito
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

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
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

/**
 * Initializes single source shortest path data (path, dist).
 * Receives the content of the source vertex and returns a pointer to the source vertex.
 * Used by all single-source shortest path algorithms.
 */
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
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
	vector<T> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->dist == INF) // missing or disconnected
		return res;
	for ( ; v != nullptr; v = v->path)
		res.push_back(v->info);
	reverse(res.begin(), res.end());
	return res;
}

/*
template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	auto s = initSingleSource(orig);
	queue< Vertex<T>* > q;
	q.push(s);
	while( ! q.empty() ) {
		auto v = q.front();
		q.pop();
		for(auto e: v->adj)
			if (relax(v, e.dest, 1))
				q.push(e.dest);
	}
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	initSingleSource(orig);
	for (unsigned i = 1; i < vertexSet.size(); i++)
		for (auto v: vertexSet)
			for (auto e: v->adj)
				relax(v, e.dest, e.weight);
	for (auto v: vertexSet)
		for (auto e: v->adj)
			if (relax(v, e.dest, e.weight))
				cout << "Negative cycle!" << endl;
}
*/

/**************** All Pairs Shortest Path  ***************/

template <class T>
void deleteMatrix(T **m, int n) {
	if (m != nullptr) {
		for (int i = 0; i < n; i++)
			if (m[i] != nullptr)
				delete [] m[i];
		delete [] m;
	}
}

template <class T>
Graph<T>::~Graph() {
	deleteMatrix(W, vertexSet.size());
	deleteMatrix(P, vertexSet.size());
}

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	unsigned n = vertexSet.size();
	deleteMatrix(W, n);
	deleteMatrix(P, n);
	W = new double *[n];
	P = new int *[n];
	for (unsigned i = 0; i < n; i++) {
		W[i] = new double[n];
		P[i] = new int[n];
		for (unsigned j = 0; j < n; j++) {
			W[i][j] = i == j? 0 : INF;
			P[i][j] = -1;
		}
		for (auto e : vertexSet[i]->adj) {
			int j = findVertexIdx(e.dest->info);
			W[i][j]  = e.weight;
			P[i][j]  = i;
		}
	}

	for(unsigned k = 0; k < n; k++)
		for(unsigned i = 0; i < n; i++)
			for(unsigned j = 0; j < n; j++) {
				if(W[i][k] == INF || W[k][j] == INF)
					continue; // avoid overflow
				int val = W[i][k] + W[k][j];
				if (val < W[i][j]) {
					W[i][j] = val;
					P[i][j] = P[k][j];
				}
			}
}


template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	int i = findVertexIdx(orig);
	int j = findVertexIdx(dest);
	if (i == -1 || j == -1 || W[i][j] == INF) // missing or disconnected
		return res;
	for ( ; j != -1; j = P[i][j])
		res.push_back(vertexSet[j]->info);
	reverse(res.begin(), res.end());
	return res;
}

/**************** Minimum Spanning Tree  ***************/

template <class T>
vector<Vertex<T>* > Graph<T>::calculatePrim() {
	for(auto v : vertexSet) {
		v->dist = INF;
		v->path = nullptr;
		v->visited = false;
	}
	auto s = vertexSet.at(0);
	s->dist = 0;
	MutablePriorityQueue<Vertex<T>> q;
	q.insert(s);
	while( ! q.empty() ) {
		auto v = q.extractMin();
		v->visited = true;
		for(auto e : v->adj) {
			if(!e.dest->visited){
				auto oldDist = e.dest->dist;
				if (e.dest->dist > e.weight){
					e.dest->dist = e.weight;
					e.dest->path = v;
					if (oldDist == INF)
						q.insert(e.dest);
					else
						q.decreaseKey(e.dest);
				}
			}
		}
	}
	return vertexSet;
}

template <class T>
priority_queue<Edge<T>> Graph<T>::buildHeap(){
	priority_queue<Edge<T>> heap;
	for(auto v : vertexSet){
		for(auto edge : v->adj)
			heap.push(edge);
	}
	return heap;
}

template <class T>
int findDisjSet(vector<vector<Vertex<T> *>> & vectorDisjSet, Vertex<T> * ver){
	for(size_t i = 0; i < vectorDisjSet.size(); i++)
		if(find(vectorDisjSet.at(i).begin(), vectorDisjSet.at(i).end(), ver) != vectorDisjSet.at(i).end())
			return i;
	return -1;
}

template <class T>
void uniteDisjSet(vector<vector<Vertex<T> *>> & vectorDisjSet, int disj1, int disj2){
	vectorDisjSet.at(disj1).insert(vectorDisjSet.at(disj1).end(), vectorDisjSet.at(disj2).begin(), vectorDisjSet.at(disj2).end());
	vectorDisjSet.erase(vectorDisjSet.begin() + disj2);
}

template <class T>
vector<Vertex<T>*> Graph<T>::calculateKruskal() {
	int edgesAccepted = 0;

	priority_queue<Edge<T>> h = buildHeap();
	
	vector<vector<Vertex<T> *>> vectorDisjSet;
	int i = 0;
	for(auto v: vertexSet){
		vector<Vertex<T> * > DisjSet = {v};
		vectorDisjSet.push_back(DisjSet);
	}

	while(edgesAccepted < getNumVertex()-1) {
		Edge<T> e = h.top();
		h.pop();
		int oriDisjSet = findDisjSet(vectorDisjSet, e.orig);
		int destDisjSet = findDisjSet(vectorDisjSet, e.dest);

		if(oriDisjSet != destDisjSet && e.dest->path == NULL) {
			// cout << e.getWeight() <<  " (" << e.orig->info << "->" << e.dest->info << ") ";
			e.dest->path = e.orig;
			edgesAccepted++;
			uniteDisjSet(vectorDisjSet, oriDisjSet, destDisjSet);
		}		
	}
	cout << endl;
	cout << vectorDisjSet.size() << endl;
	/*
	for(auto v: vectorDisjSet.at(0)){
		cout << v->info << "<-";
		if(v->path != NULL)
			cout << v->path->info;
		cout << "|";		
	}
	cout << endl;
	*/
	return vertexSet;
}


#endif /* GRAPH_H_ */
