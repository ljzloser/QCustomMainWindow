#include "qcustomtitlebar.h"

QCustomTitleBar::QCustomTitleBar(QWidget* parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    IConLabel = new QLabel(this);
    IConLabel->setFixedSize(30, 30);
    IConLabel->setScaledContents(true);
    IConLabel->setMouseTracking(true);

    titleLabel = new QLabel(this);
    titleLabel->setStyleSheet("font-size: 15px;");
    titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    titleLabel->setContentsMargins(0, 0, 0, 0);
    titleLabel->setFixedHeight(30);
    titleLabel->setMouseTracking(true);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QCustomTitleBar::customContextMenuRequested, this, &QCustomTitleBar::showMenu);
    menu = new QMenu(this);

    minButton = new QPushButton(this);
    minButton->setFixedSize(30, 30);
    minButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
    minButton->setCursor(Qt::PointingHandCursor);
    connect(minButton, &QPushButton::clicked, this, &QCustomTitleBar::minButtonClicked);

    maxButton = new QPushButton(this);
    maxButton->setFixedSize(30, 30);
    maxButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    maxButton->setCursor(Qt::PointingHandCursor);
    connect(maxButton, &QPushButton::clicked, this, &QCustomTitleBar::updateIcon);
    connect(maxButton, &QPushButton::clicked, this, &QCustomTitleBar::maxButtonClicked);

    closeButton = new QPushButton(this);
    closeButton->setFixedSize(30, 30);
    closeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    closeButton->setCursor(Qt::PointingHandCursor);
    connect(closeButton, &QPushButton::clicked, this, &QCustomTitleBar::closeButtonClicked);

    layout->addWidget(IConLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(minButton);
    layout->addWidget(maxButton);
    layout->addWidget(closeButton);

    setLayout(layout);
    setTitleText("Title");
    IConLabel->setPixmap(style()->standardIcon(QStyle::SP_TitleBarMenuButton).pixmap(30, 30));
    flag = false;

    QAction* minimizeAction = menu->addAction("最小化");
    minimizeAction->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
    connect(minimizeAction, &QAction::triggered, this, &QCustomTitleBar::minButtonClicked);

    QAction* maximizeAction = menu->addAction("最大化/还原");
    maximizeAction->setObjectName("maximizeAction");
    maximizeAction->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    connect(maximizeAction, &QAction::triggered, this, &QCustomTitleBar::maxButtonClicked);
    connect(maximizeAction, &QAction::triggered, this, &QCustomTitleBar::updateIcon);

    QAction* quitAction = menu->addAction("退出");
    quitAction->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    connect(quitAction, &QAction::triggered, this, &QCustomTitleBar::closeButtonClicked);
}

QCustomTitleBar::~QCustomTitleBar()
{
    delete layout;
	delete IConLabel;
	delete titleLabel;
	delete minButton;
	delete maxButton;
	delete closeButton;
	delete menu;
}

void QCustomTitleBar::setTitleIcon(const QIcon& icon)
{
    IConLabel->setPixmap(icon.pixmap(30, 30));
}

void QCustomTitleBar::setTitleText(const QString& text)
{
    titleLabel->setText(text);
}

void QCustomTitleBar::updateIcon()
{
    if (flag) {
        maxButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
        for (QAction* action : menu->actions()) {
            if (action->objectName() == "maximizeAction") {
                action->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
                break;
            }
        }
        flag = false;
    }
    else {
        maxButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarNormalButton));
        for (QAction* action : menu->actions()) {
            if (action->objectName() == "maximizeAction") {
                action->setIcon(style()->standardIcon(QStyle::SP_TitleBarNormalButton));
                break;
            }
        }
        flag = true;
    }
}

void QCustomTitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        maxButton->click();
        return QWidget::mouseDoubleClickEvent(event);
    }
}

void QCustomTitleBar::setCustomMenu(QMenu* menu)
{
    this->menu = menu;
}

QAction* QCustomTitleBar::addCustomMenuAction(QAction* action)
{
    menu->addAction(action);
    return action;
}

void QCustomTitleBar::showMenu()
{
    menu->exec(QCursor::pos());
}
