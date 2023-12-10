
#include <QtWidgets/QApplication>
#include "MyDrawBoardWidget.h"
#include"homework.h"
#include<iostream>
#include<chrono>
#include<thread>
using namespace ComputerGraphics;
int main(int argc, char *argv[])
{
    const double frameRate = 60.0;
    const std::chrono::duration<double> frameDuration(1.0 / frameRate);


    QApplication a(argc, argv);
    //ƽʱʵ��
    //MyDrawBoardWidget::getDrawBoardInstance()->show();
    //��ĩ��Ŀ
    homework::GetInstance()->show();

    return a.exec();
}
