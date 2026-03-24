#pragma once
#include "../Game/Systems/Pools/ProjectilePool/ProjectilePool.h"
#include "../Game/Systems/Pools/EnemyPool/EnemyPool.h"
#include "../Game/Core/Scene/Scene(BaseClass)/Scene.h"
#include "../Game/Core/Factory/EntityFactory.h"
#include "../Game/Core/Camera/Camera.h"
#include "../Game/Core/World/World.h"
#include "../Game/FrameWork/Timers/Timer.h"
#include "../Game/Systems/Pools/GemsPool/GemPool.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h"
#include "../Game/Systems/Particles/ParticleSystem.h"

#include <unordered_map>
#include <memory>

struct LevelSpawnPlan
{
	int swarmLeft = 0;
	int bomberLeft = 0;
	int wallLeft = 0;
	int airLeft = 0;

	float acc = 0.0f;
	float interval = 0.35f; 
};


using Id = uint32_t;
class Entity;
class GObject;
class MovementSystem;

enum class EnemyTargetTypes
{
	Base,
	Player,
	Weapons,
	Walls

};

enum SoundFlags;
class GameScene : public Scene
{
public:
	GameScene();

public:
	void Init() override;
	void LevelUp();
	void Update(float deltaTime) override;
	void RecomputeSpawnTimers();
	void GenerateCollisionsEventsForAll();
	void SpawnEnemyWavesSimple(float dt);
	void SpawnEnemyWaves(float dt);
	void BuildSpawnPlanForLevel();
	void SetCurrentLevel();
	void Render() override;

private:
	int m_lastLevelGemCheckpoint;
	int m_currentlevel;
	std::vector<ReportedTarget> m_reportedTargets;
	std::vector<MoveEvent> m_moveEvents;
	EntityFactory m_factory;	
	EnemyTargetTypes m_enemyTargetTypes;
	ProjectilePool m_projectilePool;	
	GemPool m_gemPool;
	Id m_playerId = 0;	
	Id m_baseId = 0;
	Id m_testobj = 0;
	bool bPlayerCanFaceMouse();
	LevelSpawnPlan m_plan;
	void DispatchMoveEvents(float deltaTime);
	ParticleSystem m_particles;
	
	
	Enemy* _enemy;
	bool m_hasDroppedGem = false;
	ProjectileType m_currentProjectile = ProjectileType::Sweep;
public:
	void Fire();
	void MoveBase();
	void SpawnEnemiesSimple(float dt);

	void Shutdown();
	void Restart();
	

	void PlayEnemyHitSound(const char* filename) override;

	void PlayBaseHitSound(const char* filename) override;

	

	
	static Vector2 GameScene::RandomSpawnAround(const Vector2& center, float minR, float maxR);
	
	void NextWeapon();	
	void EmitExplosion(Vector2 pos) override;
	GObject* basegobjectref;
    void AddMoveEvents(Entity* caller, Entity* target, float speed);	
	bool m_basemoved;
	
	Enemy* enemy;

	float m_spawnMultiplier = 1.0f;   // tweak to test: 0.5 = easier, 2.0 = harder
	float m_spawnRateScale = 1.0f;

	void ReportTarget(ReportedTarget report) override;


	Timer m_enemySpawnTimer;
	int m_enemiesToSpawn = 0;

	

	
	void SpawnGem(Vector2 pos, int value) override;

	std::unique_ptr<EnemyPool> m_enemyPool;

	
	
	
	Timer m_bomberTimer;
	Timer m_wallTimer;
	Timer m_airborne;


	float m_basehealth;
	float m_wallIntegrity;
	float m_baselevel;
	float m_noOfGems;

	
	

	float GetBaseHealth() const { return m_basehealth; }
	float GetWallIntegrity() const { return m_wallIntegrity; }
	
	float GetGemCount() const { return m_noOfGems; }


	bool m_shootinputbuffered;

	Timer* m_spawnTimer;
	int m_spawnPerWave = 5;

	Timer* m_spawnSwarm = nullptr;
	Timer* m_spawnWallBreaker = nullptr;
	Timer* m_spawnBomber = nullptr;
	Timer* m_spawnAirborne = nullptr;

	int m_enemyselectcounter = 0;
	void CameraShake() override;
};
	
	


