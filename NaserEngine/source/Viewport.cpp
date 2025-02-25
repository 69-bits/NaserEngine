#include "Viewport.h"
#include "Window.h"
#include "DeviceContext.h"

HRESULT 
Viewport::init(const Window& window) {
  // Checa si la ventana está inicializada
	if (window.m_hWnd == nullptr) {
		ERROR("Viewport", "init", "Window is not initialized. // Oopsie Viewport╰(*°▽°*)╯");
	}

  // Configura el viewport
	m_viewport.Width = static_cast<float>(window.m_width);
	m_viewport.Height = static_cast<float>(window.m_height);
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;
}

HRESULT 
Viewport::init(unsigned int width, unsigned int height)
{
	// Checa si la ventana está inicializada
	if (width == 0 || height == 0) {
    ERROR("Viewport", "init", "Invalid width or height. // Oopsie Viewport╰(*°▽°*)╯");
	}

	// Configura el viewport
	m_viewport.Width = static_cast<float>(width);
	m_viewport.Height = static_cast<float>(height);
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;
}

void 
Viewport::update() {
}

void 
Viewport::render(DeviceContext& deviceContext) {
  // Establece el viewport
	deviceContext.RSSetViewports(1, &m_viewport);
}

void 
Viewport::destroy() {
}
