#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent)
    : QWidget(parent)
{
    full_layout = new QVBoxLayout;
    full_layout->setMargin(0);

    timer = new QTimer(this);

    image_dir_init();
    imageList_Set();
    viewer_Set();
    connect_Set();

    full_layout->addWidget(viewer);
    setLayout(full_layout);
}

void ImageWidget::setPlayMode(bool mode)
{
    if(mode == true)
        timer->start(2000);
    else
        timer->stop();
}

void ImageWidget::changeImageList(int num)
{
    if(num < IMAGE_DIR_NUM)
        viewer_Select(num);
    else
        return;
}

void ImageWidget::image_dir_init()
{
    main_dir = QDir(IMAGE_DIR_PATH);
    if(!main_dir.exists())
        main_dir.mkpath(IMAGE_DIR_PATH);

    main_dir_list = main_dir.entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot);
    for (int cnt=0; cnt<main_dir_list.size(); cnt++)
    {
        QFileInfo var = main_dir_list.at(cnt);
        sub_dir_name[cnt] = var.absoluteFilePath();
    }
}

void ImageWidget::imageList_Set()
{
    for (int i=0; i<IMAGE_DIR_NUM; i++)
    {
        img_list[i] = new QListWidget(this);
        sub_dir[i] = QDir(IMAGE_DIR_PATH + QString::number(i+1));
        if(!sub_dir[i].exists())
            sub_dir[i].mkpath(IMAGE_DIR_PATH + QString::number(i+1));

        sub_dir_list[i] = sub_dir[i].entryInfoList(QDir::Files|QDir::NoDotAndDotDot);
        for (int cnt = 0; cnt < sub_dir_list[i].size(); cnt++)
        {
            QFileInfo var = sub_dir_list[i].at(cnt);
            img_list[i]->insertItem(cnt,var.absoluteFilePath());
        }
    }
}

void ImageWidget::viewer_Set()
{
    viewer = new QLabel(this);
    viewer->setAlignment(Qt::AlignCenter);
    image = new QPixmap;
    viewer->clear();
}

void ImageWidget::connect_Set()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(viewer_Show()));
}

void ImageWidget::viewer_Select(int num)
{
    if(0 != img_list[num]->count())
    {
        image_num = 0;
        image->load(img_list[num]->item(image_num)->text());
        viewer->setPixmap(image->scaled(viewer->width(), viewer->height(), Qt::KeepAspectRatio));
        img_target_list = img_list[num];
    }

    else
    {
        viewer->clear();
    }
}

void ImageWidget::viewer_Show()
{
    if(img_target_list->count() == 1)
        image_num = 0;

    if(img_target_list->count()-1 > image_num)
    {
        ++image_num;
    }

    else
        image_num = 0;

    image->load(img_target_list->item(image_num)->text());
    viewer->setPixmap(image->scaled(viewer->width(), viewer->height(), Qt::KeepAspectRatio));
}
