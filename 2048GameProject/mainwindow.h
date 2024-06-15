#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include <QTextBrowser>
#include <QSettings>
//#include <QTextCodec>
#include <QTimer>
#include <QDateTime>
//#include <QSound>
#include <QSoundEffect>
#include <QPaintEvent>
#include <QPainter>
#include <QFile>
#include "gamelogic.h"


//游戏界面头文件代码及相关ui界面的设置
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool isPlay = true;                             //默认设置音乐关
    GameLogic* game;                                //游戏对象
    QSoundEffect* voice;                            //游戏声音对象
    int highGrade = 0;                              //最高分

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initAll();                                 //初始化界面
    void showMessage();                             //展示信息
    void showBroad();                               //展示游戏界面
    void keyPressEvent(QKeyEvent *event);           //按键事件
    void changeColor(QLabel* label, int num);       //根据value自动调整颜色
    void Music_On();                                //背景音乐
    void paintEvent(QPaintEvent *);                 //游戏背景事件

signals:

    void showdlg();                                 //连接主界面和游戏界面的信号

private slots:

    void on_pushButton_start_clicked();             //开始按钮

    void on_pushButton_close_clicked();             //退出按钮

    void on_pushButton_music_clicked();             //背景音乐按钮

    void on_horizontalSlider_valueChanged(int value);//进度条设置游戏加成比例

    void timeUpdate();                              //时间更新函数

    void getshowwnd();                              //接收来自主界面的信号

    void showBestGrade(int);                        //最高分显示
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
