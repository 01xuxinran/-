#include "mainsence.h"
#include "ui_mainsence.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
MainSence::MainSence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainSence)
{
    ui->setupUi(this);
    //配置主场景
    setFixedSize(520,788);
    //设置固定大小
    setWindowIcon( QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("coin window");
    //退出按钮的实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });


    //开始按钮
   MyPushButton *startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    //实例化选择关卡场景
    choiceScene=new ChoiceLevelScene;

    //监听选择关卡的按钮信号
    connect(choiceScene,&ChoiceLevelScene::choiceSceneBack,this,[=](){
        choiceScene->hide();
        this->show();            });

    connect(startBtn,&MyPushButton::clicked,[=](){
       // QDebug()<<" it is start";

        startBtn->zoom1();
        startBtn->zoom2();


        //延时进入到关卡,保证用户的体验感
        QTimer::singleShot(500,this,[=](){
            //进入到选择关卡场景中
            //自身隐藏
            this->hide();
            //选择关卡
            choiceScene->show();



        });

    });

}





void MainSence::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
   //利用画家添加资源图片
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
   //在背景上画图标
    pix.load(":/res/Title.png");
    //缩放
    pix=pix.scaled(pix.width()*0.7,pix.height()*0.7);
    painter.drawPixmap(10,30,pix);

}




MainSence::~MainSence()
{
    delete ui;
}

