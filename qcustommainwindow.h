﻿#pragma once

#include <QtWidgets/QWidget>
#include "ui_qcustommainwindow.h"
#include <qlayout.h>
#include <qmenubar.h>
#include <qstatusbar.h>
#include <qrect.h>
#include <qtimer.h>
#include <qpainter.h>
#include <qbrush.h>
#include <qcolor.h>
#include <qpen.h>
#include <qcursor.h>
#include <qevent.h>

class QCustomMainWindow : public QWidget
{
	Q_OBJECT

public:
	QCustomMainWindow(QWidget* parent = nullptr);
	~QCustomMainWindow();
	//加载布局
	void loadLayout();
	//最大化及还原窗口
	void showCustomNormal();
	//设置标题栏
	void setTitleBar(QWidget* titleBar);
	//设置菜单栏
	void setMenuBar(QWidget* menuBar);
	//设置主窗口
	void setMainWidget(QWidget* mainWidget);
	//设置状态栏
	void setStatusBar(QWidget* statusBar);
	//获取标题栏
	QWidget* getTitleBar() { return this->titleBar; }
	//获取菜单栏
	QWidget* getMenuBar() { return this->menuBar; }
	//获取主窗口
	QWidget* getMainWidget() { return this->mainWidget; }
	//获取状态栏
	QWidget* getStatusBar() { return this->statusBar; }
	//设置边缘大小
	void setEdgeSize(int edge_size);
	//设置圆角半径
	void setRadius(int radius);
	//设置边框颜色
	void setBorderColor(QColor border_color, int border_size);
	//设置背景颜色
	void setBackgroundColor(QColor background_color);
	//绘图事件
	void paintEvent(QPaintEvent* event);
	//光标更新事件
	void updateCursorShape();
	//鼠标移动事件
	void mouseMoveEvent(QMouseEvent* event);
	//鼠标按下事件
	void mousePressEvent(QMouseEvent* event);
	//鼠标释放事件
	void mouseReleaseEvent(QMouseEvent* event);

private:
	Ui::QCustomMainWindowClass ui;
	QString dragging_edge = nullptr; //拖动的边缘
	bool is_dragging = false; //是否正在拖动
	int edge_size = 10; //边缘大小
	int radius = 10; //圆角半径
	QColor border_color = Qt::GlobalColor::gray; //边框颜色
	int border_size = 2; //边框大小
	QColor background_color = Qt::GlobalColor::white; //背景颜色
	QImage* background_image = nullptr; //背景图片
	QWidget* titleBar = nullptr; //标题栏
	QWidget* menuBar = nullptr; //菜单栏
	QWidget* mainWidget = nullptr; //主窗口
	QWidget* statusBar = nullptr; //状态栏
	QPoint* drag_pos = nullptr; //拖动位置
	QRect* customNormal = nullptr; //自定义正常状态
	QTimer* timer = new QTimer(); //定时器
	QVBoxLayout* layout = new QVBoxLayout(); //布局
};