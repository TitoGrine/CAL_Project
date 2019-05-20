#ifndef PARSER_H_
#define PARSER_H_

#include "../Utilities/Application.h"
#include <string>
#include "../Utilities/MapInfo.h"
#include "../Graph/Graph.h"


Graph<MapInfo> buildGraph(std::string MapName, bool bidirectional);

void buildApplication(Application * app, std::string MapName, Graph<MapInfo> * mainGraph);

#endif