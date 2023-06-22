#include "framework.h"
#include "BinaryWriter.h"

BinaryWriter::BinaryWriter(wstring path)
: _size(0)
{
	_file = CreateFile(path.c_str(), GENERIC_WRITE, 0,0,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,nullptr);
}

BinaryWriter::~BinaryWriter()
{
	CloseHandle(_file);
}

void BinaryWriter::Int(int data)
{
	WriteFile(_file, &data, sizeof(int), IN &_size, nullptr);
}

void BinaryWriter::UInt(UINT data)
{
	WriteFile(_file, &data, sizeof(UINT), IN & _size, nullptr);
}

void BinaryWriter::Float(float data)
{
	WriteFile(_file, &data, sizeof(float), IN & _size, nullptr);
}

void BinaryWriter::String(string data)
{
	UInt(data.size());

	const char* ptr = data.c_str();

	WriteFile(_file, ptr, data.size(), IN &_size, nullptr);
}

void BinaryWriter::Byte(void* data, UINT dataSize)
{
	WriteFile(_file, data, dataSize, IN &_size, nullptr);
}
