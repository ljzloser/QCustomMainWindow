#include "qcustomtitlebar.h"

QCustomTitleBar::QCustomTitleBar(QWidget* parent) : QWidget(parent)
{
	this->layout = new QHBoxLayout(this);
	this->layout->setContentsMargins(0, 0, 0, 0);

	this->iconLabel = new QLabel(this);
	this->iconLabel->setFixedSize(30, 30);
	this->iconLabel->setScaledContents(true);//设置自动缩放
	this->iconLabel->setMouseTracking(true);//设置鼠标跟踪

	this->titleLabel = new QLabel(this);
	this->titleLabel->setStyleSheet("font-size: 15px;");
	this->titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);//设置文本对齐方式为左对齐且垂直居中
	this->titleLabel->setContentsMargins(0, 0, 0, 0);
	this->titleLabel->setFixedHeight(30);
	this->titleLabel->setMouseTracking(true);//设置鼠标跟踪

	//初始化按钮图标
	this->standardIconMap.insert(ButtonIcon::MinButtonIcon, style()->standardIcon(QStyle::SP_TitleBarMinButton));
	this->standardIconMap.insert(ButtonIcon::MaxButtonIcon, style()->standardIcon(QStyle::SP_TitleBarMaxButton));
	this->standardIconMap.insert(ButtonIcon::RestoreButtonIcon, style()->standardIcon(QStyle::SP_TitleBarNormalButton));
	this->standardIconMap.insert(ButtonIcon::CloseButtonIcon, style()->standardIcon(QStyle::SP_TitleBarCloseButton));

	this->setContextMenuPolicy(Qt::CustomContextMenu);//设置标题栏为自定义上下文菜单策略
	connect(this, &QCustomTitleBar::customContextMenuRequested, this, &QCustomTitleBar::showMenu);//右键菜单信号.显示菜单
	this->menu = new QMenu(this);

	this->minButton = new QPushButton(this);
	this->minButton->setFixedSize(30, 30);
	this->minButton->setIcon(this->standardIconMap.value(ButtonIcon::MinButtonIcon));
	this->minButton->setCursor(Qt::PointingHandCursor);//设置鼠标为手型
	connect(this->minButton, &QPushButton::clicked, this, &QCustomTitleBar::minButtonClicked);//最小化按钮信号

	this->maxButton = new QPushButton(this);
	this->maxButton->setFixedSize(30, 30);
	this->maxButton->setIcon(this->standardIconMap.value(ButtonIcon::MaxButtonIcon));
	this->maxButton->setCursor(Qt::PointingHandCursor);
	connect(this->maxButton, &QPushButton::clicked, this, &QCustomTitleBar::updateIcon); //最大化按钮信号,切换图标
	connect(this->maxButton, &QPushButton::clicked, this, &QCustomTitleBar::maxButtonClicked);

	this->closeButton = new QPushButton(this);
	this->closeButton->setFixedSize(30, 30);
	this->closeButton->setIcon(this->standardIconMap.value(ButtonIcon::CloseButtonIcon));
	this->closeButton->setCursor(Qt::PointingHandCursor);
	connect(this->closeButton, &QPushButton::clicked, this, &QCustomTitleBar::closeButtonClicked);

	this->layout->addWidget(this->iconLabel);
	this->layout->addWidget(this->titleLabel);
	this->layout->addWidget(this->minButton);
	this->layout->addWidget(this->maxButton);
	this->layout->addWidget(this->closeButton);

	this->setLayout(this->layout);
	this->setTitleText("Title");
	this->iconLabel->setPixmap(style()->standardIcon(QStyle::SP_TitleBarMenuButton).pixmap(30, 30));
	this->flag = false;

	QAction* minimizeAction = this->menu->addAction("最小化");
	minimizeAction->setObjectName("minimizeAction");
	minimizeAction->setIcon(this->standardIconMap.value(ButtonIcon::MaxButtonIcon));
	connect(minimizeAction, &QAction::triggered, this, &QCustomTitleBar::minButtonClicked);

	QAction* maximizeAction = this->menu->addAction("最大化/还原");
	maximizeAction->setObjectName("maximizeAction");
	maximizeAction->setIcon(this->standardIconMap.value(ButtonIcon::MaxButtonIcon));
	connect(maximizeAction, &QAction::triggered, this, &QCustomTitleBar::maxButtonClicked);
	connect(maximizeAction, &QAction::triggered, this, &QCustomTitleBar::updateIcon);

	QAction* quitAction = this->menu->addAction("退出");
	quitAction->setObjectName("quitAction");
	quitAction->setIcon(this->standardIconMap.value(ButtonIcon::CloseButtonIcon));
	connect(quitAction, &QAction::triggered, this, &QCustomTitleBar::closeButtonClicked);
}

QCustomTitleBar::~QCustomTitleBar()
{
	delete this->layout;
	delete this->iconLabel;
	delete this->titleLabel;
	delete this->minButton;
	delete this->maxButton;
	delete this->closeButton;
	delete this->menu;
}

void QCustomTitleBar::setTitleIcon(const QIcon& icon)
{
	this->iconLabel->setPixmap(icon.pixmap(30, 30));
}

void QCustomTitleBar::setTitleIcon(const QPixmap& pixmap)
{
	this->iconLabel->setPixmap(pixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void QCustomTitleBar::setTitleText(const QString& text)
{
	this->titleLabel->setText(text);
}

void QCustomTitleBar::updateIcon()
{
	if (this->flag) {
		this->maxButton->setIcon(this->standardIconMap.value(ButtonIcon::MaxButtonIcon));
		for (QAction* action : menu->actions()) {
			if (action->objectName() == "maximizeAction") {
				action->setIcon(this->standardIconMap.value(ButtonIcon::MaxButtonIcon));
				break;
			}
		}
		this->flag = false;
	}
	else {
		this->maxButton->setIcon(this->standardIconMap.value(ButtonIcon::RestoreButtonIcon));
		for (QAction* action : menu->actions()) {
			if (action->objectName() == "maximizeAction") {
				action->setIcon(this->standardIconMap.value(ButtonIcon::RestoreButtonIcon));
				break;
			}
		}
		this->flag = true;
	}
}

void QCustomTitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		this->maxButton->click();
		return QWidget::mouseDoubleClickEvent(event);
	}
}

void QCustomTitleBar::setCustomMenu(QMenu* menu)
{
	this->menu = menu;
}

QAction* QCustomTitleBar::addCustomMenuAction(QAction* action)
{
	this->menu->addAction(action);
	return action;
}

QAction* QCustomTitleBar::addCustomMenuAction(const QString& text)
{
	QAction* action = menu->addAction(text);
	return action;
}

QAction* QCustomTitleBar::addCustomMenuAction(const QIcon& icon, const QString& text)
{
	QAction* action = menu->addAction(icon, text);
	return action;
}

QMap<QCustomTitleBar::ButtonIcon, QIcon> QCustomTitleBar::getStandardIconMap()
{
	return this->standardIconMap;
}

QIcon QCustomTitleBar::setMinButtonIcon(const QIcon& icon)
{
	// 更新最小化按钮图标
	this->standardIconMap.insert(ButtonIcon::MaxButtonIcon, icon);
	this->minButton->setIcon(icon);
	for (QAction* action : this->menu->actions()) {
		if (action->objectName() == "minimizeAction") {
			action->setIcon(icon);
			break;
		}
	}
	return icon;
}

QIcon QCustomTitleBar::setMinButtonIcon(const QString& iconPath)
{
	QIcon icon(iconPath);
	return this->setMinButtonIcon(icon);;
}

QIcon QCustomTitleBar::setMaxButtonIcon(const QIcon& icon)
{
	// 更新最大化按钮图标
	this->standardIconMap.insert(ButtonIcon::MaxButtonIcon, icon);
	this->maxButton->setIcon(icon);
	for (QAction* action : this->menu->actions()) {
		if (action->objectName() == "maximizeAction") {
			action->setIcon(icon);
			break;
		}
	}
	return icon;
}

QIcon QCustomTitleBar::setMaxButtonIcon(const QString& iconPath)
{
	QIcon icon(iconPath);
	return this->setMaxButtonIcon(icon);
}

QIcon QCustomTitleBar::setRestoreButtonIcon(const QIcon& icon)
{
	// 更新还原按钮图标
	this->standardIconMap.insert(ButtonIcon::RestoreButtonIcon, icon);
	this->maxButton->setIcon(icon);
	for (QAction* action : this->menu->actions()) {
		if (action->objectName() == "maximizeAction") {
			action->setIcon(icon);
			break;
		}
	}
	return icon;
}

QIcon QCustomTitleBar::setRestoreButtonIcon(const QString& iconPath)
{
	QIcon icon(iconPath);
	return this->setRestoreButtonIcon(icon);
}

QIcon QCustomTitleBar::setCloseButtonIcon(const QIcon& icon)
{
	// 更新关闭按钮图标
	this->standardIconMap.insert(ButtonIcon::CloseButtonIcon, icon);
	this->closeButton->setIcon(icon);
	for (QAction* action : this->menu->actions()) {
		if (action->objectName() == "quitAction") {
			action->setIcon(icon);
			break;
		}
	}
	return icon;
}

QIcon QCustomTitleBar::setCloseButtonIcon(const QString& iconPath)
{
	QIcon icon(iconPath);
	return this->setCloseButtonIcon(icon);
}

void QCustomTitleBar::showMenu()
{
	this->menu->exec(QCursor::pos());
}
