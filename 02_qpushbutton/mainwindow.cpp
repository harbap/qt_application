#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QUrl>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100,80,800,480);
    //设置主窗口背景颜色
    this->setStyleSheet("QMainWindow {background-color: rgba(230, 220,230, 100%);}");

    plabel = new QLabel(this);
    plabel->setGeometry(620,400,180,40);
    plabel->setText("没有消息");

    pushBtn1 = new QPushButton("按鈕1",this);
    pushBtn2 = new QPushButton("按鈕2",this);
    pushBtn1->setGeometry(20,10,60,30);
    pushBtn2->setGeometry(20,50,60,30);

    connect(pushBtn1,SIGNAL(clicked()),this,SLOT(pushbtn1_clicked()));
    connect(pushBtn2,SIGNAL(clicked()),this,SLOT(pushbtn2_clicked()));

    toolBar = new QToolBar(this);
    toolBar->setGeometry(100,10,180,40);
    /* 实例化 QStyle 类对象，用于设置风格，调用系统类自带的图标 */
    QStyle *style = QApplication::style();
    /* 使用 Qt 自带的标准图标，可以在帮助文档里搜索 QStyle::StandardPixmap */
    QIcon icon = style->standardIcon(QStyle::SP_TitleBarContextHelpButton);

    toolBtn = new QToolButton(this);
    toolBtn->setIcon(icon);
    toolBtn->setText("帮助");
    /*设置toolButton样式,文本的位置*/
    toolBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolBar->addWidget(toolBtn);

    /*多选一*/
    radioBtn1 = new QRadioButton(this);
    radioBtn2 = new QRadioButton(this);
    radioBtn3 = new QRadioButton(this);
    radioBtn1->setGeometry(300,10,100,50);
    radioBtn2->setGeometry(400,10,100,50);
    radioBtn3->setGeometry(500,10,100,50);
    radioBtn1->setText("开关1");
    radioBtn2->setText("开关2");
    radioBtn3->setText("开关3");
    radioBtn1->setChecked(true);
    radioBtn2->setChecked(false);
    radioBtn3->setChecked(false);

    /*checkbox*/
    chk1 = new QCheckBox("选择1",this);
    chk1->setGeometry(100,60,100,50);
    chk1->setTristate();
    chk2 = new QCheckBox("选择2",this);
    chk2->setGeometry(210,60,100,50);
    connect(chk1,SIGNAL(stateChanged(int)),this,SLOT(checkbox_changed(int)));
    connect(chk2,SIGNAL(stateChanged(int)),this,SLOT(checkbox_changed(int)));
    /*combobox*/
    QStringList itm = {"1","2","3","4","5"};
    comb = new QComboBox(this);
    comb->setGeometry(320,60,80,30);
    comb->addItems(itm);
    connect(comb,SIGNAL(currentIndexChanged(int)),this,SLOT(combobox_change(int)));

    cmd_linbtn = new QCommandLinkButton("打开/home目录","点击此处",this);
    cmd_linbtn->setGeometry(10,110,120,50);
    connect(cmd_linbtn,SIGNAL(clicked()),this,SLOT(cmd_linbtn_clicked()));

}
void MainWindow::cmd_linbtn_clicked()
{
    QDesktopServices::openUrl(QUrl("file:////home/"));
}
void MainWindow::combobox_change(int index)
{
    qDebug("index:%d\n",index);
}
void MainWindow::checkbox_changed(int state)
{
    int sta1 = 0,sta2 = 0;
    sta1 = chk1->checkState();
    sta2 = chk2->checkState();
    qDebug("sta1:%d sta2:%d\n",sta1,sta2);
    switch(state){
    case Qt::Checked:
        plabel->setText("checkbox 选中");
        break;
    case Qt::Unchecked:
        plabel->setText("checkbox 未选中");
        break;
    case Qt::PartiallyChecked:
        plabel->setText("checkbox 半选中");
        break;
    }
}
void MainWindow::pushbtn1_clicked()
{
    this->setStyleSheet("QMainWindow {background-color:rgba(255,200,238,100%);}");
}
void MainWindow::pushbtn2_clicked()
{
    this->setStyleSheet("QMainWindow {background-color:rgba(238,122,233,100%);}");
}

MainWindow::~MainWindow()
{
}

