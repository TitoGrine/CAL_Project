#pragma once

#include "MapInfo.h"

class Delivery {
    static int ID;
    int deliveryID;

    MapInfo dest;

    bool delivered;

    int volume;

    public:
        Delivery();
        Delivery(const MapInfo &dest);

        int getID() const;

        MapInfo getDest() const;

        int getVolume() const;
        void setVolume(const int &volume);

        bool isDelivered() const;
        void setDelivered(bool delivered);

};