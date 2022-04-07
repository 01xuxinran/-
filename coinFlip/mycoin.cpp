#include "mycoin.h"
#include<QDebug>
#include<QTimer>
//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}
MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret)
    {
       QString str=QString("the img is worry");
       qDebug()<<str;
       return;
    }
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始画定时器标志
    timer1=new QTimer(this);
    timer2=new QTimer(this);
    //监听正面翻反面的信号，并翻转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));

        //如果翻完了，将min重置为1
        if(this->min>this->max)
        {
            this->min=1;
            isAnimation=false;//停止做动画//
            timer1->stop();
        }

    });


    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));

        //如果翻完了，将min重置为1
        if(this->max<this->min)
        {
            this->max=8;
            isAnimation=false;//停止做动画//
            timer2->stop();
        }

    });


}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
//改变正反面标志的方法
void MyCoin::changeFlag()
{
    if(this->flag)//正到反
    {
        timer1->start(30);
        isAnimation=true;//开始做动画//
        this->flag=false;

    }
    else//反到正
    {
        timer2->start(30);
        isAnimation=true;//开始做动画//
        this->flag=true;
    }
}
