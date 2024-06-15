//主函数
#include "widget.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //抽象应用程序

    Widget wi;
    MainWindow w;
    w.setWindowTitle(QString("2048小游戏"));
    wi.setWindowTitle(QString("2048小游戏"));
    wi.show();
    w.hide();

    //connect槽，连接主界面和游戏界面，实现自由切换
    QObject::connect(&wi,SIGNAL(showwnd()),&w,SLOT(getshowwnd()));
    QObject::connect(&w,SIGNAL(showdlg()),&wi,SLOT(getshowdlg()));

    return a.exec();
}
