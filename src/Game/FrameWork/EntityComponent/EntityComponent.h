//Components that can be added to the entities which define different behaviours for entities

#pragma once

struct Camera2D;
class Entity;

//Attachable Components to the Entities
class EntityComponent 
{

public:

	explicit EntityComponent(Entity* owner);
	virtual ~EntityComponent() = default; 

protected:
	Entity* m_owner;

public:
	virtual void Render(Camera2D& camera) {}; // for debug

public:
	Entity* GetOwner();
	
};
