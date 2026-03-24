#pragma once
#include "../Game/FrameWork/Entity/Entity.h"
#include "../Game/FrameWork/Interfaces/Interfaces.h"

class Base :public Entity 
{

	// Inherited via Entity
	ECollisionResponse GetCollisionResponse() const override;
	ECollisionLayer GetCollisionLayer() const override;
	uint32_t GetCollisionMask() const override;
	ShapeData GetDefaultShape() const override;
	EMobility GetMobility() const override;
	void OnCollision(Entity* other) override;
	void TakeDamage(float amount) override;
	float GetDamageAmount() override ;

public:

	int GetBaseHealth();
	void SetBaseHealth();

	void Render(Camera2D& camera) override;
	
};

