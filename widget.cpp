#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QDebug>


Widget::Widget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::Widget)
{
	ui->setupUi(this);

}

Widget::~Widget()
{
	delete ui;

}

QString Widget::createmodbustxt()
{
	QString text;
	QFile file("modbus.xml");
	if(!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(NULL,"告警窗","modbus.xml文件不存在");
		return text;
	}
	QDomDocument doc;
	if(!doc.setContent(&file))
	{
		file.close();
		return text;
	}
	file.close();

//	uchar *sort = ui->modbuswdg->groupuchar;

	QDomNode fristnode = doc.firstChild();
//	qDebug()<<fristnode.nodeName() << fristnode.nodeValue();

	text.append("[名称]\n");
	text.append(filename + "\n");
	text.append("\n[类型]\n");
	text.append("保护测控\n");

	QDomElement root = doc.documentElement();
	QDomNode node = root.firstChild();
	QDomElement elem;
	int group = 0;
	if(node.isElement())
	{
		elem = node.toElement();
		if(elem.tagName() == QString("基本配置"))
		{
			QDomNode n = elem.firstChild();
			if(n.isElement())
			{
				QDomElement ne = n.toElement();
				group =ne.attribute("召唤分组数").toInt();
			}

		}
		if(group ==0)
		{
			return QString();
		}
	}
	for (int i = 0;i <70;i++)
	{
		findelement(root,elem,QString(),QString("index"),QString::number(i+1));
		//		findwithtype(root,elem,QString(),i+1);
		if(elem.isNull())
		{
			continue;
		}
		QDomNode n = elem.firstChild();
		n = n.nextSibling();
		if(n.isNull())
		{
			continue;
		}
		text.append("\n["+elem.tagName()+"]\n");
		while(!n.isNull())
		{
			if(n.isElement())
			{
				QDomElement ne = n.toElement();
				if(ne.tagName() == QString("描述"))
				{
					text.append(QString("%1,%2,%3,%4,,5,,\n")
								.arg(ne.attribute("no")).arg(elem.attribute("index"))
								.arg(ne.attribute("no")).arg(ne.attribute("text")));
				}
			}
			n = n.nextSibling();
		}

	}

	text.append("\n[特殊遥信]\n");
	text.append("1,255,1,网络状态A,,5,通,断\n");
	text.append("2,255,2,网络状态B,,5,通,断\n");



	return text;
}

QString Widget::createmodbuscfg()
{
	QString text;
	QFile file("modbus.xml");
	if(!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(NULL,"告警窗","modbus.xml文件不存在");
		return text;
	}
	QDomDocument doc;
	if(!doc.setContent(&file))
	{
		file.close();
		return text;
	}
	file.close();



	QDomNode fristnode = doc.firstChild();
//	qDebug()<<fristnode.nodeName() << fristnode.nodeValue();

	text.append("[属性]\n");
	text.append("名称=" +filename + "\n");
	text.append("默认规约=modbus装置规约\n");
	text.append("版本号=v1.00\n");
	text.append("可变选项组数=1\n");
	text.append("[数据分类]\n");
	text.append("数目=19\n");
	text.append("数据名称=遥测,遥信,遥脉,遥控,遥调,模拟量,动作元件,运行告警,装置自检,硬压板,软压板,故障信息,扰动数据说明,定值,定值区号,特殊遥信,保护测量,装置参数,档位\n");
	text.append("遥测=YC\n");
	text.append("遥信=YX\n");
	text.append("遥脉=YM\n");
	text.append("遥控=YK\n");
	text.append("遥调=YT\n");
	text.append("模拟量=YC\n");
	text.append("动作元件=YX\n");
	text.append("运行告警=YX\n");
	text.append("装置自检=YX\n");
	text.append("硬压板=YX\n");
	text.append("软压板=YXYK\n");
	text.append("故障信息=OTHER\n");
	text.append("扰动数据说明=OTHER\n");
	text.append("定值=OTHER\n");
	text.append("定值区号=OTHER\n");
	text.append("特殊遥信=YX\n");
	text.append("保护测量=YC\n");
	text.append("装置参数=OTHER\n");
	text.append("档位=YP\n");
	text.append("[相关信息]\n");
	text.append("数目=0\n");
	text.append("[可变选项1]\n");
	text.append("名称=可变选项1\n");
	text.append("维数=1\n");

	QDomElement root = doc.documentElement();
	QDomNode node = root.firstChild();
	QDomElement elem;
	int group = 0;
	if(node.isElement())
	{
		elem = node.toElement();
		if(elem.tagName() == QString("基本配置"))
		{
			QDomNode n = elem.firstChild();
			if(n.isElement())
			{
				QDomElement ne = n.toElement();
				group =ne.attribute("召唤分组数").toInt();
			}

		}
		if(group ==0)
		{
			return QString();
		}
	}

	int num = 4 + group * 11;

	int yknum=0;
	findelement(root,elem,"遥控");
	if(!elem.isNull())
	{
		node = elem.lastChild();
		if(node.isElement())
		{
			elem = node.toElement();
			if(elem.tagName() == QString("描述"))
			{
				yknum = elem.attribute("no").toInt();
			}
		}
	}
	int ytnum=0;
	findelement(root,elem,"遥调");
	if(!elem.isNull())
	{
		node = elem.lastChild();
		if(node.isElement())
		{
			elem = node.toElement();
			if(elem.tagName() == QString("描述"))
			{
				ytnum = elem.attribute("no").toInt();
			}
		}
	}
	if(yknum)
		num += 4+yknum*4;
	if(ytnum)
		num += 1+ytnum;
	text.append("数目="+QString::number(num)+"\n");

	int No = 1;
	if(yknum)
	{
		findelement(root,elem,"遥控");
		if(!elem.isNull())
		{
			node = elem.firstChild();
			if(node.isElement())
			{
				QDomElement yk = node.toElement();
				text.append("选项"+QString::number(No++)+"=遥控功能码,INT,"+yk.attribute("遥控功能码")+"(0-65535)\n");
				text.append("选项"+QString::number(No++)+"=遥控预置,INT,"+yk.attribute("遥控预置")+"(0-65535)\n");
				text.append("选项"+QString::number(No++)+"=控合命令字,INT,"+yk.attribute("控合命令字")+"(0-65535)\n");
				text.append("选项"+QString::number(No++)+"=控分命令字,INT,"+yk.attribute("控分命令字")+"(0-65535)\n");
				yk = yk.nextSiblingElement();
				while (!yk.isNull())
				{
					text.append("选项"+QString::number(No++)+"=遥控"+yk.attribute("no")+"控合预置地址,INT,"+yk.attribute("控合预置地址")+"(0-65535)\n");
					text.append("选项"+QString::number(No++)+"=遥控"+yk.attribute("no")+"控合地址,INT,"+yk.attribute("控合地址")+"(0-65535)\n");
					text.append("选项"+QString::number(No++)+"=遥控"+yk.attribute("no")+"控分预置地址,INT,"+yk.attribute("控分预置地址")+"(0-65535)\n");
					text.append("选项"+QString::number(No++)+"=遥控"+yk.attribute("no")+"控分地址,INT,"+yk.attribute("控分地址")+"(0-65535)\n");
					yk = yk.nextSiblingElement();
				}
			}
		}

	}
	if(ytnum)
	{
		findelement(root,elem,"遥调");
		if(!elem.isNull())
		{
			node = elem.firstChild();
			if(node.isElement())
			{
				QDomElement yt = node.toElement();
				text.append("选项"+QString::number(No++)+"=遥调功能码,INT,"+yt.attribute("遥调功能码")+"(0-65535)\n");
				yt = yt.nextSiblingElement();
				while (!yt.isNull())
				{
					text.append("选项"+QString::number(No++)+"=遥调"+yt.attribute("no")+"设置地址,INT,"+yt.attribute("设置地址")+"(0-65535)\n");
					yt = yt.nextSiblingElement();
				}
			}
		}
	}
	text.append("选项"+QString::number(No++)+"=召唤分组数,INT,"+QString::number(group)+"(0-65535)\n");
	uchar *sort = ui->modbuswdg->groupuchar;



	int index = 0;

	while (index < group * 3)
	{
		if(sort[index])
		{
			findelement(root,elem,QString("遥测"),QString("index"),QString::number(sort[index]));
			QDomElement yc;
			findelement(elem,yc,QString("选项"));
			if(!yc.isNull())
			{
				text.append("选项"+QString::number(No++)+"=遥测寄存器个数,INT,"+yc.attribute("遥测寄存器个数")+"(0-65535)\n");
				text.append("选项"+QString::number(No++)+"=遥测四字节,INT,"+yc.attribute("遥测四字节")+"(0-65535)\n");
				text.append("选项"+QString::number(No++)+"=遥测功能码,INT,"+yc.attribute("遥测功能码")+"(0-65535)\n");
				text.append("选项"+QString::number(No++)+"=遥测起始地址,INT,"+yc.attribute("遥测起始地址")+"(0-65535)\n");
			}
		}
		else
		{
			text.append("选项"+QString::number(No++)+"=遥测寄存器个数,INT,0(0-65535)\n");
			text.append("选项"+QString::number(No++)+"=遥测四字节,INT,0(0-65535)\n");
			text.append("选项"+QString::number(No++)+"=遥测功能码,INT,0(0-65535)\n");
			text.append("选项"+QString::number(No++)+"=遥测起始地址,INT,0(0-65535)\n");
		}
		index++;
		if(sort[index])
		{
			findelement(root,elem,QString("遥信"),QString("index"),QString::number(sort[index]));
			QDomElement yx;
			findelement(elem,yx,QString("选项"));
			if(!yx.isNull())
			{
				text.append("选项"+QString::number(No++)+"=遥信寄存器个数,INT,"+yx.attribute("遥信寄存器个数")+"(0-65535)\n");
				text.append("选项"+QString::number(No++)+"=遥信寄存器BIT长度,INT,"+yx.attribute("遥信寄存器BIT长度")+"(0-65535)\n");
				text.append("选项"+QString::number(No++)+"=遥信功能码,INT,"+yx.attribute("遥信功能码")+"(0-65535)\n");
				text.append("选项"+QString::number(No++)+"=遥信起始地址,INT,"+yx.attribute("遥信起始地址")+"(0-65535)\n");
			}
		}
		else
		{
			text.append("选项"+QString::number(No++)+"=遥信寄存器个数,INT,0(0-65535)\n");
			text.append("选项"+QString::number(No++)+"=遥信寄存器BIT长度,INT,0(0-65535)\n");
			text.append("选项"+QString::number(No++)+"=遥信功能码,INT,0(0-65535)\n");
			text.append("选项"+QString::number(No++)+"=遥信起始地址,INT,0(0-65535)\n");
		}
		index++;
		if(sort[index])
		{
			findelement(root,elem,QString("遥脉"),QString("index"),QString::number(sort[index]));
			QDomElement ym;
			findelement(elem,ym,QString("选项"));
			if(!ym.isNull())
			{
				text.append("选项"+QString::number(No++)+"=遥脉寄存器个数,INT,"+ym.attribute("遥脉寄存器个数")+"(0-65535)\n");
				text.append("选项"+QString::number(No++)+"=遥脉功能码,INT,"+ym.attribute("遥脉功能码")+"(0-65535)\n");
				text.append("选项"+QString::number(No++)+"=遥脉起始地址,INT,"+ym.attribute("遥脉起始地址")+"(0-65535)\n");
			}
		}
		else
		{
			text.append("选项"+QString::number(No++)+"=遥脉寄存器个数,INT,0(0-65535)\n");
			text.append("选项"+QString::number(No++)+"=遥脉功能码,INT,0(0-65535)\n");
			text.append("选项"+QString::number(No++)+"=遥脉起始地址,INT,0(0-65535)\n");
		}
		index++;
	}
	findelement(root,elem,QString("基本配置"));
	QDomElement base;
	findelement(elem,base,QString("选项"));
	if(!base.isNull())
	{
		text.append("选项"+QString::number(No++)+"=遥脉低字节寄存器在前,INT,"+base.attribute("遥脉低字节寄存器在前")+"(0-65535)\n");
		text.append("选项"+QString::number(No++)+"=遥脉BCD码格式,INT,"+base.attribute("遥脉BCD码格式")+"(0-65535)\n");
		text.append("选项"+QString::number(No++)+"=从机应答报文读取数据长度字节个数,INT,"+base.attribute("从机应答报文读取数据长度字节个数")+"(1-2)\n");
	}

	return text;
}

QString Widget::createxml()
{
	QString text;
	if(ui->CB_protocol->currentText() == QString("modbus装置规约"))
	{
		text = ui->modbuswdg->checkerror();
		if(!text.contains("出错"))
		{
			ui->modbuswdg->writeXml();
		}
	}

	return text;
}
QString Widget::createtxt()
{
	QString text;
	if(ui->CB_protocol->currentText() == QString("modbus装置规约"))
	{
		text.append(createmodbustxt());
	}

	return text;
}

QString Widget::createcfg()
{
	QString text;
	if(ui->CB_protocol->currentText() == QString("modbus装置规约"))
	{
		text.append(createmodbuscfg());
	}


	return text;
}

//void Widget::findwithtype(QDomElement &root, QDomElement &elem,QString type, int index)
//{
//	QDomNodeList list = root.childNodes();
//	for (int i =0;i<list.count();i++)
//	{
//		QDomNode node = list.at(i);
//		if(node.isElement())
//		{
//			elem = node.toElement();
//			if((type.isEmpty()||elem.tagName() == type) && elem.attribute("index") == QString::number(index))
//			{
//				return;
//			}
//		}
//	}
//	elem.clear();
//	return;
//}

void Widget::findelement(QDomElement &root, QDomElement &elem, QString tagname, QString attr, QString attrvalue)
{
	QDomNode node = root.firstChild();
	while (!node.isNull())
	{
		if(node.isElement())
		{
			elem = node.toElement();
			if((tagname.isEmpty()||elem.tagName() == tagname)&&(attr.isEmpty()||attrvalue.isEmpty()|| elem.attribute(attr) ==attrvalue) )
			{
				return;
			}
		}
		node = node.nextSibling();
	}
	elem.clear();
	return;
}

/***********************选择文件****************************/
void Widget::on_PB_selectfile_clicked()
{
	QString filedir = QFileDialog::getSaveFileName(this,tr("保存对话框"),"",tr("文本文件(*txt)"));
	if(filedir.isEmpty())
	{
		return;
	}
	filedir.remove(".txt");
	filename = filedir.split('/').last();
	filetxtdir = filedir + ".txt";
	filecfgdir = filedir + ".cfg";
	ui->LE_filedir->setText(filetxtdir);
}

/***********************导出文件****************************/
void Widget::on_PB_out_clicked()
{
	QString fileDir = ui->LE_filedir->text();
	if(fileDir.isEmpty())
	{
		QMessageBox::warning(this,tr("警告对话框"),tr("请先选择文件   "));
		return;
	}
	QString err =createxml();
	if(err.contains("出错"))
	{
		QMessageBox::warning(this,tr("警告对话框"),err+"   ");
		return;
	}
	QFile filetxt(filetxtdir);
	if(!filetxt.open(QIODevice::WriteOnly|QIODevice::Text))
	{
		QMessageBox::warning(this,tr("警告对话框"),tr("txt文件打开失败    "));
		return;
	}
	QTextStream outtxt(&filetxt);
	outtxt.setCodec("GB18030");
	outtxt << createtxt() ;
	filetxt.close();

	QFile filecfg(filecfgdir);
	if(!filecfg.open(QIODevice::WriteOnly|QIODevice::Text))
	{
		QMessageBox::warning(this,tr("警告对话框"),tr("cfg文件打开失败    "));
		return;
	}
	QTextStream outcfg(&filecfg);
	outcfg.setCodec("GB18030");
	outcfg << createcfg() ;
	filecfg.close();

	QMessageBox::information(this,tr("提示对话框"),tr("已完成       "));
}
