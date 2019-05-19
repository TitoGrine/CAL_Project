#include "parser.h"

#include <fstream>
#include <sstream>

Graph<MapInfo> buildGraph(string MapName, bool bidirectional){
	Graph<MapInfo> graph;

	ifstream nodesFile;
	nodesFile.open("./Maps/" + MapName + "/T04_nodes_X_Y_" + MapName + ".txt");

	// TODO: change to exception
	if(!nodesFile.is_open()){
		cerr << "Error opening edges file\n";
		return graph;
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
		graph.addVertex(mi, nodeX, nodeY);
	}
	
	nodesFile.close();

	// EDGES

	ifstream edgesFile;
	edgesFile.open("./Maps/" + MapName + "/T04_edges_" + MapName + ".txt");

	if(!edgesFile.is_open()){
		cerr << "Error opening edges file\n";
		return graph;
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
		Vertex<MapInfo> * v1 = graph.findVertex(mi1);
		Vertex<MapInfo> * v2 = graph.findVertex(mi2);
	
		graph.addEdge(*(v1->getInfo()), *(v2->getInfo()), v1->getEuclideanDist(v2));
		
		if(bidirectional)
			graph.addEdge(*(v2->getInfo()), *(v1->getInfo()), v2->getEuclideanDist(v1));
	}

	edgesFile.close();

	//Tags

	ifstream tagsFile;
	tagsFile.open("T04_tags_" + MapName + ".txt");

	if(!tagsFile.is_open()){
		cerr << "Error opening tags file\n";
		return graph;
	}

	string tagType;
	unsigned int numTags, numVertexes, numShops;

	getline(tagsFile, line);
	iss = istringstream(line);
	iss >> numTags;

	//Deposits
	for(unsigned int i = 0; i < numTags; i++) {
		getline(tagsFile, tagType);
		if(tagType.find("shop=") != string::npos) {
			numShops = numTags - i;
			break;
		}
		getline(tagsFile, line);
		iss = istringstream(line);
		iss >> numVertexes;
		for(unsigned int j = 0; j < numVertexes; j++) {
			getline(tagsFile, line);
			iss = istringstream(line);
			iss >> id;
			MapInfo mi(id);
			graph.addShop(mi, i);
		}
	}

	//Shops
	for(unsigned int i = 0; i < numShops; i++) {
		if(i != 0) getline(tagsFile, tagType);
		getline(tagsFile, line);
		iss = istringstream(line);
		iss >> numVertexes;
		for(unsigned int j = 0; j < numVertexes; j++) {
			getline(tagsFile, line);
			iss = istringstream(line);
			iss >> id;
			MapInfo mi(id);
			graph.addShop(mi, i);
		}
	}

	tagsFile.close();

	return graph;
}