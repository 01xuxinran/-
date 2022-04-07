#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
   // explicit MyCoin(QWidget *parent = nullptr);
//传递传入路径
    MyCoin(QString btnImg);


    //金币的属性
    int posx;
    int posy;
    bool flag;//正反的标志

    void changeFlag();//改变标志，执行反转特效
    QTimer *timer1;//正面翻反面的定时器
    QTimer *timer2;
    int min=1;
    int max=8;

    //执行动画的标志
    bool isAnimation=false;
    //重写按下
     void mousePressEvent(QMouseEvent *e);//
     bool isWin;

signals:

};

#endif // MYCOIN_H
