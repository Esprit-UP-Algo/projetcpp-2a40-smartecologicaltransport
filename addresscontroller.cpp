<<<<<<< HEAD
// addresscontroller.cpp

#include "addresscontroller.h"

AddressController::AddressController(QObject *parent) : QObject(parent)
{
}

void AddressController::setAddress(const QString &address)
{
    emit addressChanged(address);
}
=======
// addresscontroller.cpp

#include "addresscontroller.h"

AddressController::AddressController(QObject *parent) : QObject(parent)
{
}

void AddressController::setAddress(const QString &address)
{
    emit addressChanged(address);
}
>>>>>>> 125c86552904b16adbfbaa587dd8ace5bdb947be
