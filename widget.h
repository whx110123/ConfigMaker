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
	void initconfig();								//初始化
	QString createtxt();							//编写txt文件内容
	QString createcfg();							//编写cfg文件内容
	int groupsort();								//计算分组数与分组排序
	QString checkerror();							//导出前检查错误
	char grouptype[150];							//分组排序
	QAction *act1;									//右键菜单1 添加数据
	QAction *act2;									//右键菜单2 删除
	QAction *act3;									//右键菜单3 重命名
	int ycnum;										//遥测组数
	int yxnum;										//遥信组数
	int ymnum;										//遥脉组数
	int yknum;										//遥控个数
	int ytnum;										//遥调个数
	baseconfig *base;								//基本配置
	QMap<QString , class ycconfig> ycmap;			//所有遥测
	QMap<QString , class yxconfig> yxmap;			//所有遥信
	QMap<QString , class ymconfig> ymmap;			//所有遥脉
	QMap<QString , class ykconfig> ykmap;			//所有遥控
	QMap<QString , class ytconfig> ytmap;			//所有遥调

	QString filetxtdir;								//txt文件路径
	QString filecfgdir;								//cfg文件路径
	QString filename;								//文件名
	QString protocolname;							//规约名

private slots:
	void popMenu(const QPoint&);					//响应右键
	void createItem();								//创建条目
	void deleteItem();								//删除条目
	void renameItem();								//重命名条目
	void on_treeWidget_itemSelectionChanged();		//选择条目改变时，显示对应内容

	void on_PBsave_clicked();						//保存基本配置
	void on_CB1_stateChanged(int arg1);				//10进制与16进制转换
	void on_CB2_stateChanged(int arg1);				//10进制与16进制转换
	void on_CB3_stateChanged(int arg1);				//10进制与16进制转换
	void on_CB4_stateChanged(int arg1);				//10进制与16进制转换
	void on_CB5_stateChanged(int arg1);				//10进制与16进制转换
	void on_CB6_stateChanged(int arg1);				//10进制与16进制转换
	void on_CB7_stateChanged(int arg1);				//10进制与16进制转换
	void on_CB8_stateChanged(int arg1);				//10进制与16进制转换

	void on_PBycsave_clicked();						//保存遥测
	void on_CByc1_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByc2_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByc3_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByc4_stateChanged(int arg1);			//10进制与16进制转换

	void on_PByxsave_clicked();						//保存遥信
	void on_CByx1_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByx2_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByx3_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByx4_stateChanged(int arg1);			//10进制与16进制转换

	void on_PBymsave_clicked();						//保存遥脉
	void on_CBym1_stateChanged(int arg1);			//10进制与16进制转换
	void on_CBym2_stateChanged(int arg1);			//10进制与16进制转换
	void on_CBym3_stateChanged(int arg1);			//10进制与16进制转换

	void on_PByksave_clicked();						//保存单个遥控
	void on_CByk1_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByk2_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByk3_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByk4_stateChanged(int arg1);			//10进制与16进制转换

	void on_PBytsave_clicked();						//保存单个遥调
	void on_CByt1_stateChanged(int arg1);			//10进制与16进制转换

	void on_PBykssave_clicked();					//保存批量遥控

	void on_PBytssave_clicked();					//保存批量遥调

	void on_PB_selectfile_clicked();				//选择点表文件
	void on_PB_out_clicked();						//导出点表

protected:
	virtual void keyPressEvent(QKeyEvent *event);	//捕获部分键盘信号
private:
	Ui::Widget *ui;
};
#endif // WIDGET_H
