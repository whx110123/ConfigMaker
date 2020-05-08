#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAction>
#include <QStyleFactory>
#include <QMenu>
#include <QTreeWidget>
#include "config.h"

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
	void renameItem();

	void on_PBycsave_clicked();


	void on_CByc1_stateChanged(int arg1);

	void on_CByc2_stateChanged(int arg1);

	void on_CByc3_stateChanged(int arg1);

	void on_CByc4_stateChanged(int arg1);

	void on_treeWidget_itemSelectionChanged();

private:
	void initconfig();
	void formshow(QTreeWidgetItem *item);
	QAction *act1;
	QAction *act2;
	QAction *act3;
	int ycnum;
	int yxnum;
	int ymnum;
	int yknum;
	int ytnum;
	QMap<QString , class ycconfig> ycmap;
private:
	Ui::Widget *ui;
};
#endif // WIDGET_H
