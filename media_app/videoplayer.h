#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QGridLayout>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QDir>
#include <QFile>
#include <QPushButton>

#define MEDIA_NUM 4
#define VIDEO_PATH "/home/felix/WorkSpace/Qt/media_app/video/"

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayer(QWidget *parent = nullptr);
    void setPlayMode(bool mode);
    void changePlayList(int num);

private:
    QVBoxLayout *full_layout;
    QMediaPlayer *player;
    QMediaPlaylist *play_list[MEDIA_NUM];
    QVideoWidget *video_widget;
    QFileInfoList main_dir_list, sub_dir_list[MEDIA_NUM];
    QDir main_dir, sub_dir[MEDIA_NUM];
    QString sub_dir_name[MEDIA_NUM];
    QPushButton *btn[4];

    void dir_Set();
    void playList_Set();
    void player_Set();

private slots:
    void btn_clicked();
};

#endif // VIDEOPLAYER_H
