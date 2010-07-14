#ifndef SHAREDDATA_H
#define SHAREDDATA_H
#include <QStringList>
#include <QDateTime>
#include <QObject>

// Pattern Singleton

class SharedData : public QObject
{
    Q_OBJECT
public:
	static SharedData* Instance();

	void FreeInst();
	void InitArrays(); // Initialize arrays
	void ClearArrays(); //Clear arrays and free memory

	QString progHeader1; // Program header I
	QString progHeader2; // Program header II
	QString fileName;

	QStringList wellNames;
	QStringList groupNames;
	QStringList aquiferNames;
	QStringList quantMnemonic;
	QStringList quantUnits;
	QStringList quantAssociated;
	QStringList quantDescription;

	QDate initDate;
	QList<float> daysList;
	QList<QDate> datesList;
	QList<QDate> arrayList;
	QList<int> yearsIndex;

	int wellCount;
	int groupCount;
	int aquaCount;
	int quantCount;

	int nx, ny, nz;
	//
	int daysCount;
	int yearsCount;

	float oilden, waterden, gasden; // Density oil, water, gas
	//
	float* gwfr; // Group well fracture
	float* opt; // Oil production total
	float* gpt; // Gas production total
	float* wpt; // Water production total
	float* wit; // Water injection total
	float* opr; // Oil production rate
	float* wpr; // Water production rate
	float* gpr; // Gas production rate
	float* wir; // Water injection rate
	float* xloc; // X coordinate
	float* yloc; // Y coordinate
	float* qdata; // Quantity data
	bool isAllocated;

        void finishDataLoading();
signals:
        void dataUpdate();
private:
	static SharedData* self;
	static int refcount;

	SharedData();
	~SharedData();
};

#endif // SHAREDDATA_H
