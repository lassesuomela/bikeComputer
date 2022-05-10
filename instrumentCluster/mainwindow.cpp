#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    headingPixMap = new QPixmap(*ui->coursePic->pixmap());

    blinkTimer = new QTimer();
    connect(blinkTimer, SIGNAL(timeout()), this, SLOT(blinkImage()));
    monitor = new SerialMonitor();

    connect(monitor, SIGNAL(readDoneSignal(QJsonObject)), this, SLOT(serialDataSlot(QJsonObject)));

    checkPortStatus();

    QRegion *region = new QRegion(0, 0, ui->accValue->height()*0.5, ui->accValue->width()*0.5, QRegion::Ellipse);

    ui->accValue->setMask(*region);

    delete region;
    region = nullptr;
}

MainWindow::~MainWindow()
{
    disconnect(blinkTimer, SIGNAL(timeout()), this, SLOT(blinkImage()));
    disconnect(monitor, SIGNAL(readDoneSignal(QJsonObject)), this, SLOT(serialDataSlot(QJsonObject)));

    delete headingPixMap;
    headingPixMap = nullptr;
    delete ui;
    delete monitor;
    monitor = nullptr;
}

void MainWindow::setValues()
{
    ui->altValueText->setText(QString::number(alt, 'f', 0)+ " m");
    ui->speedText->setText(QString::number(speed, 'f', 1));
    ui->latValueText->setText(QString::number(lat, 'f', 5));
    ui->lngValueText->setText(QString::number(lng, 'f', 5));
    ui->satText->setText(QString::number(sat));
    ui->headingText->setText(currentHeading);
}

void MainWindow::rotateImage(int deg)
{
    QTransform transform;
    transform.rotate(deg);

    ui->coursePic->setPixmap(headingPixMap->transformed(transform));
}

void MainWindow::changeHdopColor(int val)
{
    if(val > 0 && val < 120){
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

void MainWindow::checkPortStatus()
{
    if(!monitor->isPortOpen()){
        ui->errText->setText("Error on opening port");
    }
}

void MainWindow::checkQuadrantName(double deg)
{
    int x = deg / 45.0;

    currentHeading = quadrants[x];
}

void MainWindow::serialDataSlot(QJsonObject data)
{
    if(data.contains("error")){
        startBlinkTimer();

        // reset stylesheet in case of error
        ui->accValue->setStyleSheet("");
        qDebug() << "Error:" << data["error"].toString();

        return;
    }

    // check data keys length to determine that the data was not empty
    if(data.keys().length() < 7){
        return;
    }

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
    checkQuadrantName(course);

    setValues();
}

