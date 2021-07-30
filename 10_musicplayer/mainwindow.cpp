#include "mainwindow.h"
#include <QCoreApplication>
#include <QFileInfoList>
#include <QDir>

void MainWindow::media_palyer_init()
{
    music_player = new QMediaPlayer(this);
    media_list = new QMediaPlaylist(this);
    media_list->clear();
    /*设置音乐播放器列表为media_list*/
    music_player->setPlaylist(media_list);
    music_player->setVolume(m_play_volum);
    switch(m_play_mode){
    case PLAYMODE_ONCE:
        media_list->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        pushButton[BTN_MODE]->setStyleSheet(
         "QPushButton#btn_mode {border-image:url(:/images/btn_listsingle_1.png);} \
          QPushButton#btn_mode:hover {border-image:url(:/images/btn_listsingle_2.png);}\
          QPushButton#btn_mode0 {border-image:url(:/images/btn_listsingle_1.png);}");
        break;
    case PLAYMODE_ONE_LOOP:
        media_list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        pushButton[BTN_MODE]->setStyleSheet(
         "QPushButton#btn_mode {border-image:url(:/images/btn_listscircle_single_1.png);} \
          QPushButton#btn_mode:hover {border-image:url(:/images/btn_listscircle_single_2.png);}\
          QPushButton#btn_mode0 {border-image:url(:/images/btn_listscircle_single_1.png);}");
        break;
    case PLAYMODE_SEQUENTIAL:
        media_list->setPlaybackMode(QMediaPlaylist::Sequential);
        pushButton[BTN_MODE]->setStyleSheet(
         "QPushButton#btn_mode {border-image:url(:/images/btn_listjump_1.png);} \
          QPushButton#btn_mode:hover {border-image:url(:/images/btn_listjump_2.png);}\
          QPushButton#btn_mode0 {border-image:url(:/images/btn_listjump_1.png);}");
        break;
    case PLAYMODE_LOOP:
        media_list->setPlaybackMode(QMediaPlaylist::Loop);
        pushButton[BTN_MODE]->setStyleSheet(
         "QPushButton#btn_mode {border-image:url(:/images/btn_listcircle_1.png);} \
          QPushButton#btn_mode:hover {border-image:url(:/images/btn_listcircle_2.png);}\
          QPushButton#btn_mode0 {border-image:url(:/images/btn_listcircle_1.png);}");
        break;
    case PLAYMODE_RANDOM:
        media_list->setPlaybackMode(QMediaPlaylist::Random);
        pushButton[BTN_MODE]->setStyleSheet(
         "QPushButton#btn_mode {border-image:url(:/images/btn_listrandom_1.png);} \
          QPushButton#btn_mode:hover {border-image:url(:/images/btn_listrandom_2.png);}\
          QPushButton#btn_mode0 {border-image:url(:/images/btn_listrandom_1.png);}");
        break;
    }
}
void MainWindow::btn_previous_clicked()
{
    music_player->stop();
    int count = media_list->mediaCount();
    if(count == 0)
        return;
    /*播放列表上一个*/
    media_list->previous();
    music_player->play();
}
void MainWindow::btn_next_clicked()
{
    music_player->stop();
    int count = media_list->mediaCount();
    if(count == 0)
        return;
    /*播放列表下一个*/
    media_list->next();
    music_player->play();
}
void MainWindow::btn_play_clicked()
{
    int state = music_player->state();
    switch(state){
    case QMediaPlayer::StoppedState:
        music_player->play();
        break;
    case QMediaPlayer::PlayingState:
        music_player->pause();
        break;
    case QMediaPlayer::PausedState:
        music_player->play();
        break;
    }
}
void MainWindow::media_sta_chg(QMediaPlayer::State sta)
{
    switch(sta){
    case QMediaPlayer::StoppedState:
        pushButton[1]->setChecked(false);
        break;
    case QMediaPlayer::PlayingState:
        pushButton[1]->setChecked(true);
        break;
    case QMediaPlayer::PausedState:
        pushButton[1]->setChecked(false);
        break;
    }
}
void MainWindow::media_dur_chg(qint64 dura)
{
    duration_slider->setRange(0,dura / 1000);
    int sec = dura / 1000;
    int min = sec / 60;
    sec = sec % 60;

    QString media_dur;
    media_dur.clear();
    media_dur = QString::asprintf("%02d:%02d",min,sec);

    label[3]->setText(media_dur);
}
void MainWindow::media_idx_chag(int idx)
{
    //qDebug("idx:%d",idx);
    if(idx == -1)
        return;
     if(m_last_index != idx){
        /*设置列表正在播放的选项*/
        list_widge->setCurrentRow(idx);
        m_last_index = idx;
        music_para->setValue("play_record/last_index",m_last_index);
     }
}
void MainWindow::media_sli_chg(qint64 dur)
{
    if(!duration_slider->isSliderDown())
        duration_slider->setValue(dur / 1000);
    int sec = dur / 1000;
    int min = sec / 60;
    sec = sec % 60;
    label[2]->setText(QString::asprintf("%02d:%02d",min,sec));
}
void MainWindow::sli_dura_chg()
{
    /*设置媒体播放的位置*/
    music_player->setPosition(duration_slider->value() * 1000);
    sli_press_flag = false;
}
void MainWindow::sli_dura_press()
{
    sli_press_flag = true;
}
void MainWindow::volume_slider_chg(int val)
{
    if(m_play_volum != val){
        music_player->setVolume(val);
        m_play_volum = val;
        music_para->setValue("play_volum/play_volum",val);
    }

}
void MainWindow::tm_handle()
{
    //label[1] 显示图片
    QMatrix matrix;
    QImage image(":/images/cd.png");
    static int angle = 0;
    int state = music_player->state();

    if(state == QMediaPlayer::PlayingState){
        angle += 1;
        if(angle >= 360)
            angle = 0;

        matrix.rotate(angle);
        image = image.transformed(matrix,Qt::FastTransformation);

        QPixmap fitpixmap = QPixmap::fromImage(image);

        QPainter pnt(&fitpixmap);
        pnt.setCompositionMode(QPainter::CompositionMode_Source);
        pnt.drawPixmap(0, 0, fitpixmap);
        pnt.setCompositionMode(QPainter::CompositionMode_DestinationIn);

        //根据QColor中第四个参数设置透明度，此处position的取值范围是0～255
        pnt.fillRect(fitpixmap.rect(), QColor(0, 0, 0, (255*0.7)));
        pnt.end();

        label[1]->setPixmap(fitpixmap);
        label[1]->setAlignment(Qt::AlignCenter);

    }
}
void MainWindow::list_wdg_chg(QListWidgetItem *item)
{
    music_player->stop();
    media_list->setCurrentIndex(list_widge->row(item));
    music_player->play();
}
void MainWindow::btn_volum_clicked()
{
    volum_slider->setVisible(true);

}
void MainWindow::vol_tm_handle()
{
   if(!volum_slider->isSliderDown()){
        vol_hide_timer->stop();
        volum_slider->setVisible(false);
   }
}
void MainWindow::btn_playmode_clicked()
{
    if(playmode_list->isVisible())
        playmode_list->setVisible(false);
    else
        playmode_list->setVisible(true);
}
void MainWindow::btn_playlist_clicked()
{

}
void MainWindow::playmode_list_clicked(QListWidgetItem *itm)
{
    playmode_list->setVisible(false);

    m_play_mode = playmode_list->row(itm);
    switch(m_play_mode){
    case PLAYMODE_ONCE:
        media_list->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        pushButton[BTN_MODE]->setStyleSheet(
         "QPushButton#btn_mode {border-image:url(:/images/btn_listsingle_1.png);} \
          QPushButton#btn_mode:hover {border-image:url(:/images/btn_listsingle_2.png);}\
          QPushButton#btn_mode0 {border-image:url(:/images/btn_listsingle_1.png);}");
        break;
    case PLAYMODE_ONE_LOOP:
        media_list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        pushButton[BTN_MODE]->setStyleSheet(
         "QPushButton#btn_mode {border-image:url(:/images/btn_listscircle_single_1.png);} \
          QPushButton#btn_mode:hover {border-image:url(:/images/btn_listscircle_single_2.png);}\
          QPushButton#btn_mode0 {border-image:url(:/images/btn_listscircle_single_1.png);}");
        break;
    case PLAYMODE_SEQUENTIAL:
        media_list->setPlaybackMode(QMediaPlaylist::Sequential);
        pushButton[BTN_MODE]->setStyleSheet(
         "QPushButton#btn_mode {border-image:url(:/images/btn_listjump_1.png);} \
          QPushButton#btn_mode:hover {border-image:url(:/images/btn_listjump_2.png);}\
          QPushButton#btn_mode0 {border-image:url(:/images/btn_listjump_1.png);}");
        break;
    case PLAYMODE_LOOP:
        media_list->setPlaybackMode(QMediaPlaylist::Loop);
        pushButton[BTN_MODE]->setStyleSheet(
         "QPushButton#btn_mode {border-image:url(:/images/btn_listcircle_1.png);} \
          QPushButton#btn_mode:hover {border-image:url(:/images/btn_listcircle_2.png);}\
          QPushButton#btn_mode0 {border-image:url(:/images/btn_listcircle_1.png);}");
        break;
    case PLAYMODE_RANDOM:
        media_list->setPlaybackMode(QMediaPlaylist::Random);
        pushButton[BTN_MODE]->setStyleSheet(
         "QPushButton#btn_mode {border-image:url(:/images/btn_listrandom_1.png);} \
          QPushButton#btn_mode:hover {border-image:url(:/images/btn_listrandom_2.png);}\
          QPushButton#btn_mode0 {border-image:url(:/images/btn_listrandom_1.png);}");
        break;
    }
    music_para->setValue("play_mode/cur_mode",m_play_mode);
}
void MainWindow::read_param(void)
{
    QString value;
    music_para = new QSettings("./para.ini",QSettings::IniFormat, this);
    m_play_mode = music_para->value("play_mode/cur_mode").toInt();
   // qDebug() << "m_play_volum:" << m_play_mode << endl;
    m_play_volum = music_para->value("play_volum/play_volum").toInt();
   // qDebug() << "volum:" << m_play_volum <<endl;
    m_last_index = music_para->value("play_record/last_index").toInt();
   // qDebug() << "last_index:" << m_last_index << endl;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    read_param();
    /*界面初始化*/
    music_layout();

    media_palyer_init();
    /*扫描歌曲*/
    scan_songs();

    sli_press_flag = 0;
    timer = new QTimer(this);
    timer->start(200);
    vol_hide_timer = new QTimer(this);

    if(m_last_index >= media_list->mediaCount()){
        m_last_index = 0;
        music_para->setValue("play_record/last_index",m_last_index);
    }
    if(music_player->state() != QMediaPlayer::PlayingState){
        list_widge->setCurrentRow(m_last_index);
        media_list->setCurrentIndex(m_last_index);
        music_player->play();
        pushButton[BTN_PLAY]->setChecked(true);
    }

    connect(timer,SIGNAL(timeout()),this,SLOT(tm_handle()));
    connect(vol_hide_timer,SIGNAL(timeout()),this,SLOT(vol_tm_handle()));
    /*播放按钮信号*/
    connect(pushButton[BTN_PREV],SIGNAL(clicked()),this,SLOT(btn_previous_clicked()));
    connect(pushButton[BTN_PLAY],SIGNAL(clicked()),this,SLOT(btn_play_clicked()));
    connect(pushButton[BTN_NEXT],SIGNAL(clicked()),this,SLOT(btn_next_clicked()));
    /*播放模式列表切换*/
    connect(playmode_list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(playmode_list_clicked(QListWidgetItem*)));

    /*控制按钮列表*/
    connect(pushButton[BTN_VOLUM],SIGNAL(clicked()),this,SLOT(btn_volum_clicked()));            //音量
    connect(pushButton[BTN_LIST],SIGNAL(clicked()),this,SLOT(btn_playlist_clicked()));         //音乐列表切换按钮
    connect(pushButton[BTN_MODE],SIGNAL(clicked()),this,SLOT(btn_playmode_clicked()));         //循环模式

    /*媒体信号槽链接*/
    connect(music_player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(media_sta_chg(QMediaPlayer::State)));
    connect(media_list,SIGNAL(currentIndexChanged(int)),this,SLOT(media_idx_chag(int)));          //播放列表显示歌曲切换
    connect(music_player,SIGNAL(durationChanged(qint64)),this,SLOT(media_dur_chg(qint64)));         //进度条显示音乐时长
    connect(music_player,SIGNAL(positionChanged(qint64)),this,SLOT(media_sli_chg(qint64)));         //显示播放进度

    /*列表信号槽*/
    connect(list_widge,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(list_wdg_chg(QListWidgetItem*)));
    /*进度条信号槽*/
    connect(duration_slider,SIGNAL(sliderReleased()),this,SLOT(sli_dura_chg()));

    connect(duration_slider,SIGNAL(sliderPressed()),this,SLOT(sli_dura_press()));
    connect(volum_slider,SIGNAL(valueChanged(int)),this,SLOT(volume_slider_chg(int)));
}

MainWindow::~MainWindow()
{
    timer->stop();
    delete timer;
}
void MainWindow::scan_songs()
{
    int i;
    QDir dir(QCoreApplication::applicationDirPath() + "/audio");
    QDir dir_path(dir.absolutePath());

    /*如果目录存在*/
    if(dir_path.exists()){
        /*定义过滤器*/
        QStringList filter;
        filter << "*.mp3";
        QFileInfoList files = dir_path.entryInfoList(filter,QDir::Files);
        /*遍历*/

        for(i = 0;i < files.count();i++){
            MediaObjectInfo info;
            QString file_name = QString::fromUtf8(files.at(i).fileName().replace(".mp3","").toUtf8().data());
            //qDebug() << file_name <<endl;
            info.fileName = file_name;
            info.filePath = QString::fromUtf8(files.at(i).filePath().toUtf8().data());
            /* 媒体列表添加歌曲 */
            if(media_list->addMedia(QUrl::fromLocalFile(info.filePath))){
                /* 添加到容器数组里储存 */
                media_vector.append(info);
                list_widge->addItem(file_name);
            }
        }

    }

}
void MainWindow::music_layout(void)
{
    int i ;
    char playmode[5][20] = {"单曲播放","单曲循环","顺序播放","列表循环","随机播放"};
    this->setWindowFlags(Qt::WindowCloseButtonHint);

    this->setGeometry(200,150,800,480);
    QPalette pal;

    main_win_bkground = new QLabel(this);           //用于覆盖桌面写真背景，防止背景过亮
    main_win_bkground->setMinimumSize(800,480);
    main_win_bkground->setStyleSheet("background-color: rgba(0, 0, 0, 30%);");

    /*按钮*/
    for (i = 0;i < 7;i ++){
        pushButton[i] = new QPushButton(this);
    }

    /*标签*/
    for(i = 0;i < 4;i++){
        label[i] = new QLabel(this);
    }
    /*垂直容器,垂直布局，分为列*/
    for(i = 0;i < 3;i++){
        v_wdg[i] = new QWidget(this);
        v_box[i] = new QVBoxLayout(this);
    }
    /*水平容器,水平布局*/
    for(i = 0;i < 4;i++){
        h_wdg[i] = new QWidget(this);
        h_box[i] = new QHBoxLayout(this);
    }
    /*播放进度条*/
    duration_slider = new QSlider(Qt::Horizontal,this);
    duration_slider->setMinimumSize(15,15);
    duration_slider->setMaximumHeight(15);
    duration_slider->installEventFilter(this);                          //安装事件过滤器
    duration_slider->setObjectName("duration_slider");
    volum_slider = new QSlider(Qt::Vertical,this);
    volum_slider->setGeometry(730,260,50,150);
    volum_slider->setVisible(false);
    volum_slider->setRange(0,100);
    volum_slider->setValue(m_play_volum);
    volum_slider->setObjectName("volum_slider");
    volum_slider->installEventFilter(this);
    /*音乐列表*/
    QFont l_font;
    l_font.setPixelSize(20);            //style.qss 也有设置
    list_widge = new QListWidget(this);
    list_widge->setObjectName("list_widge");
    list_widge->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    list_widge->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    list_widge->resize(350,300);                //音乐列表的宽度和高度
    list_widge->setFont(l_font);

#if 0
    /*列表遮罩*/
    listMask = new QWidget(list_widge);
    listMask->setMinimumSize(310, 50);
    listMask->setMinimumHeight(50);
    listMask->setObjectName("listMask");
    listMask->setGeometry(0, list_widge->height() - 50,310,50);
#endif
    /* 设置按钮的对象名称 */
    pushButton[BTN_PREV]->setObjectName("btn_previous");
    pushButton[BTN_PLAY]->setObjectName("btn_play");
    pushButton[BTN_NEXT]->setObjectName("btn_next");
    pushButton[BTN_FAVORI]->setObjectName("btn_favorite");
    pushButton[BTN_MODE]->setObjectName("btn_mode");
    pushButton[BTN_LIST]->setObjectName("btn_menu");
    pushButton[BTN_VOLUM]->setObjectName("btn_volume");
    pushButton[BTN_VOLUM]->installEventFilter(this);

    /*播放模式列表*/
    playmode_list = new QListWidget(this);
    playmode_list->setGeometry((float)470/800*this->geometry().width(),(float)253/480*this->geometry().height(),120,150);
    playmode_list->setObjectName("playmode_list");
    playmode_list->setVisible(false);
    playmode_list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playmode_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playmode_list->setFrameShape(QListWidget::NoFrame);                                      //隐藏外边框
    playmode_list->setFocusPolicy(Qt::NoFocus);
    QListWidgetItem *item = NULL;
    for(i = 0;i < 5;i++){
        playmode_list->addItem(playmode[i]);
        item = playmode_list->item(i);
        item->setTextAlignment(Qt::AlignCenter|Qt::AlignVCenter);
        item->setSizeHint(QSize(111,30));
    }
    playmode_list->setCurrentRow(m_play_mode);
    /*设置按钮属性,点击下去的时候状态该改变*/
    pushButton[BTN_PLAY]->setCheckable(true);          //播放按钮
    pushButton[BTN_FAVORI]->setCheckable(true);          //收藏按钮

    /*H0 横向布局间距设置*/
    v_wdg[0]->setMinimumSize(320,460);          //设置窗口最小尺寸  音乐列表
    v_wdg[0]->setMaximumWidth(480);             //设置窗口最大尺寸,窗口最大化
    v_wdg[1]->setMinimumSize(320,100);
    QSpacerItem *hSpacer0 = new QSpacerItem(10,470,QSizePolicy::Minimum,QSizePolicy::Maximum);  //音乐列表与左边边框的距离
    QSpacerItem *hSpacer1 = new QSpacerItem(20,470,QSizePolicy::Minimum,QSizePolicy::Maximum);  //歌词，进度条等与音乐列表的距离
    QSpacerItem *hSpacer2 = new QSpacerItem(10,470,QSizePolicy::Minimum,QSizePolicy::Maximum);  //歌词，进度条等与右边边框的距离
    h_box[0]->addSpacerItem(hSpacer0);
    h_box[0]->addWidget(v_wdg[0]);
    h_box[0]->addSpacerItem(hSpacer1);
    h_box[0]->addWidget(v_wdg[1]);
    h_box[0]->addSpacerItem(hSpacer2);
    h_box[0]->addWidget(v_wdg[2]);
    h_wdg[0]->setLayout(h_box[0]);
    setCentralWidget(h_wdg[0]);

    /*V0布局*/

    h_wdg[1]->setMinimumSize(320,70);
    h_wdg[1]->setMaximumHeight(80);

    QSpacerItem *vSpacer0 = new QSpacerItem(310, 10,QSizePolicy::Minimum,QSizePolicy::Maximum);    //播放列表与按钮的间距
    QSpacerItem *vSpacer1 = new QSpacerItem(310, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);   //播放按钮与底部边框的间距

    v_box[0]->addWidget(list_widge);
    v_box[0]->addSpacerItem(vSpacer0);
    v_box[0]->addWidget(h_wdg[1]);
    v_box[0]->addSpacerItem(vSpacer1);
    v_box[0]->setContentsMargins(0, 0, 0, 0);
    v_wdg[0]->setLayout(v_box[0]);

    /*H1布局*/
    for(i = 0;i < 3;i++){
        pushButton[i]->setMinimumSize(60,60);                           //上一曲,播放,下一曲按钮
    }
    QSpacerItem *hSpacer3 = new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);       //上一曲,播放,下一曲按钮布局设置
    QSpacerItem *hSpacer4 = new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    h_box[1]->addWidget(pushButton[0]);
    h_box[1]->addSpacerItem(hSpacer3);
    h_box[1]->addWidget(pushButton[1]);
    h_box[1]->addSpacerItem(hSpacer4);
    h_box[1]->addWidget(pushButton[2]);
    h_box[1]->setContentsMargins(0, 0, 0, 0);
    h_wdg[1]->setLayout(h_box[1]);

    /* V1布局 */
    QSpacerItem *vSpacer2 = new QSpacerItem(320, 0,QSizePolicy::Minimum,QSizePolicy::Maximum);
    QSpacerItem *vSpacer3 = new QSpacerItem(320, 0,QSizePolicy::Minimum,QSizePolicy::Maximum);
    QSpacerItem *vSpacer4 = new QSpacerItem(320, 0,QSizePolicy::Minimum,QSizePolicy::Minimum);
    label[1]->setMinimumSize(320, 320);
#if 0
    QImage Image;
    Image.load(":/images/cd.png");
    QPixmap pixmap = QPixmap::fromImage(Image);
    int with = 200;
    int height = 200;
    QPixmap fitpixmap = pixmap.scaled(with, height,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    label[1]->setPixmap(fitpixmap);
    label[1]->setAlignment(Qt::AlignCenter);
#else
        QPixmap pixmap(":/images/cd.png");
        QPixmap fitpixmap = pixmap.scaled(320,320,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        fitpixmap.fill(Qt::transparent);

        QPainter pnt(&fitpixmap);
        pnt.setCompositionMode(QPainter::CompositionMode_Source);
        pnt.drawPixmap(0, 0, pixmap);
        pnt.setCompositionMode(QPainter::CompositionMode_DestinationIn);

        //根据QColor中第四个参数设置透明度，此处position的取值范围是0～255
        pnt.fillRect(fitpixmap.rect(), QColor(255, 255, 255, (255*0.7)));
        pnt.end();
        label[1]->setPixmap(fitpixmap);
        label[1]->setAlignment(Qt::AlignCenter);
#endif

    v_wdg[2]->setMinimumSize(300, 90);
    v_wdg[2]->setMaximumHeight(90);
    v_box[1]->addSpacerItem(vSpacer2);
    v_box[1]->addWidget(label[1]);
    v_box[1]->addSpacerItem(vSpacer3);
    v_box[1]->addWidget(duration_slider);
    v_box[1]->addWidget(v_wdg[2]);
    v_box[1]->addSpacerItem(vSpacer4);
    v_box[1]->setContentsMargins(0, 0, 0, 0);
    v_wdg[1]->setLayout(v_box[1]);

    /* V2布局 */
    QSpacerItem *vSpacer5 = new QSpacerItem(300, 10,QSizePolicy::Minimum,QSizePolicy::Maximum);
    h_wdg[2]->setMinimumSize(320, 20);
    h_wdg[3]->setMinimumSize(320, 60);
    v_box[2]->addWidget(h_wdg[2]);
    v_box[2]->addSpacerItem(vSpacer5);
    v_box[2]->addWidget(h_wdg[3]);
    v_box[2]->setContentsMargins(0, 0, 0, 0);
    v_wdg[2]->setLayout(v_box[2]);

    /* H2布局 */
    QFont font;
    font.setPixelSize(20);
    /* 设置标签文本 */

    label[2]->setText("00:00");
    label[3]->setText("00:00");
    label[2]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label[3]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label[3]->setAlignment(Qt::AlignRight);
    label[2]->setAlignment(Qt::AlignLeft);
    label[2]->setFont(font);
    label[3]->setFont(font);

    pal.setColor(QPalette::WindowText, Qt::white);
    label[2]->setPalette(pal);
    label[3]->setPalette(pal);

    h_box[2]->addWidget(label[2]);
    h_box[2]->addWidget(label[3]);
    h_box[2]->setContentsMargins(0, 0, 0, 0);
    h_wdg[2]->setLayout(h_box[2]);

    /* H3布局 */
    QSpacerItem *hSpacer5 = new QSpacerItem(0,  60,QSizePolicy::Minimum,QSizePolicy::Maximum);
    QSpacerItem *hSpacer6 = new QSpacerItem(80, 60,QSizePolicy::Maximum,QSizePolicy::Maximum);
    QSpacerItem *hSpacer7 = new QSpacerItem(80, 60,QSizePolicy::Maximum,QSizePolicy::Maximum);
    QSpacerItem *hSpacer8 = new QSpacerItem(80, 60,QSizePolicy::Maximum,QSizePolicy::Maximum);
    QSpacerItem *hSpacer9 = new QSpacerItem(0,  60,QSizePolicy::Minimum,QSizePolicy::Maximum);
    for (i = 3; i < 7; i++) {
        pushButton[i]->setMinimumSize(50, 50);
    }

    h_box[3]->addSpacerItem(hSpacer5);
    h_box[3]->addWidget(pushButton[3]);
    h_box[3]->addSpacerItem(hSpacer6);
    h_box[3]->addWidget(pushButton[4]);
    h_box[3]->addSpacerItem(hSpacer7);
    h_box[3]->addWidget(pushButton[5]);
    h_box[3]->addSpacerItem(hSpacer8);
    h_box[3]->addWidget(pushButton[6]);
    h_box[3]->addSpacerItem(hSpacer9);
    h_box[3]->setContentsMargins(0, 0, 0, 0);
    h_box[3]->setAlignment(Qt::AlignHCenter);
    h_wdg[3]->setLayout(h_box[3]);

}



















