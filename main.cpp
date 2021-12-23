#include "mainwindow.h"

#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(560,306);
    w.setGeometry(QStyle::alignedRect(Qt::LeftToRight,
         Qt::AlignCenter, w.size(), qApp->desktop()->availableGeometry()));
    w.show();
    return a.exec();
}
