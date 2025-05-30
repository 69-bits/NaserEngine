#pragma once
// Librerias STD
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <xnamath.h>

//#include <memory>
#include <thread>

// Librerias DirectX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "Resource.h"
#include "resource.h"

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_internal.h>
#include "imgui_impl_win32.h"

#include "Utilities/Memory/TSharedPointer.h"
#include "Utilities/Memory/TWeakPointer.h"
#include "Utilities/Memory/TStaticPtr.h"
#include "Utilities/Memory/TWeakPointer.h"



// MACROS
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

#define MESSAGE( classObj, method, state )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
}

#define ERROR( classObj, method, errorMSG )  \
{                                            \
   std::wostringstream os_;                  \
   os_ << "ERROR : " << classObj << "::" << method << " : " << "  Error in data from params [" << errorMSG << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
   exit(1);                                  \
}

// Structures
struct
SimpleVertex {
  XMFLOAT3 Pos;
  XMFLOAT2 Tex;
};

// Constant Buffers
struct
CBNeverChanges {
  XMMATRIX mView;
};

// Representa la matriz de proyecci�n
struct
CBChangeOnResize {
  XMMATRIX mProjection;
};

// Representa la matriz del mundo
struct
CBChangesEveryFrame {
  XMMATRIX mWorld;
  XMFLOAT4 vMeshColor;
};

// Enumeraci�n de los tipos de extensi�n de las texturas
enum 
ExtensionType {
  DDS = 0,
  PNG = 1,
  JPG = 2,
  BMP = 3,
  TGA = 4,
  UNKNOWN = 5
};  

// Enumeraci�n de los tipos de sombreadores
enum 
ShaderType {
  VERTEX_SHADER = 0,
  PIXEL_SHADER = 1
};

enum
ComponentType {
  NONE = 0,     ///< Tipo de componente no especificado.
  TRANSFORM = 1,///< Componente de transformaci�n.
  MESH = 2,     ///< Componente de malla.
  MATERIAL = 3  ///< Componente de material.
};

struct 
Camera {
  XMFLOAT3 position; // Posici�n de la c�mara
  XMFLOAT3 target; // Punto al que mira la c�mara

  XMFLOAT3 up; // Vector de direcci�n de la c�mara
  XMFLOAT3 forward; // Vector de direcci�n de la c�mara
  XMFLOAT3 right; // Vector de direcci�n de la c�mara

  float yaw; // �ngulo de rotaci�n en el eje Y
  float pitch; // �ngulo de rotaci�n en el eje X

  Camera() {
    position = XMFLOAT3(0.0f, 1.6f, -5.0f); // Posici�n de la c�mara
    target = XMFLOAT3(0.0f, 1.6f, 0.0f); // Punto al que mira la c�mara
    up = XMFLOAT3(0.0f, 1.0f, 0.0f); // Vector de direcci�n de la c�mara
    forward = XMFLOAT3(0.0f, 0.0f, 1.0f); // Vector de direcci�n de la c�mara
    right = XMFLOAT3(1.0f, 0.0f, 0.0f); // Vector de direcci�n de la c�mara
    yaw = 0.0f; // �ngulo de rotaci�n en el eje Y
    pitch = 0.0f; // �ngulo de rotaci�n en el eje X
  }
};

struct LoadDataOBJ {
  std::string name; ///< Nombre del objeto.
  std::vector<SimpleVertex> vertex; ///< V�rtices del objeto.
  std::vector<unsigned int> index; ///< �ndices de los v�rtices.
  int numVertex = 0; ///< N�mero de v�rtices.
  int numIndex = 0; ///< N�mero de �ndices.
};