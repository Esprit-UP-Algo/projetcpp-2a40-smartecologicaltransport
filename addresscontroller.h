<<<<<<< HEAD

#ifndef ADDRESSCONTROLLER_H
#define ADDRESSCONTROLLER_H

#include <QObject>

class AddressController : public QObject
{
    Q_OBJECT

public:
    explicit AddressController(QObject *parent = nullptr);

signals:
    void addressChanged(const QString &address);

public slots:
    void setAddress(const QString &address);
};

#endif // ADDRESSCONTROLLER_H
=======

#ifndef ADDRESSCONTROLLER_H
#define ADDRESSCONTROLLER_H

#include <QObject>

class AddressController : public QObject
{
    Q_OBJECT

public:
    explicit AddressController(QObject *parent = nullptr);

signals:
    void addressChanged(const QString &address);

public slots:
    void setAddress(const QString &address);
};

#endif // ADDRESSCONTROLLER_H
>>>>>>> 125c86552904b16adbfbaa587dd8ace5bdb947be
