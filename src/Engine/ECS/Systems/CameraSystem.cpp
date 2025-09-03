#include "pch.h"
#include "CameraSystem.h"

#include <iostream>

#include "ObjectFactory.h"
#include "ECS/ECS.h"
#include "ECS/Components/Camera.h"
#include "Render/RenderWindow.h"
#include "Utils/Debug.h"

CameraSystem::CameraSystem(RenderWindow* window)
: mCurrentDisplayedCamera(0), mCurrentCamera(nullptr),
                                                   mWindow(window)
{
}

void CameraSystem::SetActiveCamera(Camera* activeCamera)
{
    mCurrentCamera = activeCamera;
    mCurrentDisplayedCamera = activeCamera->DisplayScreen;
}

Camera* CameraSystem::GetActiveCamera()
{
    return mCurrentCamera;
}

void CameraSystem::Update(ECS* globalEC)
{
    for (int i = 0; i < globalEC->mEntityCount; i++)
    {
        if (!globalEC->HasComponent<Camera>(i)) continue;
        Camera* camera = globalEC->GetComponent<Camera>(i);
        
        if (camera->DisplayScreen != mCurrentDisplayedCamera) continue;
        TRANSFORM* transform = camera->GetEntity()->GetTransform();
        sf::View view = sf::View(sf::FloatRect(transform->position, sf::Vector2f(mWindow->getSize())));
        view.zoom(camera->ZoomFactor);
        mWindow->setView(view);
    }
}
