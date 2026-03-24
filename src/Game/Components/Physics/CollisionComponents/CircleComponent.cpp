#include "CircleComponent.h"
#include "../Game/Framework/Entity/Entity.h"
#include "../Game/FrameWork/Shapes/Shape.h"

CircleComponent::CircleComponent( Entity* owner,float radius,ECollisionLayer layer, uint32_t mask,ECollisionResponse preset)
                : EntityComponent(owner), m_radius(radius), m_layer(layer), m_mask(mask), m_preset(preset){ }

CircleComponent::~CircleComponent(){}

bool CircleComponent::OverlapsAt( const Vector2& testCenter, const CircleComponent& other) const
{
    
    Vector2 delta = other.m_owner->GetPosition() - testCenter;
    float r = m_radius + other.m_radius;
    return delta.Dot(delta) <= r * r;
}

bool CircleComponent::CanCollideWith(const CircleComponent& other) const
{
    return (m_mask & static_cast<uint32_t>(other.m_layer)) != 0;
}

float CircleComponent::GetRadius() const { return m_radius; }
void CircleComponent::SetRadius(float radius) { m_radius = radius; }
ECollisionResponse CircleComponent::GetCollisionPreset() const { return m_preset; }
const Vector2& CircleComponent::GetWorldPosition() const { return m_owner->GetPosition(); }
void CircleComponent::Render(Camera2D& camera)
{
    //For Debugging colliders
    //Shape::DrawCircle(GetWorldPosition(), m_radius,Shape::ShapeColor::Green);
}

