#pragma once
#include "../Game/Gameplay/Pooled Entities/Pooled Entity (Base)/PooledEntities.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h"


class Enemy :    public PooledEntities
{

private:
	void SetShapeDateForDerivedEntities();

	EEnemyType m_enemyType;
	ShapeData m_shape;
	float m_damage;
public:

	// Inherited via PooledEntities
	ECollisionResponse GetCollisionResponse() const override;
	ECollisionLayer GetCollisionLayer() const override;
	uint32_t GetCollisionMask() const override;
	ShapeData GetDefaultShape() const override;
	EMobility GetMobility() const override;
	EEnemyType GetEnemyType();
	float GetHealth();
	float GetDamange();
	void TakeDamage(float amount) override;
	void SetShapeData(){ SetShapeDateForDerivedEntities(); }
	void SetEnemyType(EEnemyType type) { m_enemyType = type; }
	void SetHealth(float value) ;
	void SetDamage(float value) { m_damage = value; }
	void OnCollision(Entity* other) override;
};

