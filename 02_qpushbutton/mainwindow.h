#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QToolBar>
#include <QRadioButton>
#include <QCheckBox>
#include <QComboBox>
#include <QCommandLinkButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QLabel *plabel;
    QPushButton  *pushBtn1;
    QPushButton  *pushBtn2;
    QToolButton *toolBtn;           //toolButtond對象
    QToolBar    *toolBar;               //toolBar對象 对象
    QRadioButton *radioBtn1;        //单选框
    QRadioButton *radioBtn2;
    QRadioButton *radioBtn3;
    QCheckBox   *chk1;
    QCheckBox   *chk2;
    QComboBox *comb;
    QCommandLinkButton *cmd_linbtn;
private slots:
    void pushbtn1_clicked();
    void pushbtn2_clicked();
    void checkbox_changed(int state);
    void combobox_change(int);
    void cmd_linbtn_clicked();
};
#endif // MAINWINDOW_H
