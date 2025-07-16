#ifndef NAVARWID_H
#define NAVARWID_H

#include <QWidget>
#include "aesitf.h"
#include "keygen.h"
namespace Ui {
class navarwid;
}

class navarwid : public QWidget
{
    Q_OBJECT

public:
    explicit navarwid(QWidget *parent = nullptr);
    ~navarwid();
    void setKeygenWidget(Keygen *keygen);
signals:
    void navBarSig(int);

    void aesConfigUpdated(const sAesItf &config);


private slots:
    void on_MainWid_clicked();

    void on_SerSet_clicked();

private:
    Ui::navarwid *ui;
    Keygen *m_keygenWidget = nullptr;
};

#endif // NAVARWID_H
