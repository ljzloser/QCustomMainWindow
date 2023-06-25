from PyQt6.QtWidgets import QWidget, QLabel, QPushButton, QHBoxLayout, QStyle, QMenu
from PyQt6.QtCore import Qt, pyqtSignal
from PyQt6.QtGui import QCursor


class CustomTitle(QWidget):
    minButtonClicked = pyqtSignal()  # 最小化按钮信号
    maxButtonClicked = pyqtSignal()  # 最大化按钮信号
    closeButtonClicked = pyqtSignal()  # 关闭按钮信号

    def __init__(self, parent=None) -> None:
        super().__init__(parent)
        self.layout = QHBoxLayout()
        self.layout.setContentsMargins(0, 0, 0, 0)
        self.IConLabel = QLabel()
        self.IConLabel.setFixedSize(30, 30)
        self.IConLabel.setScaledContents(True)
        self.IConLabel.setMouseTracking(True)
        self.titleLabel = QLabel()
        self.titleLabel.setStyleSheet("font-size: 15px;")
        # 左中心对齐
        self.titleLabel.setAlignment(
            Qt.AlignmentFlag.AlignLeft | Qt.AlignmentFlag.AlignVCenter)
        self.titleLabel.setContentsMargins(0, 0, 0, 0)
        self.titleLabel.setFixedHeight(30)
        self.titleLabel.setMouseTracking(True)

        # 自定义菜单
        self.setContextMenuPolicy(Qt.ContextMenuPolicy.CustomContextMenu)
        self.customContextMenuRequested.connect(self.showMenu)
        self.menu = QMenu()

        # 在最右边添加三个按钮
        self.minButton = QPushButton()
        self.minButton.setFixedSize(30, 30)
        # 获取系统标题栏的图标
        self.minButton.setIcon(self.style().standardIcon(
            QStyle.StandardPixmap.SP_TitleBarMinButton))
        self.minButton.setCursor(QCursor(Qt.CursorShape.PointingHandCursor))

        self.minButton.clicked.connect(self.minButtonClicked)

        self.maxButton = QPushButton()
        self.maxButton.setFixedSize(30, 30)
        self.maxButton.setIcon(self.style().standardIcon(
            QStyle.StandardPixmap.SP_TitleBarMaxButton))
        self.maxButton.setCursor(QCursor(Qt.CursorShape.PointingHandCursor))

        self.maxButton.clicked.connect(self.updateIcon)
        self.maxButton.clicked.connect(self.maxButtonClicked)

        self.closeButton = QPushButton()
        self.closeButton.setFixedSize(30, 30)
        self.closeButton.setIcon(self.style().standardIcon(
            QStyle.StandardPixmap.SP_TitleBarCloseButton))
        self.closeButton.setCursor(QCursor(Qt.CursorShape.PointingHandCursor))
        self.closeButton.clicked.connect(self.closeButtonClicked)

        # 添加到布局中
        self.layout.addWidget(self.IConLabel)
        self.layout.addWidget(self.titleLabel)
        self.layout.addWidget(self.minButton)
        self.layout.addWidget(self.maxButton)
        self.layout.addWidget(self.closeButton)

        self.setLayout(self.layout)
        self.setTitleText("Title")
        # 获取系统标题栏的图标
        self.IConLabel.setPixmap(self.style().standardIcon(
            QStyle.StandardPixmap.SP_TitleBarMenuButton).pixmap(30, 30))
        self.flag = False

        minimizeAction = self.menu.addAction("最小化")
        minimizeAction.triggered.connect(self.minButtonClicked)
        minimizeAction.setIcon(self.style().standardIcon(
            QStyle.StandardPixmap.SP_TitleBarMinButton))
        maximizeAction = self.menu.addAction("最大化/还原")
        maximizeAction.setObjectName("maximizeAction")
        maximizeAction.triggered.connect(self.maxButtonClicked)
        maximizeAction.triggered.connect(self.updateIcon)
        maximizeAction.setIcon(self.style().standardIcon(
            QStyle.StandardPixmap.SP_TitleBarMaxButton))
        quitAction = self.menu.addAction("退出")
        quitAction.setIcon(self.style().standardIcon(
            QStyle.StandardPixmap.SP_TitleBarCloseButton))
        quitAction.triggered.connect(self.closeButtonClicked)

    def setTitleIcon(self, icon):
        """
        设置标题栏图标
        """
        self.IConLabel.setPixmap(icon)

    def setTitleText(self, text):
        """
        设置标题栏文字
        """
        self.titleLabel.setText(text)

    def updateIcon(self):
        """
        更新最大化/还原按钮图标
        """
        if self.flag:
            self.maxButton.setIcon(self.style().standardIcon(
                QStyle.StandardPixmap.SP_TitleBarMaxButton))
            # 寻找self.menu中的maximizeAction
            for action in self.menu.actions():
                if action.objectName() == "maximizeAction":
                    action.setIcon(self.style().standardIcon(
                        QStyle.StandardPixmap.SP_TitleBarMaxButton))
            self.flag = False
        else:
            self.maxButton.setIcon(self.style().standardIcon(
                QStyle.StandardPixmap.SP_TitleBarNormalButton))
            for action in self.menu.actions():
                if action.objectName() == "maximizeAction":
                    action.setIcon(self.style().standardIcon(
                        QStyle.StandardPixmap.SP_TitleBarNormalButton))
            self.flag = True

    def mouseDoubleClickEvent(self, a0) -> None:
        if a0.buttons() == Qt.MouseButton.LeftButton:
            self.maxButton.click()
            return super().mouseDoubleClickEvent(a0)

    def setCustomMenu(self, menu):
        """
        设置自定义菜单
        预置了最小化、最大化/还原、退出三个菜单项
        """
        self.menu = menu
        return self.menu

    def addCustomMenuAction(self, action):
        """
        添加自定义菜单项
        可以提前设置好triggered信号再添加    
        """
        self.menu.addAction(action)
        return action

    def showMenu(self):
        """
        显示菜单
        """
        self.menu.exec(QCursor.pos())  # 在鼠标位置显示菜单
