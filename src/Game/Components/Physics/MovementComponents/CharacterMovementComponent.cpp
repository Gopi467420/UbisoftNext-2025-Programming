#include "CharacterMovementComponent.h"
#include "../Game/Framework/Entity/Entity.h"
#include "../Game/Framework/EntityComponent/EntityComponent.h"
#include "../Game/Systems/Physics/PhysicsManager.h"
#include "../Game/Core/GameManager/GameManager.h"
#include "../Game/Components/Physics/CollisionComponents/CircleComponent.h"
#include "../Game/Math/Utils/Utils.h"

CharacterMovementComponent::CharacterMovementComponent(Entity* owner) : EntityComponent(owner){}

void CharacterMovementComponent::MoveDelta( const Vector2& desiredVelocity,float dt)
{
    if (!m_owner) return;

    CircleComponent* collider = m_owner->GetCollider();
    if (!collider) return;

    PhysicsManager& physics = GameManager::Get().GetActiveScene().GetPhysics();

    // Total displacement this frame
    Vector2 totalMove = desiredVelocity * dt;

    
    float maxStepDist = collider->GetRadius() * 0.5f;
    int steps = (int)ceilf(totalMove.Length() / maxStepDist);
    steps = Utils::ClampMin(1, steps);

    Vector2 stepMove = totalMove / 10;

    //Sub step Calculation
    for (int i = 0; i < 10; ++i)
    {
        Vector2 velocityStep = stepMove / dt;        
        physics.SlideVelocity(collider, velocityStep);      
        m_owner->SetPosition( m_owner->GetPosition() + velocityStep * dt);
    }

}