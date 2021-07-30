#include "newin.h"
#include "ui_newin.h"

newin::newin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::newin)
{
    ui->setupUi(this);
    horibar = new QScrollBar(Qt::Horizontal,this);
    horibar->setGeometry(0,450,800,30);
    verbar = new QScrollBar(Qt::Vertical,this);
    verbar->setGeometry(770,0,30,480);

    label = new QLabel(this);
    label->setText("这是一个测试");
    label->setGeometry(300,200,100,20);

    hori_sli = new QSlider(Qt::Horizontal,this);
    hori_sli->setGeometry(5,5,150,20);
    hori_sli->setRange(0,30);
    ver_sli = new QSlider(Qt::Vertical,this);
    ver_sli->setGeometry(700,300,20,150);
    hori_sli->setRange(0,30);
    connect(hori_sli,SIGNAL(valueChanged(int)),this,SLOT(hori_sli_valuechange(int)));
    connect(ver_sli,SIGNAL(valueChanged(int)),this,SLOT(ver_sli_valuechange(int)));

    prg_bar = new QProgressBar(this);
    prg_bar->setGeometry(200,50,200,60);
    prg_bar->setRange(0,100);
    value = 0;
    prg_bar->setValue(value);
    timer = new QTimer(this);
    timer->start(100);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerTimeOut()));

}
void newin::timerTimeOut()
{
    value ++;
    prg_bar->setValue(value);
    if(value >= 100)
        value = 0;
}
void newin::hori_sli_valuechange(int value)
{
  //  hori_sli->setSliderPosition(value);
    QString str ="滚动条值:" + QString::number(value);

    label->setText(str);
}
void newin::ver_sli_valuechange(int value)
{
    ver_sli->setSliderPosition(value);
}
newin::~newin()
{
    delete prg_bar;
    delete timer;
    delete label;
    delete horibar;
    delete hori_sli;
    delete verbar;
    delete ver_sli;
    delete ui;
}
