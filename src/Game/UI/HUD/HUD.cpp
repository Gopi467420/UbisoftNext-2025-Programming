#include "HUD.h"
#include "./UI/UIManager/UIManager.h"
#include "./UI/UIWidget(Base)/UIWidget.h"
#include "../Game/Core/Scene/Scene(BaseClass)/Scene.h"
#include <string>



HUD::HUD(Scene& scene) : m_scene(scene) {}

void HUD::Init()
{
    m_ui = std::make_unique<UIManager>();
    m_positions.clear();
    m_texts.clear();
    m_visible.clear();


    SetInstructions();
  
}

void HUD::SetInstructions()
{
    float x = 1730.0f;   // draw right side
    float y = 1050.0f;
    float spacing = 26.0f;

    m_instructionIds[0] = AddText({ x, y }, "Controls:", true); y -= spacing;
    m_instructionIds[1] = AddText({ x, y }, "W A S D  - Move", true); y -= spacing;
    m_instructionIds[2] = AddText({ x, y }, "Mouse L - Attack", true); y -= spacing;
    m_instructionIds[3] = AddText({ x, y }, "M       - Move Base", true); y -= spacing;
    m_instructionIds[4] = AddText({ x, y }, "E   - SwitchWeapons", true);
}

void HUD::Update(float dt)
{
   
}


void HUD::Render()
{
    if (!m_ui) return;

    for (size_t i = 0; i < m_positions.size(); ++i)
    {
        if (!m_visible[i]) continue;
        m_ui->Render(m_positions[i], m_texts[i].c_str());
    }
}

void HUD::Shutdown()
{    
      
   
}



uint32_t HUD::CreateWidget(Vector2 pos, bool visible)
{
    uint32_t id = (uint32_t)m_positions.size();

    m_positions.push_back(pos);
    m_texts.emplace_back("");     // empty text
    m_visible.push_back(visible);

    return id;
}


uint32_t HUD::AddText(const Vector2& pos, const std::string& text, bool visible = true)
{
    uint32_t id = CreateWidget(pos, visible);
    SetText(id, text);
    return id;
}

void HUD::SetText(uint32_t id, const std::string& text)
{
    if (id < m_texts.size())
        m_texts[id] = text;
}
void HUD::SetBaseStats(int health, int walls, int level, int gems)
{
    float x = 40.0f;
    float y = 1050.0f;
    float yspacing = 24.0f;

    m_headingId = CreateWidget({ x, y }, true); y -= yspacing;
    m_baseIntegrityId = CreateWidget({ x, y }, true); y -= yspacing;
   // m_wallIntegrityId = CreateWidget({ x, y }, true); y -= yspacing;
    m_levelId = CreateWidget({ x, y }, true); y -= yspacing;
    m_gemsId = CreateWidget({ x, y }, true);

    // Now SAFE to set text
    UpdateStats(health, walls, level, gems);
}
void HUD::UpdateStats(int baseHealth, int wallIntegrity, int level, int gems)
{
    m_texts[m_baseIntegrityId] = "Health: " + std::to_string(baseHealth);
   // m_texts[m_wallIntegrityId] = "Walls: " + std::to_string(wallIntegrity);
    m_texts[m_levelId] = "Level: " + std::to_string(level);
    m_texts[m_gemsId] = "EnemyKilled: " + std::to_string(gems);

}





