#include "Delivery.h"

int Delivery::ID = 0;

Delivery::Delivery(const MapInfo &mapInfo, map_info_t shop_type): dest(mapInfo), shop_type(shop_type)
{
    this->deliveryID = ID++;
    this->volume = 0;
    this->delivered = false;
}

int Delivery::getID() const 
{
    return this->deliveryID;
}

MapInfo Delivery::getDest() const 
{
    return this->dest;
}

map_info_t Delivery::getShopType() const
{
    return this->shop_type;
}

int Delivery::getVolume() const 
{
    return this->volume;
}

void Delivery::setVolume(const int &volume)
{
    this->volume = volume;
}

bool Delivery::isDelivered() const
{
    return this->delivered;
}

void Delivery::setDelivered(bool delivered)
{
    this->delivered = delivered;
}