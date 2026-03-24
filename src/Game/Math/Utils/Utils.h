#pragma once
#include <algorithm>
#include <cmath>
#include "../Game/Math/Vector/Vector2.h"



class Utils
{


public :

    float LookAt(const Vector2& from, const Vector2& to);
    inline float RadToDeg(float rad);

    static float Lerp(float a, float b, float t);

    
    static float Clamp(float value, float minValue, float maxValue);

    static Vector2 GetRandomSpawnPositionFromTarget(Vector2 targetpos, float minRadius, float maxradius);
    
    static float Distance(const Vector2& a, const Vector2& b);

    
    
    static float AngleBetween(const Vector2& from, const Vector2& to);
   
    static int RandomInt(int min, int max);
   
    static float RandomFloat(float min, float max);
    static int ClampMin(int value, int minValue);

    static float MinFloat(float a, float b);

    static float MaxFloat(float a, float b);

    static int MinInt(int a, int b);

    static int MaxInt(int a, int b);

    static float ClampFloat(float v, float lo, float hi);

    static int ClampInt(int v, int lo, int hi);

    static Vector2 Direction(const Vector2& a, const Vector2& b);

    


};


