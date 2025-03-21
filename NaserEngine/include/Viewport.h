#pragma once
#include "Prerequisites.h"

class Window;
class DeviceContext;

class Viewport
{
public:
	Viewport() = default;
	~Viewport() = default;

  /* @brief Inicializa el viewport con los parámetros especificados.
   * @param window Ventana a la que se asocia el viewport.
   * @return HRESULT Indica el éxito o fallo de la operación./
   * @return void
   * */
  HRESULT
  init(const Window & window);

  /* @brief Actualiza el estado del viewport.
   * @param width Ancho del viewport.
   * @param height Alto del viewport.
   * @return HRESULT Indica el éxito o fallo de la operación.
   * @return void
   * */
  HRESULT
  init(unsigned int width, unsigned int height);

  /* @brief Actualiza el estado del viewport.
   * @return void
   * */
  void
  update();

  /* @brief Renderiza el contenido del viewport.
   * @param deviceContext Contexto de dispositivo.
   * @return void 
   * */
  void
  render(DeviceContext& deviceContext);

  /* @brief Destruye el viewport y libera los recursos asociados.
   * @return void
   * */
  void
  destroy();

public:
  D3D11_VIEWPORT m_viewport; ///< Viewport de DirectX 11.

private:

};
