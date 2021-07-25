#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString coinpath);
    QString coinpath;
    int posx;
    int posy;
    bool flag;

    //翻转金币方法
    void changeflag();
    QTimer *timer1;//正面反转反面定时器
    QTimer *timer2;//反面反转正面定时器
    int min=1;
    int max=8;
    void mousePressEvent(QMouseEvent*e);
    bool ciswin=false;

signals:

};

#endif // MYCOIN_H
