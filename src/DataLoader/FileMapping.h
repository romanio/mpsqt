#ifndef FILEMAP_H
#define FILEMAP_H
#include <QString>
#include <QFile>

class FileMap
{
public:
	FileMap() {}
	void openFile(const QString& filename);
	void closeFile();

	inline int fileSize()
	{
		return file.size();
	}

	inline void skip(int count)
	{
		pos += count;
	}

	inline float readSingle()
	{
		pos += 4;
		return *(float*)(&mem[pos-4]);
	}

	inline int readInt32()
	{
		pos += 4;
		return *(int*)(&mem[pos-4]);
	}

	inline QString readString(int count)
	{
		pos += count;
		return QString::fromAscii((char*)(&mem[pos-count]), count);
	}

	inline void readInt32Buffer(int* buffer, int count)
	{
		pos += count * 4;
		memcpy(buffer, &mem[pos - count * 4], count * 4);
	}
	inline void readSingleBuffer(float* buffer, int count)
	{
		pos += count * 4;
		memcpy(buffer, &mem[pos - count * 4], count * 4);
	}

	inline bool eof()
	{
		return (pos > filesize)?true:false;
	}

private:
	QFile file;
	uchar* mem;
	int pos;
	int filesize;
};

#endif // FILEMAP_H
