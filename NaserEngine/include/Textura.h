#pragma once
#include "Prerequisites.h"

class DeviceContext;
class Device;


class 
Texture {
public:
  Texture() = default;
  ~Texture() = default;

  /**
   * @brief Inicializa la textura. A partir de un archivo.
   *
   * @param device Dispositivo.
   * @param fileName Nombre del archivo.
   * @param extensionType Tipo de extensi�n.
   * @return HRESULT Indica el �xito o fallo de la operaci�n.
   */
  HRESULT
  init(Device device,
      const std::string& fileName,
      ExtensionType extensionType);
  /**
   * @brief Inicializa la textura. Dentro de la aplicaci�n.
   *
   * @param device Dispositivo.
   * @param width Ancho de la textura.
   * @param height Alto de la textura.
   * @param format Formato de la textura.
   * @param bindFlags Indica c�mo se va a utilizar la textura.
   * @param sampleCount N�mero de muestras.
   * @param qualityLevels Niveles de calidad.
   * @return HRESULT Indica el �xito o fallo de la operaci�n.
   */
  HRESULT
  init(Device device,
      unsigned int width,
      unsigned int height,
      DXGI_FORMAT format,
      unsigned int bindFlags,
      unsigned int sampleCount = 1,
      unsigned int qualityLevels = 0);

  /**
  * @brief Actualiza el estado de la textura.
  */
  void
  update();

  /**
  * @brief Renderiza el contenido de la textura.
  * @param deviceContext Contexto del dispositivo.
  * @param StartSlot �ndice del primer slot.
  * @param Numviews N�mero de vistas.
  */
  void
  render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int Numviews);

  /**
  * @brief Destruye la textura y libera los recursos asociados.
  * @param device Dispositivo.
  */
  void
  destroy();

public:
  ID3D11Texture2D* m_Texture = nullptr; ///< Textura.
  ID3D11ShaderResourceView* m_ShaderResourceView; ///< Vista de recursos de sombreador.
private:

};
