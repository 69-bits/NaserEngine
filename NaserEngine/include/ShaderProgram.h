#pragma once
#include "Prerequisites.h"
#include "InputLayout.h"

class Device;
class DeviceContext;

class
ShaderProgram {
public:
  ShaderProgram() = default;
  ~ShaderProgram() = default;

  /* @brief Inicializa el programa de shaders con los parámetros especificados.
   * @param device Dispositivo de DirectX 11.
   * @param fileName Nombre del archivo de shaders.
   * @param Layout Descripción de los elementos de entrada.
   * @return HRESULT Indica el éxito o fallo de la operación.
   */
  HRESULT
  init(Device& device,
      const std::string& fileName,
      std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /* @brief Actualiza el estado del programa de shaders.
  * @return void
  * */
  void
  update();

  /* @brief Renderiza el contenido del programa de shaders.
  * @param deviceContext Contexto de dispositivo.
  * @return void
  * */
  void
  render(DeviceContext& deviceContext);

  /* @brief Destruye el programa de shaders y libera los recursos asociados.
  * @return void
  * */
  void
  destroy();

  /* @brief Crea el layout de entrada.
  * @param device Dispositivo de DirectX 11.
  * @param Layout Descripción de los elementos de entrada.
  * @return HRESULT Indica el éxito o fallo de la operación.
  * */
  HRESULT
  CreateInputLayout(Device& device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /* @brief Crea el shader especificado.
  * @param device Dispositivo de DirectX 11.
  * @param type Tipo de shader (Vertex o Pixel, para eso nuestro Enum del Prerequisites).
  * @return HRESULT Indica el éxito o fallo de la operación.
  * */
  HRESULT
  CreateShader(Device& device, ShaderType type);

  /* @brief Compila el shader especificado.
  * @param szFileName Nombre del archivo de shaders.
  * @param szEntryPoint Punto de entrada del shader.
  * @param szShaderModel Modelo del shader.
  * @param ppBlobOut Puntero al blob de salida.
  * @return HRESULT Indica el éxito o fallo de la operación.
  * */
  HRESULT
  CompileShaderFromFile(char* szFileName,
      LPCSTR szEntryPoint,
      LPCSTR szShaderModel,
      ID3DBlob** ppBlobOut);
private:
public:
  ID3D11VertexShader* m_VertexShader = nullptr; ///< Shader de vértices de DirectX 11.
  ID3D11PixelShader* m_PixelShader = nullptr; ///< Shader de píxeles de DirectX 11.
  InputLayout m_inputLayout; ///< Layout de entrada de DirectX 11.
private:
  std::string m_shaderFileName; ///< Nombre del archivo de shaders.
  ID3DBlob* m_vertexShaderData = nullptr; ///< Datos del shader de vértices.
  ID3DBlob* m_pixelShaderData = nullptr; ///< Datos del shader de píxeles.
};