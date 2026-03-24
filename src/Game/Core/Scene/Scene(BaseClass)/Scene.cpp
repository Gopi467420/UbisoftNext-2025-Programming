#include "Scene.h"
#include "../Game/FrameWork/GObject/GObject.h"

Scene::Scene(int cellsize) :m_gridHash(cellsize), m_physics(m_gridHash){}

Id Scene::GetNextId() { return m_iD++; }

Id Scene::Register(std::unique_ptr<GObject> obj)
{
    Id id = GetNextId();
    m_sceneObjects.emplace(id, std::move(obj));
    return id;
}

GObject* Scene::GetEntity(Id id)
{
    auto it = m_sceneObjects.find(id);
    return (it != m_sceneObjects.end()) ? it->second.get() : nullptr;
}

void Scene::Destroy(Id id) { m_sceneObjects.erase(id); }

void Scene::Clear() { m_sceneObjects.clear(); }

void Scene::MarkForDestroy(Id id){ if (GObject* e = GetEntityAs<GObject>(id)) e->MarkPendingDestroy(); }

