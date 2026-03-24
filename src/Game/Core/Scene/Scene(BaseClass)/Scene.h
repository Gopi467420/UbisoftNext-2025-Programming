#pragma once
#include "../Game/Core/Camera/Camera.h"
#include "../Game/Systems/Physics/PhysicsManager.h"
#include "../Game/FrameWork/Structs/Structs.h"
#include "../Game/UI/HUD/HUD.h"
#include <vector>
#include <unordered_map>
#include <memory>



using Id = uint32_t;

class GObject;
class HUD;
enum SoundFlags;
class Scene
{ 
public:

    Scene(int cellsize);

public:
    Camera2D m_camera;

    
  
  
    PhysicsManager& GetPhysics() { return m_physics; }

private:
    Id m_iD;
    
   
protected:
    PhysicsManager m_physics;
    GridHash m_gridHash;    
    std::unordered_map<Id, std::unique_ptr<GObject>> m_sceneObjects;
    std::unique_ptr<HUD> m_hud;

  
//Functions
    GObject* GetEntity(Id id);
    
    Id Register(std::unique_ptr<GObject> obj);    
    void Destroy(Id id);
    void Clear();
    void MarkForDestroy(Id id);

    template<typename T>
    T* GetEntityAs(Id id)
    {
        static_assert(std::is_base_of_v<GObject, T>, "T must derive from GObject");
        return dynamic_cast<T*>(GetEntity(id));
    }

    float m_gemcount;

public:
    bool debug;
    virtual void ReportTarget(ReportedTarget report) {};
    Id GetNextId();

    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    Camera2D& GetCamera() { return m_camera; }
    const Camera2D& GetCamera() const { return m_camera; }
    
    virtual void SpawnGem(Vector2 pos, int value) {}

    float GetGemCount() { return m_gemcount; }
    void SetGemCount(float value) { m_gemcount += value; }
    virtual void EmitExplosion(Vector2 pos) {}
    float m_enemyKillCount;

    virtual void CameraShake() {};
    virtual void playSoundInGame(const char* filename) {};
    virtual void PlayEnemyHitSound(const char* filename) {};

    virtual void PlayBaseHitSound(const char* filename) {};


};  



