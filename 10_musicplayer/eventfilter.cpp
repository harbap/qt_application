#include <mainwindow.h>
#include <QEventLoop>

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
#if 0
    if(watched == playBackModeList){                         //定义事件过滤器，指定在播放模式列表上检测
        switch (event->type()) {
        case QEvent::Leave:                                  //离开时设置当前选择的项为高亮，其他设置为原来的
            playBackModeList->currentItem()->setForeground(QColor(255, 255, 255));
            playBackModeList->currentItem()->setIcon(QIcon(pbModeArr[playBackModeList->currentRow()].icon2));;
            for (int i = 0; i < 5; i++) {
                if(i != playBackModeList->currentRow() )
                    playBackModeList->item(i)->setIcon(QIcon(pbModeArr[i].icon1));
            }
            break;
        default:
            break;
        }
    }
#endif
    if(watched == pushButton[BTN_VOLUM]){                            //定义事件过滤器，鼠标移到按钮时显示音量条
        switch (event->type()) {
        case QEvent::Enter:
            volum_slider->setVisible(true);
            vol_hide_timer->stop();
            break;

        case QEvent::MouseButtonPress:
            break;

        case QEvent::Leave:
            vol_hide_timer->start(1000);
            break;
        default:
            break;
        }
    }

    if(watched == volum_slider){                            //定义事件过滤器，指定在音量条上检测
        switch (event->type()) {
        case QEvent::Leave:
            volum_slider->setVisible(false);                //设置音量条不可见
            break;

        case QEvent::Enter:
            vol_hide_timer->stop();                      //停止音量条定时器
            break;

        case QEvent::MouseButtonPress:
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            float posPosition;
            posPosition = (float)mouseEvent->pos().y()/volum_slider->geometry().height();
            volum_slider->setValue((1 - posPosition)*volum_slider->maximum());
            music_player->setVolume(volum_slider->value());
        }
            break;

        default:
            break;
        }
    }


    if(watched == duration_slider){                         //定义事件过滤器，指定在音量条上检测
        switch (event->type()) {
        case QEvent::MouseButtonPress:
            sli_press_flag = true;
            if(sli_press_flag){
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
                float posPosition;
                posPosition = (float)mouseEvent->pos().x()/duration_slider->geometry().width();
                duration_slider->setValue(posPosition*duration_slider->maximum());
                //mediaPlayer->setPosition(songsPlaySlider->value() * 1000);
            }
            break;

        case QEvent::MouseButtonRelease:
            sli_press_flag = false;
            break;

        default:
            break;
        }
    }
#if 0
    if(watched == settingsList){                            //定义事件过滤器，指定在设置列表上检测
        switch (event->type()) {
        case QEvent::Leave:
            settingsList->setCurrentRow(-1);
            break;

        default:
            break;
        }
    }
#endif
    return QWidget::eventFilter(watched,event);//将事件传递给父类
}

