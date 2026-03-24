#include "GridHash.h"
#include "../Game/Components/Physics/CollisionComponents/CircleComponent.h"
#include "../Game/Math/Vector/Vector2.h"
#include <cmath>

GridHash::GridHash(float cellSize): CellSize(cellSize)
{
}

void GridHash::Clear(){  m_grid.clear(); }

std::vector<CircleComponent*> GridHash::GetAllColliders()
{
    std::vector<CircleComponent*> result;
    std::unordered_set<CircleComponent*> unique;

    for (auto& cell : m_grid)
    {
        for (CircleComponent* c : cell.second)
        {
            if (unique.insert(c).second){ result.push_back(c); }
        }
    }
    return result;
}

int GridHash::GetTotalColliders() const
{
    std::unordered_set<CircleComponent*> unique;

    for (const auto& cell : m_grid)
    {
        for (CircleComponent* c : cell.second)
            unique.insert(c);
    }

    return (int)unique.size();
}



GridCord GridHash::WorldToGridCord(const Vector2& position)
{
    return { (int)std::floor(position.x / CellSize), (int)std::floor(position.y / CellSize) };
}


//Gets Collider Bounds
static void GetCellRange(const Vector2& center, float r, float cellSize, int& minX, int& maxX, int& minY, int& maxY)
{
    minX = (int)std::floor((center.x - r) / cellSize);
    maxX = (int)std::floor((center.x + r) / cellSize);
    minY = (int)std::floor((center.y - r) / cellSize);
    maxY = (int)std::floor((center.y + r) / cellSize);
}

void GridHash::Insert(CircleComponent* collider, const Vector2& center, float radius)
{
    //Get Collider Bounds
    int minX, maxX, minY, maxY;
    GetCellRange(center, radius, CellSize, minX, maxX, minY, maxY);

    //For each of the values find the corresponding grid cell and map that to the collider
    for (int x = minX; x <= maxX; ++x)
    {
        for (int y = minY; y <= maxY; ++y)
        {
            m_grid[{x, y}].insert(collider);
        }
            
    }
       
}

void GridHash::Remove(CircleComponent* collider, const Vector2& center, float radius)
{
    //Gets Collider bounds
    int minX, maxX, minY, maxY;
    GetCellRange(center, radius, CellSize, minX, maxX, minY, maxY);

    for (int x = minX; x <= maxX; ++x)
    {
        for (int y = minY; y <= maxY; ++y)
        {
            GridCord key{ x, y };
            auto it = m_grid.find(key);
            if (it == m_grid.end()) continue;

            it->second.erase(collider);
            if (it->second.empty()) m_grid.erase(it);
        }
    }
       
}

void GridHash::Update(CircleComponent* collider, const Vector2& oldCenter, const Vector2& newCenter, float radius)
{
    Remove(collider, oldCenter, radius);
    Insert(collider, newCenter, radius);
}

std::vector<CircleComponent*> GridHash::Query(const Vector2& center, float radius)
{
    std::vector<CircleComponent*> Colliders;
    int minX, maxX, minY, maxY;
    GetCellRange(center, radius, CellSize, minX, maxX, minY, maxY);

    Colliders.reserve(32);

    for (int x = minX; x <= maxX; ++x)
        for (int y = minY; y <= maxY; ++y)
        {
            auto it = m_grid.find({ x, y });
            if (it == m_grid.end()) continue;

            Colliders.insert(Colliders.end(), it->second.begin(), it->second.end());
        }

    return Colliders;
}
