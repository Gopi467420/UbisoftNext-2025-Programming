#pragma once

#include "../Game/Math/Vector/Vector2.h"
#include "../Game/FrameWork/EntityComponent/EntityComponent.h"

class Entity; // forward declaration

class CharacterMovementComponent : public EntityComponent
{
private:
    Vector2 m_velocity = Vector2(0, 0);
public:
    CharacterMovementComponent(Entity* owner);
    void MoveDelta(const Vector2& desiredVelocity, float dt);




};
