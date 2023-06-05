#include "framework.h"
#include "SRVManager.h"

SRVManager* SRVManager::_instance = nullptr;
SRVManager::SRVManager()
{
}

SRVManager::~SRVManager()
{
}

shared_ptr<SRV> SRVManager::Add_SRV(wstring path)
{
    if(_srvMap.count(path) != 0)
        return _srvMap[path];

    shared_ptr<SRV> srv = make_shared<SRV>(path);
    _srvMap[path] = srv;

    return srv;
}
