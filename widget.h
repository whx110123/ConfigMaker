#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "globalfunc.h"
#include <QtXml>
#include "dialogintroduction.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = nullptr);
	~Widget();

	QString filetxtdir;								//txt文件路径
	QString filecfgdir;								//cfg文件路径
	QString filename;								//文件名
	QString createmodbustxt();
	QString createmodbuscfg();
	QString createxml();
	QString createtxt();							//编写txt文件内容
	QString createcfg();							//编写cfg文件内容
//	void findwithtype(QDomElement &root, QDomElement &elem,QString type,int index);
	void findelement(QDomElement &root, QDomElement &elem,QString tagname = QString(),QString attr= QString(),QString attrvalue= QString());
private slots:
	void on_PB_selectfile_clicked();				//选择点表文件
	void on_PB_out_clicked();						//导出点表

	void on_pbintro_clicked();

private:
	Ui::Widget *ui;
	DialogIntroduction *diaintro;
};
#endif // WIDGET_H
