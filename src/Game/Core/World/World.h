#pragma once


struct Vector2;
struct Camera2D;

class Entity;

class World
{
public:
	World();

private:
	float SCREEN_WIDTH;
	float SCREEN_HEIGHT;

public:
	Vector2 WorldToCamera(const Vector2& worldPos, const Camera2D& cam) const;
	Vector2 CameraToScreen(const Vector2& camPos) const;
	Vector2 ScreenToWorld(const Vector2& screenPos, const Camera2D& cam) const;
	Vector2 WorldToScreen(const Vector2& worldPos, const Camera2D& cam) const;

	//Helper Functions
	Vector2 GetMouseWorld(const Camera2D& cam) const;
	





};



