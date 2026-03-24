#include "ParticleSystem.h"
#include "app.h"
#include "../Game/Core/GameManager/GameManager.h"
#include "../Game/Core/CoordinateConversion/CoordinateConversion.h"
#include <cmath>
#include <cstdlib>

void ParticleSystem::Init(int maxParticles)
{
    particles.resize(maxParticles);
    for (auto& p : particles)
        p.active = false;
}

Particle* ParticleSystem::GetFreeParticle()
{
    for (auto& p : particles)
        if (!p.active) return &p;

    return nullptr;
}

void ParticleSystem::EmitExplosion(int count, const Vector2& origin, float speed)
{
    int spawned = 0;

    for (auto& p : particles)
    {
        if (p.active) continue;

        p.active = true;
        p.position = origin;

        // Use caller speed (fallback if caller passes 0)
        const float baseSpeed = (speed > 0.0001f) ? speed : 10.0f;

        float angle = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 2.0f * 3.14159f;
        Vector2 dir(std::cos(angle), std::sin(angle));

        float speedVariation = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 0.6f + 0.7f; // 0.7 to 1.3
        float particleSpeed = baseSpeed * speedVariation;

        p.velocity = dir * particleSpeed;

        p.rotation = angle;
        p.rotationSpeed = 2.0f;

        p.scale = 5.0f + (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 5.0f; // 5-10
        p.life = 60.0f;
        p.maxLife = 60.0f;

        p.behavior = EParticleBehavior::Explosion;

        if (++spawned >= count)
            break;
    }
}

// If you don’t need Powerup yet, keep it valid but empty:
void ParticleSystem::Powerup()
{
    // TODO: implement later
}

void ParticleSystem::UpdateExplosion(Particle& p)
{
    p.position += p.velocity;

    float t = p.life / p.maxLife;
    p.scale = 10.0f * t;
}

void ParticleSystem::Update(float deltaTime)
{
    (void)deltaTime; // unused for now (remove when you convert to dt-based logic)

    for (auto& p : particles)
    {
        if (!p.active) continue;

        p.life -= 1.0f; // frame-based for now
        if (p.life <= 0.0f)
        {
            p.active = false;
            continue;
        }

        switch (p.behavior)
        {
        case EParticleBehavior::Explosion:
            UpdateExplosion(p);
            break;
        default:
            break;
        }
    }
}

void ParticleSystem::Render(Camera2D cam)
{
    for (auto& p : particles)
    {
        if (!p.active) continue;

        Vector2 screen = CoordinateConversion::WorldToScreen(p.position, cam);
        Vector2 dir(std::cos(p.rotation), std::sin(p.rotation));
        Vector2 end = screen + dir * p.scale;

        App::DrawLine((int)screen.x, (int)screen.y, (int)end.x, (int)end.y, 1, 1, 1);
    }
}
