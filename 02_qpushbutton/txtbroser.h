#ifndef TXTBROSER_H
#define TXTBROSER_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
namespace Ui {
class txtbroser;
}

class txtbroser : public QMainWindow
{
    Q_OBJECT

public:
    explicit txtbroser(QWidget *parent = nullptr);
    ~txtbroser();

private:
    QAction *open_Act;
    QMenu *fileMenu;
    Ui::txtbroser *ui;
};

#endif // TXTBROSER_H
