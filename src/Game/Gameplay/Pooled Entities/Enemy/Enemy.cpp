#include "Enemy.h"
#include "../Game/Components/Physics/CollisionComponents/CircleComponent.h"
#include"../Game/Components/Attributes/Health/HealthComponent.h"
#include "../Game/Core/Scene/Scene(BaseClass)/Scene.h"
#include<assert.h>
#include "app.h"
#include <memory>

#include "../ContestAPI/SimpleSound.h"



void Enemy::SetShapeDateForDerivedEntities()
{
    auto* shape = GetComponent<ShapeComponent>();
    auto* circle = GetComponent<CircleComponent>();
    if (!shape || !circle) return;
	
    switch (m_enemyType)
    {
    case EEnemyType::ET_Bomber:      shape->SetShape(SD_CircleShape{ 20,ShapeColor::Yellow }); break;
    case EEnemyType::ET_Airborne:    shape->SetShape(SD_CircleShape{ 30,ShapeColor::Red }); break;
    case EEnemyType::ET_WallBreaker: shape->SetShape(SD_BoxShape{ 30, 30,ShapeColor::Purple }); break;
    case EEnemyType::ET_Swarm:       shape->SetShape(SD_CircleShape{ 10, ShapeColor::Orange }); break;
    default: break;
    }

    

    circle->SetRadius(ComputeColliderRadius());
}

void Enemy::SetHealth(float value)
{
	AddComponent<HealthComponent>(value);
}

void Enemy::OnCollision(Entity* other)
{
	if (!other) return;
	ECollisionLayer hitterttype = other->GetCollisionLayer();

	switch (hitterttype)
	{
	case ECollisionLayer::Player://Nothing
		break;
	case ECollisionLayer::Projectile: TakeDamage(other->GetDamageAmount()); GetScene().PlayEnemyHitSound("");
		break;
	case ECollisionLayer::Enemy:
		break;
	case ECollisionLayer::World:
		break;
	case ECollisionLayer::Camera:
		break;
	case ECollisionLayer::Base: GetScene().PlayBaseHitSound(""); Deactivate();
		break;
	default:
		break;
	}
   
}



ECollisionResponse Enemy::GetCollisionResponse() const { return ECollisionResponse::ECR_Trigger; }
ECollisionLayer Enemy::GetCollisionLayer() const { return ECollisionLayer::Enemy; }
uint32_t Enemy::GetCollisionMask() const { return DefineCollisionMask({ ECollisionLayer::Base, ECollisionLayer::Player, ECollisionLayer::Projectile }); }
ShapeData Enemy::GetDefaultShape() const { return m_shape; }
EMobility Enemy::GetMobility() const { return EMobility::Movable; }
EEnemyType Enemy::GetEnemyType() { return m_enemyType; }

float Enemy::GetHealth()
{
	auto* health = GetComponent<HealthComponent>();
	return health->GetHealth();
}

float Enemy::GetDamange()
{
	return m_damage;
}

void Enemy::TakeDamage(float amount)
{
	auto* health = GetComponent<HealthComponent>();
	health->TakeDamage(amount);

	if (health->IsDead())
	{
		GetScene().EmitExplosion(m_position);
		Deactivate();
		GetScene().m_enemyKillCount++;
	}
}
