#include "framework.h"
#include "SRV.h"

SRV::SRV(ComPtr<ID3D11ShaderResourceView> srv)
: _srv(srv)
{
}

SRV::SRV(wstring file)
{
    ScratchImage image;
    wstring path = file;
    LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, image);

    _size = Vector2((int)image.GetMetadata().width, (int)image.GetMetadata().height);

    CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(),
        _srv.GetAddressOf());
}

SRV::~SRV()
{
}

void SRV::Set(int slot)
{
    DC->PSSetShaderResources(slot, 1, _srv.GetAddressOf());
}
