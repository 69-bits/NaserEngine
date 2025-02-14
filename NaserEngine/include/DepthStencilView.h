#pragma once
#include "PreRequisites.h"

// Forward Declarations - Declaraciones Directas
class Device;
class DeviceContext;
class Textura;

class
DepthStencilView {
public:
	DepthStencilView() = default;
	~DepthStencilView() = default;
  /* Inicializa la vista de profundidad y stencil.
  * @param device Dispositivo.
  * @param depthStencil Textura de profundidad y stencil.
  * @param format Formato de la vista de profundidad y stencil.
  * @return HRESULT Indica el éxito o fallo de la operación.
	*/
	HRESULT
	init(Device& device, Textura& depthStencil, DXGI_FORMAT format);

  /* Actualiza el estado de la vista de profundidad y stencil.
  * @return void.
	*/
	void
	update();

  /* Renderiza el contenido de la vista de profundidad y stencil.
  * @param deviceContext Contexto del dispositivo.
  * @return void.
	*/
	void
	render(DeviceContext& deviceContext);

	void
	destroy();
public:
  ID3D11DepthStencilView* m_depthStencilView = nullptr; // Depth Stencil View
};