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
  std::vector<SimpleVertex> m_vertex; // Vector de v�rtices
  std::vector<unsigned int> m_index; // Vector de �ndices
  int m_numVertex; // N�mero de v�rtices
  int m_numIndex; // N�mero de �ndices
};