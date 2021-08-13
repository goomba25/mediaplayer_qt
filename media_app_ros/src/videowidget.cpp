#include "videowidget.h"

VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent)
{
    full_layout = new QVBoxLayout;
    full_layout->setMargin(0);

    video_dir_init();
    playList_Set();
    player_Set();

    full_layout->addWidget(video_widget);
    setLayout(full_layout);
}

void VideoWidget::setPlayMode(bool mode)
{
    if(mode == true)
        player->play();
    else
        player->stop();
}

void VideoWidget::changePlayList(int num)
{
    if(num < VIDEO_DIR_NUM)
        player->setPlaylist(play_list[num]);
    else
        return;
}

void VideoWidget::video_dir_init()
{
    main_dir = QDir(VIDEO_DIR_PATH);
    if(!main_dir.exists())
        main_dir.mkpath(VIDEO_DIR_PATH);

    main_dir_list = main_dir.entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot);
    for (int cnt=0; cnt<main_dir_list.size(); cnt++)
    {
        QFileInfo var = main_dir_list.at(cnt);
        sub_dir_name[cnt] = var.absoluteFilePath();
    }
}

void VideoWidget::playList_Set()
{
    for (int i=0; i<VIDEO_DIR_NUM; i++)
    {
        sub_dir[i] = QDir(VIDEO_DIR_PATH + QString::number(i+1));
        if(!sub_dir[i].exists())
            sub_dir[i].mkpath(VIDEO_DIR_PATH + QString::number(i+1));

        play_list[i] = new QMediaPlaylist;
        play_list[i]->setPlaybackMode(QMediaPlaylist::Loop);
        sub_dir_list[i] = sub_dir[i].entryInfoList(QDir::Files|QDir::NoDotAndDotDot);
        for (int cnt = 0; cnt < sub_dir_list[i].size(); cnt++)
        {
            QFileInfo var = sub_dir_list[i].at(cnt);
            play_list[i]->insertMedia(cnt, QUrl::fromLocalFile(var.absoluteFilePath()));
        }
        play_list[i]->setCurrentIndex(0);
    }
}

void VideoWidget::player_Set()
{
    video_widget = new QVideoWidget;

    player = new QMediaPlayer(this);
    player->setVideoOutput(video_widget);
    player->setPlaylist(play_list[0]);  //  default
}
