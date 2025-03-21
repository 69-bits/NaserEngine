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

  /* @brief Inicializa la vista de profundidad y stencil.
   * @param device Dispositivo.
   * @param depthStencil Textura de profundidad y stencil.
   * @param format Formato de la vista de profundidad y stencil.
   * @return HRESULT Indica el éxito o fallo de la operación.
	 */
	HRESULT
	init(Device& device, Textura& depthStencil, DXGI_FORMAT format);

  /* @brief Actualiza el estado de la vista de profundidad y stencil.
   * @return void.
	 */
	void
	update();

  /* @brief Renderiza el contenido de la vista de profundidad y stencil.
   * @param deviceContext Contexto del dispositivo.
   * @return void.
	 */
	void
	render(DeviceContext& deviceContext);

  /* @brief Destruye la vista de profundidad y stencil.
   * @return void.
   */
	void
	destroy();
public:
  ID3D11DepthStencilView* m_depthStencilView = nullptr; // Depth Stencil View
};