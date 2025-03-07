#include "SamplerState.h"
#include "Device.h"
#include "DeviceContext.h"

HRESULT SamplerState::init(Device device)
{

	HRESULT hr = S_OK;
  D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
  hr = device.m_device->CreateSamplerState(&sampDesc, &m_samplerState);
  if (FAILED(hr)) {
    ERROR("SamplerState", "init", "CreateSamplerState failed");
    return hr;
  }

  return S_OK;
}

void 
SamplerState::render(DeviceContext& deviceContext, unsigned int startSlot, unsigned int numSampler) {
	if (!m_samplerState) {
    ERROR("SamplerState", "render", "SampleState is missing");
    return;
	}

	if (!deviceContext.m_deviceContext) {
    ERROR("SamplerState", "render", "DeviceContext is missing");
    return;
	}
  deviceContext.m_deviceContext->PSSetSamplers(startSlot, numSampler, &m_samplerState);
}


void 
SamplerState::destroy() {
  m_samplerState->Release();
}
