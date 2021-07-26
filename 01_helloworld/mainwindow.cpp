#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800,480);
    pushButton = new QPushButton(this);

    pushButton->setText("I am button");
    connect(pushButton,SIGNAL(clicked()),this,SLOT(pushButtonClicked()));

    connect(this,SIGNAL(pushButtonTextChanged()),this,SLOT(changeButtonText()));
}

void MainWindow::pushButtonClicked()
{
    qDebug("button clicked");
    emit pushButtonTextChanged();
}

void MainWindow::changeButtonText()
{
    qDebug("changge buton text");
    pushButton->setText("I am clicked");
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->close();
}
