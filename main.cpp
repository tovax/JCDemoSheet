#include "JCDemoSheet.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JCDemoSheet w;
    w.show();

    return a.exec();
}
