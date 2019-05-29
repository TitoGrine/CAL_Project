#ifndef MAPINFO_H_
#define MAPINFO_H_

#include <ostream>

/**
 * @brief MapInfo class saves the information relevant to one map-graph node
 * 
 */
class MapInfo {
	// Map ID extracted from the Coords txt file in the Maps/ folder
	long mapID;

	// Flag inidicating whether it is the initial state = deposit
	bool initial = false;
	// Flag inidicating whether it is the final state = garage
	bool end = false;

public:
	/**
	 * @brief Construct a new Map Info object
	 * 
	 * @param id Map ID extracted from the nodes coord txt file
	 */
	MapInfo(long id);
	/**
	 * @brief Construct a new Map Info object
	 * 
	 * @param id Map ID extracted from the nodes coord txt file
	 * @param initial whether it is an initial state = deposit or not
	 * @param last whether it is a final state = garage or not
	 */
	MapInfo(long id, bool initial, bool last);

	/**
	 * @brief Get Map ID
	 * 
	 * @return long Map ID
	 */
	long getID() const { return this->mapID; };

	/**
	 * @brief Get initial flag
	 * 
	 * @return true If node is a deposit
	 * @return false If MapInfo is not the initial vertex
	 */
	bool isInitial() const { return this->initial; };
	bool isFinal() const { return this->end; };
	
	/**
	 * @brief Set the Initial flag private parameter to true
	 * 
	 */
	void setInitial() { this->initial = true; };
	/**
	 * @brief Set the Final flag private parameter to true
	 * 
	 */
	void setFinal() { this->end = true; };

	/**
	 * @brief Set the Initial flag private parameter to false
	 * 
	 */
	void removeInitial() { this->initial = false; };
	/**
	 * @brief Set the Final flag private parameter to false
	 * 
	 */
	void removeFinal() { this->end = false; };

	bool operator==(const MapInfo & mapInfo) const;

	MapInfo& operator=(const MapInfo& mi);

	friend std::ostream & operator<< (std::ostream &os, const MapInfo &p);

};

#endif