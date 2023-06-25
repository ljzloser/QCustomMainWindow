#ifndef CUSTOMTITLE_H
#define CUSTOMTITLE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStyle>
#include <QMenu>
#include <QCursor>
#include <QMouseEvent>

class QCustomTitleBar : public QWidget
{
	Q_OBJECT

public:
	QCustomTitleBar(QWidget* parent = nullptr);
	~QCustomTitleBar();

	void setTitleIcon(const QIcon& icon);
	void setTitleText(const QString& text);
	void setCustomMenu(QMenu* menu);
	QAction* addCustomMenuAction(QAction* action);

signals:
	void minButtonClicked();
	void maxButtonClicked();
	void closeButtonClicked();

protected:
	void mouseDoubleClickEvent(QMouseEvent* event) override;

private slots:
	void updateIcon();
	void showMenu();

private:
	QHBoxLayout* layout;
	QLabel* IConLabel;
	QLabel* titleLabel;
	QPushButton* minButton;
	QPushButton* maxButton;
	QPushButton* closeButton;
	QMenu* menu;
	bool flag;
};

#endif // CUSTOMTITLE_H
