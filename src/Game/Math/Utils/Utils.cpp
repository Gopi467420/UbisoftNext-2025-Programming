#include "Utils.h"
#include <algorithm>
#include "../Game/Math/Vector/Vector2.h"

#include "app.h"



inline float Utils::RadToDeg(float rad) { return rad * 180.0f / PI; }

 float Utils::Lerp(float a, float b, float t){ return a + (b - a) * t; }

 float Utils::Clamp(float value, float minValue, float maxValue){ return std::clamp(value, minValue, maxValue); }

 Vector2 Utils::GetRandomSpawnPositionFromTarget(Vector2 targetpos, float minRadius,float maxradius)
 {
     
     float angle = RandomFloat(0.0f, 6.283185f); // 2PI
     float radius = RandomFloat(minRadius, maxradius);

     Vector2 offset(std::cos(angle) * radius, std::sin(angle) * radius);
     return targetpos + offset;
 }
 
 float Utils::Distance(const Vector2& a, const Vector2& b)
 {
     float dx = b.x - a.x;
     float dy = b.y - a.y;
     return std::sqrt(dx * dx + dy * dy);
 }

 Vector2 Utils::Direction(const Vector2& a, const Vector2& b)
 {
     Vector2 d = b - a;
     return d.LengthSquared() > 0.0001f ? d.Normalize() : Vector2(0.0f, 0.0f);
 }

 float Utils::AngleBetween(const Vector2& from, const Vector2& to)
 {
     Vector2 dir = to - from;
     return std::atan2(dir.y, dir.x);
 }

 int Utils::RandomInt(int min, int max)
 {
     return min + (std::rand() % (max - min + 1));
 }

 float Utils::RandomFloat(float min, float max)
 {
     return min + (static_cast<float>(std::rand()) / RAND_MAX) * (max - min);
 }

 int Utils::ClampMin(int value, int minValue)
 {
     return (value < minValue) ? minValue : value;
 }

  float Utils::MinFloat(float a, float b)
 {
     return (a < b) ? a : b;
 }

  float Utils::MaxFloat(float a, float b)
 {
     return (a > b) ? a : b;
 }

  int Utils::MinInt(int a, int b)
 {
     return (a < b) ? a : b;
 }

  int Utils::MaxInt(int a, int b)
  {
      return (a > b) ? a : b;
  }
  float  Utils::ClampFloat(float v, float lo, float hi)
  {
      if (v < lo) return lo;
      if (v > hi) return hi;
      return v;
  }

  int Utils::ClampInt(int v, int lo, int hi)
  {
      if (v < lo) return lo;
      if (v > hi) return hi;
      return v;
  }