//Instead of checking collisions against all colliders every frame this script divides world space into square cells and 
// stores which colliders are inside each cell
// Query returns all nearby colliders only
#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>

class CircleComponent;
struct Vector2;

struct GridCord
{
    int x;
    int y;
    bool operator==(const GridCord& other) const { return x == other.x && y == other.y; }
};

//Hashing
struct GridCordHash
{
    size_t operator()(const GridCord& cord) const
    { 
        return std::hash<int>()(cord.x) ^ (std::hash<int>()(cord.y) << 1);
    }
};

class GridHash
{
public:
    explicit GridHash(float cellSize); 

private:
    float CellSize;
    std::unordered_map<GridCord, std::unordered_set<CircleComponent*>, GridCordHash> m_grid;

public:
    GridCord WorldToGridCord(const Vector2& position);

    void Insert(CircleComponent* collider, const Vector2& center, float radius);
    void Remove(CircleComponent* collider, const Vector2& center, float radius);
    void Update(CircleComponent* collider, const Vector2& oldCenter, const Vector2& newCenter, float r);
    std::vector<CircleComponent*> Query(const Vector2& center, float radius);
    void Clear();

    std::vector< CircleComponent*> GetAllColliders();
    int GridHash::GetTotalColliders() const;



};



