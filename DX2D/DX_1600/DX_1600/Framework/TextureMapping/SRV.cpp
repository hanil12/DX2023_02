#include "framework.h"
#include "SRV.h"

SRV::SRV(wstring file)
{
    ScratchImage image;
    wstring path = file;
    LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, image);

    _size = Vector2((int)image.GetMetadata().width, (int)image.GetMetadata().height);

    CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(),
        _shaderResourceView.GetAddressOf());
}

SRV::~SRV()
{
}

void SRV::Set(int slot)
{
    DC->PSSetShaderResources(slot, 1, _shaderResourceView.GetAddressOf());
}
