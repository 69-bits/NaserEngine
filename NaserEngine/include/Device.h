#pragma once
#include "Prerequisites.h"
class
Device {
public:
  Device() = default;
  ~Device() = default;

  /**
   * @brief Inicializa el dispositivo.
   */
  void
  init();

  /**
   * @brief Actualiza el estado del dispositivo.
   */
  void
  update();

  /**
   * @brief Renderiza el contenido utilizando el dispositivo.
   */
  void
  render();

  /**
   * @brief Destruye el dispositivo y libera los recursos asociados.
   */
  void
  destroy();

  /**
  * @brief Crea el render target view.
  * @param pResource Recurso.
  * @param pDesc Descripción del render target view.
  * @param ppRTView Puntero al render target view.
  * @return HRESULT Indica el éxito o fallo de la operación.
  */
  HRESULT
  CreateRenderTargetView(ID3D11Resource* pResource,
      const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
      ID3D11RenderTargetView** ppRTView);

  /**
  * @brief Crea una textura 2D.
  * @param pDesc Descripción de la textura.
  * @param pInitialData Datos iniciales.
  * @param ppTexture2D Puntero a la textura.
  * @return HRESULT Indica el éxito o fallo de la operación.
  */
  HRESULT
  CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
      const D3D11_SUBRESOURCE_DATA* pInitialData,
      ID3D11Texture2D** ppTexture2D);

  /**
  * @brief Crea la vista de profundidad y stencil.
  * @param pResource Recurso.
  * @param pDesc Descripción de la vista de profundidad y stencil.
  * @param ppDepthStencilView Puntero a la vista de profundidad y stencil.
  * @return HRESULT Indica el éxito o fallo de la operación.
  */
  HRESULT
  CreateDepthStencilView(ID3D11Resource* pResource,
      const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
      ID3D11DepthStencilView** ppDepthStencilView);

  /**
  * @brief Crea el sombreador de vértices.
  * @param pShaderBytecode Código de sombreador.
  * @param BytecodeLength Longitud del código de sombreador.
  * @param pClassLinkage Vinculación de clases.
  * @param ppVertexShader Puntero al sombreador de vértices.
  * @return HRESULT Indica el éxito o fallo de la operación.
  */
  HRESULT
  CreateVertexShader(const void* pShaderBytecode,
      unsigned int BytecodeLength,
      ID3D11ClassLinkage* pClassLinkage,
      ID3D11VertexShader** ppVertexShader);

  /**
  * @brief Crea el input layout.
  * @param pInputElementDescs Descripción de los elementos de entrada.
  * @param NumElements Número de elementos.
  * @param pShaderBytecodeWithInputSignature Código de sombreador con firma de entrada.
  * @param BytecodeLength Longitud del código de sombreador.
  * @param ppInputLayout Puntero al input layout.
  * @return HRESULT Indica el éxito o fallo de la operación.
  */
  HRESULT
  CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
      unsigned int NumElements,
      const void* pShaderBytecodeWithInputSignature,
      unsigned int BytecodeLength,
      ID3D11InputLayout** ppInputLayout);

  /**
  * @brief Crea el sombreador de píxeles.
  * @param pShaderBytecode Código de sombreador.
  * @param BytecodeLength Longitud del código de sombreador.
  * @param pClassLinkage Vinculación de clases.
  * @param ppPixelShader Puntero al sombreador de píxeles.
  * @return HRESULT Indica el éxito o fallo de la operación.
  */
  HRESULT
  CreatePixelShader(const void* pShaderBytecode,
      unsigned int BytecodeLength,
      ID3D11ClassLinkage* pClassLinkage,
      ID3D11PixelShader** ppPixelShader);

  /**
  * @brief Crea el buffer.
  * @param pDesc Descripción del buffer.
  * @param pInitialData Datos iniciales.
  * @param ppBuffer Puntero al buffer.
  * @return HRESULT Indica el éxito o fallo de la operación.
  */
  HRESULT
  CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
      const D3D11_SUBRESOURCE_DATA* pInitialData,
      ID3D11Buffer** ppBuffer);

  /**
  * @brief Crea el sampler state.
  * @param pSamplerDesc Descripción del sampler state.
  * @param ppSamplerState Puntero al sampler state.
  * @return HRESULT Indica el éxito o fallo de la operación.
  */
  HRESULT
  CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
      ID3D11SamplerState** ppSamplerState);

  /**
  * @brief Crea el rasterizer state.
  * @param pRasterizerDesc Descripción del rasterizer state.
  * @param ppRasterizerState Puntero al rasterizer state.
  * @return HRESULT Indica el éxito o fallo de la operación.
  */
  HRESULT
  CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc,
      ID3D11RasterizerState** ppRasterizerState);

  /**
  * @brief Crea el depth stencil state.
  * @param pDepthStencilDesc Descripción del depth stencil state.
  * @param ppDepthStencilState Puntero al depth stencil state.
  * @return HRESULT Indica el éxito o fallo de la operación.
  */
  HRESULT
  CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc,
      ID3D11BlendState** ppBlendState);
public:
  ID3D11Device* m_device = nullptr; ///< Dispositivo.
};