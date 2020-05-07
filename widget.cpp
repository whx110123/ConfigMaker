#include "widget.h"
#include "ui_widget.h"
#include <QStyleFactory>

Widget::Widget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::Widget)
{
	ui->setupUi(this);
	ui->treeWidget->setStyle(QStyleFactory::create("windows"));
}

Widget::~Widget()
{
	delete ui;
}

