#pragma once
#include "../Game/FrameWork/Interfaces/Interfaces.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h"
#include <memory>


struct Vector2;
struct Camera2D;
struct Enemydata;
struct MovementContext;
class Enemy;

class EnemyPool
{

public:

	Enemy* SpawnEnemy(EEnemyType type, Vector2 position);

	void Init(uint32_t max, Scene& scene);
	void Update(Scene& scene, float dt, const Vector2& targetPos, float targetRadius);
	MovementContext UpdateEnemyMovementCtx();
	void SwapAndRemove(int i);
	void Render(Camera2D& cam);
	void DeactivateAll();

	std::unique_ptr<Enemydata> m_enemyData;

public:
	const Enemydata& GetEnemyData() const { return *m_enemyData; }

};

