#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAction>
#include <QStyleFactory>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = nullptr);
	~Widget();

private slots:
	void popMenu(const QPoint&);
	void createItem();
	void deleteItem();
private:
	void initconfig();
	QAction *act1;
	QAction *act2;
	int ycnum;
	int yxnum;
	int ymnum;
	int yknum;
	int ytnum;
private:
	Ui::Widget *ui;
};
#endif // WIDGET_H
