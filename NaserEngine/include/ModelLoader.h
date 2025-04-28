#pragma once
#include "Prerequisites.h"
#include "MeshComponent.h"
#include "fbxsdk.h"

class 
ModelLoader
{
public:
	ModelLoader() = default;
	~ModelLoader() = default;

  /*
   * @brief Inicializa el gestor FBX.
   * @return true si la inicialización fue exitosa, false en caso contrario.
   */
  bool
  InitialiazeFBXManager();

  /*
   * @brief Carga un modelo FBX.
   * @param filepath Ruta del archivo FBX.
   * @return true si la carga fue exitosa, false en caso contrario.
   */
  bool
  LoadFBX_model(const std::string& filenpath);

  /*
   * @brief Procesa los nodos FBX.
   * @param node Puntero al nodo FBX.
   */
  void
  ProcessFBXNode(FbxNode* node);
  
  /*
   * @brief Procesa la malla FBX.
   * @param node Puntero al nodo FBX.
   */
  void
  ProcessFBXMesh(FbxNode* node);

  /*
   * @brief Procesa los materiales FBX.
   * @param material Puntero al material FBX.
   */
  void
  ProcessFBXMaterials(FbxSurfaceMaterial* material);

  /*
   * @brief Procesa las texturas FBX.
   * @param texture Puntero a la textura FBX.
   */
  std::vector<std::string>
  GetTextureFileNames() const { return textureFileNames; };

  /*
  * @brief Procesa los materiales FBX.
  * @param material Puntero al material FBX.
  */
  bool
  LoadOBJ_model(const std::string& filePath);

private:
  FbxManager* lSdkManager; /// FBX Manager
  FbxScene* lScene; /// FBX Scene
  std::vector<std::string> textureFileNames; /// Textura

public:
  std::vector<MeshComponent> m_meshes; /// Mallas
};
