#ifndef TEMPESTLOADER_H
#define TEMPESTLOADER_H

#include <QFile>
#include "IDataLoader.h"

class TempestLoader: public IDataLoader
{
public:
	virtual ~TempestLoader() {}
	virtual void openFile(QString filename);
	virtual int getElapsedTime()
	{
		return elapsedTime;
	}

private:
	int elapsedTime;
};

#endif // TEMPESTLOADER_H
