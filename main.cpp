#include "qcustommainwindow.h"
#include "qcustomtitlebar.h"
#include <QtWidgets/QApplication>
#include <qmainwindow.h>
#include "MainWindow.h"
#include <qfile.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //加载样式表
    QFile file(":/qdarkstyle/dark/darkstyle.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    a.setStyleSheet(styleSheet);
    w.show();
    w.resize(800, 600);
    return a.exec();
}
