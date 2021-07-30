#include "mainwindow.h"

#include <QApplication>
/*引入QFILE*/
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug("main :/style.qss\n");
    /*制定qss文集*/
    QFile file(":/style.qss");
    /*判断文集是否存在*/
    if(file.exists()){
        qDebug("read stle.qss\n");
        /*以只读的方式打开*/
        file.open(QFile::ReadOnly);
        /*以字符串的形式保存读出的结果*/
        QString stylesSheet = QLatin1String(file.readAll());
        /*设置全局样式*/
        qApp->setStyleSheet(stylesSheet);
        /*关闭文件*/
        file.close();
        //qDebug("styleSheet:%s\n",qPrintable(stylesSheet));
    }


    MainWindow w;
    w.show();
    return a.exec();
}
