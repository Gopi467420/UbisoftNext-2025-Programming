#pragma once
#include <vector>
#include <type_traits>
#include <memory>
#include "../Game/FrameWork/Interfaces/Interfaces.h"

// Basic Object Pool Class which handles allocation, deallocation and object reuse


struct Camera2D ;
template <typename T>
class ObjectPool
{
    static_assert( std::is_base_of<IPoolable, T>::value,"Class <T> must derive from IPoolable");
    
protected:
    std::vector<std::unique_ptr<T>> pool;

public:
    virtual ~ObjectPool() {}

    void Init(int size, Scene& scene)
    {
        pool.reserve(size);
        for (int i = 0; i < size; i++)
        {
           
            auto obj = std::make_unique<T>(); 
            obj->SetId(i);
            obj->Init();
            obj->SetScene(scene);
            obj->Deactivate();            
            pool.push_back(std::move(obj));
        }
    }

    T* GetFree()
    {
        for (auto& obj : pool)
        {
            if (!obj->IsActive()) return obj.get();
        }
        return nullptr;
    }

    void UpdateAll(float deltaTime)
    {
        for (auto& obj : pool)
        {
            if (obj->IsActive()) obj->Update(deltaTime);
        }
    }

    void RenderAll(Camera2D& camera)
    {
        for (auto& obj : pool)
        {
            if (obj->IsActive()) obj->Render( camera);

            
            
        }
    }


    std::vector<T*> GetActive()
    {
        std::vector<T*> result;
        for (auto& obj : pool)
        {
            if (obj->IsActive())
                result.push_back(obj.get());
        }
        return result;
    }

    const std::vector<std::unique_ptr<T>>& GetPool() const { return pool; }

};

