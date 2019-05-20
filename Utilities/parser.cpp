#include "parser.h"

#include <fstream>
#include <sstream>

using namespace std;

map_info_t stringToMapInfoType(string shopTypeString){

	if("department_store" == shopTypeString) return DEPARTMENT_STORE;
	if("variety_store" == shopTypeString) return VARIETY_STORE;
	if("supermarket" == shopTypeString) return SUPERMARKET;
	if("doityourself" == shopTypeString) return DIY;
	if("convenience" == shopTypeString) return CONVENIENCE;
	if("clothes" == shopTypeString) return CLOTHES;
	if("hardware" == shopTypeString) return HARDWARE;
	if("furniture" == shopTypeString) return FURNITURE;
	if("electronics" == shopTypeString) return ELECTRONICS;
	if("mobile_phone" == shopTypeString) return MOBILE_PHONE;
	if("shoes" == shopTypeString) return SHOES;
	if("alcohol" == shopTypeString) return ALCOHOL;
	else return OTHER;	
}

Graph<MapInfo> buildGraph(std::string MapName, bool bidirectional){
	Graph<MapInfo> graph;
	ifstream nodesFile;
	nodesFile.open("./Maps/" + MapName + "/T04_nodes_X_Y_" + MapName + ".txt");

	// TODO: change to exception
	if(!nodesFile.is_open())
		throw invalid_argument("Couldn't open coord file");

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

	if(!edgesFile.is_open())
		throw invalid_argument("Couldn't open edges file");

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

	return graph;
}

void buildApplication(Application * app, std::string MapName, Graph<MapInfo> * mainGraph){

	app->clear();

	string line;
	istringstream iss;
	long id;

	app->addMainGraph(mainGraph);

	//Tags

	ifstream tagsFile;
	tagsFile.open("./Maps/" + MapName + "/T04_tags_" + MapName + ".txt");

	if(!tagsFile.is_open()){
		cerr << "Couldn't open tags file\n";
		return;
	}

	string tagType, shopType;
	unsigned int numTags, numVertexes;

	getline(tagsFile, line);
	iss = istringstream(line);
	iss >> numTags;

	for(unsigned int i = 0; i < numTags; i++) {
		getline(tagsFile, tagType);
		// Deposit
		if(tagType.find("shop=") == string::npos) {
			getline(tagsFile, line);
			iss = istringstream(line);
			iss >> numVertexes;
			for(unsigned int j = 0; j < numVertexes; j++) {
				getline(tagsFile, line);
				iss = istringstream(line);
				iss >> id;
				MapInfo mi(id);
				app->addDeposit(mi);
			}
		}
		// Shops
		else{
			getline(tagsFile, line);
			iss = istringstream(line);
			iss >> numVertexes;
			shopType = tagType.substr(tagType.find("=") + 1);
			for(unsigned int j = 0; j < numVertexes; j++) {
				getline(tagsFile, line);
				iss = istringstream(line);
				iss >> id;
				MapInfo mi(id);
				app->addShop(mi, stringToMapInfoType(shopType));
			}
		}		
	}

	tagsFile.close();
cout << "Aqui\n";
}