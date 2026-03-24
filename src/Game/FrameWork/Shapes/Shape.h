#pragma once

#include "../Game/Math/Vector/Vector2.h"
#include "../Game/FrameWork/Enums/GameplayEnums.h"
#include <vector>



namespace Shape
{
    

    void GetColorRGB(ShapeColor color, float& r, float& g, float& b);

    // 3D versions (always draws black outline so boundary is visible)
    void DrawBox3D(float worldX, float worldY, float width, float height, ShapeColor color, float depthPx = 10.0f);
    void DrawCircle3D(const Vector2& worldCenter, float radius, ShapeColor color, float depthPx = 10.0f);
    void DrawRegularPolygon3D(const Vector2& worldCenter, int sides, float radius, float rotationDegrees, ShapeColor color, float depthPx = 10.0f);
}
