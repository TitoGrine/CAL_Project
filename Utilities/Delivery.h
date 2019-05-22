#pragma once

#include "MapInfo.h"

class Delivery {
    static int ID;
    int deliveryID;

    MapInfo dest;

    int volume;

    public:
        Delivery();
        Delivery(const MapInfo &dest);

        int getID() const;

        MapInfo getDest() const;

        int getVolume() const;
        void setVolume(const int &volume);
};