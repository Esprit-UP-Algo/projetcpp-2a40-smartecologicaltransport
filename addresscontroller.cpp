// addresscontroller.cpp

#include "addresscontroller.h"

AddressController::AddressController(QObject *parent) : QObject(parent)
{
}

void AddressController::setAddress(const QString &address)
{
    emit addressChanged(address);
}
