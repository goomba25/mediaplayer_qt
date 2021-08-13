#include <QDebug>
#include <QImage>
#include "qrobot.h"

QRobot::QRobot(QObject *parent) : QObject(parent)
{
    m_pFollowImg = new QImage(&m_FollowImgBuf[0], ROS_FOLLOW_IMG_W, ROS_FOLLOW_IMG_H, QImage::Format_RGB888);
    connect(&m_ROS, &QRos::rosShutdown, this, &QRobot::RosShutdownSlot);
    connect(&m_OpenTimer, &QTimer::timeout, this, &QRobot::RosOpenTimeoutSlot);
}

QRobot::~QRobot()
{
    RosClose();
    delete m_pFollowImg;
    disconnect(&m_ROS, &QRos::rosShutdown, this, &QRobot::RosShutdownSlot);
    disconnect(&m_OpenTimer, &QTimer::timeout, this, &QRobot::RosOpenTimeoutSlot);
}

bool QRobot::RobotInit(void)
{
    if(RosOpen()) return true;
    m_OpenTimer.start(1000);
    return false;
}

bool QRobot::RosOpen(){
    if(m_IsOK) return true;
    if(m_ROS.rosOpen() == false){
        qDebug() << "RosOpen failed";
        return false;
    }
    m_IsOK = true;
    // m_PubAuroraStatus = m_ROS.Advertise<fm_publisher::MsgAuroraStatus>(ROS_AURORA_STATUS_TOPIC, 1024);
    m_SubAuroraStatus = m_ROS.Subscribe(ROS_AURORA_STATUS_TOPIC, 1024, &QRobot::SubAuroraStatusCB, this);
    qDebug() << "Ros Opend";
    emit RobotInfoSignal(ROS_OPEND);
    return true;
}

void QRobot::RosClose(){
    m_ROS.UnSubscribe(m_SubAuroraStatus);
    m_ROS.UnSubscribe(m_SubFollowImage);
    m_ROS.UnAdvertise(m_PubAuroraStatus);
    m_ROS.rosClose();
    m_IsOK = false;
    emit RobotInfoSignal(ROS_CLOSED);
    qDebug() << "Ros closed";
}

void QRobot::SubAuroraStatusCB(const front_monitor_app::MsgAuroraStatus& message_holder)
{
    m_AuroraStatus.drive_mode = message_holder.drive_mode;
    m_AuroraStatus.drive_status = message_holder.drive_status;
    m_AuroraStatus.spray_status = message_holder.spray_status;
    m_AuroraStatus.error_status = message_holder.error_status;
    emit AuroraStatusSignal();
    qDebug() << "SubAuroraStatusCB";
}

bool QRobot::ChangeAuroraStatus(std::string drive_mode, int drive_status, int spray_status, int error_status){
    front_monitor_app::MsgAuroraStatus msg;
    if(!m_IsOK) return false;
    msg.drive_mode = drive_mode;
    msg.drive_status = drive_status;
    msg.spray_status = spray_status;
    msg.error_status = error_status;
    return m_ROS.Publish(m_PubAuroraStatus, msg);
}

void QRobot::SubFollowImageCB(const sensor_msgs::Image& message_holder)
{
    if(message_holder.data.size() == ROS_FOLLOW_IMG_DATA_SIZE){
        m_FollowImgMutex.lock();
        memcpy(&m_FollowImgBuf[0], &message_holder.data[0], ROS_FOLLOW_IMG_DATA_SIZE);
        m_FollowImgMutex.unlock();
        emit FollowImageReadySignal();
    }
}

bool QRobot::FollowImageRequest(bool isStart){
    if(!m_IsOK) return false;
    if(isStart){
        if(!m_ROS.isValidSubscriber(m_SubFollowImage)){
            m_SubFollowImage = m_ROS.Subscribe(ROS_FOLLOW_IMG_TOPIC, 1024000, &QRobot::SubFollowImageCB, this);
            if(!m_ROS.isValidSubscriber(m_SubFollowImage)) return false;
        }
        return true;
    }
    else{
        m_ROS.UnSubscribe(m_SubFollowImage);
        return true;
    }
}

QPixmap QRobot::GetFollowImg(){
    m_FollowImgMutex.lock();
    QPixmap pix = QPixmap::fromImage(*m_pFollowImg);
    m_FollowImgMutex.unlock();
    return pix;
}

void QRobot::RosShutdownSlot(){
    qDebug() << "RosShutdown";
    emit RobotInfoSignal(ROS_SHUTDOWN);
    RosClose();
    m_OpenTimer.start(1000);
}

void QRobot::RosOpenTimeoutSlot(){
    if(RosOpen()){
        m_OpenTimer.stop();
    }
}



