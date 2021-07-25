#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include<QPushButton>
#include <QWidget>
#include<QEvent>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    //自定义按钮构造函数,参数一：默认显示的路径，参数二：按下之后显示的图片
    MyPushButton(QString nomalimg,QString pressimg="");
    //成员属性：保存用户默认图片路径和按下之后显示的图片的路径
    QString nomalimgpath;
    QString pressimgpath;
    void zoom1();
    void zoom2();
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
signals:

};

#endif // MYPUSHBUTTON_H
