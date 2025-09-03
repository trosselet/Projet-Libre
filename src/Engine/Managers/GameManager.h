#pragma once
#include <set>

#include "GameTimer.h"

struct IScript;
class Profiler;
class Scene;
class Entity;

class GameManager
{
public:
    ~GameManager();
    GameManager();

    Scene* mpActiveScene;
    Scene* mpNextActiveScene;

    int mWindowWidth;
    int mWindowHeight;

    float mAccumulator;

    GameTimer* GetTime();

    std::vector<IScript*> dataHandler;

private:

    void HandleInput();
    void FixedUpdate();
    void Update();
    void Draw();

    Profiler* mProfiler;
    GameTimer mTimer;
    bool IsStopped;

public:
    template<typename T>
    void LaunchScene();

    template<typename S, typename ... Args>
    S* GetOrLoadGlobalScript(Entity* owner, Args&&... args);
    
    void Run();
    void Stop();

    Scene* GetScene() const { return mpActiveScene; }
};

#include "GameManager.inl"