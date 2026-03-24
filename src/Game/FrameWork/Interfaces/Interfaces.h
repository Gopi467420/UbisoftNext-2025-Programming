#pragma once
//Define Interfaces here 

class Scene;

class IPoolable
{
public:
    virtual ~IPoolable() = default;    
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;
    virtual bool IsActive() const = 0;

   
};

class IDamagable
{
public:
   
    virtual void TakeDamage(float amount) = 0;
    

};

