#pragma once

#include <cstdint>
#include <cmath>
#include "../Game/Math/Vector/Vector2.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h"

struct MovementContext;

struct TargetView
{
    const Vector2* targetPositions = nullptr;
    uint32_t targetCount = 0;
    const EEnemyType* targetTypes = nullptr;
    const uint8_t* isHighValue = nullptr;
};
static inline float Clamp01(float v) { return (v < 0.f) ? 0.f : (v > 1.f ? 1.f : v); }



class MovementSystem
{
public:
    static void Move(MovementType type, MovementContext& ctx, uint32_t index, float dt, const Vector2& center, const TargetView& targets);

    static void MoveStraight(MovementContext& ctx, uint32_t i, float dt);
    static void MoveToTarget(MovementContext& ctx,Vector2 target, uint32_t i, float dt);
    static void MoveSweepOrbit(MovementContext& ctx, uint32_t i, float dt, const Vector2& center);    
    static void MoveHoming(MovementContext& ctx, uint32_t i, float dt, const TargetView& targets, bool highValueOnly);
    
};

