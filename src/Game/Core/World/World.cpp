#include "World.h"
#include "../Game/Core/Camera/Camera.h"
#include "../ContestAPI/AppSettings.h"
#include "app.h"


World::World():SCREEN_HEIGHT(APP_VIRTUAL_HEIGHT),SCREEN_WIDTH(APP_VIRTUAL_WIDTH)
{
	//Constructor
}

Vector2 World::WorldToCamera(const Vector2& worldPos, const Camera2D& cam) const
{
	return (worldPos - cam.m_position) * cam.m_zoom;
}

Vector2 World::CameraToScreen(const Vector2& camPos) const
{
	return camPos + Vector2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
}

Vector2 World::ScreenToWorld(const Vector2& screenPos,const Camera2D& cam) const
{
    Vector2 camSpace = screenPos - Vector2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
    camSpace.y = -camSpace.y; // Y FLipped
    return camSpace / cam.m_zoom + cam.m_position;
}

Vector2 World::WorldToScreen( const Vector2& worldPos, const Camera2D& cam) const
{
    return CameraToScreen(WorldToCamera(worldPos, cam));
}


Vector2 World::GetMouseWorld(const Camera2D& cam) const
{
    float mx, my;
    App::GetMousePos(mx, my);
    return ScreenToWorld(Vector2(mx, my), cam);
}




