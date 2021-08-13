#include "imageviewer.h"

ImageViewer::ImageViewer(QWidget *parent)
    : QWidget(parent)
{
    full_layout = new QVBoxLayout;
    full_layout->setMargin(0);

    timer = new QTimer(this);

    btn_box = new QHBoxLayout;
    for (int i=0; i<MEDIA_NUM; i++)
    {
        btn[i] = new QPushButton(QString::number(i+1));
        btn_box->addWidget(btn[i]);
        connect(btn[i], &QPushButton::clicked, this, &ImageViewer::viewer_Select);
    }

    dir_Set();
    imageList_Set();
    viewer_Set();
    connect_Set();

    full_layout->addLayout(btn_box);
    full_layout->addWidget(viewer);
    setLayout(full_layout);
}

void ImageViewer::changeImageList(int num)
{
    if(num < MEDIA_NUM)
//        viewer_Select(num);
        ;
    else
        return;
}

void ImageViewer::dir_Set()
{
    main_dir = QDir(IMAGE_PATH);
    if(!main_dir.exists())
        main_dir.mkpath(IMAGE_PATH);

    main_dir_list = main_dir.entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot);
    for (int cnt=0; cnt<main_dir_list.size(); cnt++)
    {
        QFileInfo var = main_dir_list.at(cnt);
        sub_dir_name[cnt] = var.absoluteFilePath();
    }
}

void ImageViewer::imageList_Set()
{
    for (int i=0; i<MEDIA_NUM; i++)
    {
        img_list[i] = new QListWidget;
        sub_dir[i] = QDir(IMAGE_PATH + QString::number(i+1));
        if(!sub_dir[i].exists())
            sub_dir[i].mkpath(IMAGE_PATH + QString::number(i+1));

        sub_dir_list[i] = sub_dir[i].entryInfoList(QDir::Files|QDir::NoDotAndDotDot);
        for (int cnt = 0; cnt < sub_dir_list[i].size(); cnt++)
        {
            QFileInfo var = sub_dir_list[i].at(cnt);
            img_list[i]->insertItem(cnt,var.absoluteFilePath());
        }
    }
}

void ImageViewer::viewer_Set()
{
    viewer = new QLabel;
    viewer->setAlignment(Qt::AlignCenter);
    image = new QPixmap;
    viewer->clear();
}

void ImageViewer::connect_Set()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(viewer_Show()));
}

void ImageViewer::viewer_Select()
{
    /*
    if(0 != img_list[num]->count())
    {
        count = 0;
        image->load(img_list[num]->item(count)->text());
        viewer->setPixmap(image->scaled(viewer->width(), viewer->height(), Qt::KeepAspectRatio));
        timer->start(2000);
    }

    else
    {
        viewer->clear();
        timer->stop();
    }
    */

    QObject *obj = sender();

    for (int i=0; i<MEDIA_NUM; i++)
    {
        if(obj == btn[i])
        {
            img_target_list = img_list[i];
            if(0 != img_target_list->count())
            {
                count = 0;
                image->load(img_target_list->item(count)->text());
                viewer->setPixmap(image->scaled(viewer->width(), viewer->height(), Qt::KeepAspectRatio));
                timer->start(2000);
            }

            else
            {
                viewer->clear();
                timer->stop();
            }
        }
    }
}

void ImageViewer::viewer_Show()
{
    if(img_target_list->count()-1 > count)
    {
        ++count;
    }

    else
        count = 0;

    image->load(img_target_list->item(count)->text());
    viewer->setPixmap(image->scaled(viewer->width(), viewer->height(), Qt::KeepAspectRatio));
}
