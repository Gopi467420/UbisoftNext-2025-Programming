#pragma once
#include "../Game/Core/InputManager/InputManager.h"
#include "../Game/Core/Scene/GameScene/GameScene.h"
#include "../Game/Core/Scene/EndScenes/EndScene.h"

#include <vector>
#include <unordered_map>

class Entity;
class GridHash;
class UiWidget;
class HUD;


class GameManager
{
private:
    GameManager(); // Singleton
    
public:
    static GameManager& Get();

private:

    EGameState m_gameState = EGameState::EGS_None;
    InputManager m_input;
    GameScene m_gameScene;
    EndScene m_endScene;

private:
    void BindInputActions();
    void HandleInput();
    void HandleGameStateUpdate(float dt);
    void HandleGameStateRender();

public:    
    void Init();
    void Update(float deltaTime);     
    void Render();
    void Shutdown();

public:    
     GameScene& GetActiveScene() { return m_gameScene; }
     void SetGameState(EGameState state) { m_gameState = state; }
};
