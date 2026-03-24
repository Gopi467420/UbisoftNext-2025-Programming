#include "EnemySpawner.h"
#include "../Game/Systems/Pools/EnemyPool/EnemyPool.h"
#include "../Game/Math/Utils/Utils.h"

EnemySpawner::EnemySpawner(Scene& scene, EnemyPool& pool)
    : m_scene(scene), m_pool(pool)
{

}





void EnemySpawner::SpawnEnemy(int numOfSpawnPoints, int numOfEnemy, EEnemyType spawnType, Entity* target)
{
    if (numOfSpawnPoints == 0) { numOfSpawnPoints = 1; }
    if (numOfEnemy == 0) { numOfEnemy = 1; }

    float minSpawnDistanceFromTarget;   float maxSpawnDistanceFromTarget;  float minSpreadatPoint; float maxSpreadatPoint;

    switch (spawnType)
    {
    case EEnemyType::ET_Bomber:      minSpawnDistanceFromTarget = 350; maxSpawnDistanceFromTarget = 400;   minSpreadatPoint = 20;  maxSpreadatPoint = 50;  break;
    case EEnemyType::ET_Airborne:    minSpawnDistanceFromTarget = 300; maxSpawnDistanceFromTarget = 350;   minSpreadatPoint = 1;  maxSpreadatPoint = 2;  break;
    case EEnemyType::ET_WallBreaker: minSpawnDistanceFromTarget = 300; maxSpawnDistanceFromTarget = 600;   minSpreadatPoint = 15;  maxSpreadatPoint = 40;  break;
    case EEnemyType::ET_Swarm:       minSpawnDistanceFromTarget = 300; maxSpawnDistanceFromTarget = 350;   minSpreadatPoint = 15;  maxSpreadatPoint = 40;     break;
    default:break;
    }

    m_spawnPoints.clear();

}