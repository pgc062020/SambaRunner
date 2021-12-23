#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_2->clear();
    ui->label_4->clear();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::statusChecker);
    timer->start(500);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::runService);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::stopService);
    QObject::connect(this, &MainWindow::sig_clicked, this, &MainWindow::serviceHandler);
    QObject::connect(this, &MainWindow::check_finished, this, &MainWindow::setStatus);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStatus(int _status_smbd, int _status_nmbd)
{
    int _value_smbd=0;
    int _value_nmbd=0;

    if(_status_smbd != _value_smbd)
    {
        _value_smbd = _status_smbd;
        if(_value_smbd==1)
        {
            ui->label_2->setText("Stopped");
            ui->label_2->setStyleSheet("QLabel { color : red; font: italic;}");
        }
        if(_value_smbd==2)
        {
            ui->label_2->setText("Runned");
            ui->label_2->setStyleSheet("QLabel { color : green; font: italic;}");
        }
    }

    if(_status_nmbd != _value_nmbd)
    {
        _value_nmbd = _status_nmbd;
        if(_value_nmbd==1)
        {
            ui->label_4->setText("Stopped");
            ui->label_4->setStyleSheet("QLabel { color : red; font: italic;}");
        }
        if(_value_nmbd==2)
        {
            ui->label_4->setText("Runned");
            ui->label_4->setStyleSheet("QLabel { color : green; font: italic;}");
        }
    }
}

void MainWindow::statusChecker()
{
    int _status_smbd=0;
    int _status_nmbd=0;

    QString executable("systemctl");
    QStringList _serviceList;
    _serviceList << "smbd" << "nmbd";
    QString _out;

    QProcess _runCmd;
    QStringList arguments;

    for(int i=0; i < _serviceList.size(); i++)
    {
        arguments << "is-active" << _serviceList.at(i);
        _runCmd.start(executable, arguments);
        _runCmd.waitForReadyRead();
        _runCmd.waitForFinished();
        _out = _runCmd.readAllStandardOutput();
        _out = _out.trimmed();
        _runCmd.close();
        if(_serviceList.at(i) == "smbd")
        {
            if(_out == "inactive")
            {
                _status_smbd=1;
            }
            if(_out == "active")
            {
                _status_smbd=2;
            }
        }
        if(_serviceList.at(i) == "nmbd")
        {
            if(_out == "inactive")
            {
                _status_nmbd=1;
            }
            if(_out == "active")
            {
                _status_nmbd=2;
            }
        }
        _out.clear();
        arguments.clear();
        emit check_finished(_status_smbd, _status_nmbd);
    }
}

void MainWindow::runService()
{
    int k=1;
    emit sig_clicked(k);
}

void MainWindow::stopService()
{
    int k=2;
    emit sig_clicked(k);
}

void MainWindow::serviceHandler(int k)
{
    QString executable("service");
    QStringList _serviceList;
    _serviceList << "smbd" << "nmbd";
    QString startorstop="start";
    QStringList arguments;

    QProcess _serviceHandler;

    if(k==1)
    {
        startorstop="start";
    } else
    {
        startorstop="stop";
    }

    for(int o=0; o<_serviceList.size();o++)
    {
        arguments << _serviceList.at(o) << startorstop;
        _serviceHandler.start(executable, arguments);
        _serviceHandler.waitForFinished();
        _serviceHandler.close();
        arguments.clear();
    }
    startorstop.clear();
}
