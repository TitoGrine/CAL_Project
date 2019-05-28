#pragma once

#include "MapInfo.h"

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

class Delivery {
    static int ID;
    int deliveryID;

    MapInfo dest;

    map_info_t shop_type;

    bool delivered;

    int volume;

    public:
        Delivery();
        Delivery(const MapInfo &dest, map_info_t shop_type);

        int getID() const;

        MapInfo getDest() const;

        map_info_t getShopType() const;

        int getVolume() const;
        void setVolume(const int &volume);

        bool isDelivered() const;
        void setDelivered(bool delivered);

};