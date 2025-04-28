#pragma once
#include "Prerequisites.h"
#include "DeviceContext.h"
#include "ECS/ComponentType.h"

class
MeshComponent : public Component{
public:
  MeshComponent() : m_numVertex(0), m_numIndex(0), Component(ComponentType::MESH) {} // Constructor
  virtual
  ~MeshComponent() = default; // Destructor

  // M�todo para inicializar el componente
  void
  update(float deltaTime) override {}

  // M�todo para renderizar el componente
  void
  render(DeviceContext& deviceContext) override {}

public:
  std::string m_name; // Nombre del mesh
  std::vector<SimpleVertex> m_vertex; // Vector de v�rtices
  std::vector<unsigned int> m_index; // Vector de �ndices
  int m_numVertex; // N�mero de v�rtices
  int m_numIndex; // N�mero de �ndices
};