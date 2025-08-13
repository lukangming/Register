#ifndef SERIALSTATUSWID_H
#define SERIALSTATUSWID_H

#include <QWidget>
#include <QSerialPort>
namespace Ui {
class SerialStatusWid;
}

class SerialStatusWid : public QWidget
{
    Q_OBJECT

public:
    explicit SerialStatusWid(QWidget *parent = nullptr);
    ~SerialStatusWid();

private:
    Ui::SerialStatusWid *ui;
    QSerialPort *serial;
};

#endif // SERIALSTATUSWID_H
