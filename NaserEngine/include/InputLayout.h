#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

class 
InputLayout {
public:
	InputLayout () = default;
	~InputLayout () = default;

  /* @brief Inicializa el layout de entrada con los parámetros especificados.
   * @param device Dispositivo de DirectX 11.
   * @param layout Descripción de los elementos de entrada.
   * @param VertexShaderData Datos del shader de vértices.
   * @return HRESULT Indica el éxito o fallo de la operación.
	*/
	HRESULT
	init(Device& device, std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3D10Blob* VertexShaderData);

  /* @brief Actualiza el estado del layout de entrada.
   * @return void
   * */
	void
  update();

  /* @brief Renderiza el contenido del layout de entrada.
   * @param deviceContext Contexto de dispositivo.
   * @return void
   * */
	void
  render(DeviceContext& deviceContext);

  /* @brief Destruye el layout de entrada y libera los recursos asociados.
   * @return void
   * */
	void
  destroy();

  ID3D11InputLayout* m_inputLayout = nullptr; ///< Layout de entrada de DirectX 11.
private:
  
};
