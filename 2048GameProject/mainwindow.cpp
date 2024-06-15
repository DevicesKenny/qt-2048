//游戏界面的设置
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamelogic.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    game = new GameLogic;
    ui->setupUi(this);
    //this->setStyleSheet("background-color:rgb(120, 132, 145)");
    showBroad();
    //锁定窗口大小
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(),this->height());

    //获取当前系统时间
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeUpdate()));
    timer->start(1000);

    QByteArray qba;
    //读取最高分的文件
    QFile file(":/test.db");
    if(file.open(QIODevice::ReadOnly ))
    {
        // file.read((char*)&highGrade,sizeof(highGrade));
        qba = file.readLine();
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/main_duolaameng.jpg"),QRect());
}

void MainWindow::timeUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->label_time->setText(str);
}


void MainWindow::initAll()
{
    game->initAll();
    on_horizontalSlider_valueChanged(ui->horizontalSlider->value());
}

void MainWindow::on_pushButton_start_clicked()
{
    ui->pushButton_start->setText("重新开始");
    initAll();

    //初始化默认创建两个数
    game->createNum();
    game->createNum();
    game->setGameStart(true);

    showBroad();
    showMessage();
}

void MainWindow::showBestGrade(int score)
{
    qDebug() << "score:" << score;
    // 如果当前分数高于最高分
    if (score >= highGrade)
    {
        // 更新最高分
        highGrade = score;
        ui->label_showBest->setText(QString("%1").arg(highGrade));

        // 将新的最高分存入文件

        QFile file(":/test.db");
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);
        out << highGrade;
        file.close();
    }
}
void MainWindow::Music_On()
{
    if(isPlay)
    {
        ui->pushButton_music->setText("音乐：开");
        voice = new QSoundEffect(this);
        voice->setSource(QUrl::fromLocalFile(":/supermario.wav"));
        voice->setLoopCount(QSoundEffect::Infinite);
        voice->setVolume(1.0);
        voice->play();
    }
    else
    {
        voice->stop();
        ui->pushButton_music->setText("音乐：关");
    }
    isPlay = !isPlay;
}

void MainWindow::on_pushButton_music_clicked()
{
    Music_On();
}

void MainWindow::on_pushButton_close_clicked()
{
    this->hide();
    emit showdlg();
}

void MainWindow::getshowwnd()
{
    this->show();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    value = ui->horizontalSlider->value();
    ui->label_showGradeUpCoefficient->setText(QString::number(value*2)+"%");
    game->setGradeUpCoefficient((float)ui->horizontalSlider->value()/100);

    if     (value < 20)
        ui->label_showDifficult->setText("简单");
    else if(value < 40)
        ui->label_showDifficult->setText("正常");
    else if(value < 60)
        ui->label_showDifficult->setText("困难");
    else if(value < 80)
        ui->label_showDifficult->setText("地狱");
    else
        ui->label_showDifficult->setText("混沌");
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!game->getGameStart())
        return;
    switch(event->key())
    {
    case Qt::Key_W:
        game->process(CMD_UP);
        showBestGrade(game->getGrade());
        break;
    case Qt::Key_S:
        game->process(CMD_DOWN);
        showBestGrade(game->getGrade());
        break;
    case Qt::Key_A:
        game->process(CMD_LEFT);
        showBestGrade(game->getGrade());
        break;
    case Qt::Key_D:
        game->process(CMD_RIGHT);
        showBestGrade(game->getGrade());
        break;
    }
    showBroad();
    showMessage();
    switch(game->judge())
    {
    case STAT_PROCESS:
        break;
    case STAT_WIN:
        QMessageBox::information(NULL,"2048","大吉大利，今晚吃鸡！\n\t兄弟，牛逼！");
        break;
    case STAT_LOSE:
        QMessageBox::information(NULL,"2048","兄弟，你噶了！");
        break;
    }
}

void MainWindow::showMessage()
{
    ui->label_showGrade->setText(QString::number(game->getGrade()));
    ui->label_showGradeBasic->setText(QString::number(game->getGradeBasic()));
    ui->label_showGradeUp->setText(QString::number(game->getGradeUp()));
    ui->label_showStep->setText(QString::number(game->getStep()));
}

void MainWindow::showBroad()
{
    //第一行
    if(game->getData(0,0))
        ui->label_00->setText(QString::number(game->getData(0,0)));
    else
        ui->label_00->setText(" ");
    if(game->getData(0,1))
        ui->label_01->setText(QString::number(game->getData(0,1)));
    else
        ui->label_01->setText(" ");
    if(game->getData(0,2))
        ui->label_02->setText(QString::number(game->getData(0,2)));
    else
        ui->label_02->setText(" ");
    if(game->getData(0,3))
        ui->label_03->setText(QString::number(game->getData(0,3)));
    else
        ui->label_03->setText(" ");
    changeColor(ui->label_00, game->getData(0,0));
    changeColor(ui->label_01, game->getData(0,1));
    changeColor(ui->label_02, game->getData(0,2));
    changeColor(ui->label_03, game->getData(0,3));

    //第二行
    if(game->getData(1,0))
        ui->label_10->setText(QString::number(game->getData(1,0)));
    else
        ui->label_10->setText(" ");
    if(game->getData(1,1))
        ui->label_11->setText(QString::number(game->getData(1,1)));
    else
        ui->label_11->setText(" ");
    if(game->getData(1,2))
        ui->label_12->setText(QString::number(game->getData(1,2)));
    else
        ui->label_12->setText(" ");
    if(game->getData(1,3))
        ui->label_13->setText(QString::number(game->getData(1,3)));
    else
        ui->label_13->setText(" ");
    changeColor(ui->label_10, game->getData(1,0));
    changeColor(ui->label_11, game->getData(1,1));
    changeColor(ui->label_12, game->getData(1,2));
    changeColor(ui->label_13, game->getData(1,3));

    //第三行
    if(game->getData(2,0))
        ui->label_20->setText(QString::number(game->getData(2,0)));
    else
        ui->label_20->setText(" ");
    if(game->getData(2,1))
        ui->label_21->setText(QString::number(game->getData(2,1)));
    else
        ui->label_21->setText(" ");
    if(game->getData(2,2))
        ui->label_22->setText(QString::number(game->getData(2,2)));
    else
        ui->label_22->setText(" ");
    if(game->getData(2,3))
        ui->label_23->setText(QString::number(game->getData(2,3)));
    else
        ui->label_23->setText(" ");
    changeColor(ui->label_20, game->getData(2,0));
    changeColor(ui->label_21, game->getData(2,1));
    changeColor(ui->label_22, game->getData(2,2));
    changeColor(ui->label_23, game->getData(2,3));

    //第四行
    if(game->getData(3,0))
        ui->label_30->setText(QString::number(game->getData(3,0)));
    else
        ui->label_30->setText(" ");
    if(game->getData(3,1))
        ui->label_31->setText(QString::number(game->getData(3,1)));
    else
        ui->label_31->setText(" ");
    if(game->getData(3,2))
        ui->label_32->setText(QString::number(game->getData(3,2)));
    else
        ui->label_32->setText(" ");
    if(game->getData(3,3))
        ui->label_33->setText(QString::number(game->getData(3,3)));
    else
        ui->label_33->setText(" ");
    changeColor(ui->label_30, game->getData(3,0));
    changeColor(ui->label_31, game->getData(3,1));
    changeColor(ui->label_32, game->getData(3,2));
    changeColor(ui->label_33, game->getData(3,3));
}

//改变方块的StyleSheet
void MainWindow::changeColor(QLabel* label, int num)
{
    label->setAlignment(Qt::AlignCenter);           //设置对齐方式
    switch (num)
    {
    case 2:    label->setStyleSheet("background-color: rgb(238,228,218);"
                             "color: rgb(55, 59, 56);"
                             "font:bold 75 30pt ""微软雅黑"""); break;
    case 4:    label->setStyleSheet("background-color: rgb(237,224,200);"
                             "color: rgb(55, 59, 56);"
                             "font:bold 75 30pt ""微软雅黑"""); break;
    case 8:    label->setStyleSheet("background-color: rgb(242,177,121);"
                             "color: rgb(55, 59, 56);"
                             "font:bold 75 30pt ""微软雅黑"""); break;
    case 16:   label->setStyleSheet("background-color: rgb(245,150,100);"
                             "color: rgb(55, 59, 56);"
                             "font:bold 75 30pt ""微软雅黑"""); break;
    case 32:   label->setStyleSheet("background-color: rgb(245,125,95);"
                             "color: rgb(55, 59, 56);"
                             "font:bold 75 30pt ""微软雅黑"""); break;
    case 64:   label->setStyleSheet("background-color: rgb(245,95,60);"
                             "color: rgb(55, 59, 56);"
                             "font:bold 75 30pt ""微软雅黑"""); break;
    case 128:  label->setStyleSheet("background-color: rgb(237,207,114);"
                             "color: rgb(55, 59, 56);"
                             "font:bold 75 25pt ""微软雅黑"""); break;
    case 256:  label->setStyleSheet("background-color: rgb(237,204,97);"
                             "color: rgb(55, 59, 56);"
                             "font:bold 75 25pt ""微软雅黑"""); break;
    case 512:  label->setStyleSheet("background-color: rgb(237,204,97);"
                             "color: rgb(55, 59, 56);"
                             "font:bold 75 25pt ""微软雅黑"""); break;
    case 1024: label->setStyleSheet("background-color: rgb(237,204,97);"
                             "color: rgb(55, 59, 56);"
                             "font:bold 75 20pt ""微软雅黑"""); break;
    case 2048: label->setStyleSheet("background-color: rgb(237,204,97);"
                             "color: rgb(55, 59, 56);"
                             "font:bold 75 20pt ""微软雅黑"""); break;
    default:   label->setStyleSheet("background-color: rgb(238,228,218);"
                             "color: rgb(55, 59, 56);"
                             "font:bold 75 40pt ""微软雅黑"""); break;
    }
}
