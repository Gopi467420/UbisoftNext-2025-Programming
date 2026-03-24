#pragma once
#include <vector>
#include "../Game/Gameplay/Pooled Entities/Gems/Gems.h"

class Camera2D;
class Vector2;
class Gems;
class Scene;
class GemPool
{
public:
    void Init(uint32_t max, Scene& scene);

    Gems* Spawn(const Vector2& pos, GemType type);
    void Update(float dt, Vector2 baseloc);
    void Render(Camera2D& cam);

private:
    void SwapRemove(uint32_t i);

private:
    std::vector<Gems*> entities;     // collision shells

    // SoA
    std::vector<Vector2> positions;
    std::vector<float> lifetimes;
    std::vector<float> values;
    std::vector<GemType> types;

    uint32_t aliveCount = 0;
};
