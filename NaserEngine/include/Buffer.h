#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;
class MeshComponent;

class
Buffer {
public:
  Buffer() = default;
  ~Buffer() = default;

  /* @brief Inicializa el Vertex, Index y Constant Buffer
   * @param device Dispositivo de DirectX
   * @param mesh MeshComponent que contiene los datos
   * @param bindFlag Flag de bind
   * @return HRESULT Indica el éxito o fallo de la operación.
   */
  HRESULT
  init(Device& device, const MeshComponent& mesh, unsigned int bindFlag);

  
  /* @brief Inicializa el Constant Buffer
   * @param device Dispositivo de DirectX
   * @param ByteWidth Tamaño del Buffer
   * @return HRESULT Indica el éxito o fallo de la operación.
   */
  HRESULT
  init(Device& device, unsigned int ByteWidth);

  /* @brief Actualiza el Buffer
   * @param deviceContext Contexto de Dispositivo de DirectX
   * @param DstSubresource Subrecurso de destino
   * @param pDstBox Caja de destino
   * @param pSrcData Datos de origen
   * @param SrcRowPitch Fila de origen
   * @param SrcDepthPitch Profundidad de origen
   * @return void
   */
  void
  update(DeviceContext& deviceContext,
      unsigned int DstSubresource,
      const D3D11_BOX* pDstBox,
      const void* pSrcData,
      unsigned int SrcRowPitch,
      unsigned int SrcDepthPitch);

  /* @brief Renderiza el Buffer
   * @param deviceContext Contexto de Dispositivo de DirectX
   * @param StartSlot Ranura de inicio
   * @param NumBuffers Número de Buffers
   * @param format Formato de DXGI
   * @param setPixelShader Establecer Pixel Shader
   * @return void
   */
  void
  render(DeviceContext& deviceContext,
      unsigned int StartSlot,
      unsigned int NumBuffers,
      bool setPixelShader = false,
      DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN);

  /* @brief Destruye el Buffer
   * @return void
   */
  void
  destroy();

private:
  /* @brief Crea el Buffer
   * @param device Dispositivo de DirectX
   * @param desc Descripción del Buffer
   * @param initData Datos de Inicialización
   * @return HRESULT Indica el éxito o fallo de la operación.
   */
  HRESULT
  createBuffer(Device& device,
      D3D11_BUFFER_DESC& desc,
      D3D11_SUBRESOURCE_DATA* initData); 

private:
  ID3D11Buffer* m_buffer = nullptr; // Vertex, Index y Constant Buffers
  unsigned int m_stride = 0; // stride de los Vertex Buffers
  unsigned int m_offset = 0; // offset de los Vertex Buffers
  unsigned int m_bindFlag = 0; // bind flag de los Vertex Buffers
};