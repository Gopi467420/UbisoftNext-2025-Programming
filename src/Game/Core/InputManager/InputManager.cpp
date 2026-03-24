#include "InputManager.h"
#include "app.h" 

void InputManager::BindKey(EInputAction action, App::Key key)
{
    InputBinding b;
    b.m_action = action;
    b.m_key = key;
    b.m_mouseButton = -1;
    m_bindings.push_back(b);
}

void InputManager::BindMouse(EInputAction action, int mouseButton)
{
    InputBinding b;
    b.m_action = action;
    b.m_key = App::KEY_None;
    b.m_mouseButton = mouseButton;
    m_bindings.push_back(b);
}

void InputManager::Update(float deltaTime)
{
    
    m_pressed.fill(false);
    m_released.fill(false);

    
    m_down.fill(false);

    for (const InputBinding& b : m_bindings)
    {
        bool isDown = false;



        if(b.m_mouseButton >= 0)
        {
            isDown = App::IsMousePressed(b.m_mouseButton);
        }
        else
        {
            isDown = App::IsKeyPressed(b.m_key);
        }

       

        const size_t idx = ToIndex(b.m_action);
        if (idx < kMaxActions)
        {
           
            m_down[idx] = m_down[idx] || isDown;
        }
    }

 
    for (size_t i = 0; i < kMaxActions; ++i)
    {
        if (m_down[i] && !m_prevDown[i]) m_pressed[i] = true;
        if (!m_down[i] && m_prevDown[i]) m_released[i] = true;
        m_prevDown[i] = m_down[i];
    }
}

bool InputManager::Down(EInputAction action) const
{
    return m_down[ToIndex(action)];
}

bool InputManager::Pressed(EInputAction action) const
{
    return m_pressed[ToIndex(action)];
}

bool InputManager::Released(EInputAction action) const
{
    return m_released[ToIndex(action)];
}
