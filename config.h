#ifndef CONFIG_H
#define CONFIG_H

#include <QStringList>

class config
{
public:
	config();
	QStringList textlst;				//描述
};

class baseconfig :public config
{
public:
	baseconfig();
	ushort ykcode;						//遥控功能码
	ushort ykselect;					//遥控预置标志
	ushort ykclose;						//控合命令字
	ushort ykopen;						//控分命令字
	ushort ytcode;						//遥调功能码
	ushort ymseq;						//遥脉低字节寄存器在前
	ushort ymbcd;						//遥脉BCD码格式
	ushort datalen;						//从机应答报文读取数据长度字节个数
};

class ycconfig :public config
{
public:
	ycconfig();
	ushort ycnum;						//遥测寄存器个数
	ushort yctype;						//遥测四字节
	ushort yccode;						//遥测功能码
	ushort ycaddr;						//遥测起始地址
};

class yxconfig :public config
{
public:
	yxconfig();
	ushort yxnum;						//遥信寄存器个数
	ushort yxtype;						//遥信寄存器BIT长度
	ushort yxcode;						//遥信功能码
	ushort yxaddr;						//遥信起始地址
};

class ymconfig :public config
{
public:
	ymconfig();
	ushort ymnum;						//遥脉寄存器个数
	ushort ymcode;						//遥脉功能码
	ushort ymaddr;						//遥脉起始地址
};

class ykconfig :public config
{
public:
	ykconfig();
	ushort ykcloseaddrsel;				//遥控 控合预置地址
	ushort ykcloseaddr;					//遥控 控合地址
	ushort ykopenaddrsel;				//遥控 控分预置地址
	ushort ykopenaddr;					//遥控 控分地址
};

class ytconfig :public config
{
public:
	ytconfig();
	ushort ytaddr;						//遥调 设置地址
};

#endif // CONFIG_H
