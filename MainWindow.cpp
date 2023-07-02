#include "MainWindow.h"
#include <qwebengineview.h>
#include <qwebengineprofile.h>
#include <qmainwindow.h>

#include <QWebEngineView>
#include <qwebenginepage.h>
#include <qurl.h>


MainWindow::MainWindow(QWidget* parent): QCustomMainWindow(parent)
{
    QCustomTitleBar* titleBar = new QCustomTitleBar();
    titleBar->setTitleText("QCustomMainWindow");
    QObject::connect(titleBar, &QCustomTitleBar::closeButtonClicked, this, &MainWindow::close);
    QObject::connect(titleBar, &QCustomTitleBar::maxButtonClicked, this, &MainWindow::showCustomNormal);
    QObject::connect(titleBar, &QCustomTitleBar::minButtonClicked, this, &MainWindow::showMinimized);
    QObject::connect(this,&MainWindow::windowStateChanged,titleBar,&QCustomTitleBar::updateIcon);

    this->setTitleBar(titleBar);

    QMainWindow * widget = new QMainWindow();

    this->setMainWidget(widget);



    this->setBorderColor(Qt::GlobalColor::lightGray,2);
    //����ɫΪ#19232D
    this->setBackgroundColor(QColor("#19232D"));
    //�ָ�����ɫ
    this->setSplitLineColor(Qt::GlobalColor::lightGray);
    this->setEdgeSize(8);

}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QCustomMainWindow::paintEvent(event);
}

//void MainWindow::setTitleBar(QWidget* titleBar)
//{
//    //QCustomMainWindow::setTitleBar(titleBar);
//}
//
//void MainWindow::setMainWidget(QWidget* widget)
//{
//    /*QCustomMainWindow::setMainWidget(widget);*/
//}
