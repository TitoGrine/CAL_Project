#ifndef PARSER_H_
#define PARSER_H_

#include "../Graph/Graph.h"
#include "../Utilities/MapInfo.h"
#include <string>

Graph<MapInfo> * buildGraph(std::string MapName);

#endif