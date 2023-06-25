#pragma once
#include "qcustommainwindow.h"
#include "qcustomtitlebar.h"
#include "framelesswidget.h"
class MainWindow :public QCustomMainWindow//QCustomMainWindow
{
    Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	//void setTitleBar(QWidget *titleBar);
	//void setMainWidget(QWidget *widget) override;
	void paintEvent(QPaintEvent *event) override;
	
};

