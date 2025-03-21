#include "BaseApp.h"

HRESULT
BaseApp::init() {
	HRESULT hr = S_OK;

	// Create Swapchain and BackBuffer
	hr = m_swapchain.init(m_device, m_deviceContext, m_backBuffer, m_window);
	if (FAILED(hr)) {
		return hr;
	}

	// Create a render target view
	hr = m_renderTargetView.init(m_device,
		m_backBuffer,
		DXGI_FORMAT_R8G8B8A8_UNORM);

	if (FAILED(hr)) {
		return hr;
	}

	// Create a depth stencil
	hr = m_depthStencil.init(m_device,
		m_window.m_width,
		m_window.m_height,
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		D3D11_BIND_DEPTH_STENCIL,
		4,
		0);
	if (FAILED(hr))
		return hr;

	// Create the depth stencil view
	hr = m_depthStencilView.init(m_device,
		m_depthStencil,
		DXGI_FORMAT_D24_UNORM_S8_UINT);

	if (FAILED(hr))
		return hr;


	// Setup the viewport
	hr = m_viewport.init(m_window);

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
	hr = m_shaderProgram.init(m_device, "NaserEngine.fx", Layout);

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


	for (SimpleVertex vertex : vertices) {
		m_mesh.m_vertex.push_back(vertex);
	}

	for (unsigned int index : indices) {
		m_mesh.m_index.push_back(index);
	}

	m_mesh.m_numVertex = m_mesh.m_vertex.size();
	m_mesh.m_numIndex = m_mesh.m_index.size();

	hr = m_vertexBuffer.init(m_device, m_mesh, D3D11_BIND_VERTEX_BUFFER);
	if (FAILED(hr)) {
		ERROR("VertexBuffer", "Resize", "Failed to create new Buffer");
		return hr;
	}

	hr = m_indexBuffer.init(m_device, m_mesh, D3D11_BIND_INDEX_BUFFER);
	if (FAILED(hr)) {
		ERROR("IndexBuffer", "Resize", "Failed to create new Buffer");
		return hr;
	}

	// Create the constant buffers

	hr = m_neverChange.init(m_device, sizeof(CBNeverChanges));
	if (FAILED(hr)) {
		ERROR("Buffer", "init", "Failed to create new Buffer");
		return hr;
	}

	hr = m_changeOnResize.init(m_device, sizeof(CBChangeOnResize));
	if (FAILED(hr)) {
		ERROR("Buffer", "init", "Failed to create new Buffer");
		return hr;
	}

	hr = m_changesEveryFrame.init(m_device, sizeof(CBChangesEveryFrame));
	if (FAILED(hr)) {
		ERROR("Buffer", "init", "Failed to create new Buffer");
		return hr;
	}

	hr = m_modelTexture.initTexture(m_device, "seafloor.dds", DDS);
	if (FAILED(hr)) {
		ERROR("Texture", "initTexture", "Failed to create new Texture");
		return hr;
	}

	// Create the sample state

	hr = m_samplerState.init(m_device);
	if (FAILED(hr))
		return hr;

	// Initialize the world matrices
	m_modelMatrix = XMMatrixIdentity();

  scale.x = 1.0f;
  scale.y = 1.0f;
  scale.z = 1.0f;

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_View = XMMatrixLookAtLH(Eye, At, Up);

  m_gui.Init(m_window.m_hWnd, m_device.m_device, m_deviceContext.m_deviceContext);

	return S_OK;
}

void 
BaseApp::CleanupDevice() {
	if (m_deviceContext.m_deviceContext) m_deviceContext.m_deviceContext->ClearState();

	m_shaderProgram.destroy();

	m_depthStencil.destroy();
	m_depthStencilView.destroy();
	m_renderTargetView.destroy();
	m_swapchain.destroy();
	m_deviceContext.destroy();
	m_device.destroy();
	m_samplerState.destroy();
  m_gui.destroy();
}


void
BaseApp::update() {

  m_gui.update();

	ImGui::SetNextWindowSize(ImVec2(400.0f, 300.0f)); // Tamaño inicial de la ventana (ancho, alto)
	ImGui::Begin("Mi Ventana");
	ImGui::Text("Holaaaaaa");
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(400.0f, 300.0f)); // Tamaño inicial de la ventana (ancho, alto)
	ImGui::Begin("Mi Ventana 2");
	ImGui::Text("Adiosssss");
	ImGui::End();

	m_gui.transformWindow();

	// Actualizar tiempo y rotaci�n
	static float t = 0.0f;
	if (m_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE) {
		t += (float)XM_PI * 0.0125f;
	}
	else {
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

  InputActionMap(t);

	// Actualizar la rotaci�n del objeto y el color
	m_vMeshColor = XMFLOAT4(
		(sinf(t * 1.0f) + 1.0f) * 0.5f,
		(cosf(t * 3.0f) + 1.0f) * 0.5f,
		(sinf(t * 5.0f) + 1.0f) * 0.5f,
		1.0f
	);


  XMMATRIX scaleMatrix = XMMatrixScaling(scale.x, scale.y, scale.z);
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
  XMMATRIX translationMatrix = XMMatrixTranslation(position.x, position.y, position.z);

  // Componer la matriz final en el orden: Escala * Rotacion * Traslacion
  m_modelMatrix = scaleMatrix * rotationMatrix * translationMatrix;


	// Actualizar el buffer constante del frame
	cb.mWorld = XMMatrixTranspose(m_modelMatrix);
	cb.vMeshColor = m_vMeshColor;
	//g_deviceContext.UpdateSubresource(g_pCBChangesEveryFrame, 0, nullptr, &cb, 0, 0);

	m_changesEveryFrame.update(m_deviceContext, 0, nullptr, &cb, 0, 0);



	// Actualizar la matriz de proyecci�n
  float FOV = XMConvertToRadians(90.0f);
	m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, m_window.m_width / (float)m_window.m_height, 0.01f, 100.0f);

	// Actualizar la vista (si es necesario cambiar din�micamente)
	/*cbNeverChanges.mView = XMMatrixTranspose(m_View);

	m_neverChange.update(m_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);*/

	updateCamera();

	//g_deviceContext.UpdateSubresource(g_pCBNeverChanges, 0, nullptr, &cbNeverChanges, 0, 0);

	// Actualizar la proyecci�n en el buffer constante
	cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
	m_changeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);
	//g_deviceContext.UpdateSubresource(g_pCBChangeOnResize, 0, nullptr, &cbChangesOnResize, 0, 0);
}

void
BaseApp::render() {
	// Limpiar los buffers
	const float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha

	// Set Render Target View
	m_renderTargetView.render(m_deviceContext, m_depthStencilView, 1, ClearColor);

	// Set Viewport
	m_viewport.render(m_deviceContext);

	// Set Depth Stencil View
	m_depthStencilView.render(m_deviceContext);

	// Configurar los buffers y shaders para el pipeline
	m_shaderProgram.render(m_deviceContext);

	/*g_deviceContext.IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);
	g_deviceContext.IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);*/

	m_vertexBuffer.render(m_deviceContext, 0, 1);
	m_indexBuffer.render(m_deviceContext, 0, 1, DXGI_FORMAT_R32_UINT);

	m_deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Asignar shaders y buffers constantes
	/*g_deviceContext.VSSetConstantBuffers(0, 1, &g_pCBNeverChanges);
	g_deviceContext.VSSetConstantBuffers(1, 1, &g_pCBChangeOnResize);
	g_deviceContext.VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);*/

	m_neverChange.render(m_deviceContext, 0, 1);
	m_changeOnResize.render(m_deviceContext, 1, 1);
	m_changesEveryFrame.render(m_deviceContext, 2, 1);

	m_modelTexture.render(m_deviceContext, 0, 1);

	//g_deviceContext.PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
	m_changesEveryFrame.render(m_deviceContext, 2, 1, DXGI_FORMAT_UNKNOWN, true);
	//g_deviceContext.PSSetShaderResources(0, 1, &g_pTextureRV);
	//g_deviceContext.PSSetSamplers(0, 1, &g_samplerState.m_samplerState);
  m_samplerState.render(m_deviceContext, 0, 1);

	// Dibujar
	m_deviceContext.DrawIndexed(36, 0, 0);
	m_gui.render();
	// Presentar el frame en pantalla
	m_swapchain.present();

  
}


int
BaseApp::run(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPWSTR lpCmdLine,
  int nCmdShow,
  WNDPROC wndproc) {

  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  if (FAILED(m_window.init(hInstance, nCmdShow, wndproc)))
    return 0;

  if (FAILED(init())) {
		CleanupDevice();
		return 0;
	}


  // Main message loop
  MSG msg = { 0 };
  while (WM_QUIT != msg.message) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else {
      update();
      render();
    }
  }

	CleanupDevice();

  return (int)msg.wParam;

}

HRESULT 
BaseApp::resize(HWND hwwnd, LPARAM lparam) {
	if (m_swapchain.m_swapchain) {

		m_renderTargetView.destroy();
		m_depthStencil.destroy();
		m_depthStencilView.destroy();
		m_backBuffer.destroy();
		m_window.m_width = LOWORD(lparam);
		m_window.m_height = HIWORD(lparam);

		HRESULT hr = m_swapchain.m_swapchain->ResizeBuffers(0, m_window.m_width, m_window.m_height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
		if (FAILED(hr)) {
			ERROR("SwapChain", "Resize", "Failed to resize the SwapChain buffers");
			return hr;
		}

		hr = m_swapchain.m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_backBuffer.m_Texture));
		if (FAILED(hr)) {
			ERROR("SwapChain", "Resize", "Failed to get new back buffer");
		}

		hr = m_renderTargetView.init(m_device, m_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);
		if (FAILED(hr)) {
			ERROR("RenderTargetView", "Resize", "Failed to create new RenderTargetView");
			return hr;
		}

		hr = m_depthStencil.init(m_device, m_window.m_width, m_window.m_height, DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_DEPTH_STENCIL, 4, 0);
		if (FAILED(hr)) {
			ERROR("DepthStencil", "Resize", "Failed to create new DepthStencil");
			return hr;
		}

		hr = m_depthStencilView.init(m_device, m_depthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT);
		if (FAILED(hr)) {
			ERROR("DepthStencilView", "Resize", "Failed to create new DepthStencilView");
			return hr;
		}

		hr = m_viewport.init(m_window);
		if (FAILED(hr)) {
			ERROR("Viewport", "Resize", "Failed to create new Viewport");
			return hr;
		}

		m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, m_window.m_width / (float)m_window.m_height, 0.01f, 100.0f);
		cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
    m_changeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);
	}
}

void 
BaseApp::InputActionMap(float DeltaTime) {
	float Sensibility = 0.001f;
	float moveSpeedCamera = 0.01f;
	if (keys['W']) {
    position.y += Sensibility * DeltaTime;
  }
	if (keys['S']) {
		position.y -= Sensibility * DeltaTime;
	}
  if (keys['A']) {
    position.x -= Sensibility * DeltaTime;
  }
  if (keys['D']) {
    position.x += Sensibility * DeltaTime;
  }
  if (keys['Q']) {
    position.z -= Sensibility * DeltaTime;
  }
  if (keys['E']) {
    position.z += Sensibility * DeltaTime;
  }

	XMVECTOR pos = XMLoadFloat3(&m_camera.position);
	XMVECTOR forward = XMLoadFloat3(&m_camera.forward);
	XMVECTOR right = XMLoadFloat3(&m_camera.right);

	if (keys['W']) {
		pos += forward * moveSpeedCamera;
	}
	if (keys['S']) {
		pos -= forward * moveSpeedCamera;
	}
	if (keys['A']) {
		pos -= right * moveSpeedCamera;
	}
	if (keys['D']) {
		pos += right * moveSpeedCamera;
	}


  XMStoreFloat3(&m_camera.position, pos);

}

void 
BaseApp::updateCamera() {
  // Normalizar el vector de dirección
  XMVECTOR pos = XMLoadFloat3(&m_camera.position);
  XMVECTOR dir = XMLoadFloat3(&m_camera.forward);
  XMVECTOR up = XMLoadFloat3(&m_camera.up);

  // Calcular la matriz de vista
	m_View = XMMatrixLookAtLH(pos, pos + dir, up);

  cbNeverChanges.mView = XMMatrixTranspose(m_View);
  m_neverChange.update(m_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
}

void 
BaseApp::rotateCamera(int mouseX, int mouseY) {
  float offsetX = (mouseX - lastMouseX) * sensivility;
  float offsetY = (mouseY - lastMouseY) * sensivility;
  lastMouseX = mouseX;
  lastMouseY = mouseY;

	m_camera.yaw += offsetX;
	m_camera.pitch += offsetY;

  //Limitar la inclinación de la cámara

	if (m_camera.pitch > 1.5f) m_camera.pitch = 1.5f;
	if (m_camera.pitch < -1.5f) m_camera.pitch = -1.5f;

  XMVECTOR forward = XMVectorSet(
    cosf(m_camera.yaw) * cosf(m_camera.pitch),
    sinf(m_camera.pitch),
    sinf(m_camera.yaw) * cosf(m_camera.pitch),
    0.0f
  );

  XMVECTOR right = XMVector3Cross(forward, XMLoadFloat3(&m_camera.up));

  XMStoreFloat3(&m_camera.forward, XMVector3Normalize(forward));
  XMStoreFloat3(&m_camera.right, XMVector3Normalize(right));
}
