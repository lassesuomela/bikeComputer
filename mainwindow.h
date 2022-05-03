#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialmonitor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SerialMonitor *monitor;

    int sat, hdop, course;
    double speed, lat, lng, alt;

    void setValues();
    void rotateImage(int);

private slots:
    void serialDataSlot(QJsonObject);
};
#endif // MAINWINDOW_H
