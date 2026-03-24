#include "HealthComponent.h"
#include "../Game/Math/Utils/Utils.h"
#include "app.h"
#include "../Game/Core/CoordinateConversion/CoordinateConversion.h"
#include "../Game/FrameWork/Entity/Entity.h"

#include "HealthComponent.h"
#include <algorithm>
#include  "math.h"

HealthComponent::HealthComponent(Entity* owner, float maxHealth)
    : EntityComponent(owner)
    , m_health(maxHealth)
    , m_maxHealth(maxHealth)
{
}

void HealthComponent::TakeDamage(float damage)
{
    if (damage <= 0.0f) return;
    if (IsDead()) return;

    const float old = m_health;
    m_health = Utils::MaxFloat(0.0f, m_health - damage);
   
  
    if (OnHealthChanged && m_health != old)
        OnHealthChanged(m_health, m_maxHealth);

    if (m_health <= 0.0f)
    {
        if (OnDeath)
            OnDeath(m_health, m_maxHealth);
    }
}

void HealthComponent::Heal(float amount)
{
    if (amount <= 0.0f) return;
    if (IsDead()) return;

    const float old = m_health;


    m_health = Utils::MaxInt(m_maxHealth, m_health + amount);

    if (OnHealthChanged && m_health != old)
        OnHealthChanged(m_health, m_maxHealth);
}

bool HealthComponent::IsDead() const
{
    return m_health <= 0.0f;
}

void HealthComponent::Reset()
{
    m_health = m_maxHealth;
    if (OnHealthChanged)
        OnHealthChanged(m_health, m_maxHealth);
}

float HealthComponent::GetHealth() const { return m_health; }
float HealthComponent::GetMaxHealth() const { return m_maxHealth; }

float HealthComponent::GetHealthPercent() const
{
    return (m_maxHealth > 0.0f) ? (m_health / m_maxHealth) : 0.0f;
}

void HealthComponent::SetHealth(float newHealth)
{
    const float old = m_health;
    m_health = std::clamp(newHealth, 0.0f, m_maxHealth);

    if (OnHealthChanged && m_health != old)
        OnHealthChanged(m_health, m_maxHealth);

    if (m_health <= 0.0f && old > 0.0f)
    {
        if (OnDeath)
            OnDeath(m_health, m_maxHealth);
    }
}

void HealthComponent::Render(Camera2D& camera)
{
    Vector2 pos = CoordinateConversion::WorldToScreen(GetOwner()->GetPosition(), camera);
    std::string text = std::to_string(m_health);
    //App::Print(pos.x, pos.y, text.c_str());
}
