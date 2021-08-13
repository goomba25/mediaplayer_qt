#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QDir>
#include <QFile>
#include <QListWidget>
#include <QTimer>

#define IMAGE_DIR_NUM 2
#define IMAGE_DIR_PATH "/home/felix/catkin_ws/src/media_app_ros/image/"

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr);
    void setPlayMode(bool mode);
    void changeImageList(int num);

private:
    QVBoxLayout *full_layout;
    QLabel *viewer;
    QPixmap *image;
    QFileInfoList main_dir_list, sub_dir_list[IMAGE_DIR_NUM];
    QDir main_dir, sub_dir[IMAGE_DIR_NUM];
    QString sub_dir_name[IMAGE_DIR_NUM];
    QListWidget *img_list[IMAGE_DIR_NUM], *img_target_list;
    QTimer *timer;

    int image_num = 0;

    void image_dir_init();
    void imageList_Set();
    void viewer_Set();
    void connect_Set();
    void viewer_Select(int num);

private slots:
    void viewer_Show();
};

#endif // IMAGEWIDGET_H
