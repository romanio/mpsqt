#include <QFileInfo>
#include "TempestLoader.h"
#include "FileMapping.h"
#include "..\SharedData\SharedData.h"

void TempestLoader::openFile(QString filename)
{
	SharedData* sdata = SharedData::Instance();
	sdata->fileName = filename;
	FileMap fmap;
	int numb[100];
	//
	// For detaled see to "Roxar technical reference"
	// Read mis-file
	QFileInfo fileInfo(filename);
	QString baseName = fileInfo.baseName();
	QString pathName = fileInfo.absolutePath();
	QString fname(pathName + "/" + baseName + ".mis");

	fmap.openFile(fname);
	fmap.skip(16);
	int d = fmap.readInt32();
	int m = fmap.readInt32();
	int y = fmap.readInt32();
	sdata->initDate.setDate(y, m, d);
	fmap.skip(54);
	sdata->progHeader1 = fmap.readString(75);
	sdata->progHeader2 = fmap.readString(75);
	fmap.skip(12);
	fmap.readInt32Buffer(numb, 100);
	sdata->wellCount = numb[2];
	sdata->groupCount = numb[11];
	sdata->aquaCount = numb[32];
	sdata->quantCount = numb[37];
	sdata->nx = numb[43];
	sdata->ny = numb[44];
	sdata->nz = numb[45];
	fmap.skip(12);
	int nc = fmap.readInt32();
	int nl = fmap.readInt32();
	fmap.skip(4);
	int ms = fmap.readInt32();
	int mp = fmap.readInt32();
	fmap.skip(mp * 16 + nc * 16 + mp * 4 + nc * mp * 4 + mp * 4 + 3 * nc * 4 + nl * 16 + nc * nl * 4 + ms * 16 + nc * ms * 4);
	sdata->oilden = fmap.readSingle();
	sdata->gasden = fmap.readSingle();
	sdata->waterden = fmap.readSingle();
	fmap.closeFile();

	// Read ctl-file
	sdata->daysList.clear();
	sdata->datesList.clear();
	sdata->arrayList.clear();
	sdata->yearsIndex.clear();
	fname = pathName + "/" + baseName + ".ctl";
	fmap.openFile(fname);
	fmap.skip(12);
	while (!fmap.eof())
	{
		fmap.skip(4);
		int isArray = fmap.readInt32();
		int isRate = fmap.readInt32();
		float v = fmap.readSingle();
		if (isArray == 1) sdata->arrayList.append(sdata->initDate.addDays((int)v));
		if (isRate == 1)
		{
			sdata->daysList.append(v);
			sdata->datesList.append(sdata->initDate.addDays((int)v));
			if (sdata->datesList.last().day() == 01 && sdata->datesList.last().month() == 01)
				sdata->yearsIndex.append(sdata->datesList.count() - 1);
		}
		fmap.skip(8);
	}
	fmap.closeFile();
	sdata->daysCount = sdata->daysList.count();
	sdata->yearsCount = sdata->yearsIndex.count();

	// Read rate-file
	fname = pathName + "/" + baseName + ".rat";
	fmap.openFile(fname);

	// Initialization
	sdata->InitArrays();
	for (int i = 0; i < sdata->wellCount; ++i) sdata->wellNames.append(fmap.readString(16));
	for (int i = 0; i < sdata->groupCount; ++i) sdata->groupNames.append(fmap.readString(16));
	for (int i = 0; i < sdata->aquaCount; ++i) sdata->aquiferNames.append(fmap.readString(16));
	for (int i = 0; i < sdata->quantCount; ++i)
	{
		sdata->quantMnemonic.append(fmap.readString(16));
		sdata->quantUnits.append(fmap.readString(16));
		sdata->quantAssociated.append(fmap.readString(16));
		sdata->quantDescription.append(fmap.readString(48));
		fmap.skip(numb[39] * 4 + numb[40] * 4);
	}

	int leng = (numb[20] + numb[1] + 1) * (numb[15] + 2) + 2 * numb[20] + 4 * numb[1] + 2 * numb[1] * numb[4];

	// Found  max-array of float
	int fbufflen = numb[48];
	if (fbufflen < 15) fbufflen = 15;
	if (fbufflen < leng) fbufflen = leng;
	float* fbuff = new float[fbufflen];
	int* ibuff = new int[numb[46]];

	int _status = 0;
	for (int istep = 0; istep < sdata->daysCount; ++istep)
	{
		for (int iw = 0; iw < sdata->wellCount; ++iw)
		{
			fmap.readInt32Buffer(ibuff, numb[46]);
			_status = ibuff[3];

			//IRPTR + IRLIM
			fmap.skip(numb[4] * numb[47] * 4 + numb[6] * 2 * 4);

			//WRATE
			fmap.readSingleBuffer(fbuff, numb[48]);

			sdata->xloc[iw] = fbuff[0];
			sdata->yloc[iw] = fbuff[1];

			//WRVOL
			fmap.readSingleBuffer(fbuff, 15);

			sdata->opr[istep * sdata->wellCount + iw] = 0;
			sdata->gpr[istep * sdata->wellCount + iw] = 0;
			sdata->wpr[istep * sdata->wellCount + iw] = 0;
			sdata->wir[istep *  sdata->wellCount + iw] = 0;

			if (_status == 1)
			{
				sdata->opr[istep * sdata->wellCount + iw] = fbuff[0];
				sdata->gpr[istep * sdata->wellCount + iw] = fbuff[1];
				sdata->wpr[istep * sdata->wellCount + iw] = fbuff[2];
			}

			if (_status == 2)
			{
				sdata->wir[istep * sdata->wellCount + iw] = fbuff[1];
			}

			sdata->opt[istep * sdata->wellCount + iw] = fbuff[5];
			sdata->gpt[istep * sdata->wellCount + iw] = fbuff[6];
			sdata->wpt[istep * sdata->wellCount + iw] = fbuff[7];
			sdata->wit[istep * sdata->wellCount + iw] = fbuff[11];

			//WRMS + WMCMP + WRCMP
			fmap.skip(numb[1] * 3 * 4 + numb[4] * 2 * 4 + numb[4] * numb[1] * 4);

			//WVCMP
			if (numb[54] == 1)
				fmap.skip(numb[4] * 15 * 4);

			//WVLAY
			if (numb[55] == 1)
				fmap.skip(numb[4] * numb[51] * 4);
		}

		//Group data
		for (int ig = 0; ig < sdata->groupCount; ig++)
		{
			fmap.skip(4);
			fmap.readSingleBuffer(fbuff, leng);

			fmap.skip(numb[20] * numb[52] * 4);

			for (int iw = 0; iw < sdata->wellCount; iw++)
			{
				sdata->gwfr[ig *  sdata->wellCount  + iw] = fmap.readSingle();
			}

			fmap.skip(numb[4] * numb[53] * 4);
		}

		//Aquifer data
		fmap.skip(numb[32] * numb[33] * 4);

		// Quantities
		for (int iq = 0; iq < sdata->quantCount; ++iq)
		{
			sdata->qdata[istep * sdata->quantCount + iq] = fmap.readSingle();
		}
	}

	fmap.closeFile();
        sdata->finishDataLoading();
	sdata->FreeInst();
}
