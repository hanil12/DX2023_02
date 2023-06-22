#include "framework.h"
#include "BinaryReader.h"

BinaryReader::BinaryReader(wstring path)
: _size(0)
{
    _file = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ,
    0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    assert(_file != nullptr);
}

BinaryReader::~BinaryReader()
{
    CloseHandle(_file);
}

int BinaryReader::Int()
{
    int temp = 0;
    assert(ReadFile(_file, OUT &temp, sizeof(int), OUT &_size, nullptr));

    return temp;
}

UINT BinaryReader::UInt()
{
    UINT temp = 0;
    assert(ReadFile(_file, OUT & temp, sizeof(UINT), OUT & _size, nullptr));

    return temp;
}

float BinaryReader::Float()
{
    float temp = 0;
    assert(ReadFile(_file, OUT & temp, sizeof(float), OUT & _size, nullptr));

    return temp;
}

string BinaryReader::String()
{
    UINT size = UInt();

    char* temp = new char[size + 1]();

    assert(ReadFile(_file, OUT temp, sizeof(char) * size, &_size, nullptr));

    string str = temp;

    delete[] temp;

    return str;
}

void BinaryReader::Byte(OUT void** data, UINT dataSize)
{
    assert(ReadFile(_file, OUT *data, dataSize, OUT &_size, nullptr));
}
