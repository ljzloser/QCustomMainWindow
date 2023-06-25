from PyQt6.QtWidgets import QWidget, QApplication, QVBoxLayout, QMainWindow, QMenuBar, QStatusBar
from PyQt6.QtCore import Qt, QRect,QTimer
from PyQt6.QtGui import QPainter, QColor, QBrush, QPen,QCursor
from CustomTitle import CustomTitle

# 自定义边框窗口


class CustomWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowFlag(Qt.WindowType.FramelessWindowHint)  # 隐藏边框
        self.setAttribute(
            Qt.WidgetAttribute.WA_TranslucentBackground)  # 设置窗口背景透明

        self.setMouseTracking(True)  # 设置鼠标跟踪
        self.setAttribute(Qt.WidgetAttribute.WA_Hover,True)  # 设置鼠标悬停
        self.dragging_edge = None  # 拖动的边缘
        self.is_dragging = False  # 是否正在拖动

        self.edge_size = 10  # 边缘大小
        self.radius = 10  # 圆角角度
        self.border_color = Qt.GlobalColor.gray  # 边框颜色
        self.border_size = 2  # 边框大小
        self.background_color = Qt.GlobalColor.white  # 背景颜色
        self.background_image = None  # 背景图片
        self.title_bar = None  # 标题栏
        self.menu_bar = None  # 菜单栏
        self.main_widget = None  # 主窗口
        self.status_bar = None  # 底部状态栏
        self.drag_pos = None  # 拖动位置
        self.customNormal = None  # 自定义正常状态
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.CurrsorUpdate)
        self.timer.start(1000)

        self.layout = QVBoxLayout()  # 创建一个垂直布局放置标题栏,菜单栏,主窗口，底部状态栏
        self.layout.setContentsMargins(
            self.edge_size, self.edge_size, self.edge_size, self.edge_size)  # 设置边距为边缘距离
        self.layout.setSpacing(2)  # 设置各个控件之间的间距为2

        self.setLayout(self.layout)  # 设置布局

    def loadLayout(self):
        """
        重新加载布局
        """
        # 移除布局中的所有部件
        while self.layout.count():
            item = self.layout.takeAt(0)
        if self.title_bar is not None:
            self.layout.addWidget(self.title_bar)
        if self.menu_bar is not None:
            self.layout.addWidget(self.menu_bar)
        if self.main_widget is not None:
            self.layout.addWidget(self.main_widget)
        if self.status_bar is not None:
            self.layout.addWidget(self.status_bar)

    def showCustomNormal(self):
        """
        最大化窗口
        """
        if self.isMaximized() == False:
            self.customNormal = self.geometry()
            self.showMaximized()
        else:
            self.setGeometry(self.customNormal)

    # 设置标题栏
    def setTitleBar(self, title_bar):
        """
        设置标题栏
        :param title_bar: 标题栏
        :return: None
        """
        self.title_bar = title_bar
        self.title_bar.setMouseTracking(True)  # 设置鼠标跟踪
        self.title_bar.setFixedHeight(30)  # 设置标题栏高度
        self.title_bar.minButtonClicked.connect(
            self.showMinimized)  # 最小化按钮点击信号连接到最小化窗口槽函数
        self.title_bar.maxButtonClicked.connect(
            self.showCustomNormal)   # 最大化按钮点击信号连接到最大化窗口槽函数
        self.title_bar.closeButtonClicked.connect(
            self.close)  # 关闭按钮点击信号连接到关闭窗口槽函数
        self.loadLayout()

    # 设置菜单栏

    def setMenuBar(self, menu_bar):
        """
        设置菜单栏
        :param menu_bar: 菜单栏
        :return: None
        """
        self.menu_bar = menu_bar

        self.menu_bar.setFixedHeight(20)
        self.loadLayout()
    # 设置主窗口

    def setMainWidget(self, main_widget):
        """
        设置主窗口
        :param main_widget: 主窗口
        :return: None
        """
        self.main_widget = main_widget
        # self.main_widget.setMouseTracking(True)  # 设置鼠标跟踪
        self.loadLayout()
    # 设置底部状态栏

    def setStatusBar(self, status_bar):
        """
        设置底部状态栏
        :param status_bar: 底部状态栏
        :return: None
        """
        self.status_bar = status_bar
        # self.layout.insertWidget(6, self.status_bar)
        self.status_bar.setFixedHeight(20)
        self.loadLayout()

    def getTitleBar(self):
        return self.title_bar

    def getMenuBar(self):
        return self.menu_bar

    def getMainWidget(self):
        return self.main_widget

    def getStatusBar(self):
        return self.status_bar

    def setEdgeSize(self, size=5):
        """
        设置边缘大小
        :param size: 边缘大小
        :return: None
        """
        self.edge_size = size
        self.layout.setContentsMargins(
            self.edge_size, self.edge_size, self.edge_size, self.edge_size)  # 设置边距为边缘距离

    def setRadius(self, radius=10):
        """
        设置圆角角度
        :param radius: 圆角角度
        :return: None
        """
        self.radius = radius
    # 设置边框颜色

    def setBorderColor(self, color, width=2):
        """
        设置边框颜色
        :param color: 颜色
        :param width: 边框宽度
        :return: None
        """
        self.border_color = color
        self.border_size = width
    # 设置背景颜色

    def setBackgroundColor(self, color):
        """
        设置背景颜色
        :param color: 颜色
        :return: None
        """
        self.background_color = color
    # 设置背景图片

    def setBackgroundImage(self, image):
        """
        设置背景图片
        :param image: 图片
        :return: None
        """
        self.background_image = image

    def paintEvent(self, event):
        # 先绘制一层边框颜色的圆角矩形，大小为窗口大小
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)  # 抗锯齿
        painter.setPen(Qt.PenStyle.NoPen)  # 无边框
        painter.setBrush(QBrush(self.border_color))  # 边框颜色
        painter.drawRoundedRect(
            self.rect(), self.radius, self.radius)  # 绘制圆角矩形
        # 再绘制一层背景颜色的圆角矩形，大小为窗口大小减去边框大小
        painter.setBrush(QBrush(self.background_color))  # 背景颜色
        painter.drawRoundedRect(self.rect().adjusted(self.border_size, self.border_size, -
                                self.border_size, -self.border_size), self.radius, self.radius)  # 绘制圆角矩形

        if self.background_image:
            # 如果有背景图片，绘制背景图片
            image = self.background_image.scaled(self.rect().adjusted(
                self.border_size, self.border_size, -self.border_size, -self.border_size).size())  # 缩放图片
            painter.setBrush(QBrush(image))
            painter.drawRoundedRect(self.rect().adjusted(
                self.border_size, self.border_size, -self.border_size, -self.border_size), self.radius, self.radius)  # 绘制圆角矩形

        for i in range(1, self.layout.count()):
            x = self.layout.itemAt(i).geometry().x()
            y = self.layout.itemAt(i).geometry().y() - 1
            w = self.layout.itemAt(i).geometry().width()
            h = 1
            # 绘制一条分割线
            painter.setPen(QPen(QColor(0, 0, 0, 50), 1))
            painter.drawLine(x, y, x + w, y + h)

    # 重写鼠标事件
    # 当鼠标移动到窗口边缘时，改变鼠标形状
    def CurrsorUpdate(self):
        # 在鼠标移动时触发此事件
        if not self.isMaximized():
            # 获取窗口的绝对位置
            window_rect = self.geometry()
            # 获取鼠标绝对位置
            mouse_pos = QCursor().pos()
            if not self.is_dragging:
                # 判断鼠标位置
                if mouse_pos.x() < window_rect.x() + self.edge_size:
                    # 鼠标在左边缘
                    if mouse_pos.y() < window_rect.y() + self.edge_size:
                        # 鼠标在左上角
                        self.dragging_edge = 'top_left'
                        self.setCursor(Qt.CursorShape.SizeFDiagCursor)
                    elif mouse_pos.y() > window_rect.height() - self.edge_size + window_rect.y():
                        # 鼠标在左下角
                        self.dragging_edge = 'bottom_left'
                        self.setCursor(Qt.CursorShape.SizeBDiagCursor)
                    else:
                        # 鼠标在左边
                        self.dragging_edge = 'left'
                        self.setCursor(Qt.CursorShape.SizeHorCursor)
                elif mouse_pos.x() > window_rect.width() - self.edge_size + window_rect.x():
                    # 鼠标在右边缘
                    if mouse_pos.y() < window_rect.y() + self.edge_size:
                        # 鼠标在右上角
                        self.dragging_edge = 'top_right'
                        self.setCursor(Qt.CursorShape.SizeBDiagCursor)
                    elif mouse_pos.y() > window_rect.height() - self.edge_size + window_rect.y():
                        # 鼠标在右下角
                        self.dragging_edge = 'bottom_right'
                        self.setCursor(Qt.CursorShape.SizeFDiagCursor)
                    else:
                        # 鼠标在右边
                        self.dragging_edge = 'right'
                        self.setCursor(Qt.CursorShape.SizeHorCursor)
                else:
                    # 鼠标在上边缘
                    if mouse_pos.y() < window_rect.y() + self.edge_size:
                        # 鼠标在上边
                        self.dragging_edge = 'top'
                        self.setCursor(Qt.CursorShape.SizeVerCursor)
                    elif mouse_pos.y() > window_rect.height() - self.edge_size + window_rect.y():
                        # 鼠标在下边
                        self.dragging_edge = 'bottom'
                        self.setCursor(Qt.CursorShape.SizeVerCursor)
                    else:
                        # 鼠标在中间
                        self.dragging_edge = None
                        self.setCursor(Qt.CursorShape.ArrowCursor)
    def mouseMoveEvent(self, event):
        # 在鼠标移动时触发此事件
        if not self.isMaximized():
            # 获取窗口的绝对位置
            window_rect = self.geometry()
            # 获取鼠标绝对位置
            mouse_pos = self.mapToGlobal(event.pos())
            if not self.is_dragging:
                # 判断鼠标位置
                if mouse_pos.x() < window_rect.x() + self.edge_size:
                    # 鼠标在左边缘
                    if mouse_pos.y() < window_rect.y() + self.edge_size:
                        # 鼠标在左上角
                        self.dragging_edge = 'top_left'
                        self.setCursor(Qt.CursorShape.SizeFDiagCursor)
                    elif mouse_pos.y() > window_rect.height() - self.edge_size + window_rect.y():
                        # 鼠标在左下角
                        self.dragging_edge = 'bottom_left'
                        self.setCursor(Qt.CursorShape.SizeBDiagCursor)
                    else:
                        # 鼠标在左边
                        self.dragging_edge = 'left'
                        self.setCursor(Qt.CursorShape.SizeHorCursor)
                elif mouse_pos.x() > window_rect.width() - self.edge_size + window_rect.x():
                    # 鼠标在右边缘
                    if mouse_pos.y() < window_rect.y() + self.edge_size:
                        # 鼠标在右上角
                        self.dragging_edge = 'top_right'
                        self.setCursor(Qt.CursorShape.SizeBDiagCursor)
                    elif mouse_pos.y() > window_rect.height() - self.edge_size + window_rect.y():
                        # 鼠标在右下角
                        self.dragging_edge = 'bottom_right'
                        self.setCursor(Qt.CursorShape.SizeFDiagCursor)
                    else:
                        # 鼠标在右边
                        self.dragging_edge = 'right'
                        self.setCursor(Qt.CursorShape.SizeHorCursor)
                else:
                    # 鼠标在上边缘
                    if mouse_pos.y() < window_rect.y() + self.edge_size:
                        # 鼠标在上边
                        self.dragging_edge = 'top'
                        self.setCursor(Qt.CursorShape.SizeVerCursor)
                    elif mouse_pos.y() > window_rect.height() - self.edge_size + window_rect.y():
                        # 鼠标在下边
                        self.dragging_edge = 'bottom'
                        self.setCursor(Qt.CursorShape.SizeVerCursor)
                    else:
                        # 鼠标在中间
                        self.dragging_edge = None
                        self.setCursor(Qt.CursorShape.ArrowCursor)

            # 判断是否正在拖动
            if self.is_dragging:
                # 获取窗口最小宽度和高度
                min_width = self.minimumWidth()
                min_height = self.minimumHeight()
                # 正在拖动
                if self.dragging_edge is not None:
                    # 拖动边缘不为空,根据拖动边缘设置窗口大小,并且考虑最小宽度和高度
                    if self.dragging_edge == 'top_left':
                        # 左上角
                        # 右下角坐标不变
                        rect = QRect(mouse_pos.x(), mouse_pos.y(), window_rect.width(
                        ) + window_rect.x() - mouse_pos.x(), window_rect.height() + window_rect.y() - mouse_pos.y())
                        # 判断右下角坐标和 window_rect 的右下角坐标是否相同
                        if rect.bottomRight() == window_rect.bottomRight():
                            if rect.width() < min_width:
                                rect.setX(rect.x() - min_width + rect.width())
                            if rect.height() < min_height:
                                rect.setY(
                                    rect.y() - min_height + rect.height())
                            self.setGeometry(rect)
                    elif self.dragging_edge == 'top':
                        # 上边
                        # 右下角坐标的 x 不变, y 不变
                        rect = QRect(window_rect.x(), mouse_pos.y(), window_rect.width(
                        ), window_rect.height() + window_rect.y() - mouse_pos.y())
                        # 判断右下角坐标和 window_rect 的右下角坐标是否相同
                        if rect.bottomRight() == window_rect.bottomRight():
                            if rect.height() < min_height:
                                rect.setY(
                                    rect.y() - min_height + rect.height())
                            self.setGeometry(rect)
                    elif self.dragging_edge == 'top_right':
                        # 右上角
                        # 左下角坐标的 x 不变, y 不变
                        rect = QRect(window_rect.x(), mouse_pos.y(), mouse_pos.x(
                        ) - window_rect.x(), window_rect.height() + window_rect.y() - mouse_pos.y())
                        # 判断左下角坐标和 window_rect 的左下角坐标是否相同
                        if rect.bottomLeft() == window_rect.bottomLeft():
                            if rect.width() < min_width:
                                rect.setX(window_rect.x())
                            if rect.height() < min_height:
                                rect.setY(window_rect.y())
                            self.setGeometry(rect)
                    elif self.dragging_edge == 'right':
                        # 右边
                        self.setGeometry(window_rect.x(), window_rect.y(), max(
                            mouse_pos.x() - window_rect.x(), min_width), window_rect.height())
                    elif self.dragging_edge == 'bottom_right':
                        # 右下角
                        self.setGeometry(window_rect.x(), window_rect.y(), max(mouse_pos.x(
                        ) - window_rect.x(), min_width), max(mouse_pos.y() - window_rect.y(), min_height))
                    elif self.dragging_edge == 'bottom':
                        # 下边
                        self.setGeometry(window_rect.x(), window_rect.y(), window_rect.width(), max(
                            mouse_pos.y() - window_rect.y(), min_height))
                    elif self.dragging_edge == 'bottom_left':
                        # 左下角
                        # 右上角坐标的 x 不变, y 不变
                        rect = QRect(mouse_pos.x(), window_rect.y(), window_rect.width(
                        ) + window_rect.x() - mouse_pos.x(), max(mouse_pos.y() - window_rect.y(), min_height))
                        # 判断右上角坐标和 window_rect 的右上角坐标是否相同
                        if rect.topRight() == window_rect.topRight():
                            if rect.width() < min_width:
                                rect.setX(rect.x() - min_width + rect.width())
                            self.setGeometry(rect)
                    elif self.dragging_edge == 'left':
                        # 左边
                        # 右下角坐标的 x 不变, y 不变
                        rect = QRect(mouse_pos.x(), window_rect.y(), window_rect.width(
                        ) + window_rect.x() - mouse_pos.x(), window_rect.height())
                        # 判断右下角坐标和 window_rect 的右下角坐标是否相同
                        if rect.bottomRight() == window_rect.bottomRight():
                            if rect.width() < min_width:
                                rect.setX(rect.x() - min_width + rect.width())
                            self.setGeometry(rect)
                else:
                    # 拖动边缘为空
                    # self.move(self.pos() + event.pos() - self.drag_pos)
                    pass
            if self.title_bar is not None and self.drag_pos is not None:
                # 标题栏不为空,并且拖动边缘为空
                # 移动窗口
                self.move(self.pos() + event.pos() - self.drag_pos)

    def mousePressEvent(self, event):
        # 不是最大化状态
        if not self.isMaximized():
            # 在鼠标按下时触发此事件
            if event.button() == Qt.MouseButton.LeftButton and self.dragging_edge is not None:
                # 鼠标左键按下
                self.is_dragging = True
            if event.button() == Qt.MouseButton.LeftButton and self.title_bar is not None:
                rect = self.title_bar.geometry()
                if rect.contains(event.pos()):
                    self.drag_pos = event.pos()

    def mouseReleaseEvent(self, event):
        # 在鼠标释放时触发此事件
        if event.button() == Qt.MouseButton.LeftButton:
            # 鼠标左键释放
            self.is_dragging = False
            self.drag_pos = None
            self.dragging_edge = None
            self.setCursor(Qt.CursorShape.ArrowCursor)



if __name__ == '__main__':
    app = QApplication([])
    window = CustomWindow()
    window.setTitleBar(CustomTitle())
    # window.setMenuBar(QLabel('QMenuBar'))
    window.setMainWidget(QMainWindow())
    # window.setStatusBar(QLabel('QStatusBar'))
    menubar = QMenuBar()
    file_menu = menubar.addMenu('File')
    file_menu.addAction('New')

    menubar.addMenu('Edit')
    menubar.addMenu('View')
    menubar.addMenu('Help')

    window.setMenuBar(menubar)
    statusbar = QStatusBar()
    window.setStatusBar(statusbar)
    statusbar.showMessage('this a statusbar', 5000)

    window.show()
    app.exec()
