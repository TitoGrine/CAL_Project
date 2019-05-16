#include "parser.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Graph * buildGraph(string MapName)
{
	Graph * graph = new Graph();

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
		graph->addVertex(id, nodeX, nodeY);
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
		graph->addEdge(pt1, pt2, graph->findVertex(pt1)->getEuclideanDist(graph->findVertex(pt2)));
	}

	edgesFile.close();

	return graph;
}