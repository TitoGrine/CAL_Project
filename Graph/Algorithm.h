#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "Graph.h"
#include "../Utilities/debugGraph.h"
#include "../Utilities/mingw.thread.h"
#include "../Utilities/Delivery.h"
#include "../Utilities/MapInfo.h"
#include "../Utilities/timeLog.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <thread>

// #include "../GraphViewer/graphviewer.h"

/**
 * @brief Auxilary function of Depth First Search algorithm. Called recursively, 
 * checking if the connected vertexes of vertex v have been visited. If so, calls 
 * it self again using the adjacent vertex, if not continues.
 * 
 * @param v 		Vertex to be searched
 * @param res 		Vector holding the visited vertexes so far by the DFS
 */
template <class T>
void dfsVisit(Vertex<T> *v, std::vector<Vertex<T> *> & res);

/**
 * @brief Calculates the Depth First Search of the vertex inicial in the Graph graph.
 * Uses the auxilary funtion dfsVisit().
 * 
 * @param graph 	Graph containig at least the initial vertex
 * @param initial 	Starting vertex of DFS
 * @return std::vector<Vertex<T> *> Returns the corresponding DFS in order
 */
template <class T>
std::vector<Vertex<T> *> dfs(Graph<T> * graph, Vertex<T> * initial);

/**
 * @brief Calculates the Strong Connected Component of graph that includes the vertex 
 * initial. Works for both directed and undirected graphs.
 * 
 * @param graph 			Graph containig at least the initial vertex
 * @param initial 			Starting vertex contained in the SCC	
 * @param bidirectional 	Signals if the graph is directed (false) or not (true)
 * @return std::vector<Vertex<T> *>	Returns the corresponding SCC containing initial 
 */
template <class T>
std::vector<Vertex<T> *> scc(Graph<T> * graph, Vertex<T> * initial, bool bidirectional);

/**
 * @brief Calculates the Strong Connected Component of the mainGraph that includes both
 * the initial and last vertex. Returns a new Graph without the vertexes and edges that
 * do not belong in the SCC.
 * 
 * @param mainGraph 		Graph containig at least the initial and last vertex
 * @param initial 			Vertex that must be contained in the SCC
 * @param last 				Vertex that must be contained in the SCC
 * @param bidirectional 	Tells if the graph is directed (false) or not (true)
 * @return Graph<T> 		New graph containing only vertexes and edges that belong in the SCC
 */
template <class T>
Graph<T> shrinkGraph(Graph<T> * mainGraph, Vertex<T> * initial, Vertex<T> * last, bool bidirectional);

/**
 * @brief Calculates the shortest path between origin and dest using Dijkstra's Algorithm.
 * 
 * @param graph 			Graph containig at least the initial and last vertex
 * @param origin 			Starting vertex of the desired path
 * @param dest 				Last vertex of the desired path
 * @return std::vector<Vertex<T> *> 	Vector containing the vertexes in the shortest Path in visiting order
 */
template <class T>
std::vector<Vertex<T> *> dijkstraShortestPath(Graph<T> * graph, const T &origin, const T &dest);

/**
 * @brief Calculates the shortest path between origin and dest using A*'s Algorithm.
 * 
 * @param graph 			Graph containig at least the initial and last vertex
 * @param origin 			Starting vertex of the desired path
 * @param dest 				Last vertex of the desired path
 * @param aStarType			Indicates whether it should use Euclidian or Manhattan distance as heuristics
 * @return std::vector<Vertex<T> *> 	Vector containing the vertexes in the shortest Path in visiting order
 */
template <class T>
std::vector<Vertex<T> *> aStarShortestPath(Graph<T> * graph, const T &origin, const T &dest, algorithm_t aStartType);

/**
 * @brief Calculates the shortest path between origin and dest, that
 * includes the delivery point of interest, using Dijkstra's Algorithm.
 * Uses threads in order to accelerate the calculation processing, having one calculate
 * the path between the origin and the delivery vertex, and the other between the delivery
 * and the dest vertex.
 * 
 * @param graph 			Graph containig at least the initial, delivery and last vertex
 * @param origin 			Starting vertex of the desired path
 * @param delivery 			Point of interest that must be included in the path
 * @param dest 				Last vertex of the desired path
 * @param bidirectional 	Indicates whether the graph is directed (false) or not (true)
 * @return std::vector<Vertex<T> *> 	Vector containing the vertexes in the shortest Path in visiting order
 */
template <class T>
std::vector<Vertex<T> *> bidirectionalDijkstra(Graph<T> * graph, const T &origin, const T &delivery, const T &dest, bool bidirectional);

/**
 * @brief Calculates the shortest path between origin and dest, that
 * includes the delivery point of interest, using A*'s Algorithm.
 * Uses threads in order to accelerate the calculation processing, having one calculate
 * the path between the origin and the delivery vertex, and the other between the delivery
 * and the dest vertex.
 * 
 * @param graph 			Graph containig at least the initial, delivery and last vertex
 * @param origin 			Starting vertex of the desired path
 * @param delivery 			Point of interest that must be included in the path
 * @param dest 				Last vertex of the desired path
 * @param aStarType			Indicates whether it should use Euclidean or Manhattan distance as heuristics 
 * @param bidirectional 	Indicates whether the graph is directed (false) or not (true)
 * @return std::vector<Vertex<T> *> 	Vector containing the vertexes in the shortest Path in visiting order
 */
template <class T>
std::vector<Vertex<T> *> bidirectionalAStar(Graph<T> * graph, const T &origin, const T &delivery, const T &dest, algorithm_t aStarType, bool bidirectional);

/**
 * @brief Calculates the shortest distance and path between all pairs of point belonging
 * to the graph. Stores the results in two matrixes contained in the Graph class.
 * 
 * @param graph 		Graph to be analysed
 */
template <class T>
void FloydWarshallShortestPath(Graph<T> * graph); 

/**
 * @brief Calculates the shortest path between origin and dest that contains all the vertexes
 * included in the vector  deliveries, that can be transported by the truck with the given capacity, 
 * using the Nearest Neighbor Algorithm. It uses Euclidean distance as the criteria for the 
 * Priority Queue, and A*'s algorithm to get intermidiate paths.
 * 
 * @param graph 			Graph containig at least the initial, deliveries and last vertexes
 * @param origin 			Starting vertex of the desired path
 * @param deliveries 		Points of interest that must be included in the path until maximum capacity is reached
 * @param dest 				Last vertex of the desired path
 * @param truckCapacity 	Maximum capacity that the truck used can hold (INF = unlimited)
 * @return std::vector<Vertex<T> *> 	Resulting path for the given truck
 */
template <class T>
std::vector<Vertex<T> *> NearestNeighborEuclidean(Graph<T> * graph, const T &origin,  vector<Delivery*> deliveries, const T &dest, double truckCapacity);

/**
 * @brief Calculates the shortest path between origin and dest that contains all the vertexes
 * included in the vector  deliveries, that can be transported by the truck with the given capacity, 
 * using the Nearest Neighbor Algorithm. It uses both the distance and path matrixes calculated by
 * the Floyd-Warshall's algorithms. Requires the mentioned algorithm to be executed prior.
 * 
 * @param graph 			Graph containig at least the initial, deliveries and last vertexes
 * @param origin 			Starting vertex of the desired path
 * @param deliveries 		Points of interest that must be included in the path until maximum capacity is reached
 * @param dest 				Last vertex of the desired path
 * @param truckCapacity 	Maximum capacity that the truck used can hold (INF = unlimited)
 * @return std::vector<Vertex<T> *> 	Resulting path for the given truck
 * */
template <class T>
std::vector<Vertex<T> *> NearestNeighborFloyd(Graph<T> * graph, const T &origin,  vector<Delivery*> deliveries, const T &dest, double truckCapacity);

/**
 * @brief Swaps vertexes in the current path with indexes between i and k.
 * 
 * @param current_path 		Path to be swapped
 * @param i 				Lowest index to swap
 * @param k 				Highest index to swap
 * @return vector<Vertex<T> *> 	Corresponding path with swapped vertexes
 */
template <class T>
vector<Vertex<T> *> twoOptSwap(const vector<Vertex<T> *> &current_path, int i, int k);

/**
 * @brief Calculates the path weight that goes through all the vertexes in the given path
 * vector, and changes it to the shortest path. Uses A*'s algorithms to contruct the path.
 * 
 * @param graph 			Graph that includes all vertexes in path
 * @param path 				Vertexes that must be visited in the calculated path
 * @return double 			Calculated path weight
 */
template <class T>
double calculatePathWeight(Graph<T> * graph, vector<Vertex<T> *> &path);  

/**
 * @brief Checks whether there can exist a path including all vertexes in path
 * in the given graph. Uses various DFS in order to calculate the result.
 * 
 * @param graph 			Graph that includes all vertexes in path
 * @param path 				Vertexes to be checked for a valid path
 * @return true 			There is a path connecting all vertexes
 * @return false 			There isn't a path connecting all vertexes
 */
template <class T>
bool validPath(Graph<T> * graph, const vector<Vertex<T> *> &path);

/**
 * @brief Given the vertexes which must be included in the path, attempts to calculate
 * the shortest path connecting all between the first and last vertex, by swapping
 * the order of the points of interest looking for an improvement. Returns the calculated
 * path when a set of iterations has been done with no improvement.
 * 
* @param graph 			Graph that includes all vertexes in path
 * @param path 			Vertexes that must be included in the improved path
 * @return std::vector<Vertex<T> *> 	Improved path
 */
template <class T>
std::vector<Vertex<T> *> improvePath(Graph<T> * graph, vector<Vertex<T> *> path);

/**
 * @brief Attemps to calculate the shortest path between origin and dest, passing through all
 * vertexes contained in the vector deliveries. It uses the auxilary function improvePath in
 * order to achieve the result
 * 
 * @param graph 			Graph containig at least the initial, deliveries and last vertexes
 * @param origin 			Starting vertex of the desired path
 * @param deliveries 		Points of interest that must be included in the path until maximum capacity is reached
 * @param dest 				Last vertex of the desired path
 * @return std::vector<Vertex<T> *>  Improved path with the vertexes by order in which they should be visited
 */
template <class T>
std::vector<Vertex<T> *> twoOptAlgorithm(Graph<T> * graph, const T &origin, const vector<T> deliveries, const T &dest);


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


template <class T>
std::vector<Vertex<T> *> scc(Graph<T> * graph, Vertex<T> * initial, bool bidirectional){
	// ofstream out;
	// out.open("teste.txt");

	startTime();

	vector<Vertex<T> *> res_normal = dfs(graph, initial);

	// printVertex(res_normal, out);

	if(bidirectional){
		writeTime(SCC, graph, bidirectional);
		return res_normal;
	}

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

	writeTime(SCC, graph, bidirectional);

	return res;
}

template <class T>
void append(vector<Vertex<T>*> &vec, vector<Vertex<T>*> &appendix){
	if(appendix.empty())
		return;

	for(Vertex<T>* vertex : appendix)
		vec.push_back(vertex);
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
inline bool aStarEuclidianRelax(Vertex<T> *v, Vertex<T> *w, Vertex<T> *dest, double weight) {
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
inline bool aStarManhattanRelax(Vertex<T> *v, Vertex<T> *w, Vertex<T> *dest, double weight) {
	double heuristicDistance = v->getDist() - v->getManhattanDist(dest) + weight + w->getEuclideanDist(dest);
	if (w->getDist() > heuristicDistance) {
		w->setDist(heuristicDistance);
		w->setPath(v); 
		return true;
	}
	else
		return false;
}

template <class T>
inline bool relax(Vertex<T> *v, Vertex<T> *w, Vertex<T> *dest, double weight, algorithm_t algorithm) 
{	
	switch (algorithm)
	{
	case DIJKSTRA: case BIDIJKSTRA:
		return dijkstraRelax(v, w, weight);
	case ASTAR_EUCLIDIAN: case BIASTAR_EUCLIDIAN:
		return aStarEuclidianRelax(v, w, dest, weight);
	case ASTAR_MANHATTAN: case BIASTAR_MANHATTAN:
		return aStarManhattanRelax(v, w, dest, weight);
	default:
		throw invalid_argument("Algorithm must be either A* or Dijkstra type");
	}
}

template <class T>
static std::vector<Vertex<T> *> shortestPath(Graph<T> * graph, const T &origin, const T &dest, algorithm_t algorithm)
{
	std::vector<Vertex<T> *> result;
	auto s = graph->initSingleSource(origin);
	Vertex<T>* d = graph->findVertex(dest);
	MutablePriorityQueue<Vertex<T>> q;
	q.insert(s);

	while( ! q.empty() ) {
		auto v = q.extractMin();

		if(v == d)
			return graph->getPath(origin, dest);
			
		for(unsigned int i = 0; i < v->getAdj()->size(); i++) {
			auto e = v->getAdj()->at(i);
			auto oldDist = e.getDest()->getDist();
			if (relax(v, e.getDest(), d, e.getWeight(), algorithm)) {
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
std::vector<Vertex<T> *> dijkstraShortestPath(Graph<T> * graph, const T &origin, const T &dest)
{
	return shortestPath(graph, origin, dest, DIJKSTRA);
}

template <class T>
std::vector<Vertex<T> *> aStarShortestPath(Graph<T> * graph, const T &origin, const T &dest, algorithm_t aStartType)
{
	return shortestPath(graph, origin, dest, aStartType);
}


template <class T>
std::vector<Vertex<T> *> bidirectionalDijkstra(Graph<T> * graph, const T &origin, const T &delivery, const T &dest, bool bidirectional)
{
	startTime();

    vector<Vertex<T> *> final_path, path;

	thread t1(dijkstraShortestPath<T>, graph, origin, delivery);
	
	if(bidirectional){
	//	thread t2(dijkstraShortestPath<T>, graph, delivery, dest);
		Graph<T> newGraph = graph->duplicate();
		dijkstraShortestPath<T>(&newGraph, delivery, dest);

		t1.join();

		final_path = graph->getPath(origin, delivery);
		path = newGraph.getPath(delivery, dest);

		final_path.insert(final_path.end(), path.begin(), path.end());
	}
	else{ 
		Graph<T> invertedGraph = graph->invert();
		dijkstraShortestPath<T>(&invertedGraph, dest, delivery);

		t1.join();

		final_path = graph->getPath(origin, delivery);
		path = invertedGraph.getPath(dest, delivery);

		// TODO: verify
		final_path.insert(final_path.end(), path.rbegin(), path.rend());
	}
//	cout << final_path.size() << " <- final_path\n";


	writeTime(BIDIJKSTRA, graph, bidirectional);

	return final_path;
}

template <class T>
std::vector<Vertex<T> *> bidirectionalAStar(Graph<T> * graph, const T &origin, const T &delivery, const T &dest, algorithm_t aStarType, bool bidirectional)
{
	startTime();

    vector<Vertex<T> *> final_path, path;

	thread t1(aStarShortestPath<T>, graph, origin, delivery, aStarType);
	
	if(bidirectional){
		Graph<T> newGraph = graph->duplicate();
		aStarShortestPath<T>(&newGraph, delivery, dest, aStarType);

		t1.join();

		final_path = graph->getPath(origin, delivery);
		path = newGraph.getPath(delivery, dest);


		final_path.insert(final_path.end(), path.begin(), path.end());
	}
	else{ 
		Graph<T> invertedGraph = graph->invert();
		aStarShortestPath<T>(&invertedGraph, dest, delivery, aStarType);

		t1.join();

		final_path = graph->getPath(origin, delivery);
		path = invertedGraph.getPath(dest, delivery);

		// TODO: verify
		final_path.insert(final_path.end(), path.rbegin(), path.rend());
	}

	writeTime(aStarType, graph, bidirectional);

	return final_path;
}

template <class T>
void FloydWarshallShortestPath(Graph<T> * graph) {
	bool undirected = true; // In the future replace it by function argument?

	//startTime();

	unsigned n = graph->getVertexSet().size();

	graph->resetMatrixW(n);
	graph->resetMatrixP(n);
	
	for (unsigned i = 0; i < n; i++) {
		for (unsigned j = i; j < n; j++) {
			graph->setW(i, j, graph->edgeWeight(i, j));
			graph->setW(j, i, graph->edgeWeight(j, i));
			graph->setP(i, j, graph->nextVertex(i, j));
			graph->setP(j, i, graph->nextVertex(j, i));
		}
	}

	for(unsigned k = 0; k < n; k++)
		for(unsigned j = 0; j < n; j++)
			for(unsigned i = undirected ? j + 1 : 0; i < n; i++) {
				if(j == k || i == k || i == j || graph->getW(i, k) == INF || graph->getW(k, j) == INF)
					continue; // avoid overflow and unnecessary calculations
				double val = graph->getW(i, k) + graph->getW(k, j);
				if (val < graph->getW(i, j)) {
					graph->setW(i, j, val);
					if(undirected) graph->setW(j, i, val);

					graph->setP(i, j, graph->getP(i, k));
					if(undirected) graph->setP(j, i, graph->getP(j, k));
				}
			}

	//writeTime(FW, graph, true);	
}

template <class T>
std::vector<Vertex<T> *> NearestNeighborEuclidean(Graph<T> * graph, const T &origin, vector<Delivery*> deliveries, const T &dest, double truckCapacity)
{
	startTime();

	vector<Vertex<T> *>result;
	Vertex<T>* start = graph->findVertex(origin);

	MutablePriorityQueue<Vertex<T>> Q;
	
	for(Delivery* delivery : deliveries){
		graph->findVertex(delivery->getDest())->setDist(start->getEuclideanDist(graph->findVertex(delivery->getDest())));
		Q.insert(graph->findVertex(delivery->getDest()));
	}

	result.push_back(start);

	while(!Q.empty()) {
		if(truckCapacity <= 0) break;

		Vertex<T>* vertex = Q.extractMin();

		vector<Vertex<T> *> path = aStarShortestPath(graph, *(result.back()->getInfo()), *(vertex->getInfo()), ASTAR_EUCLIDIAN);
		for(unsigned i = 1; i < path.size(); i++){
			result.push_back(path.at(i));
		}

		for(Delivery* delivery : deliveries){
			graph->findVertex(delivery->getDest())->setDist(vertex->getEuclideanDist(graph->findVertex(delivery->getDest())));
		}

		for(Delivery* delivery : deliveries) {
			if(delivery->getDest() == *vertex->getInfo()) {
				truckCapacity -= delivery->getVolume();
				if(truckCapacity >= 0) delivery->setDelivered(true);
				break;
			}
		}
	}

	vector<Vertex<T> *> path = aStarShortestPath(graph, *(result.back()->getInfo()), dest, ASTAR_EUCLIDIAN);
	for(unsigned i = 1; i < path.size(); i++ ){
		result.push_back(path.at(i));
	}

	writeTime(NNEUCLIDIAN, graph, true);	

	return result;
}

template <class T>
std::vector<Vertex<T> *> NearestNeighborFloyd(Graph<T> * graph, const T &origin, vector<Delivery*> deliveries, const T &dest, double truckCapacity){
	startTime();

	vector<Vertex<T> *> result;

	int inicial = graph->findVertexIdx(origin);

	MutablePriorityQueue<Vertex<T>> Q;

	for(Delivery* delivery: deliveries){
		Vertex<T>* vertex = graph->findVertex(delivery->getDest());
		vertex->setDist(graph->getW(inicial, graph->findVertexIdx(delivery->getDest())));
		Q.insert(vertex);
	}

	result.push_back(graph->findVertex(origin));

	while(!Q.empty()) {
		Vertex<T>* vertex = Q.extractMin();
		int vertexIndex = graph->findVertexIdx(*(vertex->getInfo()));

		for(Delivery* delivery : deliveries) {
			if(delivery->getDest() == *vertex->getInfo()) {
				truckCapacity -= delivery->getVolume();
				delivery->setDelivered(true);
				break;
			}
		}
		if(truckCapacity < 0) break;

		vector<T> path = graph->getFloydWarshallPath(*(result.back()->getInfo()), *(vertex->getInfo()));
		for(unsigned i = 1; i < path.size(); i++){
			result.push_back(graph->findVertex(path.at(i)));
		}

		for(Delivery* delivery : deliveries){
			vertex->setDist(graph->getW(vertexIndex, graph->findVertexIdx(delivery->getDest())));
		}
	}
	
	vector<T> path = graph->getFloydWarshallPath(*(result.back()->getInfo()), dest);
	for(unsigned i = 1; i < path.size(); i++ ){
			result.push_back(graph->findVertex(path.at(i)));
	}

	writeTime(NNFW, graph, true);	

	return result;
}

template <class T>
vector<Vertex<T> *> twoOptSwap(const vector<Vertex<T> *> &current_path, int i, int k){
	vector<Vertex<T> *> new_path = current_path;

	while (i < k) {
        swap(new_path.at(i), new_path.at(k));
        i++;
        k--;
    }

	return new_path;
}

template <class T>
double calculatePathWeight(Graph<T> * graph, vector<Vertex<T> *> &path){
	double weight = 0;
	vector<Vertex<T> *> new_path;
	vector<Vertex<T> *> intermediate_path;
	
	for(unsigned int i = 0; i < path.size() - 1; i++){
		intermediate_path =  aStarShortestPath(graph, *(path.at(i)->getInfo()), *(path.at(i + 1)->getInfo()), ASTAR_EUCLIDIAN);
		weight += intermediate_path.back()->getDist();
		append(new_path, intermediate_path);
		new_path.pop_back();
	}

	new_path.push_back(path.back());

	path = new_path;

	return weight;
}

template <class T>
bool validPath(Graph<T> * graph, const vector<Vertex<T> *> &path){
	for(unsigned int i = 0; i < path.size() - 1; i++)
		if(!containsVertex(dfs(graph, path.at(i)), path.at(i + 1))) 
			return false;

	return true;
}

template <class T>
std::vector<Vertex<T> *> improvePath(Graph<T> * graph, vector<Vertex<T> *> path){
	vector<Vertex<T> *> deliveryOrder = path;
	vector<Vertex<T> *> new_deliveryOrder;
	double currentBestWeight = calculatePathWeight(graph, path);
	double lastBestWeight = -1;
	double pathWeight = -1;
	
	vector<Vertex<T> *> bestPath = path;

	while(currentBestWeight != lastBestWeight){
		lastBestWeight = currentBestWeight;

		for(unsigned int i = 1; i < deliveryOrder.size() - 3; i++)
			for(unsigned int k = i + 1; k < deliveryOrder.size() - 2; k++){
				path = twoOptSwap(deliveryOrder, i, k);

				new_deliveryOrder = path;

				if(validPath(graph, path)){
					pathWeight = calculatePathWeight(graph, path);

					if(pathWeight < currentBestWeight){
						bestPath = path;
						deliveryOrder = new_deliveryOrder;
						currentBestWeight = pathWeight;
					}
				}
			}

	}

	writeTime(OPT2, graph, true);	

	return bestPath;
}

template <class T>
std::vector<Vertex<T> *> twoOptAlgorithm(Graph<T> * graph, const T &origin, const T &dest, const vector<T> deliveries){
	startTime();

	vector<Vertex<T> *> possible_solution;

	possible_solution.push_back(graph->findVertex(origin));
	
	for(T info : deliveries){
		possible_solution.push_back(graph->findVertex(info));
	}

	possible_solution.push_back(graph->findVertex(dest));

	return improvePath(graph, possible_solution);
}

#endif