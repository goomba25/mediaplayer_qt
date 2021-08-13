#include "windowframe.h"

WindowFrame::WindowFrame(QWidget *parent)
    : QMainWindow(parent)
{
    center = new QStackedWidget;

    video_player = new VideoPlayer;
    image_viewer = new ImageViewer;
    center->insertWidget(0, video_player);
    center->insertWidget(1, image_viewer);
    center->setCurrentIndex(1);

    this->setCentralWidget(center);
}
