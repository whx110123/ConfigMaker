#ifndef CONFIG_H
#define CONFIG_H

#include <QStringList>

class config
{
public:
	config();
	QStringList textlst;
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

#endif // CONFIG_H
