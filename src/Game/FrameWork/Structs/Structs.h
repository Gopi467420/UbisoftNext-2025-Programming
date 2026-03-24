#pragma once
#include "../Game/Math/Vector/Vector2.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h"
#include <vector>
#include <variant>
#include <string>
#include <cstdint>
#include <memory>

class Entity;
class Enemy;
class Projectiles;

struct CollisionEvent
{
    Entity* entityA;
    Entity* entityB;
  //  Vector2 contactPoint;
  //  Vector2 normal;
  //  bool isTrigger;
};



struct MoveEvent
{
    Entity* Caller;
    Entity* Target;
    float speed = 0.0f;
};


struct ReportedTarget
{
public:    

    Entity* ReportedEntity;
    Vector2 ReportedPosition;

};

struct SD_CircleShape
{

    float radius = 0.0f;
    ShapeColor color;
};

struct SD_BoxShape
{

    float width = 0.0f;
    float height = 0.0f;
    ShapeColor color;
};

struct SD_PolygonShape
{
   int sides;
   float radius = 0.0f;
   ShapeColor color;
};

struct Enemydata
{
    uint32_t aliveCount = 0;   
    std::vector<Enemy*> enemy;
    std::vector<Vector2> positions;
    std::vector<Vector2> direction;
    std::vector<float> speeds;
    std::vector<float> health;
    std::vector<float> damage;
    std::vector<int> loot;
    std::vector<EEnemyType> types;
    std::vector<Entity*> targets;

};

struct Projectiledata
{
    uint32_t aliveCount = 0;

    std::vector<Projectiles*> projectiles;
    std::vector<ProjectileType> type;
    std::vector<Vector2> positions;
    std::vector<Vector2> direction;
    std::vector<float> lifetime;
    std::vector<float> damage;
    std::vector<float> speed;   

    // Sweep
    std::vector<Vector2> sweepCenters;
    std::vector<float> sweepAngle;
    std::vector<float> sweepAngularSpeed;
    std::vector<float> sweepRadius;

    // Homing/Zone
    std::vector<int>   targetIndex;
    std::vector<float> acquireRadius;
    std::vector<float> turnRate;
};

using ShapeData = std::variant< SD_CircleShape, SD_BoxShape, SD_PolygonShape >;

struct EnemyStats
{
    EnemyStats() = default;

    EnemyStats(float speed, float health, float damage, float loot, Entity* target, ShapeData shape)
        : m_speed(speed), m_health(health), m_damage(damage), m_loot(loot), m_target(target), m_shape(shape) { }

    float m_speed = 0;
    float m_health = 0;
    float m_damage = 0;
    float m_loot = 0;
    float m_mass = 0;
    ShapeData m_shape;
    
    Entity* m_target = nullptr;

}; 


struct MovementContext
{
    Vector2* positions = nullptr;
    Vector2* directions = nullptr;
    float* speeds = nullptr;

    // SweepOrbit
    Vector2* sweepCenters = nullptr;
    float* sweepAngle = nullptr;
    float* sweepAngularSpeed = nullptr;
    float* sweepRadius = nullptr;

    // Homing / ZoneHoming
    int* targetIndex = nullptr;
    float* acquireRadius = nullptr;
    float* turnRate = nullptr;
};