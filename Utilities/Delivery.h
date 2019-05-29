#pragma once

#include "MapInfo.h"

/**
 * @brief Enum with the diferent kind of tags in the txt file
 * 
 */
enum map_info_t {
	DEPARTMENT_STORE,
	VARIETY_STORE,
	SUPERMARKET,
	DIY,
	CONVENIENCE,
	CLOTHES,
	HARDWARE,
	FURNITURE,
	ELECTRONICS,
	MOBILE_PHONE,
	SHOES,
	ALCOHOL,
	_N_SHOPS_TYPE,
	DEPOSIT,
	OTHER	
};

/**
 * @brief Delivery class
 * 
 */
class Delivery {
    static int ID;
	// Delivery ID
    int deliveryID;

	// Delivery destiny
    MapInfo dest;

	// Delivery Type
    map_info_t shop_type;

	// Whether it was already delivered or not (usefull for the last problem)
    bool delivered;

	// Delivery volume (usefull for the last problem)
    int volume;

    public:
		/**
		 * @brief Construct a new Delivery object
		 * 
		 */
        Delivery();
		/**
		 * @brief Construct a new Delivery object initializing its volume with 0
		 * 
		 * @param dest MapInfo type corresponding to the delivery destiny
		 * @param shop_type Value from the map_info_t enum that representes the correct type of the delivery
		 */
        Delivery(const MapInfo &dest, map_info_t shop_type);

		/**
		 * @brief Get Delivery ID
		 * 
		 * @return int Delivery ID
		 */
        int getID() const;

		/**
		 * @brief Get the dest private parameter
		 * 
		 * @return MapInfo Destiny of the delivery
		 */
        MapInfo getDest() const;

		/**
		 * @brief Get the Shop Type value in the enum
		 * 
		 * @return map_info_t Value corresponding to the shop type
		 */
        map_info_t getShopType() const;

		/**
		 * @brief Get the Volume private parameter
		 * 
		 * @return int Volume of the Delivery
		 */
        int getVolume() const;

		/**
		 * @brief Set the Volume private parameter
		 * 
		 * @param volume New delivery volume
		 */
        void setVolume(const int &volume);

		/**
		 * @brief Get deliverd private parameter
		 * 
		 * @return true If the delivered flag is true
		 * @return false If the delivered flag is false
		 */
        bool isDelivered() const;
		/**
		 * @brief Set the Delivered private parameter
		 * 
		 * @param delivered Wheter the delivery was delivered or not
		 */
        void setDelivered(bool delivered);

};