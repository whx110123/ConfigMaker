#include "globalfunc.h"

QStringList mStrToList(QString str,int mod)
{
	QStringList strlist = QStringList();
	if(!str.isEmpty())
	{
		strlist = str.split('\n');
		for (int i = 0;i < strlist.length();i++)
		{
			strlist.replace(i,strlist.value(i).trimmed());
		}
		strlist.removeAll("");
	}
	if(mod == 1 && strlist.length() >0)
	{
		return QStringList()<<strlist.at(0);
	}
	return strlist;
}

void mXmlToTxt(QString protocolname,QString filename)
{

}
