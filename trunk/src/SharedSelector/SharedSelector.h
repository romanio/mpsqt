#ifndef SHAREDSELECTOR_H
#define SHAREDSELECTOR_H
#include <QObject>
#include <QDebug>

// Pattern Singleton

class SharedSelector : public QObject
{
        Q_OBJECT
public:
        static SharedSelector* Instance();
	void FreeInst();
        void setGroupID(int gid)
        {
            groupID = gid;
            wellID = -1;
            emit selectionChange();
            qDebug() << "Group ID = " << groupID;
        }
        int getGroupID()
        {
            return groupID;
        }

        void setWellID(int wid)
        {
            wellID = wid;
            groupID = -1;
            emit selectionChange();
            qDebug() << "Well ID = " << wellID;
        }

        int getWellID()
        {
            return wellID;
        }

signals:
        void selectionChange();
private:
        static SharedSelector* self;
	static int refcount;
        int groupID;
        int wellID;
        SharedSelector();
        ~SharedSelector();
};

#endif // SHAREDSELECTOR_H
