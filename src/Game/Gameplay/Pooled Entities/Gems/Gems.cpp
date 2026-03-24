#include "Gems.h"


void Gems::OnCollision(Entity* other)
{
	Deactivate();
}
uint32_t Gems::GetCollisionMask() const { return DefineCollisionMask({ ECollisionLayer::Base}); }
ECollisionResponse Gems::GetCollisionResponse() const { return ECollisionResponse::ECR_Trigger; }
ECollisionLayer Gems::GetCollisionLayer() const { return ECollisionLayer::Gem; }
ShapeData Gems::GetDefaultShape() const { return SD_CircleShape{ 5 }; }
EMobility Gems::GetMobility() const { return EMobility::Static; }

 