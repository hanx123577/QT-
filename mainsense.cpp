#include "mainsense.h"
#include "ui_mainsense.h"
#include"QPainter"
#include"mypushbutton.h"
#include"levelsense.h"
#include"QTimer"
#include"QSound"
mainSense::mainSense(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainSense)
{
    ui->setupUi(this);
    //配置主场景
    //设置固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币Demo");
    //菜单栏退出的实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    //准备开始音效
    QSound *startsound=new QSound(":/res/TapButtonSound.wav",this);

    //设置开始按钮
    MyPushButton *startbtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    //startbtn->show();
    startbtn->setParent(this);
    startbtn->move(this->width()*0.3,this->height()*0.7);
    //实例化关卡选择窗口对象
    levelsense=new LevelSense;
    //监听返回按钮信号
    connect(levelsense,&LevelSense::chooseback,[=](){
        this->show();
        levelsense->hide();});

    //信号槽函数
    connect(startbtn,&MyPushButton::clicked,[=](){
     startsound->play();
     startbtn->zoom1();
     startbtn->zoom2();


     //延时100ms后跳转到关卡选择场景
     QTimer::singleShot(100,this,[=](){
         //设置levelsense的矩形窗口
         levelsense->setGeometry(this->geometry());
         //隐藏当前对象
         this->hide();
         //展示新窗口
         levelsense->show();


     });

  });

}
void mainSense::paintEvent(QPaintEvent*)
{   //画背景图
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画图标图片
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.7);
    painter.drawPixmap(10,30,pix);

}

mainSense::~mainSense()
{
    delete ui;
}

