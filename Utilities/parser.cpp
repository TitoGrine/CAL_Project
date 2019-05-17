#include "parser.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

template <class T>
Graph<MapInfo> * buildGraph(string MapName)
{
	Graph<MapInfo> * graph = new Graph<MapInfo>();

	ifstream nodesFile;
	nodesFile.open("./Maps/" + MapName + "/T04_nodes_X_Y_" + MapName + ".txt");

	// TODO: change to exception
	if(!nodesFile.is_open()){
		cerr << "Error opening edges file\n";
		return NULL;
	}

	string line;
	istringstream iss;
	char p;
	long id, numberNodes;
	double nodeX, nodeY;

	getline(nodesFile, line);
	iss = istringstream(line);
	iss >> numberNodes;

	for(long i = 0; i < numberNodes; i++){
		getline(nodesFile, line);
		iss = istringstream(line);
		iss >> p >> id >> p >> nodeX >> p >> nodeY >> p;
		MapInfo mi(id);
		graph->addVertex(mi, nodeX, nodeY);
	}
	
	nodesFile.close();

	// EDGES

	ifstream edgesFile;
	edgesFile.open("./Maps/" + MapName + "/T04_edges_" + MapName + ".txt");

	if(!edgesFile.is_open()){
		cerr << "Error opening edges file\n";
		return NULL;
	}

	
	unsigned int pt1, pt2, numberEdeges;

	getline(edgesFile, line);
	iss = istringstream(line);
	iss >> numberEdeges;

	for(unsigned int i = 0; i < numberEdeges; i++){
		getline(edgesFile, line);
		iss = istringstream(line);
		iss >> p >> pt1 >> p >> pt2 >> p;
		MapInfo mi1(pt1);
		MapInfo mi2(pt2);
		Vertex<T> * v1 = graph->findVertex(mi1);
		Vertex<T> * v2 = graph->findVertex(mi2);
	
		graph->addEdge(v1->getInfo(), v2->getInfo(), v1->getEuclideanDist(v2));
	}

	edgesFile.close();

	return graph;
}