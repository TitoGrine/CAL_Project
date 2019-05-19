#pragma once

#include "Graph.h"
#include "../Utilities/debugGraph.h"
#include "../Utilities/mingw.thread.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <thread>

template <class T>
std::vector<Vertex<T> *> dfs(Graph<T> * graph, Vertex<T> * initial);

template <class T>
std::vector<Vertex<T> *> scc(Graph<T> * graph, Vertex<T> * initial, bool bidirectional);

template <class T>
std::vector<T> dijkstraShortestPath(Graph<T> * graph, const T &origin, const T &dest);

template <class T>
std::vector<T> aStarShortestPath(Graph<T> * graph, const T &origin, const T &dest);

template <class T>
std::vector<T> FloydWarshallShortestPath(Graph<T> * graph, const T &origin, const T &dest); 

template <class T>
std::vector<T> NearestNeighbor(Graph<T> * graph, const T &origin, const vector<T> deliveries);

template <class T>
std::vector<T> bidirectionalDijkstra(Graph<T> * graph, const T &origin, const T &delivery, const T &dest);

template <class T>
std::vector<T> bidirectionalAStar(Graph<T> * graph, const T &origin, const T &delivery, const T &dest);

/* ------------------------------------------------------------------------------------------------ */
template <class T>
void dfsVisit(Vertex<T> *v, std::vector<Vertex<T> *> & res);

template <class T>
bool containsVertex(std::vector<Vertex<T> *> vectorVert, Vertex<T> * vert);

/* ------------------------------------------------------------------------------------------------ */

template <class T>
void dfsVisit(Vertex<T> *v, std::vector<Vertex<T> *> & res) {
	v->setVisited(true);
	res.push_back(v);
	for(unsigned int i = 0; i < v->getAdj()->size(); i++)
		if(!v->getAdj()->at(i).getDest()->getVisited())
			dfsVisit(v->getAdj()->at(i).getDest(), res);
}

template <class T>
std::vector<Vertex<T> *> dfs(Graph<T> * graph, Vertex<T> * initial) {
	std::vector<Vertex<T> *> res;
	for(auto vertex: graph->getVertexSet())
		vertex->setVisited(false);
	dfsVisit(initial, res);
	return res;
}

template <class T>
bool containsVertex(std::vector<Vertex<T> *> vectorVert, Vertex<T> * vert){
	for(auto v : vectorVert)
		if(vert->getInfo() == v->getInfo())
			return true;
	return false;
}


template <class T>
std::vector<Vertex<T> *> scc(Graph<T> * graph, Vertex<T> * initial, bool bidirectional){

	vector<Vertex<T> *> res_normal = dfs(graph, initial);

	if(bidirectional)
		return res_normal;

	// TODO: mudar para não alterar proprio grafo
	Graph<T> invertedGraph = graph->invert();

	// TODO: optimize em vez de reaproveitar funcao
	Vertex<T> * invInitial = invertedGraph.findVertex( *(initial->getInfo()));

	vector<Vertex<T> *> res_invert = dfs(&invertedGraph, invInitial);

	
	vector<Vertex<T> *> res;
	for(auto v: res_normal)
		if(containsVertex(res, v))
			res.push_back(v);

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


template <class T>
std::vector<T> bidirectionalDijkstra(Graph<T> * graph, const T &origin, const T &delivery, const T &dest)
{

    vector<T> final_path, path;

	thread t1(dijkstraShortestPath, graph, origin, delivery);
	thread t2(dijkstraShortestPath, graph, delivery, dest);
	
	t1.join();
	t2.join();

	final_path = graph->getPath(origin, delivery);
	path = graph->getPath(delivery, origin);

	final_path.insert(final_path.end(), path.begin(), path.end());

	return final_path;
}

template <class T>
std::vector<T> bidirectionalAStar(Graph<T> * graph, const T &origin, const T &delivery, const T &dest)
{
    vector<T> final_path, path;

	thread t1(aStarShortestPath, graph, origin, delivery);
	thread t2(aStarShortestPath, graph, delivery, dest);
	
	t1.join();
	t2.join();

	final_path = graph->getPath(origin, delivery);
	path = graph->getPath(delivery, origin);

	final_path.insert(final_path.end(), path.begin(), path.end());

	return final_path;
}

template <class T>
std::vector<T> FloydWarshallShortestPath(Graph<T> * graph, const T &origin, const T &dest) {
	unsigned n = graph->getVertexSet().size();

	graph->resetMatrixW(n);
	graph->resetMatrixP(n);
	
	for (unsigned i = 0; i < n; i++) {
		for (unsigned j = 0; j < n; j++) {
			graph->setW(i, j, i == j? 0 : INF);
			graph->setP(i, j, -1);
		}
		for (auto e : graph->getVertexSet().at(i)->adj) {
			int j = graph->findVertexIdx(e.dest->info);
			graph->setW(i, j, e.weight);
			graph->setP(i, j, i);
		}
	}

	for(unsigned k = 0; k < n; k++)
		for(unsigned i = 0; i < n; i++)
			for(unsigned j = 0; j < n; j++) {
				if(graph->getW(i, k) == INF || graph->getW(k, j) == INF)
					continue; // avoid overflow
				int val = graph->getW(i, k) + graph->getW(k, j);
				if (val < graph->getW(i, j)) {
					graph->setW(i, j, val);
					graph->setP(i, j, graph->getP(k, j));
				}
			}
}

template <class T>
std::vector<T> NearestNeighbor(Graph<T> * graph, const T &origin, const vector<T> deliveries){

	vector<T> result;
	Vertex<T>* start = graph->findVertex(origin);

	for(auto vertex : graph->getVertexSet()){
		vertex->setDist(start->getEuclideanDist(vertex));
	}

	MutablePriorityQueue<Vertex<T>*> Q;
	MutablePriorityQueue<Vertex<T>*> aux;

	for(T info : deliveries){
		Q.insert(graph->findVertex(info));
	}

	while(!Q.empty()) {
		Vertex<T>* vertex = Q.extractMin();

		result.push_back(vertex->getInfo());

		aux = Q;

		while(!aux.empty()){
			Vertex<T>* v = aux.extractMin();
			v->setDist(vertex->getEuclideanDist(v));
		}
	}

	return result;
}
