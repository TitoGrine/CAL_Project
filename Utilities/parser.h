#ifndef PARSER_H_
#define PARSER_H_

#include "../Utilities/Application.h"
#include <string>
#include "../Utilities/MapInfo.h"
#include "../Graph/Graph.h"

/**
 * @brief Function that has a shopTypeString as input (from the txt tags) and outputs the corresponding value in the map_info_t enum
 * 
 * @param shopTypeString String with the shop Type (parsed from the txt tags file)
 * @return map_info_t Value in the enum corresponding to the string
 */
map_info_t stringToMapInfoType(string shopTypeString);

/**
 * @brief Funtcion that does the opposit from the one before. Has a shop type as input and outputs the corresponding string
 * 
 * @param shop_type Enum value from the desired shop type
 * @return std::string Output string corresponding to the shop_type
 */
std::string mapInfoTypeToString(map_info_t shop_type);

/**
 * @brief Funciton that parses the coord file and the edges file and outputs a new Graph
 * 
 * @param graph Resulting graph from the parsing
 * @param MapName Name of the city of the map present in the /Map folder
 * @param bidirectional Whether the map must be a Directed Graph or not
 */
void buildGraph(Graph<MapInfo> & graph, std::string MapName, bool bidirectional);

/**
 * @brief Function tha builds an application with a graph and parsing the tag files
 * 
 * @param app Application to be initialized
 * @param MapName Name of the City int the Map/ folder to parse the tags
 * @param mainGraph Graph of the city to initialize the Application
 */
void buildApplication(Application * app, std::string MapName, Graph<MapInfo> * mainGraph);

#endif