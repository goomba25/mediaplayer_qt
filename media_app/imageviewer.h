#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QDir>
#include <QFile>
#include <QListWidget>
#include <QTimer>
#include <QPushButton>

#define MEDIA_NUM 2
#define IMAGE_PATH "/home/felix/WorkSpace/Qt/media_app/image/"

class ImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewer(QWidget *parent = nullptr);
    void changeImageList(int num);

private:
    QVBoxLayout *full_layout;
    QLabel *viewer;
    QPixmap *image;
    QFileInfoList main_dir_list, sub_dir_list[MEDIA_NUM];
    QDir main_dir, sub_dir[MEDIA_NUM];
    QString sub_dir_name[MEDIA_NUM];
    QListWidget *img_list[MEDIA_NUM], *img_target_list;
    QTimer *timer;

    QHBoxLayout *btn_box;
    QPushButton *btn[MEDIA_NUM];

    int count = 0;

    void dir_Set();
    void imageList_Set();
    void viewer_Set();
    void connect_Set();
//    void viewer_Select(int num);

private slots:
    void viewer_Select();
    void viewer_Show();
};

#endif // IMAGEVIEWER_H
