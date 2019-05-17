#include "Algorithm.h"

#include <iostream>
#include <fstream>

using namespace std;

/*
vector<Vertex<T> *> dfs(Graph * graph) {
	vector<Vertex<T> *> res;
	for(auto vertex: graph->getVertexSet())
		vertex->setVisited(false);
	for(auto vertex: graph->getVertexSet())
		if(!vertex->getVisited())
			dfsVisit(vertex, res);
	return res;
}
*/

template <class T>
static void dfsVisit(Vertex<T> *v, vector<Vertex<T> *> & res) {
	v->setVisited(true);
	res.push_back(v);
	for(unsigned int i = 0; i < v->getAdj()->size(); i++)
		if(!v->getAdj()->at(i).getDest()->getVisited())
			dfsVisit(v->getAdj()->at(i).getDest(), res);
}

template <class T>
vector<Vertex<T> *> dfs(Graph<T> * graph, Vertex<T> * initial) {
	vector<Vertex<T> *> res;
	for(auto vertex: graph->getVertexSet())
		vertex->setVisited(false);
	dfsVisit(initial, res);
	return res;
}

template <class T>
static void printVertex(vector<Vertex<T> *> verts, ostream & output){
	for(auto v: verts)
		output << v->getInfo() << " ; ";
	output << endl;
}

template <class T>
static void prinntEdgesDest(vector<Edge<T>> * edges){
	for(unsigned int i = 0; i < edges->size(); i++)
		cout << edges->at(i).getDest()->getInfo() << " ; ";
	cout << endl;
}

template <class T>
bool containsVertex(vector<Vertex<T> *> vectorVert, Vertex<T> * vert){
	for(auto v : vectorVert)
		if(vert->getInfo == v->getInfo())
			return true;
	return false;
}

template <class T>
vector<Vertex<T> *> scc(Graph<T> * graph, Vertex<T> * initial){
	ofstream out;
	out.open("teste.txt");
	vector<Vertex<T> *> res_normal = dfs(graph, initial);
	printVertex(res_normal, out);
	// TODO: mudar para não alterar proprio grafo
	Graph<T> invertedGraph = graph->invert();

	// TODO: optimize em vez de reaproveitar funcao
	Vertex<T> * invInitial = invertedGraph.findVertex(initial->getInfo());

	vector<Vertex<T> *> res_invert = dfs(&invertedGraph, invInitial);

	printVertex(res_invert, out);
	
	vector<Vertex<T> *> res;
	for(auto v: res_normal)
		if(containsVertex(res, v))
			res.push_back(v);

	printVertex(res, out);
	out.close();
	return res;
}

/**
 * Analyzes an edge in single source shortest path algorithm.
 * Returns true if the target vertex was relaxed (dist, path).
 * Used by all single-source shortest path algorithms.
 */
template <class T>
inline bool relax(Vertex<T> *v, Vertex<T> *w, double weight) {
	if (v->getDist() + weight < w->getDist()) {
		w->setDist(v->getDist() + weight);
		w->setPath(v);
		return true;
	}
	else
		return false;
}

template <class T>
void dijkstraShortestPath(Graph<T> * graph, const T &origin) {
	auto s = graph->initSingleSource(origin);
	MutablePriorityQueue<Vertex<T>> q;
	q.insert(s);
	while( ! q.empty() ) {
		auto v = q.extractMin();
		for(unsigned int i = 0; i < v->getAdj()->size(); i++) {
			auto e = v->getAdj()->at(i);
			auto oldDist = e.getDest()->getDist();
			if (relax(v, e.getDest(), e.getWeight())) {
				if (oldDist == INF)
					q.insert(e.getDest());
				else
					q.decreaseKey(e.getDest());
			}
		}
	}
}
