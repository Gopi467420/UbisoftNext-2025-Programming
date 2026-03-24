#include "EnemyPool.h"
#include "../Game/FrameWork/Structs/Structs.h"
#include "../Game/Gameplay/Pooled Entities/Enemy/Enemy.h"
#include "../Game/Core/CoordinateConversion/CoordinateConversion.h"
#include"../Game/Core/MovementSystem/MovementSystem.h"
#include "../Game/Core/Scene/Scene(BaseClass)/Scene.h"
#include "../Game/Components/Physics/CollisionComponents/CircleComponent.h"
#include "app.h"

struct EnemyArchetype
{
    float health;
    float damage;
    float speed;
    float mass;
    float loot;
};

static EnemyArchetype gEnemyLookupTable[] =
{
    { 2500, 600,  30, 1,  500 }, // Bomber
    { 3000, 700,  50, 2,  500 }, // Airborne
    { 1000, 150,  60, 4,   50 }, // WallBreaker
    {   50,  50, 100, 4,   10 }, // Swarm
};
void EnemyPool::Init(uint32_t max, Scene& scene)
{
    m_enemyData = std::make_unique<Enemydata>();
	m_enemyData->enemy.resize(max);
    m_enemyData->positions.resize(max); 
    m_enemyData->direction.resize(max);
    m_enemyData->speeds.resize(max);
    m_enemyData->health.resize(max);
    m_enemyData->damage.resize(max);
    m_enemyData->types.resize(max);
    m_enemyData->targets.resize(max);
    m_enemyData->loot.resize(max);
    m_enemyData->aliveCount = 0;

	for (int i = 0; i < max; i++)
	{
       
        Enemy* e = new Enemy();
    e->SetScene(scene);   // IMPORTANT
    e->Init();            // IMPORTANT (creates components incl collider)
    e->Deactivate();      // start inactive / unregistered
    //e->SetPoolIndex(i);

    m_enemyData->enemy[i] = e;

	}


    
}




void EnemyPool::Update(Scene& scene, float dt, const Vector2& targetPos, float targetRadius)
{

    MovementContext ctx = UpdateEnemyMovementCtx();

    uint32_t i = 0;
    while (i < m_enemyData->aliveCount)
    {
        Enemy* e = m_enemyData->enemy[i];

        
        // Move SOA
        MovementSystem::MoveToTarget(ctx, targetPos, i, dt);
        scene.GetPhysics().ApplyEnemySeparation(i, *m_enemyData, dt);
        // Sync entity transform
        e->SetPosition(m_enemyData->positions[i]);
        e->Update(dt);

       

        // Reach base -> kill + remove
        /*float enemyR = 0.0f;
        if (auto* c = e->GetCollider()) enemyR = c->GetRadius();

        Vector2 d = targetPos - m_enemyData->positions[i];
        float reach = targetRadius + enemyR;
        if (d.LengthSquared() <= reach * reach)
        {
                     // unregister collider
           // SwapAndRemove((int)i);   
           // e->Deactivate();   // remove from active region



            continue;
        }*/
        
        if (!e || !e->IsActive())
        {
            SwapAndRemove((int)i);
            continue; // re-process swapped one
        }
        else
        {
            ++i;

        }

       
    }
}

MovementContext EnemyPool::UpdateEnemyMovementCtx()
{
    MovementContext ctx{};
    ctx.positions = m_enemyData->positions.data();
    ctx.directions = m_enemyData->direction.data();
    ctx.speeds = m_enemyData->speeds.data();


    return ctx;
}

void EnemyPool::SwapAndRemove(int i)
{ 
    int last = (int)m_enemyData->aliveCount - 1;
    if (i < 0 || i > last) return;

    // Swap pointers so we DON'T lose the removed enemy (it goes to [last])
    std::swap(m_enemyData->enemy[i], m_enemyData->enemy[last]);

    // Swap SOA data too
    std::swap(m_enemyData->positions[i], m_enemyData->positions[last]);
    std::swap(m_enemyData->direction[i], m_enemyData->direction[last]);
    std::swap(m_enemyData->speeds[i], m_enemyData->speeds[last]);
    std::swap(m_enemyData->health[i], m_enemyData->health[last]);
    std::swap(m_enemyData->damage[i], m_enemyData->damage[last]);
    std::swap(m_enemyData->types[i], m_enemyData->types[last]);
    std::swap(m_enemyData->targets[i], m_enemyData->targets[last]);
    std::swap(m_enemyData->loot[i], m_enemyData->loot[last]);

    m_enemyData->aliveCount--;

   
}

void EnemyPool::Render(Camera2D& cam)
{
    for (int i = 0; i < m_enemyData->aliveCount; i++)
    {
        Enemy* e = m_enemyData->enemy[i];
        if (e )
        {
            if (e && !e->IsActive())// App::Print(50, 130, "FOUND INACTIVE INSIDE aliveCount!");

            std::string text =
                "ptr=" + std::to_string((int)e->GetEnemyType()) +
                " soa=" + std::to_string((int)m_enemyData->types[i]);

           // App::Print(CoordinateConversion::WorldToScreen(e->GetPosition(), cam).x, CoordinateConversion::WorldToScreen(e->GetPosition(), cam).y, text.c_str());
           

           // text = "" + std::to_string((int)(e->GetEnemyType()));
            //App::Print(CoordinateConversion::WorldToScreen(e->GetPosition(), cam).x, CoordinateConversion::WorldToScreen(e->GetPosition(), cam).y, text.c_str());
            e->Render(cam);
            
        }
    }


    std::string text = "EAliveCount: " + std::to_string(m_enemyData->aliveCount);
    App::Print(50, 70, text.c_str());
}

void EnemyPool::DeactivateAll()
{

    for (uint32_t i = 0; i < m_enemyData->aliveCount; i++)
    {
        Enemy* e = m_enemyData->enemy[i];
        if (e)
        {
            e->Deactivate();
        }
    }

    m_enemyData->aliveCount = 0;
}

Enemy* EnemyPool::SpawnEnemy(EEnemyType type, Vector2 position)
{

    if (m_enemyData->aliveCount >= m_enemyData->enemy.size()) return nullptr;

    uint32_t id = m_enemyData->aliveCount++;
    const EnemyArchetype& a = gEnemyLookupTable[(int)type];

    Enemy* e = m_enemyData->enemy[id];
    if (!e) { m_enemyData->aliveCount--; return nullptr; }

    // Write SOA first
    m_enemyData->positions[id] = position;
    m_enemyData->direction[id] = Vector2(0, 0);    
    m_enemyData->types[id] = type;
    m_enemyData->speeds[id] = a.speed;
    m_enemyData->health[id] = a.health;
    m_enemyData->damage[id] = a.damage;
    m_enemyData->loot[id] = a.loot;

   
    if (e)
    {
        e->SetEnemyType(type);
        e->SetShapeData();
        e->SetHealth(m_enemyData->health[id]);
        e->SetDamage(m_enemyData->damage[id]);
        m_enemyData->positions[id] = position;
        e->SetPosition(position);  

        e->Activate();
        return e;
    }
}


