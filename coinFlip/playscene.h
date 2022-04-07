#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include<mycoin.h>
#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
   // explicit PlayScene(QWidget *parent = nullptr);
  PlayScene(int levelNum);
  int levelIndex;
  //重写paintEvent，画背景图片
      void paintEvent(QPaintEvent *);
      PlayScene *choiceScene=NULL;

      int gameArray[4][4];
      MyCoin *coinEtn[4][4];

      bool isWin;
signals:
     void choiceSceneBack1();

};

#endif // PLAYSCENE_H
