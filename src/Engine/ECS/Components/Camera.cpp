#include "pch.h"
#include "Camera.h"

#include "ECS/Systems/CameraSystem.h"

Camera::Camera(Entity* entity, int display) : Component(entity), DisplayScreen(display)
{
    Engine::instance().GetCameraSystem()->SetActiveCamera(this);
}

Camera::~Camera()
{
}

int Camera::GetBitmask()
{
    return BITMASK;
}
