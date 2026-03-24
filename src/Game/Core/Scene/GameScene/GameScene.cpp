
#include "GameScene.h"
#include "../Game/Core/CoordinateConversion/CoordinateConversion.h"
#include "../Game/Core/Factory/EntityFactory.h"
#include "../Game/FrameWork/GObject/GObject.h"
#include "../Game/FrameWork/Structs/Structs.h"
#include "../Game/Gameplay/Player/Player.h"
#include "../Game/Gameplay/Base/Base.h"
#include "../Game/Math/Vector/Vector2.h"
#include "../Game/Math/Utils/Utils.h"
#include "../Game/Components/Physics/CollisionComponents/CircleComponent.h"
#include "../Game/Gameplay/EnemySpawner/EnemySpawner.h"
#include "../Game/Core/Camera/Camera.h"
#include "../Game/UI/HUD/HUD.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h"
#include "../Game/FrameWork/Shapes/Shape.h"
#include "../Game/Gameplay/Pooled Entities/Enemy/Enemy.h"
#include "../Game/Systems/Pools/EnemyPool/EnemyPool.h"
#include "../Game/Core/GameManager/GameManager.h"
#include "../Game/Core/MovementSystem/MovementSystem.h"

#include<assert.h>
#include "app.h"
#include <memory>

#include "../ContestAPI/SimpleSound.h"


GameScene::GameScene() :Scene(120) {}
void GameScene::Init()
{

   
    //Add more entities here 
	m_playerId = Register(m_factory.CreatePlayer());   
    m_baseId = Register(m_factory.CreateBase());
   
    m_enemyPool = std::make_unique<EnemyPool>();
   
    //Init more pools here
   m_projectilePool.Init(200, *this);
  
    m_gemPool.Init(5, *this);
    m_particles.Init(600);
    m_enemyPool->Init(200, *this);
    //Init memeber variables
  
    m_hud = std::make_unique<HUD>(*this);
  

    m_hud->Init();
    m_hud->SetBaseStats(100, 0, 1, 0);
    m_basemoved = true; //temp

   
    m_currentlevel = 1;
    m_spawnMultiplier = 2.0f; // test
    
    

    Base* base = GetEntityAs<Base>(m_baseId);
     basegobjectref = GetEntity(m_baseId);

   
     m_spawnTimer = new Timer();
    
     m_spawnTimer->Start(.1);
  
     m_spawnSwarm = new Timer();       m_spawnSwarm->Start(5);      // fast
     m_spawnWallBreaker = new Timer(); m_spawnWallBreaker->Start(0.1f);
     m_spawnBomber = new Timer();      m_spawnBomber->Start(.5f);
     m_spawnAirborne = new Timer();    m_spawnAirborne->Start(1.0f);
    

     //CSimpleSound::GetInstance().Initialize();
    
}



 
 static int frame = 0;
void GameScene::Update(float deltaTime)
{

    if (GetEntityAs<Base>(m_baseId)->GetBaseHealth() <= 0)
    {
       
        GameManager::Get().SetGameState(EGameState::EGS_End);
       

    }
   
   
    //for slowmo later

    float dt = deltaTime;

    for (auto& it : m_sceneObjects) 
    {
        GObject* obj = it.second.get();
        obj->Update(dt);

    }

    m_particles.Update(deltaTime);
   
    
     Base* base = GetEntityAs<Base>(m_baseId);
  

      m_camera.SetPosition((GetEntityAs<Player>(m_playerId)->GetPosition()));

      m_camera.Update(dt);
      
      SpawnEnemiesSimple(dt);
      
      if (m_spawnTimer->Update(dt))
      {
          if (m_enemyPool->GetEnemyData().aliveCount < 100)
          {
             // m_enemyPool->SpawnEnemy(EEnemyType::ET_WallBreaker, Vector2(Utils::RandomInt(-500, 500), Utils::RandomInt(-600, 600)));

          }
         
      }
   
    m_gemPool.Update(dt, base->GetPosition());
    m_hud->UpdateStats(GetEntityAs<Base>(m_baseId)->GetBaseHealth(), m_wallIntegrity, m_currentlevel,Utils::ClampInt(m_enemyKillCount,0,MAXINT));
    m_hud->Update(dt);

   
   SetCurrentLevel();
   SpawnEnemyWaves(dt);
     
   m_projectilePool.Update(dt, basegobjectref->GetPosition(), m_enemyPool->GetEnemyData());
   if((base)) 
   m_enemyPool->Update(*this,dt,base->GetPosition(),base->GetCollider()->GetRadius());
  //Debug
  // m_enemySpawner->SpawnEnemy(3, 2, EEnemyType::ET_Swarm, base);
   

  // if (GetEntityAs<Base>(m_baseId)->GetBaseHealth() < 0) { GameManager::Get().SetGameState(EGameState::EGS_End); }
   
   
  

     

        
GenerateCollisionsEventsForAll();
   
}

void GameScene::GenerateCollisionsEventsForAll()
{
    m_physics.ResolveAllCollision();

    // Dispatch collision events
    for (const CollisionEvent& ev : m_physics.GetCollisionEvents())
    {
        ev.entityA->OnCollision(ev.entityB);
        ev.entityB->OnCollision(ev.entityA);
    }

    m_physics.ClearCollisionEvents();

}


void GameScene::SpawnEnemyWaves(float dt)
{
    Entity* target = GetEntityAs<Base>(m_baseId);  
    int points = Utils::RandomInt(1, 2);
    int count = Utils::RandomInt(0, 3);
    points = 1; // sequence
    int SpawnrateS= 5;
    int SpawnrateW = 50 + SpawnrateS;
    int SpawnrateB = 100 + SpawnrateS;
    int SpawnrateA = 200 + SpawnrateS;


    //Utils::RandomInt(120, 150)
   
   
   
    

  


    
   


   
   
   
}

void GameScene::SetCurrentLevel()
{
    int checkpoint = (int)(m_enemyKillCount / Utils::RandomInt(10, 20));
    if (checkpoint > m_lastLevelGemCheckpoint)
    {
        m_currentlevel++;
        m_lastLevelGemCheckpoint = checkpoint;        
    }
}

void GameScene::Render()
{
   m_hud->Render();
  
   m_particles.Render(m_camera);

 
 
   Shape::DrawCircle3D(CoordinateConversion::GetMouseWorld(m_camera), 6.0f, ShapeColor::Cyan, 4.0f);
    for (auto& it : m_sceneObjects) { it.second->Render(m_camera); }
    

  m_projectilePool.Render(m_camera);


  m_enemyPool->Render(m_camera);
    
       
        std::string text = "Colliders: " + std::to_string(m_gridHash.GetTotalColliders());
        App::Print(50, 50, text.c_str());

         m_gemPool.Render(m_camera);
        
        
       if(m_shootinputbuffered)
           {
           App::Print(50, 90, "Fire");

           }

 }

bool GameScene::bPlayerCanFaceMouse(){ return true; }









void GameScene::AddMoveEvents(Entity* caller, Entity* target, float speed)
{
    MoveEvent ev;
    ev.Caller = caller;
    ev.Target = target;
    ev.speed = speed;
    m_moveEvents.push_back(ev);
}

void GameScene::ReportTarget(ReportedTarget report) 
{ 
   // m_basemoved = false;
    m_reportedTargets.push_back(report);
}

void GameScene::SpawnGem(Vector2 pos, int value)
{
    if (m_hasDroppedGem) return;
    GemType t = static_cast<GemType>( Utils::RandomInt(0, static_cast<int>(GemType::Count) - 1));   
   m_gemPool.Spawn(pos, t);
   m_gemcount += value;
   m_hasDroppedGem = false;
}

void GameScene::CameraShake()
{
    m_camera.StartShake(12.0f, 0.20f);
}







void GameScene::Fire()
{
    auto shooter = GetEntityAs<Player>(m_playerId);

    if (!shooter) return;
    m_shootinputbuffered = true;
    Vector2 dir = CoordinateConversion::GetMouseWorld(m_camera) - shooter->GetPosition();

    if (dir.Length() > 0.0001f) { shooter->SetPlayerFacing(dir.Normalize()); }
    else { shooter->SetPlayerFacing(Vector2(1.0f, 0.0f)); }

    Vector2 direction = (CoordinateConversion::GetMouseWorld(m_camera) - shooter->GetPosition()).Normalize();
   
    m_projectilePool.Spawn(shooter->GetSpawnPosition(), direction, m_currentProjectile, m_currentlevel, basegobjectref->GetPosition());

    m_shootinputbuffered = false;
  
}

void GameScene::NextWeapon()
{
    switch (m_currentProjectile)
    {
    case ProjectileType::Rocket: m_currentProjectile = ProjectileType::Homing; break;
    case ProjectileType::Sweep: m_currentProjectile=  ProjectileType::Rocket; break;
    case ProjectileType::Homing:m_currentProjectile =ProjectileType::Sweep;    break;
   
    default:  break;
    }
    
 
}

void GameScene::EmitExplosion(Vector2 pos)
{
    m_particles.EmitExplosion(100, pos, 10);
   
}
  



void GameScene::MoveBase()
{
    if (m_gemcount < 0) return;
    GetEntity(m_baseId)->SetPosition(GetEntity(m_playerId)->GetPosition());   
    m_basemoved = true;   
    m_gemcount -= 1000;
}


Vector2 GameScene::RandomSpawnAround(const Vector2& center, float minR, float maxR)
{
    float ang = (float)Utils::RandomInt(0, 6283) / 1000.0f;  // ~0..2pi
    float r = (float)Utils::RandomInt((int)minR, (int)maxR);
    return center + Vector2(cosf(ang), sinf(ang)) * r;
}

void GameScene::SpawnEnemiesSimple(float dt)
{
    if (!m_enemyPool) return;

    Base* base = GetEntityAs<Base>(m_baseId);
    if (!base) return;
    m_enemyselectcounter++;
    // safety cap so you don't overflow the pool
    const uint32_t alive = m_enemyPool->GetEnemyData().aliveCount;
    const uint32_t maxAlive = 300;
    if (alive >= maxAlive) return;

    const Vector2 basePos = base->GetPosition();

    float basemin = 300;
    float basemax = 600;

    // Swarm
    if (m_spawnSwarm && m_spawnSwarm->Update(dt))
    {
        Vector2 p = RandomSpawnAround(basePos, basemin, basemax);
        m_enemyPool->SpawnEnemy(EEnemyType::ET_Swarm, p);
        m_spawnSwarm->Start(0.01f); // reset interval
    }
   
   

    // WallBreaker
    if (m_spawnWallBreaker && m_spawnWallBreaker->Update(dt))
    {
        Vector2 p = RandomSpawnAround(basePos, basemin + 20, basemax + 30);
        m_enemyPool->SpawnEnemy(EEnemyType::ET_WallBreaker, p);
        m_spawnWallBreaker->Start(0.08f);
    }
   

    // Bomber
    if (m_spawnBomber && m_spawnBomber->Update(dt))
    {
        Vector2 p = RandomSpawnAround(basePos, basemin + 30, basemax + 40);
        m_enemyPool->SpawnEnemy(EEnemyType::ET_Bomber, p);
        m_spawnBomber->Start(.5f);
    }

  

    // Airborne
    if (m_spawnAirborne && m_spawnAirborne->Update(dt))
    {
        Vector2 p = RandomSpawnAround(basePos, basemin + 40, basemax + 40);
        m_enemyPool->SpawnEnemy(EEnemyType::ET_Airborne, p);
        m_spawnAirborne->Start(1.0f);
    }
    
    
}

void GameScene::Shutdown()
{
    CSimpleSound::GetInstance().Shutdown();
}

void GameScene::Restart()
{
    m_enemyPool->DeactivateAll();
    m_projectilePool.DeactivateAll();
    GetEntityAs<Base>(m_baseId)->SetBaseHealth();
    m_currentlevel = 1;
    m_enemyKillCount = 0;
    GameManager::Get().SetGameState(EGameState::EGS_Playing);
  
}


void GameScene::PlayEnemyHitSound(const char* filename)
{
    App::PlayAudio("./Data/TestData/EnemyHit.wav", true);
 }

void GameScene::PlayBaseHitSound(const char* filename)
{
    App::PlayAudio("./Data/TestData/BaseHit.wav", true);
}


