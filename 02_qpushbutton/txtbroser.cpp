#include "txtbroser.h"
#include "ui_txtbroser.h"

txtbroser::txtbroser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::txtbroser)
{
    ui->setupUi(this);
    this->setGeometry(0, 0, 800, 480);
    //fileMenu = new QMenu("file",this);
    open_Act = new QAction("打开文件",this);
 //   fileMenu->addAction(open_Act);
   // menuBar()->addMenu(fileMenu);
    ui->menubar->addAction(open_Act);

}

txtbroser::~txtbroser()
{
    delete ui;
}
