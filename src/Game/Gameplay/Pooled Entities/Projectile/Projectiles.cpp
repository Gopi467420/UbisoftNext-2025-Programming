#include "Projectiles.h"
#include "../Game/Components/Physics/CollisionComponents/CircleComponent.h"

#include "../Game/Core/GameManager/GameManager.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h"
#include "app.h"




void Projectiles::OnCollision(Entity* other)
{
   
   
   
}
uint32_t Projectiles::GetCollisionMask() const { return DefineCollisionMask({ ECollisionLayer::Enemy}); }
ECollisionResponse Projectiles::GetCollisionResponse() const { return ECollisionResponse::ECR_Trigger; }
ECollisionLayer Projectiles::GetCollisionLayer() const { return ECollisionLayer::Projectile; }
ShapeData Projectiles::GetDefaultShape() const { return m_shape; }
EMobility Projectiles::GetMobility() const { return EMobility::Movable; }

float Projectiles::GetDamageAmount()
{
	return m_damage;
}

void Projectiles::SetDamageAmount(float damage)
{
	m_damage = damage;
}

void Projectiles::SetShapeData(ShapeData shape)
{
	auto* shapecom = GetComponent<ShapeComponent>();
    auto* circle = GetComponent<CircleComponent>();
    if (!shapecom || !circle) return;

	shapecom->SetShape(shape);
    circle->SetRadius(ComputeColliderRadius());
}

