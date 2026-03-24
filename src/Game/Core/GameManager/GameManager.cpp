#include "GameManager.h"
#include "../Game/Core/Scene/GameScene/GameScene.h"
#include "../Game/Core/Scene/EndScenes/EndScene.h"

GameManager::GameManager() {}

GameManager& GameManager::Get()
{
    static GameManager instance;
    return instance;
}


void GameManager::Init()
{
    m_gameState = EGameState::EGS_Playing;   
    m_gameScene.Init();
   
    BindInputActions();
    
}




void GameManager::Update(float deltaTime)
{   
    float dt = deltaTime;
    if (dt > 0.033f) dt = 0.033f;
    if (dt < 0.0f) dt = 0.0f;
    
    m_input.Update(dt);
    
   // if (m_gameState != EGameState::EGS_Playing)  return;
    //Delta time clamping
  

    
   
    HandleInput();
    HandleGameStateUpdate(dt);

}



void GameManager::Render()
{
    HandleGameStateRender();
  
   
}
    
void GameManager::Shutdown()
{
    m_gameScene.Shutdown();
}
void GameManager::HandleGameStateRender()
{
    switch (m_gameState)
    {
    case EGameState::EGS_None:
        break;
    case EGameState::EGS_StartScreen:
        break;
    case EGameState::EGS_Playing:    m_gameScene.Render();
        break;
    case EGameState::EGS_Paused:
        break;
    case EGameState::EGS_End: m_endScene.Render();
        break;
    default:
        break;
    }
}

void GameManager::HandleGameStateUpdate(float dt)
{
    switch (m_gameState)
    {
    case EGameState::EGS_None:
        break;
    case EGameState::EGS_StartScreen:
        break;
    case EGameState::EGS_Playing:  m_gameScene.Update(dt);
        break;
    case EGameState::EGS_Paused:
        break;
    case EGameState::EGS_End: 
        break;
    default:
        break;
    }
}
void GameManager::HandleInput()
{
    if (m_input.Pressed(EInputAction::IA_Fire)) { m_gameScene.Fire(); }
   // if (m_input.Pressed(EInputAction::IA_MoveBase)) { m_gameScene.MoveBase(); }
    
    if (m_input.Pressed(EInputAction::IA_MoveBase))   m_gameScene.MoveBase();

    if (m_input.Pressed(EInputAction::IA_NextWeapon)) m_gameScene.NextWeapon();

    if (m_input.Pressed(EInputAction::IA_Restart)) { if (m_gameState == EGameState::EGS_End) { m_gameScene.Restart(); } }//m_gameState = EGameState::EGS_Playing;
}
    
 




void GameManager::BindInputActions()
{
    m_input.BindMouse(EInputAction::IA_Fire, 0);
    m_input.BindKey(EInputAction::IA_NextWeapon, App::KEY_E);
    m_input.BindKey(EInputAction::IA_MoveBase, App::KEY_M);
    m_input.BindKey(EInputAction::IA_Restart, App::KEY_R);


    
  
  
}


