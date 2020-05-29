#ifndef MODBUSFRM_H
#define MODBUSFRM_H

#include <QMap>
#include <QWidget>
#include <QAction>
#include <QStyleFactory>
#include <QMenu>
#include <QTreeWidget>

namespace Ui {
	class ModbusFrm;
}

struct modbusItemData
{
	QStringList textlst;				//描述

	ushort groupnum;					//分组数

	ushort ycnum;						//遥测寄存器个数
	ushort yctype;						//遥测四字节
	ushort yccode;						//遥测功能码
	ushort ycaddr;						//遥测起始地址

	ushort yxnum;						//遥信寄存器个数
	ushort yxtype;						//遥信寄存器BIT长度
	ushort yxcode;						//遥信功能码
	ushort yxaddr;						//遥信起始地址

	ushort ymnum;						//遥脉寄存器个数
	ushort ymcode;						//遥脉功能码
	ushort ymaddr;						//遥脉起始地址

	ushort ykcode;						//遥控功能码
	ushort ykselect;					//遥控预置标志
	ushort ykclose;						//控合命令字
	ushort ykopen;						//控分命令字
	ushort ykcloseaddrsel;				//遥控 控合预置地址
	ushort ykcloseaddr;					//遥控 控合地址
	ushort ykopenaddrsel;				//遥控 控分预置地址
	ushort ykopenaddr;					//遥控 控分地址

	ushort ytcode;						//遥调功能码
	ushort ytaddr;						//遥调 设置地址

	ushort ymseq;						//遥脉低字节寄存器在前
	ushort ymbcd;						//遥脉BCD码格式
	ushort datalen;						//从机应答报文读取数据长度字节个数
};
Q_DECLARE_METATYPE(modbusItemData)

static modbusItemData defaultdata = {
	QStringList(),
	0,0,0,0,0,0,0,0,0,0,
	0,0,5,0,0xffff,0,0,0,0,0,
	6,0,0,0,1
};

enum pointtype
{
	BASE = 1000,
	YC,
	YX,
	YM,
	YK,
	YT,
	YCITEM,
	YXITEM,
	YMITEM,
	YKITEM,
	YTITEM
};
class ModbusFrm : public QWidget
{
	Q_OBJECT

public:
	explicit ModbusFrm(QWidget *parent = nullptr);
	~ModbusFrm();
public:
	void initconfig();								//初始化
	void groupscla();								//计算分组数
	QString checkerror();							//导出前检查错误
//	QString groupsort();							//分组排序
	void groupucharsort();
	uchar groupuchar[255];

private slots:
	void popMenu(const QPoint&);					//响应右键
	void createItem();								//创建条目
	void deleteItem();								//删除条目
	void renameItem();								//重命名条目
//	void on_treeWidget_itemSelectionChanged();		//选择条目改变时，显示对应内容
//	void on_PBsave_clicked();						//保存
	void saveItem(QTreeWidgetItem *item);
	void refreshItem(QTreeWidgetItem *item);
	void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

	void on_CB1_stateChanged(int arg1);				//10进制与16进制转换
	void on_CB2_stateChanged(int arg1);				//10进制与16进制转换
	void on_CB3_stateChanged(int arg1);				//10进制与16进制转换
	void on_CB4_stateChanged(int arg1);				//10进制与16进制转换
	void on_CB5_stateChanged(int arg1);				//10进制与16进制转换
	void on_CB6_stateChanged(int arg1);				//10进制与16进制转换
	void on_CB7_stateChanged(int arg1);				//10进制与16进制转换
	void on_CB8_stateChanged(int arg1);				//10进制与16进制转换
	void on_CByc1_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByc2_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByc3_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByc4_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByx1_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByx2_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByx3_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByx4_stateChanged(int arg1);			//10进制与16进制转换
	void on_CBym1_stateChanged(int arg1);			//10进制与16进制转换
	void on_CBym2_stateChanged(int arg1);			//10进制与16进制转换
	void on_CBym3_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByk1_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByk2_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByk3_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByk4_stateChanged(int arg1);			//10进制与16进制转换
	void on_CByt1_stateChanged(int arg1);			//10进制与16进制转换

	void on_PBykadd_clicked();

	void on_PBytadd_clicked();

protected:
//	virtual void keyPressEvent(QKeyEvent *event);	//捕获部分键盘信号
public:
	void writeXml();
	void readXml();
private:
	Ui::ModbusFrm *ui;
};

#endif // MODBUSFRM_H
