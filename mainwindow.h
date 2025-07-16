#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "navarwid.h"
#include "keygen.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event)override;

protected slots:
    void navBarSlot(int);

private:
    Ui::MainWindow *ui;
    navarwid* mNavar;
    Keygen* mkeygen;

    void initWid();
    void saveAllSettings();
    void loadAllSettings();
};
#endif // MAINWINDOW_H
