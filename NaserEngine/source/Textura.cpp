#include "Textura.h"
#include "Device.h"
#include "DeviceContext.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

HRESULT
Texture::init(Device device,
  const std::string& fileName,
  ExtensionType extensionType) {

  int width, height, channels;
  D3D11_TEXTURE2D_DESC textureDesc = {};
  D3D11_SUBRESOURCE_DATA initData = {};
  D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
  unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &channels, 4);

  if (!device.m_device) {
    ERROR("Texture", "init", "Device is nullptr", "( ˆ𐃷ˆ) .ᐟ.ᐟ");
    return E_INVALIDARG;
  }
  HRESULT hr = S_OK;
  switch (extensionType) {
  case DDS:
    hr = D3DX11CreateShaderResourceViewFromFile(
      device.m_device,
      fileName.c_str(),
      nullptr,
      nullptr,
      &m_ShaderResourceView,
      nullptr);

    if (FAILED(hr)) {
      ERROR("Texture", "init",
        ("Failed to create ShaderResourceView from file. HRESULT: " + fileName).c_str());
      return hr;

    }
    break;

  case PNG:
    if (!data) {
      ERROR("Texture", "init", "Failed to load image", "( ˆ𐃷ˆ) .ᐟ.ᐟ");
      return E_FAIL;
    }

    // Crear descripción de textura
    textureDesc.Width = width;
    textureDesc.Height = height;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    // Crear datos de subrecarga
    initData.pSysMem = data;
    initData.SysMemPitch = width * 4;

    hr = device.CreateTexture2D(&textureDesc, &initData, &m_Texture);
    stbi_image_free(data); // Liberar los datos de imagen inmediatamente

    if (FAILED(hr)) {
      ERROR("Texture", "init", "Failed to create Texture2D", "( ˆ𐃷ˆ) .ᐟ.ᐟ");
      return hr;
    }

    // Crear Shader Resource View
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    hr = device.m_device->CreateShaderResourceView(m_Texture, &srvDesc, &m_ShaderResourceView);
    SAFE_RELEASE(m_Texture); //Liberar la textura inmediatamente

    if (FAILED(hr)) {
      ERROR("Texture", "init", "Failed to create ShaderResourceView", "( ˆ𐃷ˆ) .ᐟ.ᐟ");
      return hr;
    }
    break;

  default:
    ERROR("Texture", "init", "Invalid extension type", "( ˆ𐃷ˆ) .ᐟ.ᐟ");
    return E_INVALIDARG;
  }
  return hr;
}

HRESULT
Texture::init(Device device,
  unsigned int width,
  unsigned int height,
  DXGI_FORMAT format,
  unsigned int bindFlags,
  unsigned int sampleCount,
  unsigned int qualityLevels)
{
  if (!device.m_device) {
    ERROR("Texture", "init", "Device is nullptr", "( ˆ𐃷ˆ) .ᐟ.ᐟ");
    return E_INVALIDARG;
  }

  if (!width || !height) {
    ERROR("Texture", "init", "Invalid width or height", "( ˆ𐃷ˆ) .ᐟ.ᐟ");
    return E_INVALIDARG;
  }

  HRESULT hr = S_OK;

  //Configuracion de la textura
  CD3D11_TEXTURE2D_DESC desc = {};
  desc.Width = width;
  desc.Height = height;
  desc.MipLevels = 1;
  desc.ArraySize = 1;
  desc.Format = format;
  desc.SampleDesc.Count = sampleCount;
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.BindFlags = bindFlags;

  hr = device.CreateTexture2D(&desc, nullptr, &m_Texture);
  if (FAILED(hr)) {
    ERROR("Texture", "init", "Failed to create Texture2D", "( ˆ𐃷ˆ) .ᐟ.ᐟ");
    return hr;
  }
}

void
Texture::update() {
}

void
Texture::render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int Numviews) {
  if (m_ShaderResourceView) {
    ID3D11ShaderResourceView* nullSRV[] = { nullptr };
    deviceContext.PSSetShaderResources(StartSlot, Numviews, nullSRV);
    deviceContext.PSSetShaderResources(StartSlot, Numviews, &m_ShaderResourceView);
  }
  else {
    ERROR("Texture", "render", "Texture resource is not initialized", "( ˆ𐃷ˆ) .ᐟ.ᐟ");
  }
}

void
Texture::destroy() {
}




