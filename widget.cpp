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
	}
	else if(curItem->text(0).contains(tr("遥脉")))
	{
		++ymnum;
	}
	else if(curItem->text(0).contains(tr("遥控")))
	{
		++yknum;
	}
	else if(curItem->text(0).contains(tr("遥调")))
	{
		++ytnum;
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
	}
	else if(parent->text(0).contains(tr("遥脉")))
	{
		ymnum--;
	}
	else if(parent->text(0).contains(tr("遥控")))
	{
		yknum--;
	}
	else if(parent->text(0).contains(tr("遥调")))
	{
		ytnum--;
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
		if(parent->text(0).contains(tr("遥测")))
		{
			for (int i = 0;i < parent->childCount();i++)
			{
				if(parent->child(i)->text(0) == newname)
				{
					QMessageBox::warning(this,tr("告警对话框"),tr("已存在此命名！"),QMessageBox::Ok);
					return;
				}
			}
			ycmap.insert(newname,ycmap[curItem->text(0)]);
			ycmap.erase(ycmap.find(curItem->text(0)));
			curItem->setText(0,newname);
		}
		on_treeWidget_itemSelectionChanged();
	}

}

void Widget::initconfig()
{
	ui->treeWidget->setStyle(QStyleFactory::create("windows"));
	ui->treeWidget->setSortingEnabled(true);
	ui->treeWidget->header()->setSortIndicatorShown(true);
	ui->treeWidget->header()->setSortIndicator(0, Qt::AscendingOrder);//这三句改变排序
	ui->stackconfig->setCurrentIndex(ui->stackconfig->count()-1);

	act1 = new QAction(tr("添加一组数据"),this);
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
}



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
	}
	else
	{
		if(curItem->text(0).contains(tr("基本配置")))
		{
			return;
		}

	}
}
