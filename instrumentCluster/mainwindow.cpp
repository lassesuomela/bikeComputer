#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    blinkTimer = new QTimer();
    connect(blinkTimer, SIGNAL(timeout()), this, SLOT(blinkImage()));

    monitor = new SerialMonitor();

    connect(monitor, SIGNAL(readDoneSignal(QJsonObject)), this, SLOT(serialDataSlot(QJsonObject)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete monitor;
    monitor = nullptr;

}

void MainWindow::setValues()
{
    ui->altValueText->setText(QString::number(alt)+ " m");
    ui->speedText->setText(QString::number(speed));
    ui->confidenceValueText->setText(QString::number(hdop));
    ui->latValueText->setText(QString::number(lat));
    ui->lngValueText->setText(QString::number(lng));
    ui->satText->setText(QString::number(sat));
}

void MainWindow::rotateImage(int degree)
{


}

void MainWindow::blinkImage()
{
    if(ui->satImage->pixmap()->isNull()){

    }
}

void MainWindow::startBlinkTimer()
{
    blinkTimer->start(100);
}

void MainWindow::stopBlinkTimer()
{
    blinkTimer->stop();
}

void MainWindow::serialDataSlot(QJsonObject data)
{
    if(data["error"] != NULL){
        //Todo: blink satellite img
        startBlinkTimer();
        return;
    }

    stopBlinkTimer();

    // keys: lat, lng, speed, altitude, course, hdop, satellites
    lat = data["lat"].toDouble();
    lng = data["lng"].toDouble();
    speed = data["speed"].toDouble();
    alt = data["altitude"].toDouble();
    course = data["course"].toInt();
    hdop = data["hdop"].toInt();
    sat = data["satellites"].toInt();

    rotateImage(course);

    setValues();
}
