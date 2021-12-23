#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void IsRunned();
    void IsStoped();
    void check_finished(int _status_smbd, int _status_nmbd);
    void sig_clicked(int k);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setStatus(int _status_smbd, int _status_nmbd);
    void runService();
    void stopService();
    void statusChecker();
    void serviceHandler(int k);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
