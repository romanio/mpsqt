#ifndef IDATALOADER_H
#define IDATALOADER_H
#include <QString>

class IDataLoader
{
public:
	virtual ~IDataLoader() {}
	virtual void openFile(QString filename)=0;
	virtual int getElapsedTime()=0;
};

#endif // IDATALOADER_H
