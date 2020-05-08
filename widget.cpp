#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::Widget)
{
	ui->setupUi(this);
	initconfig();
}

Widget::~Widget()
{
	delete ui;
	delete base;
}

void Widget::initconfig()
{
	ui->treeWidget->setStyle(QStyleFactory::create("windows"));
	ui->treeWidget->setSortingEnabled(true);
	ui->treeWidget->header()->setSortIndicatorShown(true);
	ui->treeWidget->header()->setSortIndicator(0, Qt::AscendingOrder);//这三句改变排序
	ui->stackconfig->setCurrentIndex(ui->stackconfig->count()-1);

	act1 = new QAction(tr("添加数据"),this);
	act2 = new QAction(tr("删除"),this);
	act3= new QAction(tr("重命名"),this);
	connect(act1, SIGNAL(triggered()), this, SLOT(createItem()));
	connect(act2, SIGNAL(triggered()),	this,SLOT(deleteItem()));
	connect(act3, SIGNAL(triggered()),	this,SLOT(renameItem()));
	connect(ui->treeWidget,SIGNAL(customContextMenuRequested(const QPoint&)), this,SLOT(popMenu(const QPoint&)));//检测鼠标右键
	ycnum = 0;
	yxnum = 0;
	ymnum = 0;
	yknum = 0;
	ytnum = 0;
	base = new baseconfig();
}

void Widget::popMenu(const QPoint &point)
{
	QMenu menu(ui->treeWidget);
	QTreeWidgetItem* curItem=ui->treeWidget->currentItem();  //获取当前被点击的节点
	if(curItem==NULL)
		return;
	if(curItem->flags() & Qt::ItemNeverHasChildren)
	{
		menu.addAction(act3);
		menu.addAction(act2);
		menu.exec(QCursor::pos());  //在当前鼠标位置显示
	}
	else
	{
		if(curItem->text(0).contains(tr("基本配置")))
		{
			return;
		}
		menu.addAction(act1);
		menu.exec(QCursor::pos());  //在当前鼠标位置显示
	}
}

void Widget::createItem()
{
	config *cfg;
	QTreeWidgetItem* curItem=ui->treeWidget->currentItem();  //获取当前被点击的节点
	if(curItem==NULL)
		return;
	int tmp = curItem->childCount()+1;
	for (int i = 1;i < curItem->childCount();i++)
	{
		if(curItem->child(i)->text(0).toUInt() - curItem->child(i-1)->text(0).toUInt() != 1)
		{
			tmp = curItem->child(i-1)->text(0).toUInt() + 1;
			break;
		}
	}
	if(curItem->childCount() > 0 && curItem->child(0)->text(0).toUInt() > 1)
	{
		tmp = 1;
	}
	QString strtmp = QString("%1").arg(QString::number(tmp),2,QLatin1Char('0'));
	if(curItem->text(0).contains(tr("遥测")))
	{
		++ycnum;
		cfg = new ycconfig;
		ycmap.insert(strtmp,*(ycconfig *)cfg);
		delete cfg;
	}
	else if(curItem->text(0).contains(tr("遥信")))
	{
		++yxnum;
		cfg = new yxconfig;
		yxmap.insert(strtmp,*(yxconfig *)cfg);
		delete cfg;
	}
	else if(curItem->text(0).contains(tr("遥脉")))
	{
		++ymnum;
		cfg = new ymconfig;
		ymmap.insert(strtmp,*(ymconfig *)cfg);
		delete cfg;
	}
	else if(curItem->text(0).contains(tr("遥控")))
	{
		++yknum;
		cfg = new ykconfig;
		ykmap.insert(strtmp,*(ykconfig *)cfg);
		delete cfg;
	}
	else if(curItem->text(0).contains(tr("遥调")))
	{
		++ytnum;
		cfg = new ytconfig;
		ytmap.insert(strtmp,*(ytconfig *)cfg);
		delete cfg;
	}
	QTreeWidgetItem* newItem = new QTreeWidgetItem(curItem,QStringList() << strtmp);
	newItem->setFlags(newItem->flags() | Qt::ItemNeverHasChildren);
	curItem->setExpanded(true);
	on_treeWidget_itemSelectionChanged();
}

void Widget::deleteItem()
{
	QTreeWidgetItem* curItem=ui->treeWidget->currentItem();  //获取当前被点击的节点
	if(curItem==NULL)
		return;
	QTreeWidgetItem *parent = curItem->parent();
	if(parent==NULL)
		return;
	if(parent->text(0).contains(tr("遥测")))
	{
		ycnum--;
		ycmap.erase(ycmap.find(curItem->text(0)));
	}
	else if(parent->text(0).contains(tr("遥信")))
	{
		yxnum--;
		yxmap.erase(yxmap.find(curItem->text(0)));
	}
	else if(parent->text(0).contains(tr("遥脉")))
	{
		ymnum--;
		ymmap.erase(ymmap.find(curItem->text(0)));
	}
	else if(parent->text(0).contains(tr("遥控")))
	{
		yknum--;
		ykmap.erase(ykmap.find(curItem->text(0)));
	}
	else if(parent->text(0).contains(tr("遥调")))
	{
		ytnum--;
		ytmap.erase(ytmap.find(curItem->text(0)));
	}

	parent->removeChild(curItem);
	on_treeWidget_itemSelectionChanged();
}

void Widget::renameItem()
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
		if(parent->text(0).contains(tr("遥测")))
		{
			ycmap.insert(newname,ycmap[curItem->text(0)]);
			ycmap.erase(ycmap.find(curItem->text(0)));			
		}
		else if(parent->text(0).contains(tr("遥信")))
		{
			yxmap.insert(newname,yxmap[curItem->text(0)]);
			yxmap.erase(yxmap.find(curItem->text(0)));
		}
		else if(parent->text(0).contains(tr("遥脉")))
		{
			ymmap.insert(newname,ymmap[curItem->text(0)]);
			ymmap.erase(ymmap.find(curItem->text(0)));
		}
		else if(parent->text(0).contains(tr("遥控")))
		{
			ykmap.insert(newname,ykmap[curItem->text(0)]);
			ykmap.erase(ykmap.find(curItem->text(0)));
		}
		else if(parent->text(0).contains(tr("遥调")))
		{
			ytmap.insert(newname,ytmap[curItem->text(0)]);
			ytmap.erase(ytmap.find(curItem->text(0)));
		}
		else
		{
			return;
		}
		curItem->setText(0,newname);
		on_treeWidget_itemSelectionChanged();
	}
}

void Widget::on_treeWidget_itemSelectionChanged()
{
	QTreeWidgetItem* curItem=ui->treeWidget->currentItem();  //获取当前被点击的节点
	if(curItem==NULL)
		return;
	if(curItem->flags() & Qt::ItemNeverHasChildren)
	{
		QTreeWidgetItem *parent = curItem->parent();
		if(parent==NULL)
			return;
		if(parent->text(0).contains(tr("遥测")))
		{
			ui->stackconfig->setCurrentIndex(1);
			QString key = curItem->text(0);
			QString text;
			foreach(QString tmp,ycmap[key].textlst)
			{
				text.append(tmp + "\n");
			}
			ui->TEyc->setPlainText(text);
			ui->Labelyc->setText(key);
			ui->Labelycnum->setText(QString::number(ycmap[key].textlst.length()));
			ui->LEyc1->setText(QString::number(ycmap[key].ycnum,ui->CByc1->isChecked()?16:10));
			ui->LEyc2->setText(QString::number(ycmap[key].yctype,ui->CByc2->isChecked()?16:10));
			ui->LEyc3->setText(QString::number(ycmap[key].yccode,ui->CByc3->isChecked()?16:10));
			ui->LEyc4->setText(QString::number(ycmap[key].ycaddr,ui->CByc4->isChecked()?16:10));
		}
		else if(parent->text(0).contains(tr("遥信")))
		{
			ui->stackconfig->setCurrentIndex(2);
			QString key = curItem->text(0);
			QString text;
			foreach(QString tmp,yxmap[key].textlst)
			{
				text.append(tmp + "\n");
			}
			ui->TEyx->setPlainText(text);
			ui->Labelyx->setText(key);
			ui->Labelyxnum->setText(QString::number(yxmap[key].textlst.length()));
			ui->LEyx1->setText(QString::number(yxmap[key].yxnum,ui->CByx1->isChecked()?16:10));
			ui->LEyx2->setText(QString::number(yxmap[key].yxtype,ui->CByx2->isChecked()?16:10));
			ui->LEyx3->setText(QString::number(yxmap[key].yxcode,ui->CByx3->isChecked()?16:10));
			ui->LEyx4->setText(QString::number(yxmap[key].yxaddr,ui->CByx4->isChecked()?16:10));
		}
		else if(parent->text(0).contains(tr("遥脉")))
		{
			ui->stackconfig->setCurrentIndex(3);
			QString key = curItem->text(0);
			QString text;
			foreach(QString tmp,ymmap[key].textlst)
			{
				text.append(tmp + "\n");
			}
			ui->TEym->setPlainText(text);
			ui->Labelym->setText(key);
			ui->Labelymnum->setText(QString::number(ymmap[key].textlst.length()));
			ui->LEym1->setText(QString::number(ymmap[key].ymnum,ui->CBym1->isChecked()?16:10));
			ui->LEym2->setText(QString::number(ymmap[key].ymcode,ui->CBym2->isChecked()?16:10));
			ui->LEym3->setText(QString::number(ymmap[key].ymaddr,ui->CBym3->isChecked()?16:10));
		}
		else if(parent->text(0).contains(tr("遥控")))
		{
			ui->stackconfig->setCurrentIndex(4);
			QString key = curItem->text(0);
			QString text;
			foreach(QString tmp,ykmap[key].textlst)
			{
				text.append(tmp + "\n");
			}
			ui->TEyk->setPlainText(text);
			ui->Labelyk->setText(key);
			ui->Labelyknum->setText(QString::number(ykmap[key].textlst.length()));
			ui->LEyk1->setText(QString::number(ykmap[key].ykcloseaddrsel,ui->CByk1->isChecked()?16:10));
			ui->LEyk2->setText(QString::number(ykmap[key].ykcloseaddr,ui->CByk2->isChecked()?16:10));
			ui->LEyk3->setText(QString::number(ykmap[key].ykopenaddrsel,ui->CByk3->isChecked()?16:10));
			ui->LEyk4->setText(QString::number(ykmap[key].ykopenaddr,ui->CByk4->isChecked()?16:10));
		}
		else if(parent->text(0).contains(tr("遥调")))
		{
			ui->stackconfig->setCurrentIndex(5);
			QString key = curItem->text(0);
			QString text;
			foreach(QString tmp,ytmap[key].textlst)
			{
				text.append(tmp + "\n");
			}
			ui->TEyt->setPlainText(text);
			ui->Labelyt->setText(key);
			ui->Labelytnum->setText(QString::number(ytmap[key].textlst.length()));
			ui->LEyt1->setText(QString::number(ytmap[key].ytaddr,ui->CByt1->isChecked()?16:10));

		}
	}
	else
	{
		ui->stackconfig->setCurrentIndex(0);
		ui->LE1->setText(QString::number(base->ykcode,ui->CB1->isChecked()?16:10));
		ui->LE2->setText(QString::number(base->ykselect,ui->CB2->isChecked()?16:10));
		ui->LE3->setText(QString::number(base->ykclose,ui->CB3->isChecked()?16:10));
		ui->LE4->setText(QString::number(base->ykopen,ui->CB4->isChecked()?16:10));
		ui->LE5->setText(QString::number(base->ytcode,ui->CB5->isChecked()?16:10));
		ui->LE6->setText(QString::number(base->ymseq,ui->CB6->isChecked()?16:10));
		ui->LE7->setText(QString::number(base->ymbcd,ui->CB7->isChecked()?16:10));
		ui->LE8->setText(QString::number(base->datalen,ui->CB8->isChecked()?16:10));
	}
}

/***********************基本配置****************************/
void Widget::on_PBsave_clicked()
{
	base->ykcode = ui->LE1->text().toUShort(0,ui->CB1->isChecked()?16:10);
	base->ykselect = ui->LE2->text().toUShort(0,ui->CB2->isChecked()?16:10);
	base->ykclose = ui->LE3->text().toUShort(0,ui->CB3->isChecked()?16:10);
	base->ykopen = ui->LE4->text().toUShort(0,ui->CB4->isChecked()?16:10);
	base->ytcode = ui->LE5->text().toUShort(0,ui->CB5->isChecked()?16:10);
	base->ymseq = ui->LE6->text().toUShort(0,ui->CB6->isChecked()?16:10);
	base->ymbcd = ui->LE7->text().toUShort(0,ui->CB7->isChecked()?16:10);
	base->datalen = ui->LE8->text().toUShort(0,ui->CB8->isChecked()?16:10);
	on_treeWidget_itemSelectionChanged();
}

void Widget::on_CB1_stateChanged(int arg1)
{
	ushort ss = ui->LE1->text().toUShort(0,arg1?10:16);
	ui->LE1->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CB2_stateChanged(int arg1)
{
	ushort ss = ui->LE2->text().toUShort(0,arg1?10:16);
	ui->LE2->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CB3_stateChanged(int arg1)
{
	ushort ss = ui->LE3->text().toUShort(0,arg1?10:16);
	ui->LE3->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CB4_stateChanged(int arg1)
{
	ushort ss = ui->LE4->text().toUShort(0,arg1?10:16);
	ui->LE4->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CB5_stateChanged(int arg1)
{
	ushort ss = ui->LE5->text().toUShort(0,arg1?10:16);
	ui->LE5->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CB6_stateChanged(int arg1)
{
	ushort ss = ui->LE6->text().toUShort(0,arg1?10:16);
	ui->LE6->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CB7_stateChanged(int arg1)
{
	ushort ss = ui->LE7->text().toUShort(0,arg1?10:16);
	ui->LE7->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CB8_stateChanged(int arg1)
{
	ushort ss = ui->LE8->text().toUShort(0,arg1?10:16);
	ui->LE8->setText(QString::number(ss,arg1?16:10));
}

/***********************遥测****************************/
void Widget::on_PBycsave_clicked()
{
	QString key = ui->Labelyc->text();
	QString text = ui->TEyc->toPlainText().trimmed();
	if(text.isEmpty())
	{
		ycmap[key].textlst.clear();
	}
	else
	{
		ycmap[key].textlst = text.split('\n');
		ycmap[key].textlst.removeAll("");
		for (int i = 0;i < ycmap[key].textlst.length();i++)
		{
			ycmap[key].textlst.replace(i,ycmap[key].textlst.value(i).trimmed());
		}
	}
	ui->Labelycnum->setText(QString::number(ycmap[key].textlst.length()));
	ycmap[key].ycnum = ui->LEyc1->text().toUShort(0,ui->CByc1->isChecked()?16:10);
	ycmap[key].yctype = ui->LEyc2->text().toUShort(0,ui->CByc2->isChecked()?16:10);
	ycmap[key].yccode = ui->LEyc3->text().toUShort(0,ui->CByc3->isChecked()?16:10);
	ycmap[key].ycaddr = ui->LEyc4->text().toUShort(0,ui->CByc4->isChecked()?16:10);
	on_treeWidget_itemSelectionChanged();
}


void Widget::on_CByc1_stateChanged(int arg1)
{
	ushort ss = ui->LEyc1->text().toUShort(0,arg1?10:16);
	ui->LEyc1->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CByc2_stateChanged(int arg1)
{
	ushort ss = ui->LEyc2->text().toUShort(0,arg1?10:16);
	ui->LEyc2->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CByc3_stateChanged(int arg1)
{
	ushort ss = ui->LEyc3->text().toUShort(0,arg1?10:16);
	ui->LEyc3->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CByc4_stateChanged(int arg1)
{
	ushort ss = ui->LEyc4->text().toUShort(0,arg1?10:16);
	ui->LEyc4->setText(QString::number(ss,arg1?16:10));
}

/***********************遥信****************************/
void Widget::on_PByxsave_clicked()
{
	QString key = ui->Labelyx->text();
	QString text = ui->TEyx->toPlainText().trimmed();
	if(text.isEmpty())
	{
		yxmap[key].textlst.clear();
	}
	else
	{
		yxmap[key].textlst = text.split('\n');
		yxmap[key].textlst.removeAll("");
		for (int i = 0;i < yxmap[key].textlst.length();i++)
		{
			yxmap[key].textlst.replace(i,yxmap[key].textlst.value(i).trimmed());
		}
	}
	ui->Labelyxnum->setText(QString::number(yxmap[key].textlst.length()));
	yxmap[key].yxnum = ui->LEyx1->text().toUShort(0,ui->CByx1->isChecked()?16:10);
	yxmap[key].yxtype = ui->LEyx2->text().toUShort(0,ui->CByx2->isChecked()?16:10);
	yxmap[key].yxcode = ui->LEyx3->text().toUShort(0,ui->CByx3->isChecked()?16:10);
	yxmap[key].yxaddr = ui->LEyx4->text().toUShort(0,ui->CByx4->isChecked()?16:10);
	on_treeWidget_itemSelectionChanged();
}


void Widget::on_CByx1_stateChanged(int arg1)
{
	ushort ss = ui->LEyx1->text().toUShort(0,arg1?10:16);
	ui->LEyx1->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CByx2_stateChanged(int arg1)
{
	ushort ss = ui->LEyx2->text().toUShort(0,arg1?10:16);
	ui->LEyx2->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CByx3_stateChanged(int arg1)
{
	ushort ss = ui->LEyx3->text().toUShort(0,arg1?10:16);
	ui->LEyx3->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CByx4_stateChanged(int arg1)
{
	ushort ss = ui->LEyx4->text().toUShort(0,arg1?10:16);
	ui->LEyx4->setText(QString::number(ss,arg1?16:10));
}

/***********************遥脉****************************/
void Widget::on_PBymsave_clicked()
{
	QString key = ui->Labelym->text();
	QString text = ui->TEym->toPlainText().trimmed();
	if(text.isEmpty())
	{
		ymmap[key].textlst.clear();
	}
	else
	{
		ymmap[key].textlst = text.split('\n');
		ymmap[key].textlst.removeAll("");
		for (int i = 0;i < ymmap[key].textlst.length();i++)
		{
			ymmap[key].textlst.replace(i,ymmap[key].textlst.value(i).trimmed());
		}
	}
	ui->Labelymnum->setText(QString::number(ymmap[key].textlst.length()));
	ymmap[key].ymnum = ui->LEym1->text().toUShort(0,ui->CBym1->isChecked()?16:10);
	ymmap[key].ymcode = ui->LEym2->text().toUShort(0,ui->CBym2->isChecked()?16:10);
	ymmap[key].ymaddr = ui->LEym3->text().toUShort(0,ui->CBym3->isChecked()?16:10);
	on_treeWidget_itemSelectionChanged();
}


void Widget::on_CBym1_stateChanged(int arg1)
{
	ushort ss = ui->LEym1->text().toUShort(0,arg1?10:16);
	ui->LEym1->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CBym2_stateChanged(int arg1)
{
	ushort ss = ui->LEym2->text().toUShort(0,arg1?10:16);
	ui->LEym2->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CBym3_stateChanged(int arg1)
{
	ushort ss = ui->LEym3->text().toUShort(0,arg1?10:16);
	ui->LEym3->setText(QString::number(ss,arg1?16:10));
}

/***********************遥控****************************/
void Widget::on_PByksave_clicked()
{
	QString key = ui->Labelyk->text();
	QString text = ui->TEyk->toPlainText().trimmed();
	if(text.isEmpty())
	{
		ykmap[key].textlst.clear();
	}
	else
	{
		ykmap[key].textlst.clear();
		ykmap[key].textlst << text.split('\n').at(0).trimmed();
		ykmap[key].textlst.removeAll("");
	}
	ui->Labelyknum->setText(QString::number(ykmap[key].textlst.length()));
	ykmap[key].ykcloseaddrsel = ui->LEyk1->text().toUShort(0,ui->CByk1->isChecked()?16:10);
	ykmap[key].ykcloseaddr = ui->LEyk2->text().toUShort(0,ui->CByk2->isChecked()?16:10);
	ykmap[key].ykopenaddrsel = ui->LEyk3->text().toUShort(0,ui->CByk3->isChecked()?16:10);
	ykmap[key].ykopenaddr = ui->LEyk4->text().toUShort(0,ui->CByk4->isChecked()?16:10);
	on_treeWidget_itemSelectionChanged();
}


void Widget::on_CByk1_stateChanged(int arg1)
{
	ushort ss = ui->LEyk1->text().toUShort(0,arg1?10:16);
	ui->LEyk1->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CByk2_stateChanged(int arg1)
{
	ushort ss = ui->LEyk2->text().toUShort(0,arg1?10:16);
	ui->LEyk2->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CByk3_stateChanged(int arg1)
{
	ushort ss = ui->LEyk3->text().toUShort(0,arg1?10:16);
	ui->LEyk3->setText(QString::number(ss,arg1?16:10));
}

void Widget::on_CByk4_stateChanged(int arg1)
{
	ushort ss = ui->LEyk4->text().toUShort(0,arg1?10:16);
	ui->LEyk4->setText(QString::number(ss,arg1?16:10));
}

/***********************遥调****************************/
void Widget::on_PBytsave_clicked()
{
	QString key = ui->Labelyt->text();
	QString text = ui->TEyt->toPlainText().trimmed();
	if(text.isEmpty())
	{
		ytmap[key].textlst.clear();
	}
	else
	{
		ytmap[key].textlst.clear();
		ytmap[key].textlst << text.split('\n').at(0).trimmed();
		ytmap[key].textlst.removeAll("");
	}
	ui->Labelytnum->setText(QString::number(ytmap[key].textlst.length()));
	ytmap[key].ytaddr = ui->LEyt1->text().toUShort(0,ui->CByt1->isChecked()?16:10);
	on_treeWidget_itemSelectionChanged();
}

void Widget::on_CByt1_stateChanged(int arg1)
{
	ushort ss = ui->LEyt1->text().toUShort(0,arg1?10:16);
	ui->LEyt1->setText(QString::number(ss,arg1?16:10));
}

