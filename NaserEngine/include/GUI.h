#pragma once
#include "Prerequisites.h"
#include "Textura.h"

class
GUI {
public:
  GUI() = default;
  ~GUI() = default;

  /* Inicializa la interfaz gráfica de usuario.
   * @param window Ventana.
   * @param device Dispositivo.
   * @param devicecontext Contexto del dispositivo.
   * @return void.
   */
  void
  Init(void* window, ID3D11Device* device, ID3D11DeviceContext* devicecontext);

  /* Actualiza el estado de la interfaz gráfica de usuario.
   * @return void.
   */
  void
  update();

  /* Renderiza el contenido de la interfaz gráfica de usuario.
   * @return void.
   */
  void
  render();

  /* Destruye la interfaz gráfica de usuario.
   * @return void.
   */
  void
  destroy();

  /* Transforma la ventana.
   * @return void.
   */
  void
  transformWindow();

  /* Establece el estilo de la interfaz gráfica de usuario.
   * @return void.
   */
  void
  setupGUIStyle();


private:
  Textura texture; // Textura

};
