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
#include <QDialogButtonBox>
#include <QDebug>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QTimeEdit>
#include <QDateEdit>
#include <QDial>
#include <QPixmap>


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
    QDialogButtonBox *dlg_btn;
    QPushButton *dlg_pshbtn;
    QLineEdit *lin_edt;
    QTextEdit *txt_edt;             //丰富文本显示,可显示图片文字
    QPlainTextEdit *plan_edt;       //TextEdit的低配版本,只显示文字，但速度快,本代码就不实现历程与TextEdit一样。
    QPushButton *btn_sel,*btn_clr;
    QSpinBox *spinbox;              //利用窗口背景不透明调节器
    QDoubleSpinBox *doubspinbox;    //与spinbox一样,设置的是浮点值,参考spinbox

    QDateTimeEdit *dt_edt;
    QTimeEdit *t_edt;
    QDateEdit *d_edt;
    QDial *dial;

    QLabel *lab_img;

    QPushButton *btn_newWdg;
    QPushButton *btn_txtWin;
private slots:
    void pushbtn1_clicked();
    void pushbtn2_clicked();
    void checkbox_changed(int state);
    void combobox_change(int);
    void cmd_linbtn_clicked();
    void dialog_btn_clicked(QAbstractButton *button);
    void btnsel_clicked();
    void btnclr_clicked();
    void spinbox_valuechange(int val);
    void dial_valuechanged(int val);
    void btn_neWdgclicked();
    void btn_txtWinclicked();
};
#endif // MAINWINDOW_H
