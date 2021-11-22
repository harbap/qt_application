#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QThread>
#include <QMatrix>

class ShowVideo ;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void btn_connect_clicked();
    void showImg(QPixmap &pix);
private:
    QPushButton *btn_connect;
    QLabel *lb;
    class ShowVideo *s;
    int connect_flag;

};

class ShowVideo : public QThread
{
    Q_OBJECT
public :
    ShowVideo(QObject *parent = 0);
    ~ShowVideo();
    void connect_server();
    void disconnect_server();
    int tcp_recv(unsigned char *pdata,int len,int timeout);
protected:
    void run();
signals:
    void image(QPixmap &pix);
private:
    int sk_fd;
    char srv_ip[30];
    int srv_port;
    bool thread_run;
};


#endif // MAINWINDOW_H
