//Helper Script for converting to diffrent coordinate systems
#pragma once

#include "../Game/Core/Camera/Camera.h"
#include "../ContestAPI/AppSettings.h"
#include "app.h"

struct Vector2;

namespace CoordinateConversion
{
    Vector2 WorldToCamera(const Vector2& worldPos, const Camera2D& cam);
    Vector2 CameraToScreen(const Vector2& camPos);
    Vector2 ScreenToWorld(const Vector2& screenPos, const Camera2D& cam);
    Vector2 WorldToScreen(const Vector2& worldPos, const Camera2D& cam);
    Vector2 GetMouseWorld(const Camera2D& cam);
}