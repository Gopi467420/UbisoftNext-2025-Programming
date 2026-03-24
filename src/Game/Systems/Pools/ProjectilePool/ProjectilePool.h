#pragma once
#include <vector>
#include "../Game/Gameplay/Pooled Entities/Projectile/Projectiles.h"
#include "../Game/FrameWork/Structs/Structs.h"

class Scene;
class ProjectilePool
{
public:

    ProjectilePool() = default;

    void Init(uint32_t max, Scene& scene);
    void Update(float dt, const Vector2& basePos, const Enemydata& enemies);
    MovementContext BuildProjectileMovementCtx() const;
    MovementContext UpdateProjectileMovementCtx();
    void Render(Camera2D& cam);
    Projectiles* Spawn(const Vector2& pos, Vector2 direction, ProjectileType type, int level, const Vector2& basePos);
    void DeactivateAll();

private:
    std::vector<Projectiles*> entities; 

    //Shared
    std::vector<Vector2> positions; 
    std::vector<Vector2> directions;
    std::vector<float> lifetimes;    
    std::vector<float> damages;   
    std::vector<float> speeds;
    std::vector<ProjectileType> types;

    Scene* m_scene;
    
    
    //Aoe
    std::vector<float>   aoeRadius;



    std::vector<float> targetIndex;
    std::vector<float> acquireRadius;
    std::vector<float> turnRate;
    uint32_t aliveCount = 0;

    //homing and high value 
    std::vector<Vector2> sweepCenters;
    std::vector<float>   sweepAngle;
    std::vector<float>   sweepRadius;
    std::vector<float>   sweepAngularSpeed;

    std::vector<Vector2> hvTargetPoint;     // for HighValueTarget “duplicate at point”
    std::vector<float>   hvLife;            // optional, can reuse lifetimes

    std::vector<uint32_t> homingTargetId;   // pool index into EnemyPool (INVALID = 0xFFFFFFFF)
    std::vector<float>    homingTurnRate;
    std::vector<float>    homingAcquireRadius;


    std::unique_ptr<Projectiledata> m_projectileData;
   
   
    void SwapRemove(uint32_t i);



     bool expired;
     bool inactive;


};



