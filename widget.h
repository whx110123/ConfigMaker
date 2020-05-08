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

private:
	void initconfig();
	QAction *act1;
	QAction *act2;
	QAction *act3;
	int ycnum;
	int yxnum;
	int ymnum;
	int yknum;
	int ytnum;
	baseconfig *base;
	QMap<QString , class ycconfig> ycmap;
	QMap<QString , class yxconfig> yxmap;
	QMap<QString , class ymconfig> ymmap;
	QMap<QString , class ykconfig> ykmap;
	QMap<QString , class ytconfig> ytmap;

private slots:
	void popMenu(const QPoint&);
	void createItem();
	void deleteItem();
	void renameItem();
	void on_treeWidget_itemSelectionChanged();

	void on_PBsave_clicked();
	void on_CB1_stateChanged(int arg1);
	void on_CB2_stateChanged(int arg1);
	void on_CB3_stateChanged(int arg1);
	void on_CB4_stateChanged(int arg1);
	void on_CB5_stateChanged(int arg1);
	void on_CB6_stateChanged(int arg1);
	void on_CB7_stateChanged(int arg1);
	void on_CB8_stateChanged(int arg1);

	void on_PBycsave_clicked();
	void on_CByc1_stateChanged(int arg1);
	void on_CByc2_stateChanged(int arg1);
	void on_CByc3_stateChanged(int arg1);
	void on_CByc4_stateChanged(int arg1);

	void on_PByxsave_clicked();
	void on_CByx1_stateChanged(int arg1);
	void on_CByx2_stateChanged(int arg1);
	void on_CByx3_stateChanged(int arg1);
	void on_CByx4_stateChanged(int arg1);

	void on_PBymsave_clicked();
	void on_CBym1_stateChanged(int arg1);
	void on_CBym2_stateChanged(int arg1);
	void on_CBym3_stateChanged(int arg1);

	void on_PByksave_clicked();
	void on_CByk1_stateChanged(int arg1);
	void on_CByk2_stateChanged(int arg1);
	void on_CByk3_stateChanged(int arg1);
	void on_CByk4_stateChanged(int arg1);

	void on_PBytsave_clicked();
	void on_CByt1_stateChanged(int arg1);





private:
	Ui::Widget *ui;
};
#endif // WIDGET_H
