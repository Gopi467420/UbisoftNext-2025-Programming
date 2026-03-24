#include "EntityComponent.h"

EntityComponent::EntityComponent(Entity* owner) : m_owner(owner)
{

}

Entity* EntityComponent::GetOwner()
{
	return m_owner;
}

