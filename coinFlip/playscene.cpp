#include "playscene.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include<QLabel>
#include<QString>
#include"mycoin.h"
#include"dataconfig.h"
#include"mypushbutton.h"
#include"QPropertyAnimation"
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}
PlayScene::PlayScene(int levelNum)
{
    QString str=QString("come in the %1 game").arg(levelNum);
    qDebug()<<str;
    this->levelIndex=levelNum;


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
    MyPushButton *backBtn1=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn1->setParent(this);
    backBtn1->move(this->width()-backBtn1->width(),this->height()-backBtn1->height());
    //点击返回
    connect(backBtn1,&MyPushButton::clicked,[=](){
      // QDebug()<<"fanhui";
        //告诉主场景，我返回了
        emit this->choiceSceneBack1();
    });


//显示当前的关卡数
    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("hua wen xin wei");
    font.setPointSize(20);
    QString str1=QString("leavel: %1").arg(this->levelIndex);
    label->setText(str1);
     //   label->setFont(font);
  //  label->setText(this->levelIndex);
   // label->move(100,500);
    label->setGeometry(30,this->height()-50,120,50);//矩形区域

    dataConfig config;
    //初始化每个关卡的二维数组
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片显示
    QLabel *winLabel=new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());



    //显示金币的背景图片
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QPixmap pix=QPixmap(":/res/BoardNode.png");
            QLabel *label=new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(QPixmap(pix));
            label->setParent(this);
            label->move(157+i*50,200+j*50);


            //创建金币
            QString str;
            if(this->gameArray[i][j]==1)
            {
                str=":/res/Coin0001.png";
            }
            else
            {
                str=":/res/Coin0008.png";
            }


            MyCoin *coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(159+i*50,204+j*50);

            //给金币赋值
            coin->posx=i;
            coin->posy=j;
            coin->flag=this->gameArray[i][j];//1正

            //将金币放入金币的二位数组中，以便能后期维护
            coinEtn[i][j]=coin;

            //点击金币，及逆行翻转
            connect(coin,&MyCoin::clicked,[=](){
                coin->changeFlag();
                this->gameArray[i][j]=this->gameArray[i][j]==0 ? 1 : 0;

                //翻转周围金币
                if(coin->posx+1<=3)//周围的右侧金币翻转
                {
                    coinEtn[coin->posx+1][coin->posy]->changeFlag();
                    this->gameArray[coin->posx+1][coin->posy]=this->gameArray[coin->posx+1][coin->posy]==0?1:0;
                }
                if(coin->posx-1>=0)
                {
                    coinEtn[coin->posx-1][coin->posy]->changeFlag();
                    this->gameArray[coin->posx-1][coin->posy]=this->gameArray[coin->posx-1][coin->posy]==0?1:0;

                }
                if(coin->posy+1<=3)//周围的上侧金币翻转
                {
                    coinEtn[coin->posx][coin->posy+1]->changeFlag();
                    this->gameArray[coin->posx][coin->posy+1]=this->gameArray[coin->posx][coin->posy+1]==0?1:0;
                }
                if(coin->posy-1>=0)
                {
                    coinEtn[coin->posx][coin->posy-1]->changeFlag();
                    this->gameArray[coin->posx][coin->posy-1]=this->gameArray[coin->posx][coin->posy-1]==0?1:0;

                }
                //判断是否胜利
                this->isWin=true;
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        if(coinEtn[i][j]->flag==false)
                        {
                            this->isWin=false;
                            break;
                        }
                    }
                }
                if(this->isWin==true)
                {
                    qDebug()<<"win";
                    //将所有胜利的代码写为true
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            coinEtn[i][j]->disconnect();
                        }
                    }
                    //将胜利的图片砸下来
                   QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                  animation->setDuration(1000);
                  //设置开始位置 结束 位置 曲线
                  //起始位置
                  animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
                  //结束位置
                  animation->setEndValue(QRect(this->x(),this->y()+114,this->width(),this->height()));
                  //设置弹跳曲线
                  animation->setEasingCurve(QEasingCurve::OutBounce);
                  //执行动画
                  animation->start();


                }
            });
        }
    }




}
void PlayScene::paintEvent(QPaintEvent *)
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
