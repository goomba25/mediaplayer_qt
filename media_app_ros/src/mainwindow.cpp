#include <QDebug>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    center_widget = new QStackedWidget(this);
    video_widget = new VideoWidget(this);
    image_widget = new ImageWidget(this);

    center_widget->insertWidget(0, video_widget);
    center_widget->insertWidget(1, image_widget);
    center_widget->setCurrentIndex(0);

    this->setCentralWidget(center_widget);

    connect(&m_Robot, &QRobot::AuroraStatusSignal,
            this, &MainWindow::AuroraStatusSlot);

    if(!m_Robot.RobotInit())
    {
        qDebug() << "Robot Init failed...";
    }
//    image_widget->changeImageList(0);
    video_widget->changePlayList(0);
    video_widget->setPlayMode(1);
}

void MainWindow::AuroraStatusSlot()
{
    if(m_Robot.m_AuroraStatus.spray_status == 1)
    {
        qDebug() << "Aurora Status received\n[Spray ON]";
//        image_widget->changeImageList(0);
//        image_widget->setPlayMode(1);
    }

    else
    {
        qDebug() << "Aurora Status received\n[Spray OFF]";
//        image_widget->changeImageList(1);
//        image_widget->setPlayMode(1);
    }
}
