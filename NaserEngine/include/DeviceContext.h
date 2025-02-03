#pragma once
#include "PreRequisites.h"
class
DeviceContext {
public:
	DeviceContext() = default;
	~DeviceContext() = default;
	/**
		 * @brief Inicializa el contexto del dispositivo.
		 */
	void
	init();

	/**
		 * @brief Actualiza el estado del contexto del dispositivo.
		 */
	void
	update();

	/**
		 * @brief Renderiza el contenido utilizando el contexto del dispositivo.
		 */
	void
	render();

	/**
		 * @brief Destruye el contexto del dispositivo y libera los recursos asociados.
		 */
	void
	destroy();

	/**
		* @brief Establece los viewports.
		*
		* @param NumViewports N�mero de viewports.
		* @param pViewports Puntero a los viewports.
		*/
	void
	RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports);

  /**
    * @brief Establece los recursos de sombreador.
    *
    * @param StartSlot �ndice del primer slot.
    * @param NumViews N�mero de vistas.
    * @param ppShaderResourceViews Puntero a las vistas de recursos de sombreador.
    */
	void
	PSSetShaderResources(unsigned int StartSlot,
			unsigned int NumViews,
			ID3D11ShaderResourceView* const* ppShaderResourceViews);

  /**
    * @brief Establece el sombreador de v�rtices.
    *
    * @param pVertexShader Puntero al sombreador de v�rtices.
    * @param ppClassInstances Puntero a las instancias de clase.
    * @param NumClassInstances N�mero de instancias de clase.
    */
	void
	IASetInputLayout(ID3D11InputLayout* pInputLayout);

  /**
    * @brief Establece el sombreador de v�rtices.
    *
    * @param pVertexShader Puntero al sombreador de v�rtices.
    * @param ppClassInstances Puntero a las instancias de clase.
    * @param NumClassInstances N�mero de instancias de clase.
    */
	void
	VSSetShader(ID3D11VertexShader* pVertexShader,
			ID3D11ClassInstance* const* ppClassInstances,
			unsigned int NumClassInstances);

  /**
    * @brief Establece el sombreador de p�xeles.
    *
    * @param pPixelShader Puntero al sombreador de p�xeles.
    * @param ppClassInstances Puntero a las instancias de clase.
    * @param NumClassInstances N�mero de instancias de clase.
    */
	void
	PSSetShader(ID3D11PixelShader* pPixelShader,
			ID3D11ClassInstance* const* ppClassInstances,
			unsigned int NumClassInstances);

  /**
    * @brief Crea una vista de recurso de destino de representaci�n.
    *
    * @param pResource Puntero al recurso.
    * @param pDesc Puntero a la descripci�n de la vista de recurso de destino de representaci�n.
    * @param ppRTView Puntero a la vista de recurso de destino de representaci�n.
    */
	void
	UpdateSubresource(ID3D11Resource* pDstResource,
			unsigned int DstSubresource,
			const D3D11_BOX* pDstBox,
			const void* pSrcData,
			unsigned int SrcRowPitch,
			unsigned int SrcDepthPitch);

  /**
    * @brief Establece los buffers de v�rtices.
    *
    * @param StartSlot �ndice del primer slot.
    * @param NumBuffers N�mero de buffers.
    * @param ppVertexBuffers Puntero a los buffers de v�rtices.
    * @param pStrides Puntero a los desplazamientos.
    * @param pOffsets Puntero a los desplazamientos.
    */
	void
	IASetVertexBuffers(unsigned int StartSlot,
			unsigned int NumBuffers,
			ID3D11Buffer* const* ppVertexBuffers,
			const unsigned int* pStrides,
			const unsigned int* pOffsets);

  /**
    * @brief Establece el buffer de �ndices.
    *
    * @param pIndexBuffer Puntero al buffer de �ndices.
    * @param Format Formato de los �ndices.
    * @param Offset Desplazamiento.
    */
	void
	IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
			DXGI_FORMAT Format,
			unsigned int Offset);

  /**
    * @brief Establece los recursos de sombreador.
    *
    * @param StartSlot �ndice del primer slot.
    * @param NumViews N�mero de vistas.
    * @param ppShaderResourceViews Puntero a las vistas de recursos de sombreador.
    */
	void
	PSSetSamplers(unsigned int StartSlot,
			unsigned int NumSamplers,
			ID3D11SamplerState* const* ppSamplers);

  /**
    * @brief Establece el estado de rasterizaci�n.
    *
    * @param pRasterizerState Puntero al estado de rasterizaci�n.
    */
	void
	RSSetState(ID3D11RasterizerState* pRasterizerState);

  /**
  * @brief Establece el estado de mezcla.
  *
  * @param pBlendState Puntero al estado de mezcla.
  * @param BlendFactor Factor de mezcla.
  * @param SampleMask M�scara de muestra.
  */
	void
	OMSetBlendState(ID3D11BlendState* pBlendState,
			const float BlendFactor[4],
			unsigned int SampleMask);

  /**
    * @brief Establece los objetivos de representaci�n.
    *
    * @param NumViews N�mero de vistas.
    * @param ppRenderTargetViews Puntero a las vistas de destino de representaci�n.
    * @param pDepthStencilView Puntero a la vista de destino de representaci�n de profundidad.
    */
	void
	OMSetRenderTargets(unsigned int NumViews,
			ID3D11RenderTargetView* const* ppRenderTargetViews,
			ID3D11DepthStencilView* pDepthStencilView);

  /**
    * @brief Establece la topolog�a primitiva.
    *
    * @param Topology Topolog�a primitiva.
    */
	void
	IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);

  /**
    * @brief Limpia la vista de destino de representaci�n.
    *
    * @param pRenderTargetView Puntero a la vista de destino de representaci�n.
    * @param ColorRGBA Color RGBA.
    */
	void
	ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
			const float ColorRGBA[4]);

  /**
    * @brief Limpia la vista de destino de representaci�n de profundidad y estencil.
    *
    * @param pDepthStencilView Puntero a la vista de destino de representaci�n de profundidad y estencil.
    * @param ClearFlags Banderas de limpieza.
    * @param Depth Profundidad.
    * @param Stencil Stencil.
    */
	void
	ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
			unsigned int ClearFlags,
			float Depth,
			UINT8 Stencil);

  /**
    * @brief Establece los buffers de constantes.
    *
    * @param StartSlot �ndice del primer slot.
    * @param NumBuffers N�mero de buffers.
    * @param ppConstantBuffers Puntero a los buffers de constantes.
    */
	void
	VSSetConstantBuffers(unsigned int StartSlot,
			unsigned int NumBuffers,
			ID3D11Buffer* const* ppConstantBuffers);

  /**
    * @brief Establece los buffers de constantes.
    *
    * @param StartSlot �ndice del primer slot.
    * @param NumBuffers N�mero de buffers.
    * @param ppConstantBuffers Puntero a los buffers de constantes.
    */
	void
	PSSetConstantBuffers(unsigned int StartSlot,
			unsigned int NumBuffers,
			ID3D11Buffer* const* ppConstantBuffers);

  /**
    * @brief Dibuja instancias.
    *
    * @param VertexCount N�mero de v�rtices.
    * @param StartVertexLocation Localizaci�n del primer v�rtice.
    */
	void
	DrawIndexed(unsigned int IndexCount,
			unsigned int StartIndexLocation,
			int BaseVertexLocation);

public:
  ID3D11DeviceContext* m_deviceContext = nullptr; ///< Contexto del dispositivo.
};