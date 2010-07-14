#include "SharedSelector.h"
#include <QDebug>

SharedSelector::SharedSelector()
{
    wellID = -1;
    groupID = 0;
}

SharedSelector::~SharedSelector()
{

}

SharedSelector* SharedSelector::Instance()
{
        if (!self) self = new SharedSelector();
	refcount++;
	return self;
}

void SharedSelector::FreeInst()
{
	refcount--;
	if (!refcount)
	{
		delete this;
		self = 0;
	}
}

SharedSelector* SharedSelector::self = 0;
int SharedSelector::refcount = 0;
