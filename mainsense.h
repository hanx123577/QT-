#ifndef MAINSENSE_H
#define MAINSENSE_H

#include <QMainWindow>
#include<levelsense.h>

QT_BEGIN_NAMESPACE
namespace Ui { class mainSense; }
QT_END_NAMESPACE

class mainSense : public QMainWindow
{
    Q_OBJECT

public:
    mainSense(QWidget *parent = nullptr);
    ~mainSense();
    //重写画家事件
    void paintEvent(QPaintEvent*);
    LevelSense *levelsense=NULL;

private:
    Ui::mainSense *ui;
};
#endif // MAINSENSE_H
