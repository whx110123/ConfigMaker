#ifndef CONFIG_H
#define CONFIG_H

#include <QStringList>

class config
{
public:
	config();
	QStringList textlst;
};

class baseconfig :public config
{
public:
	baseconfig();
	ushort ykcode;
	ushort ykselect;
	ushort ykclose;
	ushort ykopen;
	ushort ytcode;
	ushort ymseq;
	ushort ymbcd;
	ushort datalen;
};

class ycconfig :public config
{
public:
	ycconfig();
	ushort ycnum;
	ushort yctype;
	ushort yccode;
	ushort ycaddr;
};

class yxconfig :public config
{
public:
	yxconfig();
	ushort yxnum;
	ushort yxtype;
	ushort yxcode;
	ushort yxaddr;
};

class ymconfig :public config
{
public:
	ymconfig();
	ushort ymnum;
	ushort ymcode;
	ushort ymaddr;
};

class ykconfig :public config
{
public:
	ykconfig();
	ushort ykcloseaddrsel;
	ushort ykcloseaddr;
	ushort ykopenaddrsel;
	ushort ykopenaddr;
};

class ytconfig :public config
{
public:
	ytconfig();
	ushort ytaddr;
};

#endif // CONFIG_H
