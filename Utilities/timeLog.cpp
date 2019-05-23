#include "timeLog.h"

#include <chrono>
#include <fstream>
#include <string>
#include <windows.h>


using namespace std;

#define INFO_BUFFER_SIZE 32767
TCHAR  infoBuf[INFO_BUFFER_SIZE];
DWORD  bufCharCount = INFO_BUFFER_SIZE;

static chrono::high_resolution_clock::time_point startingTime;

const static string timesFileName = "times.csv";

string algorithmToString(algorithm_t algorithm){
	switch (algorithm)
	{
	case BIDIJKSTRA:
		return "bidijkstra";
	case BIASTAR_EUCLIDIAN:
		return "bia* euclidian";
	case DIJKSTRA:
		return "dijkstra";
	case ASTAR_EUCLIDIAN:
		return "a* euclidian";
	case SCC:
		return "scc";
	case INVERT_GRAPH:
		return "graph inversion";
	case NNFW:
		return "NN FW";
	case NNEUCLIDIAN:
		return "NN euclidian";
	case OPT2:
		return "OPT-2";
	case FW:
		return "Floyd-Warshall";
	default:
		return "";
	}
}

void startTime(){
	startingTime = chrono::high_resolution_clock::now();
}

long long getElapsedTimeMiliSeconds(){
	auto finish = chrono::high_resolution_clock::now();
	long long mili = chrono::duration_cast<chrono::milliseconds>(finish - startingTime).count();

	return mili;
}

void writeTime(const algorithm_t& algorithm, Graph<MapInfo> * graph, bool bidirectional) {
	ofstream timeCSV;
	timeCSV.open(timesFileName, std::ios_base::app);
	if(!timeCSV.is_open())
		throw logic_error("failed to open timeCSV");
	
	unsigned n_edges = 0;
	for(int i = 0; i < graph->getNumVertex(); i++)
		n_edges += graph->getVertexSet().at(i)->getAdj()->size();

	if( !GetUserName( infoBuf, &bufCharCount ) )
  		cerr << "error getting name\n"; 

	timeCSV  << infoBuf << ","; 
    timeCSV << algorithmToString(algorithm) << "," ;
	timeCSV << graph->getNumVertex() << "," << n_edges << "," << getElapsedTimeMiliSeconds() << "," << (bidirectional ? "V" : "F" ) << endl;
	timeCSV.close();
}


