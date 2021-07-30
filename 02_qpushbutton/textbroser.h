#ifndef TEXTBROSER_H
#define TEXTBROSER_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QAction>
#include <QMenuBar>
#include <QMenu>

namespace Ui {
class TextBroser;
}

class TextBroser : public QMainWindow
{
    Q_OBJECT

public:
    explicit TextBroser(QWidget *parent = nullptr);
    ~TextBroser();

private:
    Ui::TextBroser *ui;
    QTextBrowser *txt_bro;
    QAction *open_Act;
    QMenuBar *menubar;
    QMenu *fileMenu;
private slots:
    void open_act_tri();
};

#endif // TEXTBROSER_H
