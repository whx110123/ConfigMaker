#include "widget.h"
#include "ui_widget.h"

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
	QTreeWidgetItem* curItem=ui->treeWidget->currentItem();  //获取当前被点击的节点
	if(curItem==NULL)
		return;
	int tmp = 0;
	if(curItem->text(0).contains(tr("遥测")))
	{
		tmp = ++ycnum;
	}
	else if(curItem->text(0).contains(tr("遥信")))
	{
		tmp = ++yxnum;
	}
	else if(curItem->text(0).contains(tr("遥脉")))
	{
		tmp = ++ymnum;
	}
	else if(curItem->text(0).contains(tr("遥控")))
	{
		tmp = ++yknum;
	}
	else if(curItem->text(0).contains(tr("遥调")))
	{
		tmp = ++ytnum;
	}

	for (int i = 1;i < curItem->childCount();i++)
	{
		if(curItem->child(i)->text(0).toUInt() - curItem->child(i-1)->text(0).toUInt() != 1)
		{
			tmp = curItem->child(i-1)->text(0).toUInt() + 1;
		}
	}
	if(curItem->childCount() > 0 && curItem->child(0)->text(0).toUInt() > 1)
	{
		tmp = 1;
	}
	QTreeWidgetItem* newItem = new QTreeWidgetItem(curItem,QStringList() << QString("%1").arg(QString::number(tmp),2,QLatin1Char('0')));
	newItem->setFlags(newItem->flags() | Qt::ItemNeverHasChildren | Qt::ItemIsEditable);
	curItem->setExpanded(true);
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
}

void Widget::initconfig()
{
	ui->treeWidget->setStyle(QStyleFactory::create("windows"));
	ui->treeWidget->setSortingEnabled(true);
	ui->treeWidget->header()->setSortIndicatorShown(true);
	ui->treeWidget->header()->setSortIndicator(0, Qt::AscendingOrder);//这三句改变排序

	act1 = new QAction(tr("添加一组数据"),this);
	act2 = new QAction(tr("删除"),this);
	connect(act1, SIGNAL(triggered()), this, SLOT(createItem()));
	connect(act2, SIGNAL(triggered()),	this,SLOT(deleteItem()));
	connect(ui->treeWidget,SIGNAL(customContextMenuRequested(const QPoint&)), this,SLOT(popMenu(const QPoint&)));//检测鼠标右键
	ycnum = 0;
	yxnum = 0;
	ymnum = 0;
	yknum = 0;
	ytnum = 0;
}

