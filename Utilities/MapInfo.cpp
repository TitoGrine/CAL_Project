#include "MapInfo.h"
#include <cmath>

using namespace std;

MapInfo::MapInfo(long id): mapID(id) {
	this->initial = false;
	this->end = false;
}

MapInfo::MapInfo(long id, bool initial, bool last): mapID(id), initial(initial), end(last) {};


bool MapInfo::operator==(const MapInfo & mapInfo) const{
	return this->mapID == mapInfo.getID();
}

MapInfo& MapInfo::operator=(const MapInfo & mi) {
	if(this == &mi) return *this;
	this->mapID = mi.getID();
	return *this;
}

ostream & operator << (ostream &os, const MapInfo &p) {
   os << p.getID();
   return os;
}