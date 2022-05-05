#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    blinkTimer = new QTimer();
    connect(blinkTimer, SIGNAL(timeout()), this, SLOT(blinkImage()));

    monitor = new SerialMonitor();

    connect(monitor, SIGNAL(readDoneSignal(QJsonObject)), this, SLOT(serialDataSlot(QJsonObject)));
}

MainWindow::~MainWindow()
{
    disconnect(blinkTimer, SIGNAL(timeout()), this, SLOT(blinkImage()));
    disconnect(monitor, SIGNAL(readDoneSignal(QJsonObject)), this, SLOT(serialDataSlot(QJsonObject)));

    delete ui;
    delete monitor;
    monitor = nullptr;
}

void MainWindow::setValues()
{
    ui->altValueText->setText(QString::number(alt, 'g', 0)+ " m");
    ui->speedText->setText(QString::number(speed, 'g', 1));
    ui->latValueText->setText(QString::number(lat, 'g', 6));
    ui->lngValueText->setText(QString::number(lng, 'g', 6));
    ui->satText->setText(QString::number(sat));
    ui->headingText->setText(QString::number(course, 'g', 0) + "°");
}

void MainWindow::rotateImage(int deg)
{


}

void MainWindow::changeHdopColor(int val)
{
    if(val < 120){
        //green
        colorValue = "background-color:rgb(92, 184, 92)";
    }else if(val < 250){
        //yellow
        colorValue = "background-color:rgb(240, 173, 78)";
    }else {
        //red
        colorValue = "background-color:rgb(217, 83, 79)";
    }

    ui->accValue->setStyleSheet(colorValue);
}

void MainWindow::blinkImage()
{
    if(!ui->satImage->isEnabled()){
        ui->satImage->setEnabled(true);
    }else{
        ui->satImage->setEnabled(false);
    }
}

void MainWindow::startBlinkTimer()
{
    if(!blinkTimer->isActive()){
        blinkTimer->start(500);
    }
}

void MainWindow::stopBlinkTimer()
{
    if(blinkTimer->isActive()){
        blinkTimer->stop();
        ui->satImage->setEnabled(true);
    }
}

void MainWindow::serialDataSlot(QJsonObject data)
{
    if(data.contains("error")){
        startBlinkTimer();

        qDebug() << "Error:" << data["error"].toString();

        return;
    }
    qDebug() << "No errors found";

    stopBlinkTimer();

    // keys: lat, lng, speed, altitude, course, hdop, satellites
    lat = data["lat"].toDouble();
    lng = data["lng"].toDouble();
    speed = data["speed"].toDouble();
    alt = data["altitude"].toDouble();
    course = data["course"].toDouble();
    hdop = data["hdop"].toInt();
    sat = data["satellites"].toInt();

    changeHdopColor(hdop);
    rotateImage(course);

    setValues();
}

