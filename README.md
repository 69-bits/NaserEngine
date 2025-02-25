# NaserEngine

**NaserEngine** es un motor de juego ligero y modular construido sobre DirectX 11. Está diseñado para ofrecer una base sólida en gráficos y renderizado en Windows, facilitando el aprendizaje y desarrollo de aplicaciones interactivas y juegos. El motor implementa componentes esenciales como la creación de dispositivos Direct3D, gestión del swap chain, render target views, depth stencil views y manejo de texturas, organizados en una arquitectura modular y extensible.

## Características

- **DirectX 11 Rendering Pipeline:**  
  Implementa las etapas fundamentales de DirectX 11, incluyendo la creación y configuración del dispositivo, el contexto, el swap chain y los recursos de renderizado.

- **Gestión de Recursos:**  
  Incluye macros y utilidades (por ejemplo, `SAFE_RELEASE`, `ERROR`, y `MESSAGE`) para la liberación segura de recursos y la depuración.

- **Soporte para MSAA:**  
  Configuración de anti-aliasing (MSAA) para mejorar la calidad visual del renderizado.

- **Administración de Ventanas:**  
  Integración con la API Win32 para la creación y manejo de ventanas, junto con un bucle de mensajes eficiente.

- **Arquitectura Modular:**  
  Organización del código en módulos que abarcan desde la gestión del dispositivo y contextos hasta la creación de vistas de renderizado y manejo de texturas.

## Requisitos Previos

- **Sistema Operativo:** Windows 10 o superior.
- **Herramientas:** Visual Studio 2019/2022 con soporte para C++.
- **SDK:** Windows SDK (DirectX está incluido).

## Instalación y Compilación

1. **Clonar el Repositorio:**

   ```bash
   git clone https://github.com/69-bits/NaserEngine.git
## Abrir la Solución

Abre el archivo `NaserEngine.sln` en Visual Studio.

## Compilar el Proyecto

Selecciona el modo **Debug** o **Release** y compila la solución.

## Estructura del Proyecto

### /src:
Contiene el código fuente del motor.
- **Device:** Manejo de creación y administración del dispositivo Direct3D.
- **DeviceContext:** Administración del contexto de renderizado.
- **SwapChain:** Gestión del swap chain y presentación del backbuffer.
- **RenderTargetView:** Implementación de las vistas de destino para el renderizado.
- **DepthStencilView:** Gestión del buffer de profundidad y stencil.
- **Textura:** Manejo de recursos de textura.
- **Window:** Creación y administración de ventanas mediante Win32.

### /include:
Archivos de cabecera que definen la interfaz de los módulos del motor.

### /docs:
Documentación, recursos y guías de uso del motor.

### /libs:
(Opcional) Dependencias de terceros o bibliotecas adicionales utilizadas por el motor.

## Uso y Extensibilidad

NaserEngine está diseñado para ser un punto de partida flexible:

- **Aprendizaje:**  
  Ideal para desarrolladores que quieren profundizar en la programación de gráficos con DirectX 11.
- **Extensión:**  
  Puedes agregar nuevos módulos, sistemas de juego o mejorar la lógica de renderizado según tus necesidades.
- **Benchmarking y Experimentación:**  
  Usa el motor como base para experimentar con técnicas modernas de renderizado y optimización gráfica.

## Contribuciones

¡Se agradecen las contribuciones!  
Si deseas mejorar el motor, reporta problemas o sugiere nuevas características abriendo un issue o enviando un pull request.

## Licencia

Este proyecto está licenciado bajo la Licencia MIT. Consulta el archivo `LICENSE` para más detalles.

## Agradecimientos

- **Documentación Oficial de DirectX 11:**  
  Fuente clave para la implementación de las técnicas de renderizado.
- **Comunidad Open Source:**  
  Agradecimientos a todas las contribuciones y recursos compartidos en línea que han ayudado a dar forma a NaserEngine.
