#pragma once

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class InMotoManager;
}

class InMotoManager : public QMainWindow
{
    Q_OBJECT

public:
    InMotoManager(QWidget *parent = nullptr);
    ~InMotoManager();

private slots:
    void onStartButtonClicked();
    void onStopButtonClicked();

private:
    Ui::InMotoManager *ui;
    QProcess *ros_start_process_;
    QProcess *ros_kill_process_;
};
