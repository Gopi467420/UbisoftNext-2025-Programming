#pragma once
#include <vector>
#include "../Game/Math/Vector/Vector2.h"
#include "../Game/Core/Camera/Camera.h"

enum class EParticleBehavior
{
    None,
    Explosion,
    PowerUp,
    Confetti
    
};

struct Particle
{
    Vector2 position;
    Vector2 velocity;

    float rotation = 0.0f;       // for line direction
    float rotationSpeed = 0.0f;

    float scale = 10.0f;         // length of line
    float life = 0.0f;           // remaining life (frames)
    float maxLife = 0.0f;

    EParticleBehavior behavior = EParticleBehavior::None;
    bool active = false;
};

class ParticleSystem
{
public:
    void Init(int maxParticles);

    void Update(float deltaTime);
    void Render(Camera2D cam);

    // Emitters
    void EmitExplosion(int count, const Vector2& origin, float speed);
    void Powerup(); 
    void Confetti(); 

private:
    std::vector<Particle> particles;

    Particle* GetFreeParticle();
    void UpdateExplosion(Particle& p);
};
