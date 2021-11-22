#include "mainwindow.h"
#include <pthread.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>

#define SRV_IP      "192.168.1.131"
#define SRV_PORT     9540

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(900,500);
    qRegisterMetaType<QPixmap>("QPixmap&");

    btn_connect = new QPushButton("连接",this);
    btn_connect->setGeometry(810,300,50,30);
    lb = new QLabel(this);
    lb->setGeometry(5,5,800,480);
    s = new ShowVideo(this);
    connect_flag = 0;
    connect(btn_connect,SIGNAL(clicked()),this,SLOT(btn_connect_clicked()));
    connect(s,SIGNAL(image(QPixmap&)),this,SLOT(showImg(QPixmap&)),Qt::QueuedConnection);
}
void MainWindow::showImg(QPixmap &pix)
{
    qDebug("showImg....");

    lb->setPixmap(pix);
}
void MainWindow::btn_connect_clicked()
{
    if(connect_flag == 0){
         s->connect_server();
         connect_flag = 1;
         btn_connect->setText("断开");
    }else{
        connect_flag = 0;
        btn_connect->setText("链接");
        s->disconnect_server();
    }

}

MainWindow::~MainWindow()
{
}
ShowVideo::ShowVideo(QObject *parent) : QThread(parent)
{
    thread_run = false;
    sk_fd = -1;
}
ShowVideo::~ShowVideo()
{

}
int ShowVideo::tcp_recv(unsigned char *pdata,int len,int timeout)
{
    struct timeval tm;
    int fd = sk_fd;

    tm.tv_sec = timeout/1000;
    tm.tv_usec = (timeout%1000) * 1000;
    fd_set fds;
    int rlen = 0,tlen = 0,clen = 0,ret = 0;

    clen = len;
    while(1){
        FD_ZERO(&fds);
        FD_SET(fd,&fds);
        ret = select(fd + 1,&fds ,NULL, NULL, &tm);
        if(ret > 0){
            rlen = recv(fd,(char*)pdata + tlen,clen , 0);
            if(rlen > 0){
                tlen += rlen;
                clen = len - tlen;
            }else if(rlen == 0)
                break;
            if(tlen >= len)
                break;
        }else if(ret == 0){
            break;
        }
        msleep(10);
    }
    return tlen;
}void ShowVideo::connect_server()
{
    qDebug("connect server\n");
    sk_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sk_fd < 0){
        qDebug("socket create error!\n");
    }
    strcpy(srv_ip,SRV_IP);
    srv_port = SRV_PORT;
    struct sockaddr_in srv_addr;
    if(sk_fd > 0){
        memset(&srv_addr,0,sizeof(struct sockaddr_in));
        srv_addr.sin_family = AF_INET;
        srv_addr.sin_port = htons(srv_port);
        inet_pton(AF_INET,srv_ip,&srv_addr.sin_addr);
        if(::connect(sk_fd,(struct sockaddr*)&srv_addr,sizeof(struct sockaddr)) < 0){
            qDebug("connet error \n");
            return;
        }else{
            qDebug("tcp is connect\n");
            thread_run = true;
            start();
        }
    }
}
void print_hex(unsigned char *pbuf,int len)
{
    unsigned char tmp[1024] = {0};

    for(int i = 0;i < len;i++){
        sprintf((char*)tmp+strlen((char*)tmp),"%02x ",pbuf[i]);
    }
    qDebug("hex:%s",tmp);
}
void ShowVideo::run()
{
    unsigned char head[10] = {0};
    int ret = 0,len = 0;
    unsigned int head_flag = 0;
    unsigned char *img = NULL;
    qDebug("thread run fd:%d\n",sk_fd);
    if(sk_fd > 0){
        while(thread_run){
            ret = tcp_recv(head,8,10);
            if(ret != 8){
                msleep(10);
                continue;
            }
            print_hex(head,ret);
            head_flag = head[0]<<24|head[1]<<16|head[2]<<8|head[3];
            qDebug("flag:%8x",head_flag);
            if(head_flag != 0xaaaaaaaa){
                msleep(1);
                continue;
            }
            len = (head[4]<<24)|(head[5]<<16)|(head[6]<<8)|head[7];
            qDebug("len:%d",len);
            if(len < 1024||len > 0x200000){
                msleep(1);
                continue;
            }
            if(img == NULL){
                img = new unsigned char[len];
            }
            memset(img,0,len);
            ret = tcp_recv(img,len,1000);
            qDebug("img ret:%d",ret);
            //  将抓到的图转为QImage对象，方便后续的处理
            QImage qimg;
           // if(QString(pix_format) == QString("MJPG"))
            {

                qimg = QImage::fromData(img, len, "jpg");
            }
            qDebug("-----");
#if 1
            QMatrix matrix;
            int angle = 180;
            matrix.rotate(angle);
            qimg = qimg.transformed(matrix,Qt::FastTransformation);
#endif
            //  转为QPixmap对象，通过QT信号发出到外部
            QPixmap pix = QPixmap::fromImage(qimg);
            emit image(pix);
            msleep(10);
        }
        if(img != NULL){
            delete img;
            img = NULL;
        }
    }
}
void ShowVideo::disconnect_server()
{
    thread_run = false;
    wait();
    close(sk_fd);
}
