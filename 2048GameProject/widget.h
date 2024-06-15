//主界面头文件代码及相关ui界面的设置
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QMessageBox>

namespace Ui{
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public :
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void paintEvent(QPaintEvent *);                    //背景事件函数

signals:
    void showwnd();                                    //连接主界面和游戏界面的信号

private slots:

    void on_pushButton_goon_clicked();                 //开始游戏操作
    void on_pushButton_help_clicked();                 //帮助按键操作
    void on_pushButton_close_clicked();                //退出游戏操作
    void getshowdlg();                                 //获取游戏界面的信号

private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
