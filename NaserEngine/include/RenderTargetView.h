#pragma once
#include "Prerequisites.h"

// Forward Declarations - Declaraciones Directas
class Device;
class DeviceContext;
class Textura;
class DepthStencilView;

class
RenderTargetView {
public:
  RenderTargetView() = default;
  ~RenderTargetView() = default;

  /* Inicializa el render target view.
  * @param device Dispositivo.
  * @param backBuffer Textura de la ventana.
  * @param Format Formato del render target view.
  * @return HRESULT Indica el éxito o fallo de la operación.
  */
  HRESULT
  init(Device& device, Textura&  backBuffer, DXGI_FORMAT Format);

  void
  update();

  /* Renderiza el contenido del render target view.
  * @param deviceContext Contexto del dispositivo.
  * @param depthStencilView Vista de profundidad y stencil.
  * @param numViews Número de vistas.
  * @param ClearColor Color de limpieza.
  * @return void.
  */
  void
  render(DeviceContext& deviceContext,
      DepthStencilView& depthStencilView,
      unsigned int numViews,
      const float ClearColor[4]);

  /* Destruye el render target view y libera los recursos asociados.
  * @return void.
  */
  void
  destroy();

public:
  ID3D11RenderTargetView* m_renderTargetView = nullptr; // Render Target View
};