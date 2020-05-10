#include "config.h"

config::config()
{
	textlst.clear();
}

baseconfig::baseconfig()
{

	ykcode = 5;
	ykselect = 0;
	ykclose = 0xffff;
	ykopen = 0;
	ytcode = 6;
	ymseq = 0;
	ymbcd = 0;
	datalen = 1;
}

ycconfig::ycconfig()
{

	ycnum = 0;
	yctype = 0;
	yccode = 0;
	ycaddr = 0;
}

yxconfig::yxconfig()
{

	yxnum = 0;
	yxtype = 0;
	yxcode = 0;
	yxaddr = 0;
}

ymconfig::ymconfig()
{
	ymnum = 0;
	ymcode = 0;
	ymaddr = 0;
}

ykconfig::ykconfig()
{
	ykcloseaddrsel = 0;
	ykcloseaddr = 0;
	ykopenaddrsel = 0;
	ykopenaddr = 0;
}

ytconfig::ytconfig()
{
	ytaddr = 0;
}
