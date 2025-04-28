#include "ECS/Actor.h"
#include "MeshComponent.h"
#include "Device.h"

Actor::Actor(Device device) {
  // Componentes por defectos
  EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
  addComponent(transform);
  EngineUtilities::TSharedPointer<MeshComponent> mesh = EngineUtilities::MakeShared<MeshComponent>();
  addComponent(mesh);

  HRESULT hr;

  std::string classNameType = "Actor -> " + m_name;
  if (m_modelBuffer.init(device, sizeof(CBChangesEveryFrame))) {
    ERROR("Actor", classNameType.c_str(), "Failed to create new CBChangesEveryFrame");
  }

  if (m_sampler.init(device)) {
    ERROR("Actor", classNameType.c_str(), "Failed to create new SamplerState");
  }
}

void 
Actor::update(float deltaTime, DeviceContext& deviceContext) {
  //update transform
  getComponent<Transform>()->update(deltaTime);

  m_model.mWorld = XMMatrixTranspose(getComponent<Transform>()->matrix);
  m_model.vMeshColor = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f); // Color del mesh

  //update attributes
  m_modelBuffer.update(deviceContext, 0, nullptr, &m_model, 0, 0);
}

void 
Actor::render(DeviceContext& deviceContext) {
  m_sampler.render(deviceContext, 0, 1);

  for (unsigned int i = 0; i < m_meshes.size(); i++) {
    m_vertexBuffers[i].render(deviceContext, 0, 1);
    m_indexBuffers[i].render(deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);

    if (m_texturas.size() > 0) {
      if (i <= m_texturas.size())
      {
        m_texturas[i].render(deviceContext, 0, 1);
      }
    }

    // Renderizar el mesh
    m_modelBuffer.render(deviceContext, 2, 1, true);

    deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext.DrawIndexed(m_meshes[i].m_numIndex, 0, 0);
  }
}

void 
Actor::setMesh(Device& device, std::vector<MeshComponent> meshes) {
  m_meshes = meshes;

  HRESULT hr;

  for (auto& mesh : m_meshes) {
    Buffer vertexBuffer;
    hr = vertexBuffer.init(device, mesh, D3D11_BIND_VERTEX_BUFFER);
    if (FAILED(hr)) {
      ERROR("Actor", "setMesh", "Failed to create new vertex buffer");
    }
    else {
      m_vertexBuffers.push_back(vertexBuffer);
    }

    //Crear index buffer
    Buffer indexBuffer;
    hr = indexBuffer.init(device, mesh, D3D11_BIND_INDEX_BUFFER);
    if (FAILED(hr)) {
      ERROR("Actor", "setMesh", "Failed to create new index buffer");
    }
    else {
      m_indexBuffers.push_back(indexBuffer);
    }

  }
}

void Actor::setTextures(std::vector<Textura> texturas) {
  m_texturas = texturas;
}

void Actor::destroy() {
  for (auto& vertexBuffer : m_vertexBuffers) {
    vertexBuffer.destroy();
  }

  for (auto& indexBuffer : m_indexBuffers) {
    indexBuffer.destroy();
  }

  for (auto& tex : m_texturas) {
    tex.destroy();
  }
  m_modelBuffer.destroy();

  //m_rasterizer.destroy();
  //m_blendstate.destroy();
  m_sampler.destroy();
}
