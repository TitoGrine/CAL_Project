#ifndef PARSER_H_
#define PARSER_H_

#include "../Utilities/MapInfo.h"
#include "../Graph/Graph.h"
#include <string>

Graph<MapInfo> buildGraph(std::string MapName, bool bidirectional);

#endif