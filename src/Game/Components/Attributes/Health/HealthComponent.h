// This component represents the health value of a the entity in the level, The health component is responsible for taking damage increasing health, updating the health widget 
#pragma once
#include <functional>
#include "../Game/FrameWork/EntityComponent/EntityComponent.h" //Parent Class

class Entity;

struct Camera2D;
class HealthComponent : public EntityComponent
{
	//Constructor
public:
	
	HealthComponent(Entity* owner, float maxHealth);

private:
	float m_health;
	float m_maxHealth;

public:
	std::function<void(float current, float max)> OnHealthChanged;
	std::function<void(float current, float max)> OnDeath;

public:
	
	void TakeDamage(float damage);
	void Heal(float amount);	
	bool IsDead() const;
	void Reset();


	//Accesors
public:
	float GetHealth() const;
	float GetMaxHealth() const;
	float GetHealthPercent() const;
	void SetHealth(float newHealth);
	float GetHealthValue() { return m_health; }
	
	virtual void Render(Camera2D& camera) override;




	

};

