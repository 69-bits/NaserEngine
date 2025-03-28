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
#include "GUI.h"
#include "ModelLoader.h"

class
  BaseApp {
public:
  BaseApp() = default;
  ~BaseApp() = default;

  /**
   * @brief Inicializa la aplicación.
   * @return HRESULT Indica el éxito o fallo de la operación.
   */
  HRESULT
  init();

  void
  CleanupDevice();

  /**
   * @brief Actualiza el estado de la aplicación.
   */
  void
  update();

  /**
   * @brief Renderiza el contenido de la aplicación.
   */
  void
  render();

  /**
   * @brief Ejecuta la aplicación.
   *
   * @param hInstance Instancia del módulo de la aplicación.
   * @param hPrevInstance Instancia previa del módulo de la aplicación.
   * @param lpCmdLine Puntero a la línea de comandos.
   * @param nCmdShow Especifica cómo se debe mostrar la ventana.
   * @param wndproc Función de procedimiento de ventana.
   * @return int Indica el éxito o fallo de la operación.
   */

  int
  run(HINSTANCE hInstance,
      HINSTANCE hPrevInstance,
      LPWSTR lpCmdLine,
      int nCmdShow,
      WNDPROC wndproc);

  /**
    * @brief Procesa los mensajes de la aplicación.
    *
    * @param hWnd Ventana de la aplicación.
    * @param message Mensaje de la aplicación.
    * @param wParam Primer parámetro del mensaje.
    * @param lParam Segundo parámetro del mensaje.
    * @return LRESULT Resultado del mensaje.
    */
  HRESULT
  resize(HWND hwwnd, LPARAM lparam);

  /**
    * @brief Procesa los mensajes de la aplicación.
    *
    * @param hWnd Ventana de la aplicación.
    * @param message Mensaje de la aplicación.
    * @param wParam Primer parámetro del mensaje.
    * @param lParam Segundo parámetro del mensaje.
    * @return LRESULT Resultado del mensaje.
    */
  void
  InputActionMap(float DeltaTime);

  /**
    * @brief Procesa los mensajes de la aplicación.
    *
    * @param hWnd Ventana de la aplicación.
    * @param message Mensaje de la aplicación.
    * @param wParam Primer parámetro del mensaje.
    * @param lParam Segundo parámetro del mensaje.
    * @return LRESULT Resultado del mensaje.
    */
  void
  updateCamera();

  /**
    * @brief Procesa los mensajes de la aplicación.
    * 
    * @param hWnd Ventana de la aplicación.
    * @param message Mensaje de la aplicación.
    * @param wParam Primer parámetro del mensaje.
    * @param lParam Segundo parámetro del mensaje.
    * @return LRESULT Resultado del mensaje.
    */
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
  GUI                                 m_gui;
  ModelLoader                         m_modelLoader;


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