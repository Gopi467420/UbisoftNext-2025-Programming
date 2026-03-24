//Trying SOA method Here
#pragma once
#include <vector>
#include <memory>
#include "../Game/Math/Vector/Vector2.h"
#include "./UI/UIManager/UIManager.h"

class Scene;
class Vector2;

class HUD
{
public:
    HUD(Scene& scene);

    void Init();
    void SetInstructions();
    void Update(float dt);
    void Render();
    void Shutdown();

   

    uint32_t AddText(const Vector2& pos, const std::string& text, bool visible);

   
    void SetText(uint32_t id, const std::string& text);

    void SetBaseStats( int health, int walls,int level,int gems);

private:
    uint32_t CreateWidget(Vector2 pos, bool visible);

private:
    Scene& m_scene;
    std::unique_ptr<UIManager> m_ui;

    // SoA
    std::vector<Vector2> m_positions;
    std::vector<std::string> m_texts;
    std::vector<bool> m_visible;

    // ids for base stats
    uint32_t m_headingId;
    uint32_t m_baseIntegrityId;
    uint32_t m_wallIntegrityId;
    uint32_t m_levelId;
    uint32_t m_gemsId;
    uint32_t m_instructionIds[6];
public:
    void UpdateStats(int baseHealth, int wallIntegrity, int level, int gems);
};
