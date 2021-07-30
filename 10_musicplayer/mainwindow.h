#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSlider>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QSpacerItem>
#include <QPushButton>
#include <QDebug>
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QSettings>

/*媒体信息结构体*/
typedef struct{
    QString fileName;    //歌曲文件名
    QString filePath;    //歌曲路径名
}MediaObjectInfo;

enum{
    BTN_PREV,           //0
    BTN_PLAY,
    BTN_NEXT,
    BTN_FAVORI,
    BTN_MODE,
    BTN_LIST,
    BTN_VOLUM,
};
enum{
    PLAYMODE_ONCE,
    PLAYMODE_ONE_LOOP,
    PLAYMODE_SEQUENTIAL,
    PLAYMODE_LOOP,
    PLAYMODE_RANDOM,
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void read_param(void);
private:
    QLabel *main_win_bkground;
    QMediaPlayer *music_player;
    QMediaPlaylist *media_list;         //媒体列表
    QListWidget *list_widge;            //音乐列表
    QSlider *duration_slider;           //播放进度条
    QSlider *volum_slider;              //声音滑条
    QPushButton *pushButton[7];         //音乐播放按钮
    QListWidget *playmode_list;         //播放模式
    QVBoxLayout *v_box[3];               //垂直布局
    QHBoxLayout *h_box[4];               //水平布局
    QWidget *v_wdg[3],*h_wdg[4];          //垂直容器，水平容器，用于容纳空间
    QLabel *label[4];
    QTimer *timer,*vol_hide_timer;
    /* 用于遮罩 */
    QWidget *listMask;

    QSettings *music_para;               //播放记录

    /* 媒体信息存储 */
    QVector<MediaObjectInfo> media_vector;

    void music_layout(void);
    void scan_songs();
    void media_palyer_init();
    bool eventFilter(QObject *watched, QEvent *event);      //事件过滤器功能函数

    int sli_press_flag;
    int m_play_mode;                //播放模式
    int m_play_volum;               //音量
    int m_last_index;

private slots:
    void btn_previous_clicked();
    void btn_next_clicked();
    void btn_play_clicked();
    void media_sta_chg(QMediaPlayer::State sta);
    void media_dur_chg(qint64 dura);
    void media_idx_chag(int idx);
    void media_sli_chg(qint64 dur);
    void list_wdg_chg(QListWidgetItem *item);
    void sli_dura_chg();
    void tm_handle();
    void sli_dura_press();
    void btn_volum_clicked();
    void vol_tm_handle();
    void btn_playmode_clicked();
    void btn_playlist_clicked();
    void playmode_list_clicked(QListWidgetItem *itm);
    void volume_slider_chg(int val);
};
#endif // MAINWINDOW_H




