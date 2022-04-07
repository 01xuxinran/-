#include "choicelevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include<QDebug>
#include<mypushbutton.h>
#include<QLabel>
ChoiceLevelScene::ChoiceLevelScene(QWidget *parent) : QMainWindow(parent)
{ 
    //配置一个选择关卡场景
    this->setFixedSize(520,788);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("coin window");
    //创建菜单栏界面
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu *startMenu=bar->addMenu("begin");
    //创建退出菜单栏
    QAction *quitAction=startMenu->addAction("quit");
    //点击退出
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
      // QDebug()<<"fanhui";
        //告诉主场景，我返回了
        emit this->choiceSceneBack();
    });

//创建选择关卡按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton *menuBtn=new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(115+i%4*80,140+i/4*80);

        connect(menuBtn,&MyPushButton::clicked,[=](){
            QString str=QString(" you choose the %1 game").arg(i+1);
            qDebug()<<str;
            //进入游戏场景
            this->hide();
            play=new PlayScene(i+1);
            play->show();



        });

      QLabel *label=new QLabel;
      label->setParent(this);
      label->setFixedSize(menuBtn->width(),menuBtn->height());
      label->setText(QString::number(i+1));
      label->move(115+i%4*80,140+i/4*80);
      //设置label上文字对其方式
      label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
     //设置让鼠标穿透
    label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }



}
void ChoiceLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
   //利用画家添加资源图片
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
   //在背景上画图标
    pix.load(":/res/Title.png");
    //缩放
   // pix=pix.scaled(pix.width()*0.7,pix.height()*0.7);
    painter.drawPixmap(10,30,pix);

}
