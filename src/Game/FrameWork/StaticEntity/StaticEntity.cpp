#include "StaticEntity.h"


void StaticEntity::Init()
{
    m_position.x = 200;
    m_position.y = 50;

    Entity::Init(); 
   
}

void StaticEntity::Update(const float deltaTime){}

void StaticEntity::Render(Camera2D& camera) { Entity::Render(camera); }

void StaticEntity::Shutdown()
{
}


uint32_t StaticEntity::GetCollisionMask() const { return DefineCollisionMask({ ECollisionLayer::Player, ECollisionLayer::Projectile, ECollisionLayer::Enemy }); }
ECollisionResponse StaticEntity::GetCollisionResponse() const { return ECollisionResponse::ECR_Block; }
ECollisionLayer StaticEntity::GetCollisionLayer() const { return ECollisionLayer::World; }
ShapeData StaticEntity::GetDefaultShape() const { return SD_BoxShape{ 50,50 }; }
EMobility StaticEntity::GetMobility() const { return EMobility::Static; }

void StaticEntity::OnCollision(Entity* other)
{


}

