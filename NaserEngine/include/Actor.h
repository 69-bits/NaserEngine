#pragma once
#include "Prerequisites.h"
#include "Entity.h"
#include "Buffer.h"
#include "Textura.h"
#include "SamplerState.h"
#include "Transform.h"

class Device;
class MeshComponent;

class
  Actor : public Entity {

public:

  Actor(Device device);
  ~Actor() = default;

  void
    update(float deltaTime, DeviceContext& deviceContext) override;

  void
    render(DeviceContext& deviceContext) override;

  void
    setMesh(Device& device, std::vector<MeshComponent> meshes);

  void
    setTextures(std::vector<Textura> texturas, Device device);

  void
    destroy();

  std::string
    getName() const { return m_name; }

  template <typename T>
  EngineUtilities::TSharedPointer<T>
    getComponent();

private:
  std::vector<MeshComponent> m_meshes;
  std::vector<Textura> m_texturas;
  std::vector<Buffer> m_vertexBuffers;
  std::vector<Buffer> m_indexBuffers;
  CBChangesEveryFrame m_model;
  Buffer m_modelBuffer;
  SamplerState m_sampler;
  std::string m_name = "Actor";
};

template <typename T>
EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
  for (auto& component : m_components) {
    EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
    if (specificComponent) {
      return specificComponent;
    }
  }
  return EngineUtilities::TSharedPointer<T>();
}