#include "FileMapping.h"
//
// Version for file size  < 2Gb
//

void FileMap::openFile(const QString& filename)
{
	file.setFileName(filename);
	file.open(QFile::ReadOnly);
	filesize = file.size();
	mem = file.map(0, filesize);
	pos = 0;
}

void FileMap::closeFile()
{
	file.unmap(mem);
	file.close();
}
