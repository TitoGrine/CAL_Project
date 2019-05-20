#pragma once

#include "Graph.h"
#include "../Utilities/debugGraph.h"
#include "../Utilities/mingw.thread.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <thread>

// #include "../GraphViewer/graphviewer.h"

template <class T>
std::vector<Vertex<T> *> dfs(Graph<T> * graph, Vertex<T> * initial);

template <class T>
std::vector<Vertex<T> *> scc(Graph<T> * graph, Vertex<T> * initial, bool bidirectional);

template <class T>
Graph<T> shrinkGraph(Graph<T> * mainGraph, Vertex<T> * initial, Vertex<T> * last, bool bidirectional);

template <class T>
std::vector<T> dijkstraShortestPath(Graph<T> * graph, const T &origin, const T &dest);

template <class T>
std::vector<T> aStarShortestPath(Graph<T> * graph, const T &origin, const T &dest);

template <class T>
void FloydWarshallShortestPath(Graph<T> * graph); 

template <class T>
std::vector<Vertex<T> *> NearestNeighborEuclidean(Graph<T> * graph, const T &origin, const vector<T> deliveries, const T &dest);

template <class T>
std::vector<Vertex<T> *> NearestNeighborFloyd(Graph<T> * graph, const T &origin, const vector<T> deliveries, const T &dest);

template <class T>
std::vector<T> bidirectionalDijkstra(Graph<T> * graph, const T &origin, const T &delivery, const T &dest, bool bidirectional);

template <class T>
std::vector<T> bidirectionalAStar(Graph<T> * graph, const T &origin, const T &delivery, const T &dest, bool bidirectional);

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
		if( *(vert->getInfo()) == *(v->getInfo()))
			return true;
	return false;
}


template <class T>
std::vector<Vertex<T> *> scc(Graph<T> * graph, Vertex<T> * initial, bool bidirectional){
	// ofstream out;
	// out.open("teste.txt");

	vector<Vertex<T> *> res_normal = dfs(graph, initial);

	// printVertex(res_normal, out);

	if(bidirectional)
		return res_normal;

	// TODO: mudar para não alterar proprio grafo
	Graph<T> invertedGraph = graph->invert();

	// TODO: optimize em vez de reaproveitar funcao
	Vertex<T> * invInitial = invertedGraph.findVertex( *(initial->getInfo()));

	vector<Vertex<T> *> res_invert = dfs(&invertedGraph, invInitial);

	// printVertex(res_invert, out);

	vector<Vertex<T> *> res;
	for(auto v: res_normal){
		if(containsVertex(res_invert, v))
			res.push_back(v);
	}

	
	// printVertex(res, out);
	// out.close();

	// GraphViewer * gv = createVertexGraphViewer(graph, 4, "GRAY");
	// paintVertexesGV(gv, 10, "GREEN", res_invert);
	// paintVertexesGV(gv, 10, "RED", res_normal);
	// gv->rearrange();
	// getchar();
	// gv->closeWindow();

	return res;
}

template <class T>
Graph<T> shrinkGraph(Graph<T> * mainGraph, Vertex<T> * initial, Vertex<T> * last, bool bidirectional){
	Graph<T> shrunkGraph;
	vector<Vertex<T> *> remainingVertexes = scc(mainGraph, initial, bidirectional);
	if(!containsVertex(remainingVertexes, last))
		throw logic_error("Last vertex is not in the same SCC");

	for(Vertex<T> * rV : remainingVertexes)
		shrunkGraph.addVertex(*(rV->getInfo()), rV->getX(), rV->getY());
	
	for(Vertex<T> * rV : remainingVertexes)
		for(auto eAdj : *(rV->getAdj()))
			shrunkGraph.addEdge(*(rV->getInfo()), *(eAdj.getDest()->getInfo()), eAdj.getWeight());

	return shrunkGraph;
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
	std::vector<T> result;
	auto s = graph->initSingleSource(origin);
	Vertex<T>* d = graph->findVertex(dest);
	MutablePriorityQueue<Vertex<T>> q;
	q.insert(s);

	while( ! q.empty() ) {
		auto v = q.extractMin();

		if(v == d) {
			result = graph->getPath(origin, dest);
			break;
		}
			
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

	return result;
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
std::vector<T> bidirectionalDijkstra(Graph<T> * graph, const T &origin, const T &delivery, const T &dest, bool bidirectional)
{
    vector<T> final_path, path;

	thread t1(dijkstraShortestPath<T>, graph, origin, delivery);
	
	if(bidirectional){
		thread t2(dijkstraShortestPath<T>, graph, delivery, dest);

		t1.join();
		t2.join();

		final_path = graph->getPath(origin, delivery);
		path = graph->getPath(delivery, dest);

		final_path.insert(final_path.end(), path.begin(), path.end());
	}
	else{ 
		Graph<T> invertedGraph = graph->invert();
		thread t2(dijkstraShortestPath<T>, &invertedGraph, dest, delivery);

		t1.join();
		t2.join();

		final_path = graph->getPath(origin, delivery);
		path = invertedGraph.getPath(dest, delivery);

		// TODO: verify
		final_path.insert(final_path.end(), path.rbegin(), path.rend());
	}

	return final_path;
}

template <class T>
std::vector<T> bidirectionalAStar(Graph<T> * graph, const T &origin, const T &delivery, const T &dest, bool bidirectional)
{
    vector<T> final_path, path;

	thread t1(aStarShortestPath<T>, graph, origin, delivery);
	
	if(bidirectional){
		thread t2(aStarShortestPath<T>, graph, delivery, dest);

		t1.join();
		t2.join();

		final_path = graph->getPath(origin, delivery);
		path = graph->getPath(delivery, dest);

		final_path.insert(final_path.end(), path.begin(), path.end());
	}
	else{ 
		Graph<T> invertedGraph = graph->invert();
		thread t2(aStarShortestPath<T>, &invertedGraph, dest, delivery);

		t1.join();
		t2.join();

		final_path = graph->getPath(origin, delivery);
		path = invertedGraph.getPath(dest, delivery);

		// TODO: verify
		final_path.insert(final_path.end(), path.rbegin(), path.rend());
	}

	return final_path;
}

template <class T>
void FloydWarshallShortestPath(Graph<T> * graph) {
	unsigned n = graph->getVertexSet().size();

	graph->resetMatrixW(n);
	graph->resetMatrixP(n);
	
	for (unsigned i = 0; i < n; i++) {
		for (unsigned j = 0; j < n; j++) {
			graph->setW(i, j, i == j? 0 : INF);
			graph->setP(i, j, -1);
		}
		for (Edge<T> e : *(graph->getVertexSet().at(i)->getAdj())) {
			int j = graph->findVertexIdx(*e.getDest()->getInfo());
			graph->setW(i, j, e.getWeight());
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
std::vector<Vertex<T> *> NearestNeighborEuclidean(Graph<T> * graph, const T &origin, const vector<T> deliveries, const T &dest){

	vector<Vertex<T> *>result;
	Vertex<T>* start = graph->findVertex(origin);

	for(Vertex<T>* vertex : graph->getVertexSet()){
		vertex->setDist(start->getEuclideanDist(vertex));
	}

	MutablePriorityQueue<Vertex<T>> Q;
	MutablePriorityQueue<Vertex<T>> aux;

	for(T info : deliveries){
		Q.insert(graph->findVertex(info));
	}

	result.push_back(graph->findVertex(origin));

	while(!Q.empty()) {
		Vertex<T>* vertex = Q.extractMin();

		vector<T> path = graph->getPath(*(result.back()->getInfo()), *(vertex->getInfo()));
		for(unsigned i = 0; i < path.size(); i++ ){
			result.push_back(graph->findVertex(path.at(i)));
		}

		result.push_back(vertex);

		aux = Q;

		while(!aux.empty()){
			Vertex<T>* v = aux.extractMin();
			v->setDist(vertex->getEuclideanDist(v));
		}
	}

	vector<T> path = graph->getPath(*(result.back()->getInfo()), dest);
		for(unsigned i = 0; i < path.size(); i++ ){
			result.push_back(graph->findVertex(path.at(i)));
		}

	result.erase(result.begin());

	return result;
}

template <class T>
std::vector<Vertex<T> *> NearestNeighborFloyd(Graph<T> * graph, const T &origin, const vector<T> deliveries, const T &dest){

	FloydWarshallShortestPath(graph);

	vector<Vertex<T> *> result;
	int inicial = graph->findVertexIdx(origin);

	for(T info : deliveries){
		Vertex<T>* vertex = graph->findVertex(info);
		vertex->setDist(graph->getW(inicial, graph->findVertexIdx(info)));
	}

	MutablePriorityQueue<Vertex<T>> Q;
	MutablePriorityQueue<Vertex<T>> aux;

	for(T info : deliveries){
		Q.insert(graph->findVertex(info));
	}

	result.push_back(graph->findVertex(origin));

	while(!Q.empty()) {
		Vertex<T>* vertex = Q.extractMin();

		vector<T> path = graph->getFloydWarshallPath(*(result.back()->getInfo()), *(vertex->getInfo()));
		for(unsigned i = 0; i < path.size(); i++ ){
			result.push_back(graph->findVertex(path.at(i)));
		}

		result.push_back(vertex); // Not sure if it's not already inlcuded in the FWPath

		aux = Q;

		while(!aux.empty()){
			Vertex<T>* v = aux.extractMin();
			v->setDist(graph->getW(graph->findVertexIdx(*(vertex->getInfo())), graph->findVertexIdx(*(v->getInfo()))));
		}
	}
	
	vector<T> path = graph->getFloydWarshallPath(*(result.back()->getInfo()), dest);
	for(unsigned i = 0; i < path.size(); i++ ){
			result.push_back(graph->findVertex(path.at(i)));
	}

	result.erase(result.begin());

	return result;
}

