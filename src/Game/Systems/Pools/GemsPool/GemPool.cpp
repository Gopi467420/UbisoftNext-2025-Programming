#include "GemPool.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h"
#include "../Game/Gameplay/Pooled Entities/Gems/Gems.h"
#include <memory>

struct GemArchetype
{
    float value;
    float lifetime;
};

static GemArchetype gGemTable[(int)GemType::Count] =
{
    { 1, 10.0f },   // Small
    { 5, 15.0f },   // Medium
    { 20, 20.0f }   // Large
};


void GemPool::Init(uint32_t max, Scene& scene)
{
    entities.resize(max);
    for (uint32_t i = 0; i < max; ++i)
    { 
        entities[i] = new Gems();
        entities[i]->SetScene(scene);
        entities[i]->Init();

    }
       
    positions.resize(max);
    lifetimes.resize(max);
    values.resize(max);
    types.resize(max);

    aliveCount = 0;
}
Gems* GemPool::Spawn(const Vector2& pos, GemType type)
{
    if (aliveCount >= entities.size()) return nullptr;

    uint32_t id = aliveCount++;

    const auto& data = gGemTable[(int)type];

    positions[id] = pos;
    lifetimes[id] = data.lifetime;
    values[id] = data.value;
    types[id] = type;

    entities[id]->SetPoolIndex(id);
    entities[id]->SetPosition(pos);
    entities[id]->SetValue(data.value);
    entities[id]->Activate();

    return entities[id];
}
void GemPool::Update(float dt, Vector2 baseloc)
{
    for (uint32_t i = 0; i < aliveCount;) 
    { 
        lifetimes[i] -= dt; 
        if (lifetimes[i] <= 0.0f) 
        { entities[i]->Deactivate(); SwapRemove(i); } 
        else { ++i; } }
}

void GemPool::Render(Camera2D& cam)
{
    for (uint32_t i = 0; i < aliveCount; ++i)
    {
        entities[i]->Render(cam);
    }
}

void GemPool::SwapRemove(uint32_t i)
{
    uint32_t last = aliveCount - 1;

    positions[i] = positions[last];
    lifetimes[i] = lifetimes[last];
    values[i] = values[last];
    types[i] = types[last];
    entities[i] = entities[last];

    entities[i]->SetPoolIndex(i);

    aliveCount--;
}
