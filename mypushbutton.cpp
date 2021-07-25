#include "mypushbutton.h"
#include "QDebug"
#include"QPropertyAnimation"
MyPushButton::MyPushButton(QString nomalimg,QString pressimg)
{
    this->nomalimgpath=nomalimg;
    this->pressimgpath=pressimg;
    QPixmap pix;
    bool ret=pix.load(nomalimg);
    if (!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}
//向下跳
void MyPushButton:: zoom1()
{
    QPropertyAnimation *qa=new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    qa->setDuration(50);
    //起始位置

    qa->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //终止位置
    qa->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳动画曲线
    qa->setEasingCurve(QEasingCurve::Linear);
    qa->start();
}
//向上跳
void MyPushButton::zoom2()
{
    QPropertyAnimation *qa=new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    qa->setDuration(50);
    //起始位置

    qa->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //终止位置
    qa->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    qa->setEasingCurve(QEasingCurve::Linear);
    qa->start();

}

void MyPushButton::mousePressEvent(QMouseEvent*e)
{
    if(MyPushButton::pressimgpath!="")
  {
    QPixmap pix;
    bool ret=pix.load(this->pressimgpath);
    if (!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
  }
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent*e)
{
    if(MyPushButton::pressimgpath!="")
  {
    QPixmap pix;
    bool ret=pix.load(this->nomalimgpath);
    if (!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
  }
    return QPushButton::mouseReleaseEvent(e);
}
