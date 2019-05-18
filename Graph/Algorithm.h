#pragma once

#include "Graph.h"
#include "../Utilities/debugGraph.h"
#include <iostream>
#include <ostream>
#include <fstream>

template <class T>
std::vector<Vertex<T> *> dfs(Graph<T> * graph, Vertex<T> * initial);

template <class T>
std::vector<Vertex<T> *> scc(Graph<T> * graph, Vertex<T> * initial);

template <class T>
std::vector<T> dijkstraShortestPath(Graph<T> * graph, const T &origin, const T &dest);

template <class T>
std::vector<T> aStarShortestPath(Graph<T> * graph, const T &origin, const T &dest);

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
static bool containsVertex(vector<Vertex<T> *> vectorVert, Vertex<T> * vert){
	for(auto v : vectorVert)
		if(vert->getInfo() == v->getInfo())
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
 * Used by Dijkstra and A* shortest path algorithms.
 */

template <class T>
inline bool dijkstraRelax(Vertex<T> *v, Vertex<T> *w, double weight) {
	if (v->getDist() + weight < w->getDist()) {
		w->setDist(v->getDist() + weight);
		w->setPath(v);
		return true;
	}
	else
		return false;
}

template <class T>
inline bool aStarRelax(Vertex<T> *v, Vertex<T> *w, Vertex<T> *dest, double weight) {
	double heuristicDistance = v->getDist() - v->getEuclideanDist(dest) + weight + w->getEuclideanDist(dest);
	if (w->getDist() > heuristicDistance) {
		w->setDist(heuristicDistance);
		w->setPath(v); 
		return true;
	}
	else
		return false;
}

template <class T>
inline bool relax(Vertex<T> *v, Vertex<T> *w, Vertex<T> *dest, double weight, bool isDijkstra) 
{
	if(isDijkstra) return dijkstraRelax(v, w, weight);
	return aStarRelax(v, w, dest, weight);
}

template <class T>
static std::vector<T> shortestPath(Graph<T> * graph, const T &origin, const T &dest, bool isDijkstra)
{
	auto s = graph->initSingleSource(origin);
	Vertex<T>* d = graph->findVertex(dest);
	MutablePriorityQueue<Vertex<T>> q;
	q.insert(s);

	while( ! q.empty() ) {
		auto v = q.extractMin();

		if(v == d) return graph->getPath(origin, dest);
			
		for(unsigned int i = 0; i < v->getAdj()->size(); i++) {
			auto e = v->getAdj()->at(i);
			auto oldDist = e.getDest()->getDist();
			if (relax(v, e.getDest(), d, e.getWeight(), isDijkstra)) {
				if (oldDist == INF)
					q.insert(e.getDest());
				else
					q.decreaseKey(e.getDest());
			}
		}
	}
}

template <class T>
std::vector<T> dijkstraShortestPath(Graph<T> * graph, const T &origin, const T &dest)
{
	return shortestPath(graph, origin, dest, true);
}

template <class T>
std::vector<T> aStarShortestPath(Graph<T> * graph, const T &origin, const T &dest)
{
	return shortestPath(graph, origin, dest, false);
}