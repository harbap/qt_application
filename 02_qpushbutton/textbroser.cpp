#include "textbroser.h"
#include <QFileDialog>
#include <QTextStream>

TextBroser::TextBroser(QWidget *parent) :
    QMainWindow(parent)
{

    fileMenu = new QMenu("file",this);
    menubar = new QMenuBar(this);
    menubar->setObjectName(QString::fromUtf8("menubar"));
   // menubar->setGeometry(1,1,798,25);
    this->setMenuBar(menubar);

    this->setWindowTitle("文本浏览器");
    //txt_bro = new QTextBrowser(this);
    //txt_bro->setGeometry(1,30,798,450);
    open_Act = new QAction("打开文件",this);
    fileMenu->addAction(open_Act);
    menubar->addMenu(fileMenu);

    connect(open_Act,SIGNAL(triggered()),this,SLOT(open_act_tri()));
}
void TextBroser::open_act_tri()
{

}
TextBroser::~TextBroser()
{
    //delete txt_bro;
    delete open_Act;

}
