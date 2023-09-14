
#include <QtWidgets/QApplication>
#include "MyDrawBoardWidget.h"
using namespace ComputerGraphics;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyDrawBoardWidget::getDrawBoardInstance()->show();
    return a.exec();
}
