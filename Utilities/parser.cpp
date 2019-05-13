#include "parser.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

GraphViewer * buildGraph(string MapName, int width, int height)
{
	GraphViewer * gv = new GraphViewer(width, height, false);
	gv->createWindow(width, height);

	ifstream nodesFile;
	nodesFile.open("./Maps/" + MapName + "/T04_nodes_X_Y_" + MapName + ".txt");

	if(!nodesFile.is_open()){
		cerr << "Error opening edges file\n";
		return NULL;
	}

	string line;
	istringstream iss;
	char p;
	unsigned int id, numberNodes;
	int nodeX, nodeY;

	getline(nodesFile, line);
	iss = istringstream(line);
	iss >> numberNodes;

	for(unsigned int i = 0; i < numberNodes; i++){
		iss = istringstream(line);
		iss >> p >> id >> p >> nodeX >> p >> nodeY >> p;
		gv->addNode(id, nodeX, nodeY);
	}
	
	nodesFile.close();

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
		iss = istringstream(line);
		iss >> p >> pt1 >> p >> pt2 >> p;
		gv->addEdge(i, pt1, pt2, EdgeType::UNDIRECTED);
	}

	edgesFile.close();
	gv->rearrange();

	return gv;
}