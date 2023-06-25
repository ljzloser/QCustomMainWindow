#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent): QCustomMainWindow(parent)
{
    QCustomTitleBar* titleBar = new QCustomTitleBar();
    titleBar->setTitleText("QCustomMainWindow");
    QObject::connect(titleBar, &QCustomTitleBar::closeButtonClicked, this, &MainWindow::close);
    QObject::connect(titleBar, &QCustomTitleBar::maxButtonClicked, this, &MainWindow::showCustomNormal);
    QObject::connect(titleBar, &QCustomTitleBar::minButtonClicked, this, &MainWindow::showMinimized);
    //QWidget * titleBar = new QWidget();
    this->setTitleBar(titleBar);

    //this->setWindowTitle("QCustomMainWindow");
    //titleBar->setFixedHeight(30);
    this->setMainWidget(new QWidget());
    //QVBoxLayout* layout = new QVBoxLayout();
    //layout->addWidget(titleBar);
    //connect(this, SIGNAL(windowStateChange(bool)), this, SLOT(windowStateChange(bool)));
    ////设置样式表
    //QStringList list;
    //list << "#titleBar{background:#BBBBBB;}";
    //list << "#titleBar{border-top-left-radius:8px;border-top-right-radius:8px;}";
    //list << "#widgetMain{border:2px solid #BBBBBB;background:#FFFFFF;}";
    //list << "#widgetMain{border-bottom-left-radius:8px;border-bottom-right-radius:8px;}";
    //this->setStyleSheet(list.join(""));
    this->setBorderColor(Qt::GlobalColor::lightGray,2);
    //背景色为#19232D
    this->setBackgroundColor(QColor("#19232D"));
    //分割线颜色
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
