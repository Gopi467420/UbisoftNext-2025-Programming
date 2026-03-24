#include "PhysicsManager.h"
#include "../Game/Components/Physics/CollisionComponents/CircleComponent.h"
#include "../Game/FrameWork/Structs/Structs.h"
#include "../Game/Framework/Entity/Entity.h"
#include "../Game/Core/GridHash/GridHash.h"
#include "../Game/Gameplay/Pooled Entities/Enemy/Enemy.h"
#include "../Game/Math/Utils/Utils.h"

#include "math.h"



PhysicsManager::PhysicsManager(GridHash& grid): m_grid(grid){}

void PhysicsManager::Register(CircleComponent* collider)
{
    if (collider->IsRegistered() || !collider->GetOwner()) return;
    m_grid.Insert(collider, collider->GetOwner()->GetPosition(), collider->GetRadius());
    collider->SetRegistered(true);
}

void PhysicsManager::Unregister(CircleComponent* collider)
{
    if (!collider->IsRegistered() || !collider->GetOwner()) return;
    m_grid.Remove(collider, collider->GetOwner()->GetPosition(), collider->GetRadius());
    collider->SetRegistered(false);
}

void PhysicsManager::OnOwnerMoved(CircleComponent* collider, const Vector2& oldPos, const Vector2& newPos)
{
    if (!collider->IsRegistered()) return;
    m_grid.Update(collider, oldPos, newPos, collider->GetRadius());
}



//Resolves collision using paired hash to avoid duuplication 

void PhysicsManager::ResolveAllCollision()
{
    ClearCollisionEvents();

    std::unordered_set<PairKey, PairHash, PairEq> seen;
    seen.reserve(2048);

    std::vector<CircleComponent*> allCollider = m_grid.GetAllColliders();

    for (CircleComponent* collider : allCollider)
    {
        if (!collider) continue;

        auto nearby = m_grid.Query(collider->GetWorldPosition(), collider->GetRadius());

        for (CircleComponent* other : nearby)
        {
            if (!other || other == collider) continue;

            Entity* aEnt = collider->GetOwner();
            Entity* bEnt = other->GetOwner();
            if (!aEnt || !bEnt) continue;

            
            const void* a = aEnt;
            const void* b = bEnt;
            if (a > b) std::swap(a, b);

            if (!seen.insert({ a, b }).second)
                continue; 

            if (!collider->CanCollideWith(*other)) continue;
            if (!other->CanCollideWith(*collider)) continue;

            if (!collider->OverlapsAt(collider->GetWorldPosition(), *other)) continue;

            m_collisionEvents.push_back({ aEnt, bEnt });
        }
    }
}




void PhysicsManager::ApplyEnemySeparation(uint32_t i, Enemydata& data, float dt)
{
    const float desiredDistance = 60.0f;
    const float forceStrength = 120.0f;

    Vector2 pos = data.positions[i];
    Vector2 separationForce(0, 0);

    for (uint32_t j = 0; j < data.aliveCount; ++j)
    {
        if (i == j) continue;

        Vector2 diff = pos - data.positions[j];
        float distSq = diff.LengthSquared();

        if (distSq > 0.0001f && distSq < desiredDistance * desiredDistance)
        {
            float dist = sqrtf(distSq);
            Vector2 push = diff / dist; // normalize

            float strength = (desiredDistance - dist) / desiredDistance;
            separationForce += push * strength;
        }
    }

    // Apply force
    data.positions[i] += separationForce * forceStrength * dt;

}









void PhysicsManager::SlideVelocity(CircleComponent* mover, Vector2& velocity)
{
    Entity* owner = mover->GetOwner();
    if (!owner) return;

    auto nearby = m_grid.Query(owner->GetPosition(), mover->GetRadius());

    for (auto* other : nearby)
    {
        if (!other || other == mover) continue;
        if (other->GetCollisionPreset() != ECollisionResponse::ECR_Block)
            continue;

        Vector2 delta = owner->GetPosition() - other->GetOwner()->GetPosition();

        float distSq = delta.LengthSquared();
        float r = mover->GetRadius() + other->GetRadius();


        if (distSq >= r * r) continue; // Is Penetrating check

        float dist = sqrtf(distSq);

        Vector2 normal = (dist > 0.0001f) ? delta / dist : Vector2(1, 0);

        // Penetration Corrected
        float intoWall = velocity.Dot(normal);
        if (intoWall < 0.0f)
        {
            velocity -= normal * intoWall;
            velocity = velocity;
        }
    }
}

const std::vector<CollisionEvent>& PhysicsManager::GetCollisionEvents() const { return m_collisionEvents; }

void PhysicsManager::ClearCollisionEvents() { m_collisionEvents.clear(); }




