#ifndef MAPINFO_H_
#define MAPINFO_H_

#include <ostream>

class MapInfo {
	long mapID;                // contents

	bool initial = false;
	bool end = false;

public:
	MapInfo(long id);
	MapInfo(long id, bool initial, bool last);
	long getID() const { return this->mapID; };

	bool isInitial() const { return this->initial; };
	bool isFinal() const { return this->end; };
	
	void setInitial() { this->initial = true; };
	void setFinal() { this->end = true; };

	void removeInitial() { this->initial = false; };
	void removeFinal() { this->end = false; };

	bool operator==(const MapInfo & mapInfo) const;

	MapInfo& operator=(const MapInfo& mi);

	friend std::ostream & operator<< (std::ostream &os, const MapInfo &p);

};

#endif