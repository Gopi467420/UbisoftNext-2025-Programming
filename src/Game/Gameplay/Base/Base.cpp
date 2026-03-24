#include "Base.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h"
#include "../Game/Components/Attributes/Health/HealthComponent.h"
#include "../Game/Core/GameManager/GameManager.h"
#include "../Game/Core/CoordinateConversion/CoordinateConversion.h"
#include "../Game/Math/Utils/Utils.h"


void Base::OnCollision(Entity* other)
{


	if (!other) return;
	ECollisionLayer hitterttype = other->GetCollisionLayer();
 
	switch (hitterttype)
	{
	case ECollisionLayer::Player://Nothing
		break;
	case ECollisionLayer::Projectile:
		break;
	case ECollisionLayer::Enemy:TakeDamage(100);
		break;
	case ECollisionLayer::World:
		break;
	case ECollisionLayer::Camera:
		break;
	case ECollisionLayer::Base:
		break;
	default:
		break;
	}
	


	//Player =  increa health
	//Enemy/ enemy projectile  =  take damage 


}

void Base::TakeDamage(float amount)
{
	if (auto* health = GetComponent<HealthComponent>())
		health->TakeDamage(amount);
	
	GameManager::Get().GetActiveScene().CameraShake();
   
}

float Base::GetDamageAmount()
{
	return 30;
}

int Base::GetBaseHealth()
{
	auto& healthcomp = *GetComponent<HealthComponent>();
	
	return healthcomp.GetHealth();
}

void Base::SetBaseHealth()
{
	auto& healthcomp = *GetComponent<HealthComponent>();
	healthcomp.SetHealth(5000.0f);
}

void Base::Render(Camera2D& camera) { Entity::Render(camera);   App::Print(CoordinateConversion::WorldToScreen(GetPosition(), camera).x - 5, CoordinateConversion::WorldToScreen(GetPosition(), camera).y - 5, "B",0,0,0); }

ECollisionResponse Base::GetCollisionResponse() const { return ECollisionResponse::ECR_Trigger; }
ECollisionLayer Base::GetCollisionLayer() const { return ECollisionLayer::Base; }
uint32_t Base::GetCollisionMask() const { return DefineCollisionMask({  ECollisionLayer::Enemy,ECollisionLayer::Projectile }); }
ShapeData Base::GetDefaultShape() const { return SD_CircleShape{30}; }
EMobility Base::GetMobility() const { return EMobility::Static; }



