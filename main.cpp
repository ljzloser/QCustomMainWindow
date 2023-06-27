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
    //QCustomMainWindow w;
    //QCustomTitleBar * titleBar = new QCustomTitleBar();
    //titleBar->setTitleText("QCustomMainWindow");
    //QObject::connect(titleBar, &QCustomTitleBar::closeButtonClicked, &w, &QCustomMainWindow::close);
    //QObject::connect(titleBar, &QCustomTitleBar::maxButtonClicked, &w, &QCustomMainWindow::showCustomNormal);
    //QObject::connect(titleBar, &QCustomTitleBar::minButtonClicked, &w, &QCustomMainWindow::showMinimized);
    //w.setTitleBar(titleBar);
    //w.setMainWidget(new QMainWindow());
    //QMenuBar * menuBar = new QMenuBar();
    //QMenu * fileMenu = menuBar->addMenu("文件");
    //fileMenu->addAction("新建");
    //fileMenu->addAction("打开");
    //fileMenu->addAction("保存");
    //fileMenu->addAction("另存为");
    //fileMenu->addAction("关闭");
    //fileMenu->addAction("退出");
    //QMenu * editMenu = menuBar->addMenu("编辑");
    //editMenu->addAction("撤销");
    //editMenu->addAction("恢复");
    //editMenu->addAction("剪切");
    //editMenu->addAction("复制");
    //editMenu->addAction("粘贴");
    //editMenu->addAction("删除");
    //w.setMenuBar(menuBar);
    //QStatusBar * statusBar = new QStatusBar();
    //statusBar->addWidget(new QLabel("状态栏"));
    //w.setStatusBar(statusBar);
    //加载样式表
    QFile file(":/qdarkstyle/dark/darkstyle.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    a.setStyleSheet(styleSheet);
    w.show();
    w.resize(800, 600);
    return a.exec();
}
