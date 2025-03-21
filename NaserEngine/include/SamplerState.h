#pragma once
#include "Prerequisites.h"

class DeviceContext;
class Device;

class 
SamplerState {
public:
	SamplerState () = default;
	~SamplerState () = default;

  /* @brief Inicializa el Sampler State.
   * @param device Dispositivo.
   * @return HRESULT Indica el éxito o fallo de la operación.
   */ 
  HRESULT 
  init(Device device);
  
  /* @brief Actualiza el Sampler State.
   * @return void
   */
  void
  render(DeviceContext &deviceContext, unsigned int startSlot, unsigned int numSampler);

  /* @brief Destruye el Sampler State.
   * @return void
   */ 
  void
  destroy();
  
  ID3D11SamplerState* m_samplerState; // Sampler State
private:
  

};
