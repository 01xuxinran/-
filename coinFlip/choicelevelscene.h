#ifndef CHOICELEVELSCENE_H
#define CHOICELEVELSCENE_H

#include <QMainWindow>
#include"playscene.h"
class ChoiceLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChoiceLevelScene(QWidget *parent = nullptr);
    //重写paintEvent，画背景图片
        void paintEvent(QPaintEvent *);
        ChoiceLevelScene *choiceScene=NULL;
//游戏场景指针对象
        PlayScene *play=NULL;
signals:
//写一个自定义的信号，告诉主场景点击了返回
        void choiceSceneBack();
};

#endif // CHOICELEVELSCENE_H
