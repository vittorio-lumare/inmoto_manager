#pragma once

#include <QMainWindow>
#include <QProcess>

#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/trigger.hpp>

namespace Ui {
class InMotoManager;
}

class InMotoManager : public QMainWindow
{
    Q_OBJECT

public:
    InMotoManager(QWidget *parent = nullptr);
    ~InMotoManager();
    void waitManagingGUI(int msecs, bool disable_gui);

private:
    // ROS calls
    void ROS_startup();
    void ROS_shutdown();
    void ROS_clearTrajectory();

private slots:
    void onStartButtonClicked();
    void onStopButtonClicked();
    void on_start_exercise_btn_clicked();

private:
    Ui::InMotoManager *ui;
    QProcess *ros_start_process_;
    QProcess *ros_kill_process_;
    QProcess *ros_start_bag_recording_;
    QProcess *ros_stop_bag_recording_;
    QProcess *ros_clear_trajectory_;

    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr client_;

};
