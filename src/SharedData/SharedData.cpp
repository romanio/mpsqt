#include "SharedData.h"

SharedData::SharedData()
{
	isAllocated = false;
}

SharedData::~SharedData()
{
	ClearArrays();
}

SharedData* SharedData::Instance()
{
	if (!self) self = new SharedData();
	refcount++;
	return self;
}

void SharedData::FreeInst()
{
	refcount--;
	if (!refcount)
	{
		delete this;
		self = 0;
	}
}

void SharedData::InitArrays()
{
	ClearArrays();
	opt  = new float[wellCount * daysCount];
	gwfr = new float[groupCount * wellCount];
	gpt  = new float[wellCount * daysCount];
	wpt  = new float[wellCount * daysCount];
	wit  = new float[wellCount * daysCount];
	opr  = new float[wellCount * daysCount];
	wpr  = new float[wellCount * daysCount];
	gpr  = new float[wellCount * daysCount];
	wir  = new float[wellCount * daysCount];
	xloc = new float[wellCount];
	yloc = new float[wellCount];
	qdata = new float[quantCount * daysCount];

	isAllocated = true;
}

void SharedData::ClearArrays()
{
	wellNames.clear();
	groupNames.clear();
	aquiferNames.clear();
	quantMnemonic.clear();
	quantUnits.clear();
	quantAssociated.clear();
	quantDescription.clear();

	if (isAllocated)
	{
		delete[] opt;
		delete[] gwfr;
		delete[] gpt;
		delete[] wpt;
		delete[] wit;
		delete[] opr;
		delete[] wpr;
		delete[] gpr;
		delete[] wir;
		delete[] xloc;
		delete[] yloc;
		delete[] qdata;
	}
}

void SharedData::finishDataLoading()
{
    emit dataUpdate();
}

SharedData* SharedData::self = 0;
int SharedData::refcount = 0;
