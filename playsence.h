#ifndef PLAYSENCE_H
#define PLAYSENCE_H

#include <QMainWindow>
#include <mycoin.h>

class playsence : public QMainWindow
{
    Q_OBJECT
public:
    //explicit playsence(QWidget *parent = nullptr);
       playsence(int levelnum);
       int levelindex;//记录选择的关卡
       void paintEvent(QPaintEvent*);
       int gamearray[4][4];
       MyCoin *coinbtn[4][4];
       int flag=0;
       bool iswin;

signals:
void chooseback();
};

#endif // PLAYSENCE_H
