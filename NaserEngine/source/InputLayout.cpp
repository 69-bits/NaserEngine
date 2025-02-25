#include "InputLayout.h"
#include "Device.h"
#include "DeviceContext.h"

HRESULT 
InputLayout::init(Device& device, std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3D10Blob* VertexShaderData)
{
  if (layout.empty()) {
    ERROR("InputLayout", "init", "Input layout is empty // Oopsie init layout ╰(*°▽°*)╯");
    return E_INVALIDARG;
  }

  if (!VertexShaderData) {
    ERROR("InputLayout", "init", "Vertex shader data is nullptr // Oopsie init layout ╰(*°▽°*)╯");
    return E_INVALIDARG;
  }

  HRESULT hr = S_OK;

  hr = device.m_device->CreateInputLayout(layout.data(),
    static_cast<unsigned int>(layout.size()),
    VertexShaderData->GetBufferPointer(),
    VertexShaderData->GetBufferSize(),
    &m_inputLayout);
}

void 
InputLayout::update() {
}

void 
InputLayout::render(DeviceContext& deviceContext) {
  if (!m_inputLayout) {
    ERROR("InputLayout", "render", "Input layout is nullptr // Oopsie render layout ╰(*°▽°*)╯");
    return;
  }
  deviceContext.IASetInputLayout(m_inputLayout);
}

void 
InputLayout::destroy() {
  SAFE_RELEASE(m_inputLayout);
}
