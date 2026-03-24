#include "CoordinateConversion.h"

Vector2 CoordinateConversion::WorldToCamera( const Vector2& worldPos, const Camera2D& cam)
{
    return (worldPos - cam.GetPosition()) * cam.m_zoom;
}

Vector2 CoordinateConversion::CameraToScreen(const Vector2& camPos)
{
    return camPos + Vector2( APP_VIRTUAL_WIDTH * 0.5f, APP_VIRTUAL_HEIGHT * 0.5f);
}

Vector2 CoordinateConversion::ScreenToWorld(const Vector2& screenPos, const Camera2D& cam)
{
    Vector2 camSpace = screenPos - Vector2(APP_VIRTUAL_WIDTH * 0.5f, APP_VIRTUAL_HEIGHT * 0.5f);

    camSpace.y = -camSpace.y; // flip Y

    return camSpace / cam.m_zoom + cam.GetPosition();
}

Vector2 CoordinateConversion::WorldToScreen( const Vector2& worldPos,const Camera2D& cam)
{
    return CameraToScreen(WorldToCamera(worldPos, cam));
}

Vector2 CoordinateConversion::GetMouseWorld(const Camera2D& cam)
{
    float mx, my;
    App::GetMousePos(mx, my);
    return ScreenToWorld(Vector2(mx, my), cam);
}