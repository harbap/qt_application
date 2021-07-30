#ifndef NEWIN_H
#define NEWIN_H

#include <QMainWindow>
#include <QScrollBar>
#include <QLabel>
#include <QSlider>
#include <QProgressBar>
#include <QTimer>

namespace Ui {
class newin;
}

class newin : public QMainWindow
{
    Q_OBJECT

public:
    explicit newin(QWidget *parent = nullptr);
    ~newin();

private:
    Ui::newin *ui;
    QScrollBar *horibar;
    QScrollBar *verbar;
    QLabel *label;
    QSlider *hori_sli;
    QSlider *ver_sli;
    QProgressBar *prg_bar;
    QTimer *timer;
    int value;
private slots:
    void hori_sli_valuechange(int);
    void ver_sli_valuechange(int);
    void timerTimeOut();
};

#endif // NEWIN_H
