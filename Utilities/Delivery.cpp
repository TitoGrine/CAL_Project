#include "Delivery.h"

int Delivery::ID = 0;

Delivery::Delivery(const MapInfo &mapInfo): dest(mapInfo)
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