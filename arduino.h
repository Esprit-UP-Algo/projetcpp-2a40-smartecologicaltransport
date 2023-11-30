#ifndef ARDUINO_H
#define ARDUINO_H

#include<QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include<QDebug>
class Arduino
{
public:
    Arduino();
    int connect_arduino();
    int close_arduino();
    int write_to_arduino(QByteArray);
    QByteArray read_from_arduino();
    QSerialPort *get_serial();
    QString getArduino_port_name();

private:
    QSerialPort *serial;
    // Replace these values with the ones you obtained for your Arduino Uno SMD
    static const quint16 arduino_uno_vendor_id = 0x1A86;
    static const quint16 arduino_uno_product_id = 0x7523;

    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;
};

#endif // ARDUINO_H
