#pragma once
#include "Prerequisites.h"

class DeviceContext;
class Device;

class 
SamplerState {
public:
	SamplerState () = default;
	~SamplerState () = default;

  HRESULT 
  init(Device device);
  
  void
  render(DeviceContext &deviceContext, unsigned int startSlot, unsigned int numSampler);

  void
  destroy();
  
  ID3D11SamplerState* m_samplerState;
private:
  

};
