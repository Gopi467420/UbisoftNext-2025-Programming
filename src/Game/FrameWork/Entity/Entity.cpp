#include "../Game/Framework/Entity/Entity.h"
#include "../Game/Components/Physics/CollisionComponents/CircleComponent.h"
#include "../Game/FrameWork/EntityComponent/EntityComponent.h"
#include "../Game/Core/GameManager/GameManager.h"
#include "../Game/Core/Scene/Scene(BaseClass)/Scene.h"
#include "assert.h"



#include "app.h"


Entity::Entity(){}
Entity::~Entity(){}

void Entity::Init(){}
void Entity::Update(float deltaTime){}
void Entity::Render(Camera2D& camera) { for (auto& it : m_components) { it->Render(camera);  } }
void Entity::Shutdown() { m_components.clear();}
void Entity::DefineBaseComponents()
{
    AddComponent<ShapeComponent>(GetDefaultShape());
    AddComponent<CircleComponent>(ComputeColliderRadius(), GetCollisionLayer(), GetCollisionMask(), GetCollisionResponse());
   
    //Add Other Common Entity Components Here
}

void Entity::RegisterColliderForNonPooledEntities()
{
    GameManager::Get().GetActiveScene().GetPhysics().Register(GetCollider());
}

float Entity::ComputeColliderRadius()
{
    auto shape = GetComponent<ShapeComponent>();
   
    if (shape){ return shape->ComputeBoundingRadius(); }
    return 0.0f;
}

void Entity::SetShapeData(ShapeData shape)
{
    m_shape = shape;
}

void Entity::OnPositionChanged(const Vector2& oldPos,const Vector2& Pos)
{
    if (!GetCollider()) return;    
    GameManager::Get().GetActiveScene().GetPhysics().OnOwnerMoved(GetCollider(), oldPos, Pos);

   
     
}



const CircleComponent* Entity::GetCollider() const  { return GetComponent<CircleComponent>(); }
CircleComponent* Entity::GetCollider() { return GetComponent<CircleComponent>(); }
EMobility Entity::GetMobility() const { return m_mobility; }