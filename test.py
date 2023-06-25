from CustomWindow import CustomWindow
from CustomTitle import CustomTitle
# 无边框窗口
class MyWindow(CustomWindow):
    def __init__(self):
        super().__init__()
        
    def setTitleBar(self, title_bar, title_bar_height=30):
        return super().setTitleBar(title_bar)
    


if __name__ == '__main__':
    import sys
    from PyQt6.QtWidgets import QApplication, QTableWidget
    from PyQt6.QtWidgets import QMenuBar, QStatusBar
    app = QApplication(sys.argv)
    window = MyWindow()
    window.setTitleBar(CustomTitle())
    window.setMainWidget(QTableWidget(10, 10))
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
    sys.exit(app.exec())