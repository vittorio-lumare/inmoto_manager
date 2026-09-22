#include "inmotomanager.h"
#include "ui_inmotomanager.h"
#include <QDebug>

namespace fs = std::filesystem;

InMotoManager::InMotoManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InMotoManager)
{
    ui->setupUi(this);

    // ROS2 container process
    ros_start_process_ = new QProcess(this);
    ros_kill_process_ = new QProcess(this);


    connect(ui->on_btn, &QPushButton::clicked, this, &InMotoManager::onStartButtonClicked);
    connect(ui->off_btn, &QPushButton::clicked, this, &InMotoManager::onStopButtonClicked);

    // Led Widget
    ui->power_led->setShape(QLed::ledShape::Circle);
    ui->power_led->setColor(QColor("green"));
}

void InMotoManager::onStartButtonClicked() {
    if (ros_start_process_->state() != QProcess::NotRunning) {
        qDebug() << "ROS 2 already active!";
        return;
    }

    //ros_process_->setCreateProcessGroup(true);

    QString prog = "bash";
    QStringList args;

    args << "-c" << "source /opt/ros/humble/setup.bash && source ~/inmoto_ws/install/setup.bash && ros2 launch inmoto_ros main_launch.py";

    qDebug() << "Starting ROS 2...";
    ros_start_process_->start(prog, args);

    // Turn on power led
    ui->power_led->setValue(true);
}

void InMotoManager::onStopButtonClicked() {

    if (ros_start_process_->state() == QProcess::NotRunning) return;

    QString prog = "bash";
    QStringList args;

    args << "-c" << "source /opt/ros/humble/setup.bash && source ~/inmoto_ws/install/setup.bash && ros2 service call /inmoto/shutdowner/shutdown_system std_srvs/srv/Trigger {}";

    qDebug() << "Shutting down ROS 2...";
    ros_kill_process_->start(prog, args);

    qDebug() << "ROS 2 shut down successfully.";

    // Turn off power led
    ui->power_led->setValue(false);
}


InMotoManager::~InMotoManager()
{
    onStopButtonClicked(); // Turns off all processes if the user closes the app 'InMotoManager'
    delete ui; // Release GUI memory
}
