#ifndef WINDOWFRAME_H
#define WINDOWFRAME_H

#include <QMainWindow>
#include <QGridLayout>
#include <QStackedWidget>

#include "videoplayer.h"
#include "imageviewer.h"

class WindowFrame : public QMainWindow
{
    Q_OBJECT
public:
    explicit WindowFrame(QWidget *parent = nullptr);

private:
    QStackedWidget *center;
    VideoPlayer *video_player;
    ImageViewer *image_viewer;
};

#endif // WINDOWFRAME_H
