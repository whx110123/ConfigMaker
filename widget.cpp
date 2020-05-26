#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QtXml>
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

QString Widget::createmodbustxt(QString filename)
{

		QFile file("modbus.xml");
		if(!file.open(QIODevice::ReadOnly))
		{
			QMessageBox::warning(NULL,"告警窗","文件不存在");
//			return;
		}

		QDomDocument doc;
		if(!doc.setContent(&file))
		{
			file.close();
//			return;
		}
		file.close();
		QDomNode fristnode = doc.firstChild();
		qDebug()<<fristnode.nodeName() << fristnode.nodeValue();





}
QString Widget::createtxt()
{
	QString text;

//	text.append("[名称]\n");
//	text.append(filename + "\n");
//	text.append("\n[类型]\n");
//	text.append("保护测控\n");

//	int groupNo = 0;
//	QMap<QString, ycconfig>::const_iterator ycNo = ycmap.constBegin();
//	QMap<QString, yxconfig>::const_iterator yxNo = yxmap.constBegin();
//	QMap<QString, ymconfig>::const_iterator ymNo = ymmap.constBegin();

//	int groupnum = groupsort();
//	for (int i = 0;i<groupnum*3;i++)
//	{
//		switch (grouptype[i])
//		{
//		case 1:
//			groupNo++;
//			text.append("\n[遥测]\n");
//			for (int i = 0;i < ycNo.value().textlst.length();i++)
//			{
//				text.append(QString::number(i+1)+","+QString::number(groupNo)+ "," +QString::number(i+1)+"," + ycNo.value().textlst.at(i)+",,5,,\n");
//			}
//			ycNo++;
//			break;
//		case 2:
//			groupNo++;
//			text.append("\n[遥信]\n");
//			for (int i = 0;i < yxNo.value().textlst.length();i++)
//			{
//				text.append(QString::number(i+1)+","+QString::number(groupNo)+ "," +QString::number(i+1)+"," + yxNo.value().textlst.at(i)+",,5,,\n");
//			}
//			yxNo++;
//			break;
//		case 3:
//			groupNo++;
//			text.append("\n[遥脉]\n");
//			for (int i = 0;i < ymNo.value().textlst.length();i++)
//			{
//				text.append(QString::number(i+1)+","+QString::number(groupNo)+ "," +QString::number(i+1)+"," + ymNo.value().textlst.at(i)+",,5,,\n");
//			}
//			ymNo++;
//			break;
//		default:
//			break;
//		}
//	}
//	if(yknum >0)
//	{
//		text.append("\n[遥控]\n");
//		QMap<QString, ykconfig>::const_iterator ykNo = ykmap.constBegin();
//		int i = 0;
//		while (ykNo != ykmap.constEnd())
//		{
//			text.append(QString::number(i+1)+",60," +QString::number(i+1)+"," + ykNo.value().textlst.at(0)+",,5,,\n");
//			ykNo++;
//			i++;
//		}
//	}
//	if(ytnum >0)
//	{
//		text.append("\n[遥调]\n");
//		QMap<QString, ytconfig>::const_iterator ytNo = ytmap.constBegin();
//		int i = 0;
//		while (ytNo != ytmap.constEnd())
//		{
//			text.append(QString::number(i+1)+",70," +QString::number(i+1)+"," + ytNo.value().textlst.at(0)+",,5,,\n");
//			ytNo++;
//			i++;
//		}
//	}
//	text.append("\n[特殊遥信]\n");
//	text.append("1,255,1,网络状态A,,5,通,断\n");
//	text.append("2,255,2,网络状态B,,5,通,断\n");
	return text;
}

QString Widget::createcfg()
{
	QString text;
//	text.append("[属性]\n");
//	text.append("名称=" +filename + "\n");
//	text.append("默认规约=modbus装置规约\n");
//	text.append("版本号=v1.00\n");
//	text.append("可变选项组数=1\n");
//	text.append("[数据分类]\n");
//	text.append("数目=19\n");
//	text.append("数据名称=遥测,遥信,遥脉,遥控,遥调,模拟量,动作元件,运行告警,装置自检,硬压板,软压板,故障信息,扰动数据说明,定值,定值区号,特殊遥信,保护测量,装置参数,档位\n");
//	text.append("遥测=YC\n");
//	text.append("遥信=YX\n");
//	text.append("遥脉=YM\n");
//	text.append("遥控=YK\n");
//	text.append("遥调=YT\n");
//	text.append("模拟量=YC\n");
//	text.append("动作元件=YX\n");
//	text.append("运行告警=YX\n");
//	text.append("装置自检=YX\n");
//	text.append("硬压板=YX\n");
//	text.append("软压板=YXYK\n");
//	text.append("故障信息=OTHER\n");
//	text.append("扰动数据说明=OTHER\n");
//	text.append("定值=OTHER\n");
//	text.append("定值区号=OTHER\n");
//	text.append("特殊遥信=YX\n");
//	text.append("保护测量=YC\n");
//	text.append("装置参数=OTHER\n");
//	text.append("档位=YP\n");
//	text.append("[相关信息]\n");
//	text.append("数目=0\n");
//	text.append("[可变选项1]\n");
//	text.append("名称=可变选项1\n");
//	text.append("维数=1\n");
//	int groups = groupsort();
//	int num = 4 + groups * 11;
//	if(yknum)
//		num += 4+yknum*4;
//	if(ytnum)
//		num += 1+ytnum;
//	text.append("数目="+QString::number(num)+"\n");
//	int No = 1;
//	if(yknum)
//	{
//		text.append("选项"+QString::number(No++)+"=遥控功能码,INT,"+QString::number(base->ykcode)+"(0-65535)\n");
//		text.append("选项"+QString::number(No++)+"=遥控预置,INT,"+QString::number(base->ykselect)+"(0-65535)\n");
//		text.append("选项"+QString::number(No++)+"=控合命令字,INT,"+QString::number(base->ykclose)+"(0-65535)\n");
//		text.append("选项"+QString::number(No++)+"=控分命令字,INT,"+QString::number(base->ykopen)+"(0-65535)\n");
//		QMap<QString, ykconfig>::const_iterator ykNo = ykmap.constBegin();
//		int i = 0;
//		while (ykNo != ykmap.constEnd())
//		{
//			text.append("选项"+QString::number(No++)+"=遥控"+QString::number(i+1)+"控合预置地址,INT,"+QString::number(ykNo.value().ykcloseaddrsel)+"(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥控"+QString::number(i+1)+"控合地址,INT,"+QString::number(ykNo.value().ykcloseaddr)+"(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥控"+QString::number(i+1)+"控分预置地址,INT,"+QString::number(ykNo.value().ykopenaddrsel)+"(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥控"+QString::number(i+1)+"控分地址,INT,"+QString::number(ykNo.value().ykopenaddr)+"(0-65535)\n");
//			ykNo++;
//			i++;
//		}
//	}
//	if(ytnum)
//	{
//		text.append("选项"+QString::number(No++)+"=遥调功能码,INT,"+QString::number(base->ytcode)+"(0-65535)\n");
//		QMap<QString, ytconfig>::const_iterator ytNo = ytmap.constBegin();
//		int i = 0;
//		while (ytNo != ytmap.constEnd())
//		{
//			text.append("选项"+QString::number(No++)+"=遥调"+QString::number(i+1)+"设置地址,INT,"+QString::number(ytNo.value().ytaddr)+"(0-65535)\n");
//			ytNo++;
//			i++;
//		}
//	}
//	text.append("选项"+QString::number(No++)+"=召唤分组数,INT,"+QString::number(groups)+"(0-65535)\n");
//	int index = 0;
//	QMap<QString, ycconfig>::const_iterator ycNo = ycmap.constBegin();
//	QMap<QString, yxconfig>::const_iterator yxNo = yxmap.constBegin();
//	QMap<QString, ymconfig>::const_iterator ymNo = ymmap.constBegin();
//	while (index < groups * 3)
//	{
//		if(grouptype[index++])
//		{
//			text.append("选项"+QString::number(No++)+"=遥测寄存器个数,INT,"+QString::number(ycNo.value().ycnum)+"(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥测四字节,INT,"+QString::number(ycNo.value().yctype)+"(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥测功能码,INT,"+QString::number(ycNo.value().yccode)+"(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥测起始地址,INT,"+QString::number(ycNo.value().ycaddr)+"(0-65535)\n");
//			ycNo++;
//		}
//		else
//		{
//			text.append("选项"+QString::number(No++)+"=遥测寄存器个数,INT,0(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥测四字节,INT,0(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥测功能码,INT,0(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥测起始地址,INT,0(0-65535)\n");
//		}

//		if(grouptype[index++])
//		{
//			text.append("选项"+QString::number(No++)+"=遥信寄存器个数,INT,"+QString::number(yxNo.value().yxnum)+"(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥信寄存器BIT长度,INT,"+QString::number(yxNo.value().yxtype)+"(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥信功能码,INT,"+QString::number(yxNo.value().yxcode)+"(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥信起始地址,INT,"+QString::number(yxNo.value().yxaddr)+"(0-65535)\n");
//			yxNo++;
//		}
//		else
//		{
//			text.append("选项"+QString::number(No++)+"=遥信寄存器个数,INT,0(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥信寄存器BIT长度,INT,0(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥信功能码,INT,0(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥信起始地址,INT,0(0-65535)\n");
//		}

//		if(grouptype[index++])
//		{
//			text.append("选项"+QString::number(No++)+"=遥脉寄存器个数,INT,"+QString::number(ymNo.value().ymnum)+"(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥脉功能码,INT,"+QString::number(ymNo.value().ymcode)+"(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥脉起始地址,INT,"+QString::number(ymNo.value().ymaddr)+"(0-65535)\n");
//			ymNo++;
//		}
//		else
//		{
//			text.append("选项"+QString::number(No++)+"=遥脉寄存器个数,INT,0(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥脉功能码,INT,0(0-65535)\n");
//			text.append("选项"+QString::number(No++)+"=遥脉起始地址,INT,0(0-65535)\n");
//		}

//	}

//	text.append("选项"+QString::number(No++)+"=遥脉低字节寄存器在前,INT,"+QString::number(base->ymseq)+"(0-65535)\n");
//	text.append("选项"+QString::number(No++)+"=遥脉BCD码格式,INT,"+QString::number(base->ymbcd)+"(0-65535)\n");
//	text.append("选项"+QString::number(No++)+"=从机应答报文读取数据长度字节个数,INT,"+QString::number(base->datalen)+"(1-2)\n");


	return text;
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
//	mXmlToTxt("modbus");

	QString err = ui->modbuswdg->checkerror();
	if(err.contains("出错"))
	{
		QMessageBox::warning(this,tr("警告对话框"),err+"   ");
		return;
	}
	else
	{
		ui->modbuswdg->writeXml();
	}

	return;
	QString fileDir = ui->LE_filedir->text();
	if(fileDir.isEmpty())
	{
		QMessageBox::warning(this,tr("警告对话框"),tr("请先选择文件   "));
		return;
	}

	QFile filetxt(filetxtdir);
	if(!filetxt.open(QIODevice::WriteOnly|QIODevice::Text))
	{
		QMessageBox::warning(this,tr("警告对话框"),tr("文件打开失败    "));
		return;
	}
	QTextStream outtxt(&filetxt);
	outtxt.setCodec("GB18030");
//	QString text = createtxt();
//	outtxt << text ;
	filetxt.close();

	QFile filecfg(filecfgdir);
	if(!filecfg.open(QIODevice::WriteOnly|QIODevice::Text))
	{
		QMessageBox::warning(this,tr("警告对话框"),tr("文件打开失败    "));
		return;
	}
	QTextStream outcfg(&filecfg);
	outcfg.setCodec("GB18030");
//	text = createcfg();
//	outcfg << text ;
	filecfg.close();

	QMessageBox::information(this,tr("提示对话框"),tr("已完成       "));
}
