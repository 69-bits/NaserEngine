﻿#include "Prerequisites.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Swapchain.h"
#include "Textura.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "MeshComponent.h"

// Global Variables
Window															g_window;
Device															g_device;
DeviceContext												g_deviceContext;
Swapchain														g_swapchain;
Textura															g_backBuffer;
Textura															g_depthStencil;
RenderTargetView										g_renderTargetView;
DepthStencilView										g_depthStencilView;
Viewport														g_viewport;
ShaderProgram												g_shaderProgram;
Buffer                              g_vertexBuffer;
Buffer                              g_indexBuffer;
MeshComponent                       g_mesh;
Buffer                              g_neverChange;
Buffer                              g_changeOnResize;
Buffer                              g_changesEveryFrame;

ID3D11Buffer* g_pVertexBuffer = nullptr;
ID3D11Buffer* g_pIndexBuffer = nullptr;
ID3D11Buffer* g_pCBNeverChanges = nullptr;
ID3D11Buffer* g_pCBChangeOnResize = nullptr;
ID3D11Buffer* g_pCBChangesEveryFrame = nullptr;
ID3D11ShaderResourceView* g_pTextureRV = nullptr;
ID3D11SamplerState* g_pSamplerLinear = nullptr;

XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);

CBChangesEveryFrame cb;
CBNeverChanges cbNeverChanges;
CBChangeOnResize cbChangesOnResize;
unsigned int stride = sizeof(SimpleVertex);
unsigned int offset = 0;
//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc(HWND, unsigned int, WPARAM, LPARAM);
void update();
void Render();


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI
wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (FAILED(g_window.init(hInstance, nCmdShow, WndProc)))
		return 0;

	if (FAILED(InitDevice())) {
		CleanupDevice();
		return 0;
	}

	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			update();
			Render();
		}
	}

	CleanupDevice();

	return (int)msg.wParam;
}

//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT
InitDevice() {
	HRESULT hr = S_OK;

	// Create Swapchain and BackBuffer
	hr = g_swapchain.init(g_device, g_deviceContext, g_backBuffer, g_window);
	if (FAILED(hr)) {
		return hr;
	}

	// Create a render target view
	hr = g_renderTargetView.init(g_device,
		g_backBuffer,
		DXGI_FORMAT_R8G8B8A8_UNORM);

	if (FAILED(hr)) {
		return hr;
	}

	// Create a depth stencil
	hr = g_depthStencil.init(g_device,
		g_window.m_width,
		g_window.m_height,
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		D3D11_BIND_DEPTH_STENCIL,
		4,
		0);
	if (FAILED(hr))
		return hr;

	// Create the depth stencil view
	hr = g_depthStencilView.init(g_device,
		g_depthStencil,
		DXGI_FORMAT_D24_UNORM_S8_UINT);

	if (FAILED(hr))
		return hr;


	// Setup the viewport
	hr = g_viewport.init(g_window);

	if (FAILED(hr))
		return hr;

	// Define the input layout
	std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

	D3D11_INPUT_ELEMENT_DESC position;
	position.SemanticName = "POSITION";
	position.SemanticIndex = 0;
	position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	position.InputSlot = 0;
	position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*0*/;
	position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	position.InstanceDataStepRate = 0;
	Layout.push_back(position);

	D3D11_INPUT_ELEMENT_DESC texcoord;
	texcoord.SemanticName = "TEXCOORD";
	texcoord.SemanticIndex = 0;
	texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
	texcoord.InputSlot = 0;
	texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
	texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	texcoord.InstanceDataStepRate = 0;
	Layout.push_back(texcoord);

	// Create the Shader Program
	hr = g_shaderProgram.init(g_device, "NaserEngine.fx", Layout);

	if (FAILED(hr))
		return hr;

	// Create vertex buffer
	SimpleVertex
		vertices[] = {
				{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

				{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

				{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

				{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

				{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },

				{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
	};

	/*D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	hr = g_device.CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
	if (FAILED(hr))
		return hr;*/

	// Create vertex buffer
	WORD
		indices[] = {
				3,1,0,
				2,1,3,

				6,4,5,
				7,4,6,

				11,9,8,
				10,9,11,

				14,12,13,
				15,12,14,

				19,17,16,
				18,17,19,

				22,20,21,
				23,20,22
	};

	/*bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 36;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;
	hr = g_device.CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
	if (FAILED(hr))
		return hr;*/

	for (SimpleVertex vertex : vertices) {
    g_mesh.m_vertex.push_back(vertex);
	}

	for (unsigned int index : indices) {
    g_mesh.m_index.push_back(index);
	}

  g_mesh.m_numVertex = g_mesh.m_vertex.size();
  g_mesh.m_numIndex = g_mesh.m_index.size();

	hr = g_vertexBuffer.init(g_device, g_mesh, D3D11_BIND_VERTEX_BUFFER);
	if (FAILED(hr)) {
		ERROR("VertexBuffer", "Resize", "Failed to create new Buffer");
		return hr;
	}

	hr = g_indexBuffer.init(g_device, g_mesh, D3D11_BIND_INDEX_BUFFER);
	if (FAILED(hr)) {
		ERROR("IndexBuffer", "Resize", "Failed to create new Buffer");
		return hr;
	}

	// Create the constant buffers

	/*bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CBNeverChanges);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = g_device.CreateBuffer(&bd, nullptr, &g_pCBNeverChanges);
	if (FAILED(hr))
		return hr;*/

  hr = g_neverChange.init(g_device, sizeof(CBNeverChanges));
  if (FAILED(hr)) {
    ERROR("Buffer", "init", "Failed to create new Buffer");
    return hr;
  }

  hr = g_changeOnResize.init(g_device, sizeof(CBChangeOnResize));
  if (FAILED(hr)) {
    ERROR("Buffer", "init", "Failed to create new Buffer");
    return hr;
  }

  hr = g_changesEveryFrame.init(g_device, sizeof(CBChangesEveryFrame));
  if (FAILED(hr)) {
    ERROR("Buffer", "init", "Failed to create new Buffer");
    return hr;
  }

	/*bd.ByteWidth = sizeof(CBChangeOnResize);
	hr = g_device.CreateBuffer(&bd, nullptr, &g_pCBChangeOnResize);
	if (FAILED(hr))
		return hr;

	bd.ByteWidth = sizeof(CBChangesEveryFrame);
	hr = g_device.CreateBuffer(&bd, nullptr, &g_pCBChangesEveryFrame);
	if (FAILED(hr))
		return hr;*/

	// Load the Texture
	hr = D3DX11CreateShaderResourceViewFromFile(g_device.m_device, "seafloor.dds", nullptr, nullptr, &g_pTextureRV, nullptr);
	if (FAILED(hr))
		return hr;

	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = g_device.CreateSamplerState(&sampDesc, &g_pSamplerLinear);
	if (FAILED(hr))
		return hr;

	// Initialize the world matrices
	g_World = XMMatrixIdentity();

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	g_View = XMMatrixLookAtLH(Eye, At, Up);



	return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void
CleanupDevice() {
	if (g_deviceContext.m_deviceContext) g_deviceContext.m_deviceContext->ClearState();

	if (g_pSamplerLinear) g_pSamplerLinear->Release();
	if (g_pTextureRV) g_pTextureRV->Release();
	if (g_pCBNeverChanges) g_pCBNeverChanges->Release();
	if (g_pCBChangeOnResize) g_pCBChangeOnResize->Release();
	if (g_pCBChangesEveryFrame) g_pCBChangesEveryFrame->Release();
	if (g_pVertexBuffer) g_pVertexBuffer->Release();
	if (g_pIndexBuffer) g_pIndexBuffer->Release();

	g_shaderProgram.destroy();

	g_depthStencil.destroy();
	g_depthStencilView.destroy();
	g_renderTargetView.destroy();
	g_swapchain.destroy();
	g_deviceContext.destroy();
	g_device.destroy();
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK
WndProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_SIZE:
		if (g_swapchain.m_swapchain) {
			g_window.m_width = LOWORD(lParam);
			g_window.m_height = HIWORD(lParam);

			// Libera los recursos existentes
			g_renderTargetView.destroy();
			g_depthStencilView.destroy();
			g_depthStencil.destroy();
			g_backBuffer.destroy();

			// Redimensionar el swap chain
			HRESULT hr = g_swapchain.m_swapchain->ResizeBuffers(0,
				g_window.m_width,
				g_window.m_height,
				DXGI_FORMAT_R8G8B8A8_UNORM,
				0);
			if (FAILED(hr)) {
				MessageBox(hWnd, "Failed to resize swap chain buffers.", "Error", MB_OK);
				PostQuitMessage(0);
			}

			// **3. RECREAR EL BACK BUFFER**
			hr = g_swapchain.m_swapchain->GetBuffer(0,
				__uuidof(ID3D11Texture2D),
				reinterpret_cast<void**>(&g_backBuffer.m_Texture));
			if (FAILED(hr)) {
				ERROR("SwapChain", "Resize", "Failed to get new back buffer");
				return hr;
			}

			// **4. RECREAR EL RENDER TARGET VIEW**
			hr = g_renderTargetView.init(g_device,
				g_backBuffer,
				DXGI_FORMAT_R8G8B8A8_UNORM);
			if (FAILED(hr)) {
				ERROR("RenderTargetView", "Resize", "Failed to create new RenderTargetView");
				return hr;
			}

			// **5. RECREAR EL DEPTH STENCIL VIEW**
			hr = g_depthStencil.init(g_device,
				g_window.m_width,
				g_window.m_height,
				DXGI_FORMAT_D24_UNORM_S8_UINT,
				D3D11_BIND_DEPTH_STENCIL,
				4,
				0);
			if (FAILED(hr)) {
				ERROR("DepthStencil", "Resize", "Failed to create new DepthStencil");
				return hr;
			}

			hr = g_depthStencilView.init(g_device,
				g_depthStencil,
				DXGI_FORMAT_D24_UNORM_S8_UINT);
			if (FAILED(hr)) {
				ERROR("DepthStencilView", "Resize", "Failed to create new DepthStencilView");
				return hr;
			}

			// Actualizar el viewport
			hr = g_viewport.init(g_window);

			if (FAILED(hr)) {
				ERROR("Viewport", "Resize", "Failed to create new Viewport");
				return hr;
			}

			// Actualizar la proyecci�n
			g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, g_window.m_width / (float)g_window.m_height, 0.01f, 100.0f);
			CBChangeOnResize cbChangesOnResize;
			cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
			g_deviceContext.UpdateSubresource(g_pCBChangeOnResize, 0, nullptr, &cbChangesOnResize, 0, 0);
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


//--------------------------------------------------------------------------------------
// Update frame-specific variables
//--------------------------------------------------------------------------------------
void update() {
	// Actualizar tiempo y rotaci�n
	static float t = 0.0f;
	if (g_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE) {
		t += (float)XM_PI * 0.0125f;
	}
	else {
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

	// Actualizar la rotaci�n del objeto y el color
	g_World = XMMatrixRotationY(t);
	g_vMeshColor = XMFLOAT4(
		(sinf(t * 1.0f) + 1.0f) * 0.5f,
		(cosf(t * 3.0f) + 1.0f) * 0.5f,
		(sinf(t * 5.0f) + 1.0f) * 0.5f,
		1.0f
	);

	// Actualizar el buffer constante del frame
	cb.mWorld = XMMatrixTranspose(g_World);
	cb.vMeshColor = g_vMeshColor;
	//g_deviceContext.UpdateSubresource(g_pCBChangesEveryFrame, 0, nullptr, &cb, 0, 0);

	g_changesEveryFrame.update(g_deviceContext, 0, nullptr, &cb, 0, 0);



	// Actualizar la matriz de proyecci�n
	g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, g_window.m_width / (float)g_window.m_height, 0.01f, 100.0f);

	// Actualizar la vista (si es necesario cambiar din�micamente)
	cbNeverChanges.mView = XMMatrixTranspose(g_View);
	
	g_neverChange.update(g_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
	//g_deviceContext.UpdateSubresource(g_pCBNeverChanges, 0, nullptr, &cbNeverChanges, 0, 0);

	// Actualizar la proyecci�n en el buffer constante
	cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
  g_changeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);
	//g_deviceContext.UpdateSubresource(g_pCBChangeOnResize, 0, nullptr, &cbChangesOnResize, 0, 0);
}

//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render() {
	// Limpiar los buffers
	const float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha

	// Set Render Target View
	g_renderTargetView.render(g_deviceContext, g_depthStencilView, 1, ClearColor);

	// Set Viewport
	g_viewport.render(g_deviceContext);

	// Set Depth Stencil View
	g_depthStencilView.render(g_deviceContext);

	// Configurar los buffers y shaders para el pipeline
	g_shaderProgram.render(g_deviceContext);

	/*g_deviceContext.IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);
	g_deviceContext.IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);*/

	g_vertexBuffer.render(g_deviceContext, 0, 1);
	g_indexBuffer.render(g_deviceContext, 0, 1, DXGI_FORMAT_R32_UINT);

	g_deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Asignar shaders y buffers constantes
	/*g_deviceContext.VSSetConstantBuffers(0, 1, &g_pCBNeverChanges);
	g_deviceContext.VSSetConstantBuffers(1, 1, &g_pCBChangeOnResize);
	g_deviceContext.VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);*/

	g_neverChange.render(g_deviceContext, 0, 1);
  g_changeOnResize.render(g_deviceContext, 1, 1);
  g_changesEveryFrame.render(g_deviceContext, 2, 1);

	//g_deviceContext.PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
  g_changesEveryFrame.render(g_deviceContext, 2, 1, DXGI_FORMAT_UNKNOWN, true);
	g_deviceContext.PSSetShaderResources(0, 1, &g_pTextureRV);
	g_deviceContext.PSSetSamplers(0, 1, &g_pSamplerLinear);

	// Dibujar
	g_deviceContext.DrawIndexed(36, 0, 0);

	// Presentar el frame en pantalla
	g_swapchain.present();
}