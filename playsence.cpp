#include "playsence.h"
#include"QDebug"
#include"QPainter"
#include"QMenuBar"
#include"mypushbutton.h"
#include"QTimer"
#include"QLabel"
#include"mycoin.h"
#include"dataconfig.h"
#include"mycoin.h"
#include"QPropertyAnimation"
#include"QSound"
playsence::playsence(int levelnum)
{
    this->levelindex=levelnum;
    //翻金币音效
    QSound *coinsound=new QSound(":/res/ConFlipSound.wav",this);
    //成功音效
    QSound *winsound=new QSound(":/res/LevelWinSound.wav",this);
    winsound->setLoops(-1);
    //初始化游戏场景
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    //setWindowTitle("游戏页面Demo");
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

    MyPushButton *btn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    btn->setParent(this);
    btn->move(this->width()-btn->width(),this->height()-btn->height());
    connect(btn,&QPushButton::clicked,[=](){
        QTimer::singleShot(100,this,[=](){
             emit this->chooseback();
        });
    });

    //添加关卡号码标签
    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(21);

    label->setFont(font);
    QString str=QString("Level%1").arg(this->levelindex);
    label->setText(str);
    label->setGeometry(30,this->height()-50,120,50);
    label->setStyleSheet("color:white");

    dataConfig config;
    //初始化每个关卡数组
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gamearray[i][j]=config.mData[this->levelindex][i][j];
        }
    }
    //胜利弹出的图片加载
    QLabel *winlabel=new QLabel;
    QPixmap wpix;
    wpix.load(":/res/LevelCompletedDialogBg.png");
    winlabel->setPixmap(wpix);
    winlabel->setGeometry(0,0,wpix.width(),wpix.height());
    winlabel->setParent(this);
    winlabel->move((this->width()-wpix.width())*0.5,-wpix.height());

    //添加金币背景
    for(int i=0;i<4;i++)

    {  for(int j=0;j<4;j++)
            //绘制金币背景图片
        {   QPixmap pix=QPixmap(":/res/BoardNode(1).png");
            QLabel *clabel=new QLabel;
            clabel->setParent(this);
            clabel->setGeometry(0,0,pix.width(),pix.height());
            clabel->setPixmap(pix);
            clabel->move(57+i*50,200+j*50);
            //创建金币和银币
            QString str;
            if(this->gamearray[i][j]==1)
            {
                str=":/res/Coin0001.png";
            }
            else
            {
                 str=":/res/Coin0008.png";
            }
            MyCoin *coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            //给每个金币的属性赋值
            coin->posx=i;
            coin->posy=j;
            coin->flag=gamearray[i][j];//1是金币，0是银币

            //创建维护金币的数组
           coinbtn[i][j]=coin;

            //点击金币进行翻转
            connect(coin,&MyPushButton::clicked,[=](){
                coinsound->play();
                coin->changeflag();
                //更新gamearray数组
                this->gamearray[i][j]=this->gamearray[i][j]==0?1:0;
            //翻转周围金币操作
                QTimer::singleShot(200,this,[=](){
                    if(coin->posx+1<=3)
                    {
                        coinbtn[coin->posx+1][coin->posy]->changeflag();
                        this->gamearray[coin->posx+1][coin->posy]=this->gamearray[i][j]==0?1:0;
                    }
                    if(coin->posx-1>=0)
                    {
                        coinbtn[coin->posx-1][coin->posy]->changeflag();
                        this->gamearray[coin->posx-1][coin->posy]=this->gamearray[i][j]==0?1:0;
                    }
                    if(coin->posy-1>=0)
                    {
                        coinbtn[coin->posx][coin->posy-1]->changeflag();
                        this->gamearray[coin->posx][coin->posy-1]=this->gamearray[i][j]==0?1:0;
                    }
                    if(coin->posy+1<=3)
                    {
                        coinbtn[coin->posx][coin->posy+1]->changeflag();
                        this->gamearray[coin->posx][coin->posy+1]=this->gamearray[i][j]==0?1:0;
                    }
                    //判断是否胜利
                    this->iswin=true;
                    for(int i=0;i<4;i++)
                    {
                        for (int j=0;j<4;j++)
                        {
                            if(coinbtn[i][j]->flag==false)
                            {

                                    this->iswin=false;
                                    break;
                            }
                        }
                    }
                    if(this->iswin==true)
                    {
                        qDebug()<<"win";
                        winsound->play();

                    //当胜利了就让所有金币不能点击,把coin中的所有win属性都设置成true
                        for(int i=0;i<4;i++)
                        {

                            for (int j=0;j<4;j++)
                            {
                            coinbtn[i][j]->ciswin=true;
                            }
                        }
                        //胜利弹出的弹出效果
                            QPropertyAnimation *animation=new QPropertyAnimation (winlabel,"geometry");

                            //设置时间间隔
                            animation->setDuration(1000);
                            //设置开始和终止位置
                            animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                            animation->setEndValue(QRect(winlabel->x(),winlabel->y()+130,winlabel->width(),winlabel->height()));
                            animation->setEasingCurve(QEasingCurve::OutBounce);
                            animation->start();

                    }


                });

            });

        }
    }



}

void playsence:: paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画图标图片
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.7);
    painter.drawPixmap(10,30,pix);
}
