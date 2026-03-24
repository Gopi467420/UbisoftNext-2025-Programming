#include "../Game/Systems/Pools/ProjectilePool/ProjectilePool.h"
#include "../Game/Gameplay/Pooled Entities/Projectile/Projectiles.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h"
#include "../Game/Gameplay/Pooled Entities/Enemy/Enemy.h"
#include "../Game/Math/Utils/Utils.h"
#include "../Game/Core/CoordinateConversion/CoordinateConversion.h"
#include "../Game/Core/Scene/Scene(BaseClass)/Scene.h"
#include "../Game/FrameWork/Structs/Structs.h"

#include"../Game/Core/MovementSystem/MovementSystem.h"
#include <assert.h>


struct ProjectileArchetype { float damage; float lifetime; float speed; ShapeData shape; };
static ProjectileArchetype gProjectilelookUpTable[]{ { 100, 1, 900, SD_PolygonShape{ 6,40,ShapeColor::Cyan }},{ 200, 15, 1000.0f,SD_PolygonShape{ 3,15,ShapeColor::Green } },{ 500, 20, 2000.0f,SD_CircleShape{ 30,ShapeColor::Gray } },{ 300.0f, 10, 300.0f,SD_PolygonShape{ 3,20 } } };
struct ProjectileLevelUpgrade
{
    float damageMult = 1.0f; float lifetimeMult = 2.5f; float speedMult = 1.0f;
    
};
static ProjectileLevelUpgrade gProjectileUpgrades[4][5] =
{
    // Rocket
    {
        {1.0f, 1.0f, 1.0f}, // level 1
        {1.2f, 1.0f, 1.0f}, // level 2
        {1.5f, 1.0f, 1.0f}, // level 3
        {2.0f, 1.2f, 1.0f}, // level 4
        {2.5f, 1.5f, 1.2f }  // level 5
    },

    // Sweep
    {
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.2f, 1.0f },
        {1.0f, 1.5f, 1.0f},
        {1.2f, 2.0f, 1.0f},
        {1.5f, 2.5f, 1.0f}
    },

    // Homing
    {
        {1.0f, 1.0f, 0.5f},
        {1.1f, 1.0f, 1.1f},
        {1.2f, 1.0f, 1.2f},
        {1.3f, 1.0f, 1.3f},
        {1.5f, 1.0f, 1.5f}
    },

    // HighValueTarget
    {
        {1.0f, 1.0f, 1.0f},
        {1.5f, 1.0f, 1.0f},
        {2.0f, 1.0f, 1.0f},
        {2.5f, 1.0f, 1.0f},
        {3.0f, 1.0f, 1.0f}
    }
};

void ProjectilePool::Init(uint32_t max, Scene& scene)
{
    m_projectileData = std::make_unique<Projectiledata>();
   
    m_projectileData->positions.resize(max);
    m_projectileData->projectiles.resize(max);
    m_projectileData->direction.resize(max);

    m_projectileData->lifetime.resize(max);
    m_projectileData->damage.resize(max);
    m_projectileData->speed.resize(max);
    m_projectileData->type.resize(max);

    // sweep
    m_projectileData->sweepCenters.resize(max);
    m_projectileData->sweepAngle.resize(max);
    m_projectileData->sweepAngularSpeed.resize(max);
    m_projectileData->sweepRadius.resize(max);

    // homing
    m_projectileData->targetIndex.resize(max);
    m_projectileData->acquireRadius.resize(max);
    m_projectileData->turnRate.resize(max);


    for (uint32_t i = 0; i < max; ++i)
    {
        Projectiles* p = new Projectiles();

        p->SetScene(scene);
        p->Init();
        p->Deactivate();
        m_projectileData->projectiles[i] = p;
    }
   



    /*directions.resize(max);
    lifetimes.resize(max);
    damages.resize(max);
    types.resize(max);
    speeds.resize(max);
    aliveCount = 0;

    sweepCenters.resize(max);
    sweepRadius.resize(max);
    sweepAngle.resize(max);
    sweepAngularSpeed.resize(max);

    targetIndex.resize(max);
    acquireRadius.resize(max);
    turnRate.resize(max);

    aoeRadius.resize(max);


    hvTargetPoint.resize(max);
    hvLife.resize(max);

    homingTargetId.resize(max);
    homingTurnRate.resize(max);
    homingAcquireRadius.resize(max);*/
    

    





}

Projectiles* ProjectilePool::Spawn(const Vector2& pos, Vector2 direction, ProjectileType type, int level, const Vector2& basePos)
{




    if (m_projectileData->aliveCount >= m_projectileData->projectiles.size()) return nullptr;

    const uint32_t id = m_projectileData->aliveCount++;
    direction = direction.Normalize();

    // lookup stats (your existing tables)
    const auto& base = gProjectilelookUpTable[(int)type];
    level = Utils::Clamp(level, 1, 5);
    const auto& up = gProjectileUpgrades[(int)type][level - 1];

    m_projectileData->type[id] = type;
    m_projectileData->positions[id] = pos;
    m_projectileData->direction[id] = direction;
    m_projectileData->damage[id] = base.damage * up.damageMult;
    m_projectileData->lifetime[id] = base.lifetime * up.lifetimeMult;
    m_projectileData->speed[id] = base.speed * up.speedMult;

    // defaults
    m_projectileData->targetIndex[id] = -1;

    // Sweep init
    if (type == ProjectileType::Sweep)
    {
        Vector2 d = pos - basePos;
        m_projectileData->sweepCenters[id] = basePos;
        m_projectileData->sweepRadius[id] = (d.Length() > 0.001f) ? d.Length() : 120.0f;
        m_projectileData->sweepAngle[id] = atan2f(d.y, d.x);
        m_projectileData->sweepAngularSpeed[id] = 0.0035f;
    }

    // Homing init
    if (type == ProjectileType::Homing)
    {
        m_projectileData->acquireRadius[id] = 999999.0f; // unused now, but ok
        m_projectileData->turnRate[id] = 8.0f;           // IMPORTANT
        m_projectileData->targetIndex[id] = -1;
    }

    // Zone init
    if (type == ProjectileType::Zone)
    {
        m_projectileData->acquireRadius[id] = 600.0f;
        m_projectileData->turnRate[id] = 0.01f;
    }

    Projectiles* p = m_projectileData->projectiles[id];
    if (p)
    {
        p->SetPosition(pos);
        p->SetDamageAmount(m_projectileData->damage[id]);
        p->Activate();
        p->SetShapeData(base.shape);
    }
    return p;






}

void ProjectilePool::DeactivateAll()
{
    for (uint32_t i = 0; i < m_projectileData->aliveCount; i++)
    {
        Projectiles* p = m_projectileData->projectiles[i];
        if (p)
        {
            p->Deactivate();
        }
    }

    m_projectileData->aliveCount = 0;

}




static MovementType ToMoveType(ProjectileType pt)
{
    switch (pt)
    {
    case ProjectileType::Rocket:  return MovementType::Straight;
    case ProjectileType::Sweep:   return MovementType::SweepOrbit;
    case ProjectileType::Homing:  return MovementType::Precision; // or Homing if you have it
    case ProjectileType::Zone:    return MovementType::Precision; // if you want same logic
    default:                      return MovementType::Straight;
    }
}


void ProjectilePool::Update(float dt, const Vector2& basePos, const Enemydata& enemies)
{
    MovementContext ctx = UpdateProjectileMovementCtx();

    TargetView targets{};
    targets.targetPositions = enemies.positions.data();
    targets.targetTypes = enemies.types.data();   // <-- add this
    targets.targetCount = enemies.aliveCount;


    uint32_t i = 0;
    while (i < m_projectileData->aliveCount)
    {
        Projectiles* p = m_projectileData->projectiles[i];

        if (p && p->IsActive())
        {
            MovementType mt = ToMoveType(m_projectileData->type[i]);
            MovementSystem::Move(mt, ctx, i, dt, basePos, targets);
            m_projectileData->lifetime[i] -= dt;

            p->SetPosition(m_projectileData->positions[i]);
            p->Update(dt);


            if (m_projectileData->lifetime[i] <= 0.0f)
            {
                p->Deactivate();
            }
        }

        if (!p || !p->IsActive())
        {
            SwapRemove(i);
        }
        else
        {
            i++;
        }
    }

   
}

MovementContext ProjectilePool::UpdateProjectileMovementCtx()
{
    MovementContext ctx{};
    ctx.positions = m_projectileData->positions.data();
    ctx.directions = m_projectileData->direction.data();
    ctx.speeds = m_projectileData->speed.data();

    // sweep
    ctx.sweepCenters = m_projectileData->sweepCenters.data();
    ctx.sweepAngle = m_projectileData->sweepAngle.data();
    ctx.sweepAngularSpeed = m_projectileData->sweepAngularSpeed.data();
    ctx.sweepRadius = m_projectileData->sweepRadius.data();

    // homing/zone
    ctx.targetIndex = m_projectileData->targetIndex.data();
    ctx.acquireRadius = m_projectileData->acquireRadius.data();
    ctx.turnRate = m_projectileData->turnRate.data();
    return ctx;
}







void ProjectilePool::Render(Camera2D& cam)
{ 
    for (int i = 0; i < m_projectileData->aliveCount; i++)
    {
        Projectiles* p = m_projectileData->projectiles[i];
        if (p)
        {
            p->Render(cam);
            std::string text = "" + std::to_string(p->GetDamageAmount());
            //App::Print(CoordinateConversion::WorldToScreen(p->GetPosition(), cam).x, CoordinateConversion::WorldToScreen(p->GetPosition(), cam).y, text.c_str());
        }
    }


    std::string text = "PAliveCount: " + std::to_string(m_projectileData->aliveCount);
    App::Print(50, 90, text.c_str());

}




void ProjectilePool::SwapRemove(uint32_t i)
{
    uint32_t last = m_projectileData->aliveCount - 1;

    m_projectileData->projectiles[i] = m_projectileData->projectiles[last];
    m_projectileData->positions[i] = m_projectileData->positions[last];
    m_projectileData->direction[i] = m_projectileData->direction[last];

    m_projectileData->lifetime[i] = m_projectileData->lifetime[last];
    m_projectileData->damage[i] = m_projectileData->damage[last];
    m_projectileData->speed[i] = m_projectileData->speed[last];
    m_projectileData->type[i] = m_projectileData->type[last];

    m_projectileData->sweepCenters[i] = m_projectileData->sweepCenters[last];
    m_projectileData->sweepAngle[i] = m_projectileData->sweepAngle[last];
    m_projectileData->sweepAngularSpeed[i] = m_projectileData->sweepAngularSpeed[last];
    m_projectileData->sweepRadius[i] = m_projectileData->sweepRadius[last];

    m_projectileData->targetIndex[i] = m_projectileData->targetIndex[last];
    m_projectileData->acquireRadius[i] = m_projectileData->acquireRadius[last];
    m_projectileData->turnRate[i] = m_projectileData->turnRate[last];
   
    m_projectileData->aliveCount--;
}
