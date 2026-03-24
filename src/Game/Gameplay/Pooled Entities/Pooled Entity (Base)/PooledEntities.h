#pragma once

#include "../Game/FrameWork/Entity/Entity.h"
#include "../Game/FrameWork/Interfaces/Interfaces.h"
#include "../Game/FrameWork/Structs/Structs.h"

class Scene;
struct Camera2D;
class PooledEntities : public Entity, IPoolable
{
private:
	bool m_active;
	Scene* m_sceneRef;

public:
	void SetScene(Scene& scene);
	Scene& GetScene();


	uint32_t GetId() const { return m_id; }
	void SetId(uint32_t id) { m_id = id; }
protected:
	
	virtual void SetShapeDateForDerivedEntities() {};

private:
	uint32_t m_id = 0;

public:

	virtual ECollisionResponse GetCollisionResponse() const = 0;
	virtual ECollisionLayer GetCollisionLayer() const = 0;
	virtual uint32_t GetCollisionMask() const = 0;
	virtual ShapeData GetDefaultShape() const = 0;
	virtual EMobility GetMobility() const = 0;
	virtual void OnCollision(Entity* other) override = 0;

	// Inherited via IPoolable	

   //Define Base Objects and Call Enitty Init
	virtual void Activate() override;
	virtual void Deactivate() override;
	virtual bool IsActive() const override;
	void SetActive(bool value) { m_active = value; }
    // Inherited via Entity
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Camera2D& camera) override;
	
	
};

