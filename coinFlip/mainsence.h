#ifndef MAINSENCE_H
#define MAINSENCE_H

#include <QMainWindow>
#include"choicelevelscene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainSence; }
QT_END_NAMESPACE

class MainSence : public QMainWindow
{
    Q_OBJECT

public:
    MainSence(QWidget *parent = nullptr);
    ~MainSence();
//重写paintEvent，画背景图片
void paintEvent(QPaintEvent *);
ChoiceLevelScene *choiceScene=NULL;




private:
    Ui::MainSence *ui;
};
#endif // MAINSENCE_H
