#include "mycoin.h"
#include"QDebug"

MyCoin::MyCoin(QString coinpath)
{
    QPixmap pix;
    bool ret=pix.load(coinpath);
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    else
    {
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //初始化定时器对象
     timer1=new QTimer(this);
     timer2=new QTimer(this);
    connect(timer1,&QTimer::timeout,[=](){
        QString str=QString(":/res/Coin000%1.png").arg(this->min++);
        QPixmap pix;
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max)
        {
            min=1;
            timer1->stop();
        }

    });

    connect(timer2,&QTimer::timeout,[=](){
        QString str=QString(":/res/Coin000%8.png").arg(this->max--);
        QPixmap pix;
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->max<this->min)
        {
            max=8;
            timer2->stop();
        }

    });
}
//设置鼠标事件，当胜利了就不允许再点击了
void MyCoin::mousePressEvent(QMouseEvent*e)
{
    if(this->ciswin)
    {
        return;
    }
    else
    {
       return  QPushButton::mousePressEvent(e);
    }
}

//反转金币方法
void MyCoin::changeflag()
{
    //如果是正面，翻转成反面
    if(this->flag==1)
    {
        timer1->start(30);
        this->flag=false;

    }
    else
     {
        timer2->start(30);
        this->flag=true;
    }

}
