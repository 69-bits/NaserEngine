#pragma once
#include "Prerequisites.h"
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
#include "SamplerState.h"

class
BaseApp {
public:
	BaseApp() = default;
	~BaseApp() = default;

  /**
   * @brief Inicializa la aplicaci�n.
   *
   * @return HRESULT Indica el �xito o fallo de la operaci�n.
   */
	HRESULT
	init();

  void
  CleanupDevice();

  /**
   * @brief Actualiza el estado de la aplicaci�n.
   */
	void
	update();

  /**
   * @brief Renderiza el contenido de la aplicaci�n.
   */
	void
	render();

  /**
   * @brief Ejecuta la aplicaci�n.
   *
   * @param hInstance Instancia del m�dulo de la aplicaci�n.
   * @param hPrevInstance Instancia previa del m�dulo de la aplicaci�n.
   * @param lpCmdLine Puntero a la l�nea de comandos.
   * @param nCmdShow Especifica c�mo se debe mostrar la ventana.
   * @param wndproc Funci�n de procedimiento de ventana.
   * @return int Indica el �xito o fallo de la operaci�n.
   */

	int
	run(HINSTANCE hInstance,
			HINSTANCE hPrevInstance,
			LPWSTR lpCmdLine,
			int nCmdShow,
			WNDPROC wndproc);

  HRESULT
  resize(HWND hwwnd, LPARAM lparam);

  void
  InputActionMap(float DeltaTime);

  void
  updateCamera();

  void 
  rotateCamera(int mouseX, int mouseY);

public:
  Window															m_window;
  Device															m_device;
  DeviceContext												m_deviceContext;
  Swapchain														m_swapchain;
  Textura															m_backBuffer;
  Textura															m_depthStencil;
  RenderTargetView										m_renderTargetView;
  DepthStencilView										m_depthStencilView;
  Viewport														m_viewport;
  ShaderProgram												m_shaderProgram;
  Buffer                              m_vertexBuffer;
  Buffer                              m_indexBuffer;
  MeshComponent                       m_mesh;
  Buffer                              m_neverChange;
  Buffer                              m_changeOnResize;
  Buffer                              m_changesEveryFrame;
  Textura                             m_modelTexture;
  SamplerState												m_samplerState;
  Camera                              m_camera;

  XMMATRIX                            m_modelMatrix;
  XMMATRIX                            m_View;
  XMMATRIX                            m_Projection;
  XMFLOAT4                            m_vMeshColor;

  XMFLOAT3 position;
  XMFLOAT3 rotation;
  XMFLOAT3 scale;

  bool keys[256] = { false };
  float sensivility = 0.002f;
  int lastMouseX;
  int lastMouseY;
  bool mouseLeftDown = false;

  CBChangesEveryFrame cb;
  CBNeverChanges cbNeverChanges;
  CBChangeOnResize cbChangesOnResize;
  unsigned int stride = sizeof(SimpleVertex);
  unsigned int offset = 0;
};