#pragma once
#include "../Game/FrameWork/Entity/Entity.h"
#include "../Game/FrameWork/Interfaces/Interfaces.h"
#include "../Game/Gameplay/Pooled Entities/Pooled Entity (Base)/PooledEntities.h"



class Projectiles : public PooledEntities
{

public:
    Projectiles() {};
    void SetPoolIndex(uint32_t index) { m_poolIndex = index; }
    uint32_t GetPoolIndex() const { return m_poolIndex; }

    void OnCollision(Entity* other) override;

    // collision
    ECollisionResponse GetCollisionResponse() const override;
    ECollisionLayer GetCollisionLayer() const override;
    uint32_t GetCollisionMask() const override;
    ShapeData GetDefaultShape() const override;
    EMobility GetMobility() const override;

private:
    uint32_t m_poolIndex = UINT32_MAX; // index for SoA
    float m_damage;
    ShapeData m_shape;
  

public:
    float GetDamageAmount() override;
    void SetDamageAmount(float damage) override;
    ShapeData GetShapeData() { return m_shape; }
    void SetShapeData(ShapeData shape);


    ProjectileType m_type = ProjectileType::Rocket;
    float m_aoeRadius = 0.0f;

    void SetType(ProjectileType t) { m_type = t; }
    void SetAoeRadius(float r) { m_aoeRadius = r; }

public:

    bool hitonce = false;
};

