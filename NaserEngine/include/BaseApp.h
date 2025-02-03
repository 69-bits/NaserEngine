#pragma once
#include "Prerequisites.h"

class
BaseApp {
public:
	BaseApp() = default;
	~BaseApp() = default;

  /**
   * @brief Inicializa la aplicación.
   *
   * @return HRESULT Indica el éxito o fallo de la operación.
   */
	HRESULT
	init();

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
   * @brief Destruye la aplicación y libera los recursos asociados.
   */
	void
	destroy();

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

private:

};