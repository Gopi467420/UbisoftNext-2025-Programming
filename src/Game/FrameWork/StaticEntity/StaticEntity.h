#pragma once
#include "../Game/Framework/Entity/Entity.h"


class CircleComponent;
class HealthComponent;

class StaticEntity :   public Entity
{


public:
	virtual void Init() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render(Camera2D& camera) override;
	virtual void Shutdown() override;

	 // Inherited via Entity
	 ECollisionResponse GetCollisionResponse() const override;
	 ECollisionLayer GetCollisionLayer() const override;
	 uint32_t GetCollisionMask() const override;	
	 ShapeData GetDefaultShape() const override; 
	 void OnCollision(Entity* other) override;
	 EMobility GetMobility() const override;

};

