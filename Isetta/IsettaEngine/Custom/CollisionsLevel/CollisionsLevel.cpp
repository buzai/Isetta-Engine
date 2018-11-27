/*
 * Copyright (c) 2018 Isetta
 */
#include "Custom/CollisionsLevel/CollisionsLevel.h"

#include "Components/FlyController.h"
#include "Components/GridComponent.h"
#include "Custom/DebugCollision.h"
#include "Custom/KeyTransform.h"
#include "Custom/OscillateMove.h"
#include "Custom/RaycastClick.h"

#include "Core/Color.h"
#include "Core/Config/Config.h"
#include "Core/Math/Vector3.h"
#include "Graphics/CameraComponent.h"
#include "Graphics/LightComponent.h"
#include "Scene/Entity.h"

#include "Application.h"
#include "Collisions/BoxCollider.h"
#include "Collisions/CapsuleCollider.h"
#include "Collisions/Collider.h"
#include "Collisions/CollisionHandler.h"
#include "Collisions/SphereCollider.h"
#include "Components/Editor/FrameReporter.h"
#include "Core/IsettaCore.h"

#include "Scene/Primitive.h"

namespace Isetta {

void CollisionsLevel::OnLevelLoad() {
  Entity* debugEntity{Entity::Instantiate("Debug")};
  debugEntity->AddComponent<FrameReporter>();

  // Camera
  Entity* cameraEntity{Entity::Instantiate("Camera")};
  cameraEntity->AddComponent<CameraComponent>();
  cameraEntity->SetTransform(Math::Vector3{0, 5, 10}, Math::Vector3{-15, 0, 0},
                             Math::Vector3::one);
  cameraEntity->AddComponent<FlyController>();

  // Light
  Entity* lightEntity{Entity::Instantiate("Light")};
  lightEntity->AddComponent<LightComponent>();
  lightEntity->SetTransform(Math::Vector3{0, 200, 600}, Math::Vector3::zero,
                            Math::Vector3::one);

  Entity* grid = Entity::Instantiate("Grid");
  grid->AddComponent<GridComponent>();
  grid->AddComponent<RaycastClick>(true, 5);

  Entity* cube = Entity::Instantiate("Cube");
  BoxCollider* cubeCol = cube->AddComponent<BoxCollider>(
      Math::Vector3{-8, 1.5f, 0}, Math::Vector3{1, 3, 10});
  cube->AddComponent<KeyTransform>();

  Entity* capsule = Entity::Instantiate("Capsule");
  CapsuleCollider* capsuleCol = capsule->AddComponent<CapsuleCollider>();
  capsule->transform->SetWorldPos(Math::Vector3{0, 1.f, 0});

  /*
  // STATIC
  const int COLLIDERS = 3;
  Entity* staticCol[COLLIDERS];

  staticCol[0] = Entity::Instantiate("box-collider", nullptr, true);
  staticCol[0]->SetTransform(Math::Vector3{0, 1, 0}, Math::Vector3{0, 0, 0});
  BoxCollider* bCol = staticCol[0]->AddComponent<BoxCollider>();
  bCol->isTrigger = true;
  CollisionHandler* handler = staticCol[0]->AddComponent<CollisionHandler>();
  handler->RegisterOnEnter([](Collider* const col) {
    LOG("collided with " + col->entity->GetName());
  });
  staticCol[0]->AddComponent<DebugCollision>();

  staticCol[1] = Entity::Instantiate("sphere-collider", nullptr, true);
  staticCol[1]->SetTransform(Math::Vector3{0, 1, -4});
  SphereCollider* sCol = staticCol[1]->AddComponent<SphereCollider>();
  sCol->isTrigger = true;
  Collider* c = staticCol[1]->GetComponent<Collider>();
  staticCol[1]->AddComponent<CollisionHandler>();
  staticCol[1]->AddComponent<DebugCollision>();

  staticCol[2] = Entity::Instantiate("capsule-collider", nullptr, true);
  staticCol[2]->SetTransform(Math::Vector3{0, 1, -8});
  CapsuleCollider* cCol = staticCol[2]->AddComponent<CapsuleCollider>(
      true, Math::Vector3::zero, 0.5, 2, CapsuleCollider::Direction::X_AXIS);
  staticCol[2]->AddComponent<CollisionHandler>();
  staticCol[2]->AddComponent<DebugCollision>();

  //// DYNAMIC
  for (int i = 0; i < COLLIDERS; i++) {
    Entity* oscillator{Entity::Instantiate("oscillator")};
    oscillator->transform->SetParent(staticCol[i]->transform);
    oscillator->transform->SetLocalPos(7 * Math::Vector3::left);
    oscillator->AddComponent<OscillateMove>(0, 1, -1, 12);
    oscillator->AddComponent<KeyTransform>(0.25);
    oscillator->AddComponent<CollisionHandler>();

    Entity* box{Entity::Instantiate("box-collider" + i)};
    box->transform->SetParent(oscillator->transform);
    box->transform->SetLocalPos(-2 * Math::Vector3::left);
    c = box->AddComponent<BoxCollider>();
    c->isTrigger = true;
    box->AddComponent<CollisionHandler>();
    box->AddComponent<DebugCollision>();

    Entity* sphere{Entity::Instantiate("sphere-collider" + i)};
    sphere->transform->SetParent(oscillator->transform);
    sphere->transform->SetLocalPos(Math::Vector3::zero);
    c = sphere->AddComponent<SphereCollider>();
    c->isTrigger = true;
    sphere->AddComponent<CollisionHandler>();
    sphere->AddComponent<DebugCollision>();

    for (int j = 0; j < 3; j++) {
      Entity* capsule{Entity::Instantiate("capsule-collider" + i + j)};
      capsule->transform->SetParent(oscillator->transform);
      capsule->transform->SetLocalPos(3 * (j + 1) * Math::Vector3::left);
      capsule->transform->SetLocalRot(-30 * Math::Vector3::up);
      CapsuleCollider* col = capsule->AddComponent<CapsuleCollider>(
          0.5, 2, static_cast<CapsuleCollider::Direction>(j));
      col->isTrigger = true;
      capsule->AddComponent<CollisionHandler>();
      capsule->AddComponent<DebugCollision>();
    }

    */
  Input::RegisterKeyPressCallback(KeyCode::ESCAPE,
                                  []() { Application::Exit(); });
}
}  // namespace Isetta
