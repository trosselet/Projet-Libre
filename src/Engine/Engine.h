#pragma once
#include "GameTimer.h"

class UserInterfaceSystem;
class RenderWindow;
class ScriptManager;
class ParticleSystem;
class CollisionSystem;
class PhysicsSystem;
class CameraSystem;
class RenderSystem;
class AnimatorSystem;
class ECS;
class GameManager;
class ObjectFactory;

class Engine
{
public:
    Engine();
    ~Engine();

    static void CreateRender();
    static RenderWindow* GetRenderWindow();
    
    static GameManager* GetGameManager();

    static CameraSystem* GetCameraSystem();
    
    static GameTimer* GetClock();
    
    static float GetDeltaTime();

    static ScriptManager* GetScriptManager();

private:
    static Engine& instance()
    {
        static Engine engine;
        return engine;
    }

    static ECS* GetECS();
    static RenderSystem* GetRenderSystem();
    static PhysicsSystem* GetPhysicsSystem();
    static CollisionSystem* GetCollisionSystem();
    static ParticleSystem* GetParticleSystem();
    static UserInterfaceSystem* GetUserInterface();
    static AnimatorSystem* GetAnimatorSystem();

    GameManager* mGameManager;

    ECS* mECS;
    RenderSystem* mRenderSystem;
    PhysicsSystem* mPhysicsSystem;
    CollisionSystem* mCollisionSystem;
    CameraSystem* mCameraSystem;
    ParticleSystem* mParticleSystem;
    ScriptManager* mScriptManager;
    UserInterfaceSystem* mUserInterface;
    AnimatorSystem* mAnimatorSystem;

    RenderWindow* mRenderWindow;

    // Make system only accessible from engine
    friend class Entity;
    friend class ECS;
    
    friend class ObjectFactory;
    
    friend class GameManager;
    friend class RenderSystem;
    friend class PhysicsSystem;
    friend class CollisionSystem;
    friend class CameraSystem;
    friend class AnimatorSystem;
    friend class ScriptManager;
    friend class Scene;
    friend class Camera;
};
