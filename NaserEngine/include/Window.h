#pragma once
#include "Prerequisites.h"

class
Window {
public:
	Window() = default;
	~Window() = default;
	/**
		 * @brief Inicializa la ventana con los parámetros especificados.
		 *
		 * @param hInstance Instancia del módulo de la aplicación.
		 * @param nCmdShow Especifica cómo se debe mostrar la ventana.
		 * @param wndproc Función de procedimiento de ventana.
		 * @return HRESULT Indica el éxito o fallo de la operación.
		 */
	HRESULT
	init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

  /* @brief Actualiza el estado de la ventana.
  * @return void
	*/
	void
	update();
	/**
		 * @brief Renderiza el contenido de la ventana.
		 */
	void
	render();
	/**
		 * @brief Destruye la ventana y libera los recursos asociados.
		 */
	void
	destroy();

public:
	HINSTANCE m_hInst = nullptr;  ///< Instancia del módulo de la aplicación
	HWND m_hWnd = nullptr; ///< Handle de la ventana.
	unsigned int m_width; ///< Ancho de la ventana.
	unsigned int m_height;///< Ancho de la ventana.
	RECT m_rect; ///< Rectángulo que define el área de la ventana.
	std::string m_windowName = "Naser Engine"; ///< Nombre de la ventana.
private:
	
};