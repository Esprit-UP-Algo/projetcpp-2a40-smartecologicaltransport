#include "arduino.h"

Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}
QString Arduino::getArduino_port_name()
{
    return arduino_port_name;
}
QSerialPort *Arduino::get_serial()
{
    return serial;
}
int Arduino::connect_arduino()
{
    foreach(const QSerialPortInfo &serial_port_info , QSerialPortInfo::availablePorts())
    {
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier())
        {
            if(serial_port_info.vendorIdentifier()== arduino_uno_vendor_id && serial_port_info.productIdentifier()==arduino_uno_product_id)
            {
                arduino_is_available=true;
                arduino_port_name=serial_port_info.portName();
            }
        }
    }
    qDebug()<<"arduino port name:"<<arduino_port_name;
    if(arduino_is_available)
    {
        serial->setPortName(arduino_port_name);
        if(serial->open(QSerialPort::ReadWrite))
        {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0;
        }
        return 1;
    }
    return -1;
}
int Arduino::close_arduino()
{
    if (serial->isOpen())
    {
        serial->close();
        return 0;
    }
    return 1;
}
int Arduino::write_to_arduino(QByteArray d)
{
    if(serial->isWritable())
    {
        qDebug()<<d;
        serial->write(d);
    }
    else
    {
        qDebug()<<"error en ecriture";
    }
}
QByteArray Arduino::read_from_arduino()
{

    QByteArray newData;

    if (serial->isReadable())
    {
        // Wait for some time to allow more data to arrive
        serial->waitForReadyRead(500);

        // Read all available data
        newData = serial->readAll();

        if (!newData.isEmpty())
        {
            data.append(newData);
            qDebug() << "QByteArray content using QDebug:" << newData;
            return newData;
        }
        else
        {
            qDebug() << "Received an empty string. Ignoring.";
        }
    }
}
