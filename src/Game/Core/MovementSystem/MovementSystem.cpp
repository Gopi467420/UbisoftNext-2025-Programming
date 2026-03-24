#include "MovementSystem.h"
#include "../Game/FrameWork/Structs/Structs.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h"


#include <cmath>



void MovementSystem::Move(MovementType type, MovementContext& ctx, uint32_t i, float dt,
    const Vector2& center, const TargetView& targets)
{
    switch (type)
    {
    case MovementType::Straight:   MoveStraight(ctx, i, dt); break;
    case MovementType::SweepOrbit: MoveSweepOrbit(ctx, i, dt, center); break;
    case MovementType::Precision:  MoveHoming(ctx, i, dt, targets, true); break;   
    default:                       MoveStraight(ctx, i, dt); break;
    }
}

void MovementSystem::MoveStraight(MovementContext& ctx, uint32_t i, float dt)
{
   
    ctx.positions[i] += ctx.directions[i] * (ctx.speeds[i] * dt);
}

void MovementSystem::MoveToTarget(MovementContext& ctx, Vector2 target, uint32_t i, float dt)
{
    if (!ctx.positions || !ctx.speeds) return;
    Vector2 toTarget = target - ctx.positions[i];
     if (toTarget.LengthSquared() > 0.00001f)
         toTarget = toTarget.Normalize();

    ctx.positions[i] += toTarget * (ctx.speeds[i] * dt);
}

void MovementSystem::MoveSweepOrbit(MovementContext& ctx, uint32_t i, float dt, const Vector2& center)
{
    ctx.sweepCenters[i] = center;

    // Update angular speed from linear speed and radius (your old logic)
    const float r = ctx.sweepRadius[i];
    if (r > 0.0001f) ctx.sweepAngularSpeed[i] = ctx.speeds[i] / r;

    ctx.sweepAngle[i] += ctx.sweepAngularSpeed[i] * dt;

    ctx.positions[i] = ctx.sweepCenters[i] + Vector2(std::cos(ctx.sweepAngle[i]), std::sin(ctx.sweepAngle[i])) * ctx.sweepRadius[i];
}

void MovementSystem::MoveHoming(MovementContext& ctx, uint32_t i, float dt,
    const TargetView& targets, bool /*unused*/)
{
    if (!targets.targetPositions || !targets.targetTypes || targets.targetCount == 0)
        return;

    int targetIndex = -1;

    for (uint32_t t = 0; t < targets.targetCount; ++t)
    {
        EEnemyType type = targets.targetTypes[t];

        // choose multiple valid target types
        if (type == EEnemyType::ET_WallBreaker || type == EEnemyType::ET_Airborne)
        {
            targetIndex = (int)t;
            break;
        }
    }

    // if none found, move straight
    if (targetIndex < 0)
    {
        ctx.positions[i] += ctx.directions[i] * (ctx.speeds[i] * dt);
        return;
    }

    Vector2 toTarget = targets.targetPositions[targetIndex] - ctx.positions[i];
    if (toTarget.LengthSquared() > 0.00001f)
        ctx.directions[i] = toTarget.Normalize();

    ctx.positions[i] += ctx.directions[i] * (ctx.speeds[i] * dt);
}




