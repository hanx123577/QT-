#include "levelsense.h"
#include"QMenuBar"
#include"QPainter"
#include"mypushbutton.h"
#include"QTimer"
#include"QLabel"
#include"QDebug"
#include"playsence.h"
#include"QSound"
LevelSense::LevelSense(QWidget *parent) : QMainWindow(parent)
{
    //设置固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("关卡选择Demo");
    //创建菜单栏
    QMenuBar*bar=menuBar();
    setMenuBar(bar);
    //创建开始菜单
   QMenu *menue= bar->addMenu("开始");
   //创建菜单项
   QAction *action= menue->addAction("退出");
   //实现退出功能
    connect(action,&QAction::triggered,[=](){
        this->close();
    });
    //选择关卡背景音效
    QSound *backgroundsound=new QSound(":/res/bkmusic.mp3",this);

    //返回按钮音效
    QSound *backsound=new QSound(":/res/BackButtonSound.wav",this);
    //创建返回按钮
    MyPushButton *btn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    btn->setParent(this);
    btn->move(this->width()-btn->width(),this->height()-btn->height());
    connect(btn,&QPushButton::clicked,[=](){
        QTimer::singleShot(100,this,[=](){
            backsound->play();
             emit this->chooseback();
        });
    });
    //创建选择按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton*cbtn=new MyPushButton(":/res/LevelIcon.png");
        cbtn->setParent(this);
        cbtn->move(25+i%4*70,130+i/4*80);
        connect(cbtn,&QPushButton::clicked,[=](){
            //添加音效
            backsound->play();
            //创建游戏页面
            psence=new playsence(i+1);
            //监听返回按钮信号
            connect(psence,&playsence::chooseback,[=](){
                //添加音效
                backsound->play();
                this->show();
                delete psence;
                psence=NULL;});
            //设置矩形至同一窗口
            psence->setGeometry(this->geometry());
            this->hide();
            psence->setWindowTitle(QString::number(i+1));
            psence->show();



    });
    QLabel *label=new QLabel;
    label->setParent(this);
    label->setText(QString::number(i+1));
    label->setFixedSize(cbtn->width(),cbtn->height());
    label->move(25+i%4*70,130+i/4*80);
    //设置居中
    label->setAlignment(Qt::AlignCenter);
    //设置鼠标穿透
    label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}
void LevelSense::paintEvent(QPaintEvent*)
{   //画背景图
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画图标图片
    pix.load(":/res/Title.png");
    painter.drawPixmap(20,30,pix);

}
