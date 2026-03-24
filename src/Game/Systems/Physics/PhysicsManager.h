#pragma once
#include "../Game/FrameWork/Structs/Structs.h"
#include "../Game/Core/GridHash/GridHash.h"
#include "../Game/Math/Vector/Vector2.h"
#include <unordered_set>
#include <vector>
#include <memory>

struct PairKey
{
    const void* a;
    const void* b;
};

struct PairHash
{
    size_t operator()(const PairKey& k) const noexcept
    {
        auto ha = std::hash<const void*>{}(k.a);
        auto hb = std::hash<const void*>{}(k.b);
        return ha ^ (hb + 0x9e3779b97f4a7c15ull + (ha << 6) + (ha >> 2));
    }
};

struct PairEq
{
    bool operator()(const PairKey& x, const PairKey& y) const noexcept
    {
        return x.a == y.a && x.b == y.b;
    }
};



class CircleComponent;
class GridHash;
class Enemy;




class PhysicsManager
{

public:
    explicit PhysicsManager(GridHash& grid);

private:
    GridHash& m_grid;
    std::vector<CollisionEvent> m_collisionEvents;

public:
    
    void Register(CircleComponent* collider);
    void Unregister(CircleComponent* collider);    
    void OnOwnerMoved(CircleComponent* collider,const Vector2& oldPos, const Vector2& newPos); //Updates Grid

    //Resolve Collisions for all the Gameobjects in the level
    void ResolveAllCollision();

    void ApplyEnemySeparation(uint32_t i, Enemydata& data, float dt);

    const std::vector<CollisionEvent>& GetCollisionEvents() const;
    void ClearCollisionEvents();
   
    void SlideVelocity(CircleComponent* mover, Vector2& velocity);
   


};
