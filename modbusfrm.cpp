#include "modbusfrm.h"
#include "ui_modbusfrm.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextStream>
#include "globalfunc.h"
#include <QtXml>



ModbusFrm::ModbusFrm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ModbusFrm)
{
	ui->setupUi(this);
	initconfig();
}

ModbusFrm::~ModbusFrm()
{
	delete ui;
}
void ModbusFrm::initconfig()
{
	ui->treeWidget->setStyle(QStyleFactory::create("windows"));			//子项目带虚线
	ui->treeWidget->setSortingEnabled(true);
	ui->treeWidget->header()->setSortIndicatorShown(true);
	ui->treeWidget->header()->setSortIndicator(0, Qt::AscendingOrder);	//这三句改变排序
	ui->treeWidget->header()->setSectionsClickable(false);				//禁止点击排序
	ui->stackconfig->setCurrentIndex(ui->stackconfig->count()-1);		//默认显示最后一个widget

	connect(ui->treeWidget,SIGNAL(customContextMenuRequested(const QPoint&)), this,SLOT(popMenu(const QPoint&)));//检测鼠标右键
	connect(ui->act1, SIGNAL(triggered()), this, SLOT(createItem()));
	connect(ui->act2, SIGNAL(triggered()),	this,SLOT(deleteItem()));
	connect(ui->act3, SIGNAL(triggered()),	this,SLOT(renameItem()));

	QTreeWidgetItem *tmp;
	tmp = new QTreeWidgetItem(ui->treeWidget,QStringList() << "00.基本配置" , BASE);
	tmp->setData(0,Qt::UserRole+1,QVariant::fromValue(defaultdata));
	tmp = new QTreeWidgetItem(ui->treeWidget,QStringList() << "01.遥测" , YC);
	tmp->setData(0,Qt::UserRole+1,QVariant::fromValue(defaultdata));
	tmp = new QTreeWidgetItem(ui->treeWidget,QStringList() << "02.遥信" , YX);
	tmp->setData(0,Qt::UserRole+1,QVariant::fromValue(defaultdata));
	tmp = new QTreeWidgetItem(ui->treeWidget,QStringList() << "03.遥脉" , YM);
	tmp->setData(0,Qt::UserRole+1,QVariant::fromValue(defaultdata));
	tmp = new QTreeWidgetItem(ui->treeWidget,QStringList() << "04.遥控" , YK);
	tmp->setData(0,Qt::UserRole+1,QVariant::fromValue(defaultdata));
	tmp = new QTreeWidgetItem(ui->treeWidget,QStringList() << "05.遥调" , YT);
	tmp->setData(0,Qt::UserRole+1,QVariant::fromValue(defaultdata));

}



void ModbusFrm::groupscla()
{
	QTreeWidgetItem *baseItem = NULL;

	int max = 0;
	for(int i = 0;i <ui->treeWidget->topLevelItemCount();i++)
	{
		if(ui->treeWidget->topLevelItem(i)->type() == YC||
		   ui->treeWidget->topLevelItem(i)->type() == YX||
		   ui->treeWidget->topLevelItem(i)->type() == YM)
		{
			max = ui->treeWidget->topLevelItem(i)->childCount() > max ? ui->treeWidget->topLevelItem(i)->childCount():max;
		}
		if(ui->treeWidget->topLevelItem(i)->type() == BASE)
		{
			baseItem = ui->treeWidget->topLevelItem(i);
		}
	}
	if(baseItem==NULL)
		return ;
	modbusItemData itemdata = baseItem->data(0,Qt::UserRole+1).value<modbusItemData>();
	itemdata.groupnum = max;
	baseItem->setData(0,Qt::UserRole+1,QVariant::fromValue(itemdata));

}

QString ModbusFrm::checkerror()
{
	QTreeWidgetItem* curItem=ui->treeWidget->currentItem();  //获取当前被点击的节点
	saveItem(curItem);
	QString text;
	for(int i = 0;i <ui->treeWidget->topLevelItemCount();i++)
	{
		QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
		modbusItemData itemdata = item->data(0,Qt::UserRole+1).value<modbusItemData>();
		switch (item->type())
		{
		case BASE:
			if(itemdata.groupnum == 0)
			{
				text.append("出错，遥测、遥信、遥脉均无数据");
				return text;
			}
			break;
		case YC:
		case YX:
		case YM:
		case YK:
		case YT:
			for (int i = 0;i <item->childCount();i++)
			{
				QTreeWidgetItem *childitem = item->child(i);
				modbusItemData childitemdata = childitem->data(0,Qt::UserRole+1).value<modbusItemData>();
				if(childitemdata.textlst.isEmpty())
				{
					text.append("出错，"+item->text(0)+childitem->text(0)+"描述为空");
					return text;
				}
			}
			break;
		default:
			break;
		}
	}
	return text;
}

//QString ModbusFrm::groupsort()
//{
//	modbusItemData itemdata = ui->treeWidget->topLevelItem(0)->data(0,Qt::UserRole+1).value<modbusItemData>();
//	int groupnum = itemdata.groupnum;
//	QString sort = QString("%1").arg(QString::number(0),groupnum*3,QLatin1Char('0'));
//	for (int i =0;i <3;i++)
//	{
//		int tmp = ui->treeWidget->topLevelItem(i+1)->childCount();
//		for (int j = 0;j <tmp;j++)
//		{
//			sort.replace(j*3+i,1,QString::number(i+1)[0]);
//		}

//	}
//	sort.remove("0");
//	return sort;

//}

void ModbusFrm::groupucharsort()
{
	memset(groupuchar,0,sizeof (groupuchar));
	int groupnum = ui->treeWidget->topLevelItem(0)->data(0,Qt::UserRole+1).value<modbusItemData>().groupnum;
	for (int i =0;i <3;i++)
	{
		int tmp = ui->treeWidget->topLevelItem(i+1)->childCount();
		int value = 0;
		for (int j = 0;j <tmp;j++)
		{
			for (int k =0;k <j*3+i;k++)
			{
				value = groupuchar[k]>value ? groupuchar[k]:value;
			}
			groupuchar[j*3+i] =value+1;
			for (int k =j*3+i+1;k<groupnum*3;k++)
			{
				if(groupuchar[k]>0)
				{
					groupuchar[k]++;
				}
			}
		}
	}
//	for (int i = 0;i<groupnum*3;i += 3) {
//		qDebug() << groupuchar[i] << groupuchar[i+1]<<groupuchar[i+2];
//	}

}



void ModbusFrm::popMenu(const QPoint &)
{
	QMenu menu(ui->treeWidget);
	QTreeWidgetItem* curItem=ui->treeWidget->currentItem();  //获取当前被点击的节点
	if(curItem==NULL)
		return;
	if(curItem->type() >= YCITEM && curItem->type() <= YTITEM)
	{
		menu.addAction(ui->act3);
		menu.addAction(ui->act2);
		menu.exec(QCursor::pos());  //在当前鼠标位置显示
	}
	else if(curItem->type() >= YC && curItem->type() <= YT)
	{

		menu.addAction(ui->act1);
		menu.exec(QCursor::pos());  //在当前鼠标位置显示
	}
}

void ModbusFrm::createItem()
{

	QTreeWidgetItem* curItem=ui->treeWidget->currentItem();  //获取当前被点击的节点
	if(curItem==NULL)
		return;

	uint tmp = 1;
	if(curItem->childCount() > 0 && curItem->child(0)->text(0).toUInt() < 2)
	{
		tmp = curItem->child(curItem->childCount()-1)->text(0).toUInt() + 1;
		for (int i = 1;i < curItem->childCount();i++)
		{
			if(curItem->child(i)->text(0).toUInt() - curItem->child(i-1)->text(0).toUInt() != 1)
			{
				tmp = curItem->child(i-1)->text(0).toUInt() + 1;
				break;
			}
		}
	}

	QString strtmp = QString("%1").arg(QString::number(tmp),2,QLatin1Char('0'));

	QTreeWidgetItem *tmpItem = new QTreeWidgetItem(curItem,QStringList() << strtmp,curItem->type()+5);//此处5是组与条目类型的差
	tmpItem->setData(0,Qt::UserRole+1,QVariant::fromValue(defaultdata));

	curItem->setExpanded(true);
	refreshItem(curItem);
//	on_treeWidget_itemSelectionChanged();
}

void ModbusFrm::deleteItem()
{
	QTreeWidgetItem* curItem=ui->treeWidget->currentItem();  //获取当前被点击的节点
	if(curItem==NULL)
		return;
	QTreeWidgetItem *parent = curItem->parent();
	if(parent==NULL)
		return;

	parent->removeChild(curItem);
	curItem=ui->treeWidget->currentItem();
	refreshItem(curItem);

//	on_treeWidget_itemSelectionChanged();
}

void ModbusFrm::renameItem()
{
	bool ok;
	QString newname = QInputDialog::getText(this, tr("输入对话框"),
											tr("新命名:"), QLineEdit::Normal,
											tr(""), &ok);
	if (ok && !newname.isEmpty())
	{
		QTreeWidgetItem* curItem=ui->treeWidget->currentItem();  //获取当前被点击的节点
		if(curItem==NULL)
			return;
		QTreeWidgetItem *parent = curItem->parent();
		if(parent==NULL)
			return;
		for (int i = 0;i < parent->childCount();i++)
		{
			if(parent->child(i)->text(0) == newname)
			{
				QMessageBox::warning(this,tr("告警对话框"),tr("已存在此命名！"),QMessageBox::Ok);
				return;
			}
		}

		curItem->setText(0,newname);
		refreshItem(curItem);
//		on_treeWidget_itemSelectionChanged();
	}
}

//void ModbusFrm::on_treeWidget_itemSelectionChanged()
//{
//	QTreeWidgetItem* curItem=ui->treeWidget->currentItem();  //获取当前被点击的节点

//}


//void ModbusFrm::on_PBsave_clicked()
//{
//	QTreeWidgetItem* curItem=ui->treeWidget->currentItem();  //获取当前被点击的节点
//	saveItem(curItem);
//}

void ModbusFrm::saveItem(QTreeWidgetItem *item)
{
	if(item==NULL)
		return;
	modbusItemData itemdata = item->data(0,Qt::UserRole+1).value<modbusItemData>();
	switch (item->type())
	{
	case YCITEM:
		itemdata.textlst = mStrToList(ui->TEyc->toPlainText().trimmed());
		itemdata.ycnum = ui->LEyc1->text().toUShort(0,ui->CByc1->isChecked()?16:10);
		itemdata.yctype = ui->LEyc2->text().toUShort(0,ui->CByc2->isChecked()?16:10);
		itemdata.yccode = ui->LEyc3->text().toUShort(0,ui->CByc3->isChecked()?16:10);
		itemdata.ycaddr = ui->LEyc4->text().toUShort(0,ui->CByc4->isChecked()?16:10);
		ui->Labelycnum->setText(QString::number(itemdata.textlst.length()));
		break;
	case YXITEM:
		itemdata.textlst = mStrToList(ui->TEyx->toPlainText().trimmed());
		itemdata.yxnum = ui->LEyx1->text().toUShort(0,ui->CByx1->isChecked()?16:10);
		itemdata.yxtype = ui->LEyx2->text().toUShort(0,ui->CByx2->isChecked()?16:10);
		itemdata.yxcode = ui->LEyx3->text().toUShort(0,ui->CByx3->isChecked()?16:10);
		itemdata.yxaddr = ui->LEyx4->text().toUShort(0,ui->CByx4->isChecked()?16:10);
		ui->Labelyxnum->setText(QString::number(itemdata.textlst.length()));
		break;
	case YMITEM:
		itemdata.textlst = mStrToList(ui->TEym->toPlainText().trimmed());
		itemdata.ymnum = ui->LEym1->text().toUShort(0,ui->CBym1->isChecked()?16:10);
		itemdata.ymcode = ui->LEym2->text().toUShort(0,ui->CBym2->isChecked()?16:10);
		itemdata.ymaddr = ui->LEym3->text().toUShort(0,ui->CBym3->isChecked()?16:10);
		ui->Labelymnum->setText(QString::number(itemdata.textlst.length()));
		break;
	case YKITEM:
		itemdata.textlst = mStrToList(ui->TEyk->toPlainText().trimmed(),1);
		itemdata.ykcloseaddrsel = ui->LEyk1->text().toUShort(0,ui->CByk1->isChecked()?16:10);
		itemdata.ykcloseaddr = ui->LEyk2->text().toUShort(0,ui->CByk2->isChecked()?16:10);
		itemdata.ykopenaddrsel = ui->LEyk3->text().toUShort(0,ui->CByk3->isChecked()?16:10);
		itemdata.ykopenaddr = ui->LEyk4->text().toUShort(0,ui->CByk4->isChecked()?16:10);
		ui->Labelyknum->setText(QString::number(itemdata.textlst.length()));
		break;
	case YTITEM:
		itemdata.textlst = mStrToList(ui->TEyt->toPlainText().trimmed(),1);
		itemdata.ytaddr = ui->LEyt1->text().toUShort(0,ui->CByt1->isChecked()?16:10);
		ui->Labelytnum->setText(QString::number(itemdata.textlst.length()));
		break;
	case BASE:
		itemdata.ymseq = ui->LE6->text().toUShort(0,ui->CB6->isChecked()?16:10);
		itemdata.ymbcd = ui->LE7->text().toUShort(0,ui->CB7->isChecked()?16:10);
		itemdata.datalen = ui->LE8->text().toUShort(0,ui->CB8->isChecked()?16:10);
		break;
	case YC:
		break;
	case YX:
		break;
	case YM:
		break;
	case YK:
		itemdata.ykcode = ui->LE1->text().toUShort(0,ui->CB1->isChecked()?16:10);
		itemdata.ykselect = ui->LE2->text().toUShort(0,ui->CB2->isChecked()?16:10);
		itemdata.ykclose = ui->LE3->text().toUShort(0,ui->CB3->isChecked()?16:10);
		itemdata.ykopen = ui->LE4->text().toUShort(0,ui->CB4->isChecked()?16:10);
		itemdata.textlst = mStrToList(ui->TEyks->toPlainText().trimmed());
		if(itemdata.textlst.isEmpty())
		{
			break;
		}
		if(item->childCount() > 0)
		{
			itemdata.textlst.clear();
			QMessageBox::warning(this,tr("警告对话框"),tr("遥控组下的遥控点先删除    "));
			break;
		}
		for (int i = 0;i < itemdata.textlst.length();i++)
		{
			QString strtmp = QString("%1").arg(QString::number(i+1),2,QLatin1Char('0'));
			QTreeWidgetItem* newItem = new QTreeWidgetItem(item,QStringList() << strtmp,YKITEM);
			modbusItemData itemdatatmp = defaultdata;
			itemdatatmp.textlst << itemdata.textlst.at(i);
			newItem->setData(0,Qt::UserRole+1,QVariant::fromValue(itemdatatmp));
		}
		itemdata.textlst.clear();
		item->setExpanded(true);

		break;
	case YT:
		itemdata.ytcode = ui->LE5->text().toUShort(0,ui->CB5->isChecked()?16:10);
		itemdata.textlst = mStrToList(ui->TEyts->toPlainText().trimmed());
		if(itemdata.textlst.isEmpty())
		{
			break;
		}
		if(item->childCount() > 0)
		{
			itemdata.textlst.clear();
			QMessageBox::warning(this,tr("警告对话框"),tr("遥调组下的遥调点先删除    "));
			break;
		}
		for (int i = 0;i < itemdata.textlst.length();i++)
		{
			QString strtmp = QString("%1").arg(QString::number(i+1),2,QLatin1Char('0'));
			QTreeWidgetItem* newItem = new QTreeWidgetItem(item,QStringList() << strtmp,YTITEM);
			modbusItemData itemdatatmp = defaultdata;
			itemdatatmp.textlst << itemdata.textlst.at(i);
			newItem->setData(0,Qt::UserRole+1,QVariant::fromValue(itemdatatmp));
		}
		itemdata.textlst.clear();
		item->setExpanded(true);
		break;
	default:
		break;
	}
	item->setData(0,Qt::UserRole+1,QVariant::fromValue(itemdata));
	refreshItem(item);
}

void ModbusFrm::refreshItem(QTreeWidgetItem *item)
{
	if(item==NULL)
		return;
	modbusItemData itemdata = item->data(0,Qt::UserRole+1).value<modbusItemData>();
	QString text;
	foreach(QString tmp,itemdata.textlst)
	{
		text.append(tmp + "\n");
	}
	switch (item->type())
	{
	case YCITEM:
		ui->stackconfig->setCurrentIndex(1);
		ui->TEyc->setPlainText(text);
		ui->Labelyc->setText(item->text(0));
		ui->Labelycnum->setText(QString::number(itemdata.textlst.length()));
		ui->LEyc1->setText(QString::number(itemdata.ycnum,ui->CByc1->isChecked()?16:10));
		ui->LEyc2->setText(QString::number(itemdata.yctype,ui->CByc2->isChecked()?16:10));
		ui->LEyc3->setText(QString::number(itemdata.yccode,ui->CByc3->isChecked()?16:10));
		ui->LEyc4->setText(QString::number(itemdata.ycaddr,ui->CByc4->isChecked()?16:10));
		break;
	case YXITEM:
		ui->stackconfig->setCurrentIndex(2);
		ui->TEyx->setPlainText(text);
		ui->Labelyx->setText(item->text(0));
		ui->Labelyxnum->setText(QString::number(itemdata.textlst.length()));
		ui->LEyx1->setText(QString::number(itemdata.yxnum,ui->CByx1->isChecked()?16:10));
		ui->LEyx2->setText(QString::number(itemdata.yxtype,ui->CByx2->isChecked()?16:10));
		ui->LEyx3->setText(QString::number(itemdata.yxcode,ui->CByx3->isChecked()?16:10));
		ui->LEyx4->setText(QString::number(itemdata.yxaddr,ui->CByx4->isChecked()?16:10));
		break;
	case YMITEM:
		ui->stackconfig->setCurrentIndex(3);
		ui->TEym->setPlainText(text);
		ui->Labelym->setText(item->text(0));
		ui->Labelymnum->setText(QString::number(itemdata.textlst.length()));
		ui->LEym1->setText(QString::number(itemdata.ymnum,ui->CBym1->isChecked()?16:10));
		ui->LEym2->setText(QString::number(itemdata.ymcode,ui->CBym2->isChecked()?16:10));
		ui->LEym3->setText(QString::number(itemdata.ymaddr,ui->CBym3->isChecked()?16:10));
		break;
	case YKITEM:
		ui->stackconfig->setCurrentIndex(4);
		ui->TEyk->setPlainText(text);
		ui->Labelyk->setText(item->text(0));
		ui->Labelyknum->setText(QString::number(itemdata.textlst.length()));
		ui->LEyk1->setText(QString::number(itemdata.ykcloseaddrsel,ui->CByk1->isChecked()?16:10));
		ui->LEyk2->setText(QString::number(itemdata.ykcloseaddr,ui->CByk2->isChecked()?16:10));
		ui->LEyk3->setText(QString::number(itemdata.ykopenaddrsel,ui->CByk3->isChecked()?16:10));
		ui->LEyk4->setText(QString::number(itemdata.ykopenaddr,ui->CByk4->isChecked()?16:10));
		break;
	case YTITEM:
		ui->stackconfig->setCurrentIndex(5);
		ui->TEyt->setPlainText(text);
		ui->Labelyt->setText(item->text(0));
		ui->Labelytnum->setText(QString::number(itemdata.textlst.length()));
		ui->LEyt1->setText(QString::number(itemdata.ytaddr,ui->CByt1->isChecked()?16:10));
		break;
	case BASE:
		ui->stackconfig->setCurrentIndex(0);

		ui->LE6->setText(QString::number(itemdata.ymseq,ui->CB6->isChecked()?16:10));
		ui->LE7->setText(QString::number(itemdata.ymbcd,ui->CB7->isChecked()?16:10));
		ui->LE8->setText(QString::number(itemdata.datalen,ui->CB8->isChecked()?16:10));
		break;
	case YC:
		ui->stackconfig->setCurrentIndex(ui->stackconfig->count()-1);
		break;
	case YX:
		ui->stackconfig->setCurrentIndex(ui->stackconfig->count()-1);
		break;
	case YM:
		ui->stackconfig->setCurrentIndex(ui->stackconfig->count()-1);
		break;
	case YK:
		ui->stackconfig->setCurrentIndex(6);
//		ui->Labelyksnum->setText(QString::number(itemdata.textlst.length()));
		ui->TEyks->setPlainText(text);
		ui->LE1->setText(QString::number(itemdata.ykcode,ui->CB1->isChecked()?16:10));
		ui->LE2->setText(QString::number(itemdata.ykselect,ui->CB2->isChecked()?16:10));
		ui->LE3->setText(QString::number(itemdata.ykclose,ui->CB3->isChecked()?16:10));
		ui->LE4->setText(QString::number(itemdata.ykopen,ui->CB4->isChecked()?16:10));
		break;
	case YT:
		ui->stackconfig->setCurrentIndex(7);
//		ui->Labelytsnum->setText(QString::number(itemdata.textlst.length()));
		ui->TEyts->setPlainText(text);
		ui->LE5->setText(QString::number(itemdata.ytcode,ui->CB5->isChecked()?16:10));
		break;
	default:
		ui->stackconfig->setCurrentIndex(ui->stackconfig->count()-1);
		break;
	}
	groupscla();
}

void ModbusFrm::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
	saveItem(previous);
	refreshItem(current);
}
/***********************基本配置****************************/

void ModbusFrm::on_CB6_stateChanged(int arg1)
{
	ushort ss = ui->LE6->text().toUShort(0,arg1?10:16);
	ui->LE6->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CB7_stateChanged(int arg1)
{
	ushort ss = ui->LE7->text().toUShort(0,arg1?10:16);
	ui->LE7->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CB8_stateChanged(int arg1)
{
	ushort ss = ui->LE8->text().toUShort(0,arg1?10:16);
	ui->LE8->setText(QString::number(ss,arg1?16:10));
}

/***********************遥测****************************/

void ModbusFrm::on_CByc1_stateChanged(int arg1)
{
	ushort ss = ui->LEyc1->text().toUShort(0,arg1?10:16);
	ui->LEyc1->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CByc2_stateChanged(int arg1)
{
	ushort ss = ui->LEyc2->text().toUShort(0,arg1?10:16);
	ui->LEyc2->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CByc3_stateChanged(int arg1)
{
	ushort ss = ui->LEyc3->text().toUShort(0,arg1?10:16);
	ui->LEyc3->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CByc4_stateChanged(int arg1)
{
	ushort ss = ui->LEyc4->text().toUShort(0,arg1?10:16);
	ui->LEyc4->setText(QString::number(ss,arg1?16:10));
}

/***********************遥信****************************/

void ModbusFrm::on_CByx1_stateChanged(int arg1)
{
	ushort ss = ui->LEyx1->text().toUShort(0,arg1?10:16);
	ui->LEyx1->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CByx2_stateChanged(int arg1)
{
	ushort ss = ui->LEyx2->text().toUShort(0,arg1?10:16);
	ui->LEyx2->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CByx3_stateChanged(int arg1)
{
	ushort ss = ui->LEyx3->text().toUShort(0,arg1?10:16);
	ui->LEyx3->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CByx4_stateChanged(int arg1)
{
	ushort ss = ui->LEyx4->text().toUShort(0,arg1?10:16);
	ui->LEyx4->setText(QString::number(ss,arg1?16:10));
}

/***********************遥脉****************************/

void ModbusFrm::on_CBym1_stateChanged(int arg1)
{
	ushort ss = ui->LEym1->text().toUShort(0,arg1?10:16);
	ui->LEym1->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CBym2_stateChanged(int arg1)
{
	ushort ss = ui->LEym2->text().toUShort(0,arg1?10:16);
	ui->LEym2->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CBym3_stateChanged(int arg1)
{
	ushort ss = ui->LEym3->text().toUShort(0,arg1?10:16);
	ui->LEym3->setText(QString::number(ss,arg1?16:10));
}

/***********************遥控****************************/
void ModbusFrm::on_CB1_stateChanged(int arg1)
{
	ushort ss = ui->LE1->text().toUShort(0,arg1?10:16);
	ui->LE1->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CB2_stateChanged(int arg1)
{
	ushort ss = ui->LE2->text().toUShort(0,arg1?10:16);
	ui->LE2->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CB3_stateChanged(int arg1)
{
	ushort ss = ui->LE3->text().toUShort(0,arg1?10:16);
	ui->LE3->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CB4_stateChanged(int arg1)
{
	ushort ss = ui->LE4->text().toUShort(0,arg1?10:16);
	ui->LE4->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CByk1_stateChanged(int arg1)
{
	ushort ss = ui->LEyk1->text().toUShort(0,arg1?10:16);
	ui->LEyk1->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CByk2_stateChanged(int arg1)
{
	ushort ss = ui->LEyk2->text().toUShort(0,arg1?10:16);
	ui->LEyk2->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CByk3_stateChanged(int arg1)
{
	ushort ss = ui->LEyk3->text().toUShort(0,arg1?10:16);
	ui->LEyk3->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CByk4_stateChanged(int arg1)
{
	ushort ss = ui->LEyk4->text().toUShort(0,arg1?10:16);
	ui->LEyk4->setText(QString::number(ss,arg1?16:10));
}

/***********************遥调****************************/
void ModbusFrm::on_CB5_stateChanged(int arg1)
{
	ushort ss = ui->LE5->text().toUShort(0,arg1?10:16);
	ui->LE5->setText(QString::number(ss,arg1?16:10));
}

void ModbusFrm::on_CByt1_stateChanged(int arg1)
{
	ushort ss = ui->LEyt1->text().toUShort(0,arg1?10:16);
	ui->LEyt1->setText(QString::number(ss,arg1?16:10));
}

/***********************键盘回车事件****************************/
//void ModbusFrm::keyPressEvent(QKeyEvent *event)
//{

//	if ( event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
//	{
//		on_PBsave_clicked();
//	}
//}

void ModbusFrm::writeXml()
{

	QFile file("modbus.xml");
	if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
	{
		return;
	}
	groupucharsort();
//	QString sort = groupsort();
	QDomDocument doc;
	QDomProcessingInstruction instruction;
	instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\"");
	doc.appendChild(instruction);

	QDomElement root = doc.createElement("modbus");
	doc.appendChild(root);
	QDomElement group;
	QDomElement setting;
	QDomElement info;
	QDomText text;
	for(int i = 0;i <ui->treeWidget->topLevelItemCount();i++)
	{
		QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
		modbusItemData itemdata = item->data(0,Qt::UserRole+1).value<modbusItemData>();
		int index = 0;
		switch (item->type())
		{
		case BASE:
			group = doc.createElement("基本配置");
			root.appendChild(group);
			setting = doc.createElement("选项");
			group.appendChild(setting);
			setting.setAttribute("召唤分组数",itemdata.groupnum);
			setting.setAttribute("遥脉低字节寄存器在前",itemdata.ymseq);
			setting.setAttribute("遥脉BCD码格式",itemdata.ymbcd);
			setting.setAttribute("从机应答报文读取数据长度字节个数",itemdata.datalen);
			break;
		case YC:
			for (int i = 0;i <item->childCount();i++)
			{
				QTreeWidgetItem *childitem = item->child(i);
				modbusItemData childitemdata = childitem->data(0,Qt::UserRole+1).value<modbusItemData>();
				group = doc.createElement("遥测");
				root.appendChild(group);
				index = groupuchar[i*3];//sort.indexOf('1',index)+1;
				group.setAttribute("index",index);
				setting = doc.createElement("选项");
				group.appendChild(setting);
				setting.setAttribute("遥测寄存器个数",childitemdata.ycnum);
				setting.setAttribute("遥测四字节",childitemdata.yctype);
				setting.setAttribute("遥测功能码",childitemdata.yccode);
				setting.setAttribute("遥测起始地址",childitemdata.ycaddr);
				for (int i=0;i<childitemdata.textlst.length();i++)
				{
					info = doc.createElement("描述");
					group.appendChild(info);
					info.setAttribute("no",i+1);
					info.setAttribute("text",childitemdata.textlst.at(i));
				}
			}
			break;
		case YX:
			for (int i = 0;i <item->childCount();i++)
			{
				QTreeWidgetItem *childitem = item->child(i);
				modbusItemData childitemdata = childitem->data(0,Qt::UserRole+1).value<modbusItemData>();
				group = doc.createElement("遥信");
				root.appendChild(group);
				index = groupuchar[i*3+1];//sort.indexOf('2',index)+1;
				group.setAttribute("index",index);
				setting = doc.createElement("选项");
				group.appendChild(setting);
				setting.setAttribute("遥信寄存器个数",childitemdata.yxnum);
				setting.setAttribute("遥信寄存器BIT长度",childitemdata.yxtype);
				setting.setAttribute("遥信功能码",childitemdata.yxcode);
				setting.setAttribute("遥信起始地址",childitemdata.yxaddr);
				for (int i=0;i<childitemdata.textlst.length();i++)
				{
					info = doc.createElement("描述");
					group.appendChild(info);
					info.setAttribute("no",i+1);
					info.setAttribute("text",childitemdata.textlst.at(i));
				}
			}
			break;
		case YM:
			for (int i = 0;i <item->childCount();i++)
			{
				QTreeWidgetItem *childitem = item->child(i);
				modbusItemData childitemdata = childitem->data(0,Qt::UserRole+1).value<modbusItemData>();
				group = doc.createElement("遥脉");
				root.appendChild(group);
				index = groupuchar[i*3+2];//sort.indexOf('3',index)+1;
				group.setAttribute("index",index);
				setting = doc.createElement("选项");
				group.appendChild(setting);
				setting.setAttribute("遥脉寄存器个数",childitemdata.ymnum);
				setting.setAttribute("遥脉功能码",childitemdata.ymcode);
				setting.setAttribute("遥脉起始地址",childitemdata.ymaddr);
				for (int i=0;i<childitemdata.textlst.length();i++)
				{
					info = doc.createElement("描述");
					group.appendChild(info);
					info.setAttribute("no",i+1);
					info.setAttribute("text",childitemdata.textlst.at(i));
				}
			}
			break;
		case YK:
			group = doc.createElement("遥控");
			root.appendChild(group);
			group.setAttribute("index",60);
			setting = doc.createElement("选项");
			group.appendChild(setting);
			setting.setAttribute("遥控功能码",itemdata.ykcode);
			setting.setAttribute("遥控预置",itemdata.ykselect);
			setting.setAttribute("控合命令字",itemdata.ykclose);
			setting.setAttribute("控分命令字",itemdata.ykopen);
			for (int i = 0;i <item->childCount();i++)
			{
				QTreeWidgetItem *childitem = item->child(i);
				modbusItemData childitemdata = childitem->data(0,Qt::UserRole+1).value<modbusItemData>();
				info = doc.createElement("描述");
				group.appendChild(info);
				info.setAttribute("no",i+1);
				QString tmp = childitemdata.textlst.at(0);
				info.setAttribute("text",childitemdata.textlst.at(0));
				info.setAttribute("控合预置地址",childitemdata.ykcloseaddrsel);
				info.setAttribute("控合地址",childitemdata.ykcloseaddr);
				info.setAttribute("控分预置地址",childitemdata.ykopenaddrsel);
				info.setAttribute("控分地址",childitemdata.ykopenaddr);
			}
			break;
		case YT:
			group = doc.createElement("遥调");
			root.appendChild(group);
			group.setAttribute("index",70);
			setting = doc.createElement("选项");
			group.appendChild(setting);
			setting.setAttribute("遥调功能码",itemdata.ytcode);
			for (int i = 0;i <item->childCount();i++)
			{
				QTreeWidgetItem *childitem = item->child(i);
				modbusItemData childitemdata = childitem->data(0,Qt::UserRole+1).value<modbusItemData>();
				info = doc.createElement("描述");
				group.appendChild(info);
				info.setAttribute("no",i+1);
				info.setAttribute("text",childitemdata.textlst.at(0));
				info.setAttribute("设置地址",childitemdata.ytaddr);
			}
			break;
		default:
			break;
		}
	}

	QTextStream out(&file);
	out.setCodec("UTF-8");
	doc.save(out,4);
	file.close();
}



