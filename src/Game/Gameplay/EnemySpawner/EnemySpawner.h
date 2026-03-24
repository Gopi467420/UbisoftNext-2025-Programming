#pragma once



#include <vector>
#include "../Game/Math/Vector/Vector2.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h" // EEnemyType

class EnemyPool;
class Scene;
class Entity;

struct ActiveWave
{
    EEnemyType type{};
    Entity* target = nullptr;

    int remaining = 0;

    float minDist = 0, maxDist = 0;
    float minSpread = 0, maxSpread = 0;

    float spawnInterval = 0.1f;
    float acc = 0.0f;

    std::vector<Vector2> spawnPoints;
};

class EnemySpawner
{
public:
    EnemySpawner(Scene& scene, EnemyPool& pool);

    void Update(float dt);
    void SpawnEnemy(int numOfSpawnPoints, int numOfEnemy, EEnemyType spawnType, Entity* target);
    void RequestWave(int numOfSpawnPoints, int numOfEnemy, EEnemyType spawnType, Entity* target);


    std::vector<Vector2> m_spawnPoints;
private:
    Scene& m_scene;
    EnemyPool& m_pool;

    std::vector<ActiveWave> m_waves;
};
