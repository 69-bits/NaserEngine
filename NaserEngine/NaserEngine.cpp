#include "Prerequisites.h"
#include "BaseApp.h"

// Global Variables
BaseApp                              g_app;

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam); // Forward declaration para ImGui

LRESULT CALLBACK
WndProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam) {

  // Handle ImGui para que no se coman los eventos de la ventana
  if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) {
    return true;
  }
    
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_SIZE:
    g_app.resize(hWnd, lParam);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
  case WM_KEYDOWN:
    g_app.keys[wParam] = true;
    break;
  case WM_KEYUP:
    g_app.keys[wParam] = false;
    break;
  case WM_LBUTTONDOWN:
    g_app.mouseLeftDown = true;
    // Guardar la posición del mouse, asi cuando rotamos la cámara, se guarda la posición en la que se hizo click
    g_app.lastMouseX = LOWORD(lParam);
    g_app.lastMouseY = HIWORD(lParam);
    break;
  case WM_LBUTTONUP:
    g_app.mouseLeftDown = false;
    break;
  case WM_MOUSEMOVE:
    // Si ImGui está capturando el mouse, no rotar la cámara
    if (ImGui::GetIO().WantCaptureMouse) {
      g_app.mouseLeftDown = false;
    }

    if (g_app.mouseLeftDown) {
      int mouseX = LOWORD(lParam);
      int mouseY = HIWORD(lParam);
      g_app.rotateCamera(mouseX, mouseY);
    }
    break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
int WINAPI
wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
  // Inicializar la aplicación
  return g_app.run(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WndProc);
}


