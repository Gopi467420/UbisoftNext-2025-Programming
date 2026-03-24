#include "PooledEntities.h"
#include "../Game/Core/Scene/Scene(BaseClass)/Scene.h"
#include "../Game/Components/Physics/CollisionComponents/CircleComponent.h"
#include <assert.h>
#include "app.h"


void PooledEntities::Init()
{
	
	AddComponent<ShapeComponent>(GetDefaultShape());
	AddComponent<CircleComponent>(ComputeColliderRadius(), GetCollisionLayer(), GetCollisionMask(), GetCollisionResponse());
	SetShapeDateForDerivedEntities();
	Entity::Init();
	
}

void PooledEntities::Update(float deltaTime)
{
	if (!m_active) return;
	Entity::Update(deltaTime);
	
}

void PooledEntities::Render(Camera2D& camera)
{

	if (!m_active) return;

	if (auto* c = GetComponent<CircleComponent>())
		c->Render(camera);

	Entity::Render(camera);
	
	
	
}



void PooledEntities::Activate()
{
	SetActive(true);

	auto* collider = GetCollider();
	if (collider && !collider->IsRegistered())
	{
		m_sceneRef->GetPhysics().Register(collider);
		collider->SetRegistered(true);
	}
}

void PooledEntities::Deactivate()
{
	SetActive(false);

	auto* collider = GetCollider();
	if (collider && collider->IsRegistered())
	{
		m_sceneRef->GetPhysics().Unregister(collider);
		collider->SetRegistered(false);
	}
}




bool PooledEntities::IsActive() const { return m_active; }

void PooledEntities::SetScene(Scene& scene) { m_sceneRef = &scene; }

Scene& PooledEntities::GetScene()
{
	return *m_sceneRef;
}
