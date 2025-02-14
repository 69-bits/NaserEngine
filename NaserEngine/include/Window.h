#pragma once
#include "Prerequisites.h"

class
Window {
public:
	Window() = default;
	~Window() = default;
	/**
		 * @brief Inicializa la ventana con los par�metros especificados.
		 *
		 * @param hInstance Instancia del m�dulo de la aplicaci�n.
		 * @param nCmdShow Especifica c�mo se debe mostrar la ventana.
		 * @param wndproc Funci�n de procedimiento de ventana.
		 * @return HRESULT Indica el �xito o fallo de la operaci�n.
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
	HINSTANCE m_hInst = nullptr;  ///< Instancia del m�dulo de la aplicaci�n
	HWND m_hWnd = nullptr; ///< Handle de la ventana.
	unsigned int m_width; ///< Ancho de la ventana.
	unsigned int m_height;///< Ancho de la ventana.
	RECT m_rect; ///< Rect�ngulo que define el �rea de la ventana.
	std::string m_windowName = "Naser Engine"; ///< Nombre de la ventana.
private:
	
};