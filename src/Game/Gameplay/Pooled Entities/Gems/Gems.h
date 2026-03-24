#pragma once
#include "../Game/Gameplay/Pooled Entities/Pooled Entity (Base)/PooledEntities.h"

class Gems : public PooledEntities
{
public:

    Gems() {};
    void SetPoolIndex(uint32_t index) { m_poolIndex = index; }
    uint32_t GetPoolIndex() const { return m_poolIndex; }

    void OnCollision(Entity* other) override;

    // collision 
    ECollisionResponse GetCollisionResponse() const override;
    ECollisionLayer GetCollisionLayer() const override;
    uint32_t GetCollisionMask() const override;
    ShapeData GetDefaultShape() const override;
    EMobility GetMobility() const override;
    void SetValue(float value) { m_value = value;  }

private:
    uint32_t m_poolIndex = UINT32_MAX; // index for SoA
    int m_value;
};

