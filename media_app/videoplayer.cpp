#include "videoplayer.h"

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent)
{
    full_layout = new QVBoxLayout;
    full_layout->setMargin(0);

    dir_Set();
    playList_Set();
    player_Set();

    setPlayMode(0);

    QHBoxLayout *hbox = new QHBoxLayout;
    btn[0] = new QPushButton("1");
    btn[1] = new QPushButton("2");
    btn[2] = new QPushButton("3");
    btn[3] = new QPushButton("4");
    hbox->addWidget(btn[0]);
    hbox->addWidget(btn[1]);
    hbox->addWidget(btn[2]);
    hbox->addWidget(btn[3]);

    for (int i=0; i<4; i++)
    {
        connect(btn[i], &QPushButton::clicked, this, &VideoPlayer::btn_clicked);
    }

    full_layout->addLayout(hbox);
    full_layout->addWidget(video_widget);
    setLayout(full_layout);
}

void VideoPlayer::btn_clicked()
{
    QObject *obj = sender();

    if(obj == btn[0])
    {
        setPlayMode(0);
        changePlayList(0);
        setPlayMode(1);
    }
    else if(obj == btn[1])
    {
        setPlayMode(0);
        changePlayList(1);
        setPlayMode(1);
    }

    else if(obj == btn[2])
    {
        setPlayMode(0);
        changePlayList(2);
        setPlayMode(1);
    }

    else
    {
        setPlayMode(0);
        changePlayList(3);
        setPlayMode(1);
    }
}

void VideoPlayer::setPlayMode(bool mode)
{
    if(mode == true)
        player->play();
    else
        player->stop();
}

void VideoPlayer::changePlayList(int num)
{
    if(num < MEDIA_NUM)
        player->setPlaylist(play_list[num]);
    else
        return;
}

void VideoPlayer::dir_Set()
{
    main_dir = QDir(VIDEO_PATH);
    if(!main_dir.exists())
        main_dir.mkpath(VIDEO_PATH);

    main_dir_list = main_dir.entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot);
    for (int cnt=0; cnt<main_dir_list.size(); cnt++)
    {
        QFileInfo var = main_dir_list.at(cnt);
        sub_dir_name[cnt] = var.absoluteFilePath();
    }
}

void VideoPlayer::playList_Set()
{
    for (int i=0; i<MEDIA_NUM; i++)
    {
        sub_dir[i] = QDir(VIDEO_PATH + QString::number(i+1));
        if(!sub_dir[i].exists())
            sub_dir[i].mkpath(VIDEO_PATH + QString::number(i+1));

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

void VideoPlayer::player_Set()
{
    video_widget = new QVideoWidget;

    player = new QMediaPlayer(this);
    player->setVideoOutput(video_widget);
    player->setPlaylist(play_list[0]);  //  default
}
