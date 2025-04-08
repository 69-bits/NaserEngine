#include "Transform.h"

#include "DeviceContext.h"

Transform::~Transform()
{
}

void
Transform::init() {
  scale.one();

  matrix = XMMatrixIdentity();
}

void 
Transform::update(float deltaTime) {
  // Aplicar escalado
  XMMATRIX scaleMatrix = XMMatrixScaling(scale.x, scale.y, scale.z);

  // Aplicar rotación
  XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

  // Aplicar traslación
  XMMATRIX translationMatrix = XMMatrixTranslation(position.x, position.y, position.z);

  // Combinación de las matrices en el siguiente orden: scale -> rotation -> translation
  matrix = scaleMatrix * rotationMatrix * translationMatrix;
}

void Transform::destroy()
{
}

void Transform::setTransform(EngineUtilities::Vector3 _position, EngineUtilities::Vector3 _rotation, EngineUtilities::Vector3 _scale)
{
  position = _position;
  rotation = _rotation;
  scale = _scale;
}

void Transform::translate(const EngineUtilities::Vector3& translation) {

}
