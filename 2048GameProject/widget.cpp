//主界面的实现
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //锁定窗口大小
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(),this->height());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::getshowdlg()
{
    ui->pushButton_goon->setText("继续游戏");
    this->show();
}

void Widget::on_pushButton_goon_clicked()
{
    this->hide();
    emit showwnd();
}

void Widget::on_pushButton_help_clicked()
{
    QMessageBox::information(NULL,"2048","一个简单的2048游戏");
}

void Widget::on_pushButton_close_clicked()
{
    this->close();
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/duolaoameng.jpg"),QRect());
}
