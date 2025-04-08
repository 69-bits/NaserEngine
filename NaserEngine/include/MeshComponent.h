#pragma once
#include "Prerequisites.h"
#include "DeviceContext.h"
#include "ComponentType.h"

class
MeshComponent : public Component{
public:
  MeshComponent() : m_numVertex(0), m_numIndex(0), Component(ComponentType::MESH) {} // Constructor
  virtual
  ~MeshComponent() = default; // Destructor

  void
  update(float deltaTime) override {}

  void
  render(DeviceContext& deviceContext) override {}

public:
  std::string m_name; // Nombre del mesh
  std::vector<SimpleVertex> m_vertex; // Vector de vértices
  std::vector<unsigned int> m_index; // Vector de índices
  int m_numVertex; // Número de vértices
  int m_numIndex; // Número de índices
};