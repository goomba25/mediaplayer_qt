#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QDir>
#include <QFile>
#include <QPushButton>

#define VIDEO_DIR_NUM 4
#define VIDEO_DIR_PATH "/home/felix/catkin_ws/src/media_app_ros/video/"

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);
    void setPlayMode(bool mode);
    void changePlayList(int num);

private:
    QVBoxLayout *full_layout;
    QMediaPlayer *player;
    QMediaPlaylist *play_list[VIDEO_DIR_NUM];
    QVideoWidget *video_widget;
    QFileInfoList main_dir_list, sub_dir_list[VIDEO_DIR_NUM];
    QDir main_dir, sub_dir[VIDEO_DIR_NUM];
    QString sub_dir_name[VIDEO_DIR_NUM];

    void video_dir_init();
    void playList_Set();
    void player_Set();
};

#endif // VIDEOWIDGET_H
