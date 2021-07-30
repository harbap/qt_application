#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QUrl>
#include <QDesktopServices>
#include "newin.h"
#include "textbroser.h"
#include "txtbroser.h"

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

    dlg_btn = new QDialogButtonBox(this);
    dlg_btn->setGeometry(580,200,200,30);
    dlg_btn->addButton(QDialogButtonBox::Ok);
    dlg_btn->button(QDialogButtonBox::Ok)->setText("确定");
    dlg_pshbtn = new QPushButton("输出编辑框内容",this);
    dlg_btn->addButton(dlg_pshbtn,QDialogButtonBox::ActionRole);
    connect(dlg_btn,SIGNAL(clicked(QAbstractButton*)),this,SLOT(dialog_btn_clicked(QAbstractButton*)));

    lin_edt = new QLineEdit(this);
    lin_edt->setGeometry(200,110,120,30);

    txt_edt = new QTextEdit(this);
    txt_edt->setGeometry(330,100,400,80);
    btn_sel = new QPushButton("全选",this);
    btn_sel->setGeometry(150,150,50,20);
    btn_clr = new QPushButton("清空",this);
    btn_clr->setGeometry(210,150,50,20);
    connect(btn_sel,SIGNAL(clicked()),this,SLOT(btnsel_clicked()));
    connect(btn_clr,SIGNAL(clicked()),this,SLOT(btnclr_clicked()));

    spinbox = new QSpinBox(this);
    spinbox->setGeometry(5,200,100,30);
    spinbox->setRange(0,100);
    spinbox->setSingleStep(10);
    spinbox->setValue(50);
    connect(spinbox,SIGNAL(valueChanged(int)),this,SLOT(spinbox_valuechange(int)));

    dt_edt = new QDateTimeEdit(QDateTime::currentDateTime(),this);
    dt_edt->setGeometry(110,200,130,30);
    d_edt = new QDateEdit(QDate::currentDate(),this);
    d_edt->setGeometry(250,200,130,30);
    t_edt = new QTimeEdit(QTime::currentTime(),this);
    t_edt->setGeometry(390,200,130,30);

    dial = new QDial(this);
    dial->setGeometry(700,240,80,80);
    dial->setPageStep(1);              //设置刻度间距
    dial->setNotchesVisible(true);      //设置刻度可见
    dial->setNotchTarget(1.00);         /* 设置两个凹槽之间的目标像素数 */
    dial->setRange(0,20);
    connect(dial,SIGNAL(valueChanged(int)),this,SLOT(dial_valuechanged(int)));

    QPixmap pixmap("/opt/i.mx/qt/02_qpushbutton/image/openedv.png");    //不需要把图片加载到Resource资源里面
    //QPixmap pixmap(":image/openedv.png"); 需要加载到Reources资源里面
    lab_img = new QLabel(this);
    lab_img->setGeometry(5,240,452,132);
    lab_img->setPixmap(pixmap);
    lab_img->setScaledContents(true);       //允许缩放,填充


    btn_newWdg = new QPushButton("新窗口1",this);
    btn_newWdg->setGeometry(10,440,60,30);
    connect(btn_newWdg,SIGNAL(clicked()),this,SLOT(btn_neWdgclicked()));

    btn_txtWin = new QPushButton("txt浏览器",this);
    btn_txtWin->setGeometry(80,440,60,30);
    connect(btn_txtWin,SIGNAL(clicked()),this,SLOT(btn_txtWinclicked()));
}
void MainWindow::btn_txtWinclicked()
{
    txtbroser *w = new txtbroser(this);
    w->setGeometry(150,110,800,480);
    w->show();
 #if 0
    TextBroser *w = new TextBroser(this);
    w->setGeometry(150,110,800,480);
    w->show();
 #endif
}
void MainWindow::btn_neWdgclicked()
{
    newin *w = new newin(this);
    w->setGeometry(150,110,800,480);
    w->show();
}
void MainWindow::dial_valuechanged(int value)
{
    plabel->setText(QString::number(value) + "km/h");
}
void MainWindow::spinbox_valuechange(int value){
    double opacity = (double)value/100;
    this->setWindowOpacity(opacity);            //设置窗口透明度
}
void MainWindow::btnsel_clicked()
{
    //qDebug("btnselect clicked\n");
    txt_edt->setFocus();
    if(!txt_edt->toPlainText().isEmpty()){
        txt_edt->selectAll();
    }
}
void MainWindow::btnclr_clicked()
{
    txt_edt->clear();
}
void MainWindow::dialog_btn_clicked(QAbstractButton *button)
{
    QString str;
    if(button == dlg_btn->button(QDialogButtonBox::Ok)){
        qDebug() <<"点击确定按键" << endl;
    }else if(button == dlg_pshbtn){
        str = "您输入的内容是";
        str += lin_edt->text();
        plabel->setText(str);
        lin_edt->clear();
        //qDebug() << "点击了自定义按键" <<endl;
    }
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

