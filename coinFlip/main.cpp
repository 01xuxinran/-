#include "mainsence.h"
#include<QDebug>
#include <QApplication>
#include"dataconfig.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainSence w;
    w.show();

    dataConfig config;

    return a.exec();
}
