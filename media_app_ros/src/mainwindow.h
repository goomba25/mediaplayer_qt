#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "videowidget.h"
#include "imagewidget.h"

#include "media_app_ros/MsgAuroraStatus.h"
#include "qrobot.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *center_widget;
    VideoWidget *video_widget;
    ImageWidget *image_widget;

    QRobot m_Robot;

private slots:
    void AuroraStatusSlot();
};

#endif // MAINWINDOW_H
