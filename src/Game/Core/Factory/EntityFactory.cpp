#include "EntityFactory.h"
//GameObjects here
#include "../Game/FrameWork/StaticEntity/StaticEntity.h"
#include "../Game/Gameplay/Player/Player.h"
#include "../Game/Gameplay/Base/Base.h"


//Components here
#include "../Game/Components/Physics/CollisionComponents/CircleComponent.h"
#include"../Game/Components/Attributes/Health/HealthComponent.h"
#include "../Game/Components/Shape/ShapeComponent.h"

#include <memory>

EntityFactory::EntityFactory() {}

std::unique_ptr<GObject> EntityFactory::CreatePlayer()
{
    auto entity = std::make_unique<Player>();   
    entity->DefineBaseComponents();
    entity->AddComponent<HealthComponent>(100.0f);
    entity->RegisterColliderForNonPooledEntities();
    return entity;
}

std::unique_ptr<GObject> EntityFactory::CreateWorldObject()
{
    auto entity = std::make_unique<StaticEntity>();
    entity->DefineBaseComponents();
    entity->RegisterColliderForNonPooledEntities();
    return entity;
}

std::unique_ptr<GObject> EntityFactory::CreateBase()
{
    auto entity = std::make_unique<Base>();
    entity->DefineBaseComponents();
    entity->AddComponent<HealthComponent>(5000.0f);
    entity->RegisterColliderForNonPooledEntities();
    return entity;
}
