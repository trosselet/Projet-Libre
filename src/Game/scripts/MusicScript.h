#pragma once
#include "scripts/Script.h"
#include "KeyCounter.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <SFML/Graphics/Text.hpp>

#include "ObjectFactory.h"
#include "ECS/Entity.h"
#include "ECS/Components/ui/Image.h"
#include "ECS/Components/ui/Text.h"

#include <map>

class BGMMusicScript;
class ParticlesScript;
class RigidBody2D;

class MusicScript : public IScript
{

public:
    struct BeatCircle {
        Entity* shape;
        float spawnTime;

        bool operator==(const BeatCircle& other) const {
            return shape == other.shape && spawnTime == other.spawnTime;
        }
    };


    struct NoteData
    {
        int x;
        int y;
        float time;
    };

    struct BeatMapData {
        const char* beatmapFile;
        const char* musicFile;
        float bpm;
        float offset;
    };

    struct PlayerData {
        int Score;
        float Accuracy;
        int MaxCombo;
        int Misses;
    };

    enum class MUSICSTATE
    {
        PLAYING,
        PAUSED,
        STOPPED
    };

public:

    MusicScript(BGMMusicScript* bgm);

    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override;

    void OnRender(RenderWindow* window) override;
    void LoadNotesFromFile(const char* filename);
    void PlayBeatmap(int key);
    void SetState(MUSICSTATE state) { mState = state; }
    MUSICSTATE GetState() { return mState; }

    void IncreaseCombo();
    void ResetCombo();
    void ShowCombo(sf::RenderWindow& window);
    void Missed();
    void CalculateScoreAndAccuracy();

    void SetupTexts();
    void SetHitAreas();

    sf::Music* GetMusic() { return &music; };

    void AddBeatmap(int key, const char* beatmapFile, const char* musicFile, float bpm, float offset) { musicList.emplace(key, new BeatMapData(beatmapFile, musicFile, bpm, offset)); }
    PlayerData GetData();

    Entity* backgroundSprite;


private:
    float BPM = 1.f;
    float SECONDS_PER_BEAT = 60.0f / BPM;
    float acc;
    float firstNote;
    float miniOffset;
    const float TIMING_WINDOW = 0.15f;
    const float FALL_SPEED = 100.0f;
    const float AR = 9.0f;
    const float outlineDuration = 0.15f;
    int playerScore = 0;
    int beatmapNotes;
    int combo = 0;
    int maxCombo = 0;
    bool musicStarted;
    bool sKeyPressed = false;
    bool dKeyPressed = false;
    bool outlineActive = false;
    int noteCounter = 0;
    int Misses = 0;

    sf::Vector2f movement;
    sf::Clock beatClock;
    sf::Music music;
    std::vector<BeatCircle> fallingCircles;
    std::vector<NoteData> noteDataList;
    Entity* hitRect;
    Entity* hitCircle;
    sf::RenderWindow* window = nullptr;

    Entity* comboText;
    Entity* maxComboText;
    Entity* BPMText;
    Entity* MissCount;
    Entity* accuracyText;
    Entity* scoreText;
    Entity* fullComboText;

    Entity* MusicContainer;

    MUSICSTATE mState;
    std::map<int, BeatMapData*> musicList;

    sf::Clock outlineTimer;

    KeyCounter key1;
    KeyCounter key2;

    ParticlesScript* mParticle;
    BGMMusicScript* bgmScript;
};