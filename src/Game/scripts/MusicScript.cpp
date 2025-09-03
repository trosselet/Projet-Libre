#include "pch.h"
#include "MusicScript.h"
#include "KeyCounter.h"
#include "Transform.h"
#include <fstream>
#include <sstream>

#include "BGMMusicScript.h"
#include "ParticlesScript.h"

MusicScript::MusicScript(BGMMusicScript* bgm) : acc(0), beatmapNotes(0), musicStarted(false), hitRect(nullptr),
                                                hitCircle(nullptr),
                                                comboText(nullptr),
                                                maxComboText(nullptr),
                                                BPMText(nullptr),
                                                MissCount(nullptr),
                                                accuracyText(nullptr),
                                                scoreText(nullptr),
                                                fullComboText(nullptr),
                                                MusicContainer(nullptr),
                                                mState(), firstNote(0),
                                                miniOffset(0),
                                                key1("key 1", sf::Vector2f(900, 1000),
                                                     Resources::instance().DEFAULT_FONT),
                                                key2("key 2", sf::Vector2f(900, 1100),
                                                     Resources::instance().DEFAULT_FONT), mParticle(nullptr),
                                                bgmScript(bgm)
{
}

void MusicScript::SetupTexts()
{
    ObjectFactory::CreateComponent<Text>(comboText, Resources::instance().DEFAULT_FONT, 20, "Combo", sf::Vector2f(525.f, 900.0f));
	ObjectFactory::CreateComponent<Text>(maxComboText, Resources::instance().DEFAULT_FONT, 20, "maxCombo", sf::Vector2f(525.f, 300.0f));
	ObjectFactory::CreateComponent<Text>(BPMText, Resources::instance().DEFAULT_FONT, 20, "Bpm", sf::Vector2f(525.f, 400.0f));
	ObjectFactory::CreateComponent<Text>(MissCount, Resources::instance().DEFAULT_FONT, 20, "Miss", sf::Vector2f(525.f, 450.0f));
	ObjectFactory::CreateComponent<Text>(accuracyText, Resources::instance().DEFAULT_FONT, 20, "acc", sf::Vector2f(525.f, 500.0f));
	ObjectFactory::CreateComponent<Text>(scoreText, Resources::instance().DEFAULT_FONT, 20, "score", sf::Vector2f(525.f, 550.0f));
	ObjectFactory::CreateComponent<Text>(fullComboText, Resources::instance().DEFAULT_FONT, 20, "fullcombo", sf::Vector2f(550.f, 600.0f));
}

void MusicScript::SetHitAreas()
{
    ObjectFactory::CreateComponent<Image>(hitCircle, Resources::instance().RESOURCE_BASIC_WOOD, sf::Vector2f(175.0f, 30.0f), sf::Vector2f(3.0f, 3.0f));
	ObjectFactory::CreateComponent<Image>(hitRect, Resources::instance().MAINCIRCLE, sf::Vector2f(1450.f, 1070.f), sf::Vector2f(0.3f, 0.3f));

    backgroundSprite = ObjectFactory::CreateEntity<Entity>(-1);
    ObjectFactory::CreateComponent<Image>(backgroundSprite, Resources::instance().RESOURCE_GOLD_BOOTS,
        Resources::instance().BLUR_SHADER, sf::Vector2f(-100, -100), sf::Vector2f(4.0f, 3.0f));
}

void MusicScript::OnStart()
{
    MusicContainer = ObjectFactory::CreateEntity<Entity>();

    comboText = ObjectFactory::CreateEntity<Entity>(MusicContainer);
    maxComboText = ObjectFactory::CreateEntity<Entity>(MusicContainer);
    BPMText = ObjectFactory::CreateEntity<Entity>(MusicContainer);
    MissCount = ObjectFactory::CreateEntity<Entity>(MusicContainer);
    accuracyText = ObjectFactory::CreateEntity<Entity>(MusicContainer);
    scoreText = ObjectFactory::CreateEntity<Entity>(MusicContainer);
    fullComboText = ObjectFactory::CreateEntity<Entity>(MusicContainer);
    fullComboText->SetEnabled(false);


    hitCircle = ObjectFactory::CreateEntity<Entity>(MusicContainer);
    mParticle = ObjectFactory::AttachScript<ParticlesScript>(hitCircle, 20000);

    hitRect = ObjectFactory::CreateEntity<Entity>(MusicContainer);
    
    SetupTexts();
    SetState(MUSICSTATE::STOPPED);

}

void MusicScript::LoadNotesFromFile(const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        Debug::Log("Failed to open file: " + std::string(filename));
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string temp;
        int x, y;
        float time;

        std::getline(ss, temp, ','); x = std::stof(temp);
        std::getline(ss, temp, ','); y = std::stof(temp);
        std::getline(ss, temp, ','); time = std::stof(temp) / 1000.0f;

        noteDataList.push_back({ x, y, time });
    }
    firstNote = noteDataList[0].time;

    Debug::Log("Loaded " + std::to_string(noteDataList.size()) + " notes from " + filename);

    beatmapNotes = noteDataList.size();
}

void MusicScript::PlayBeatmap(int key)
{

    bgmScript->PauseBGMMusic(true);
    SetupTexts();
    SetHitAreas();

    musicStarted = false;
    beatClock.restart();

    if (!music.openFromFile(musicList[key]->musicFile))
    {
        //CONSOLE_OUTPUT(L"Error loading music" << std::endl);
        return;
    }

    key1.setEnable(true);
    key2.setEnable(true);

    acc = 100;
	playerScore = 0;
	combo = 0;
    Misses = 0;
    MusicContainer->SetEnabled(true);
    music.setVolume(25);
    LoadNotesFromFile(musicList[key]->beatmapFile);
    BPM = musicList[key]->bpm;
    miniOffset = musicList[key]->offset;

    SetState(MusicScript::MUSICSTATE::PLAYING);
}

void MusicScript::OnFixedUpdate()
{
}

void MusicScript::OnUpdate()
{

    if (mState == MusicScript::MUSICSTATE::PLAYING) {
        
        float currentTime = beatClock.getElapsedTime().asSeconds();

        if (!musicStarted)
        {
            float songOffset = (( hitRect->GetComponent<Image>()->ScreenPosition.y + miniOffset ) / ( FALL_SPEED * AR ));

            if (currentTime + (noteDataList[0].time / 32) >= songOffset)
            {
                music.play();
                musicStarted = true;
            }
        }

        float beatNumber = currentTime / SECONDS_PER_BEAT;
        int closestBeat = static_cast<int>(beatNumber + 0.5f);
        float expectedTime = closestBeat * SECONDS_PER_BEAT;

        float realFallSpeed = FALL_SPEED * AR;

        static sf::Clock frameClock;
        float deltaTime = frameClock.restart().asSeconds();

        static float previousNoteTime = -1.f;
        static bool useRed = true;

        bool sKeyNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
        bool dKeyNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

        key1.update(deltaTime, sKeyPressed);
        key2.update(deltaTime, dKeyPressed);

        while (!noteDataList.empty() && noteDataList.front().time <= currentTime)
        {
            NoteData note = noteDataList.front();
            noteDataList.erase(noteDataList.begin());

            BeatCircle newCircle;
			newCircle.shape = ObjectFactory::CreateEntity<Entity>();
			newCircle.spawnTime = note.time;

            if (previousNoteTime >= 0.f)
            {
                float timeDiff = note.time - previousNoteTime;
                if (timeDiff > 0.15f)
                {
                    useRed = !useRed;
                }
            }

            if (useRed)
                ObjectFactory::CreateComponent<Image>(newCircle.shape, Resources::instance().HITCIRCLE1, sf::Vector2f(1450.f, 50.f), sf::Vector2f(0.3f, 0.3f));
            else
                ObjectFactory::CreateComponent<Image>(newCircle.shape, Resources::instance().HITCIRCLE2, sf::Vector2f(1450.f, 50.f), sf::Vector2f(0.3f, 0.3f));

            previousNoteTime = note.time;
            fallingCircles.push_back(newCircle);
        }


        for (auto& beatCircle : fallingCircles)
        {
            Image* circleImage = beatCircle.shape->GetComponent<Image>();
            circleImage->ScreenPosition.y += FALL_SPEED * AR * deltaTime;

            float circleY = circleImage->ScreenPosition.y;

            if (circleY > 1300)
            {
                beatCircle.shape->Destroy();
                fallingCircles.erase(std::remove(fallingCircles.begin(), fallingCircles.end(), beatCircle), fallingCircles.end());
                Missed();
                ResetCombo();
                break;
            }
        }

        if ((sKeyNow && !sKeyPressed) || (dKeyNow && !dKeyPressed))
        {
            sKeyPressed = sKeyNow;
            dKeyPressed = dKeyNow;

            for (auto it = fallingCircles.begin(); it != fallingCircles.end();)
            {
                Image* circleImage = it->shape->GetComponent<Image>();
                float spawnTime = it->spawnTime;

                float circleY = circleImage->ScreenPosition.y;
                float hitY = hitRect->GetComponent<Image>()->ScreenPosition.y;

                float realFallSpeed = FALL_SPEED * AR;
                float hitExpectedTime = spawnTime + (hitY / realFallSpeed);

                if (std::abs(circleY - hitY) <= 100.0f)
                {
                    float timeDifference = std::abs(currentTime - hitExpectedTime);
                    
                    if (timeDifference - 50.f <= TIMING_WINDOW)
                    {
                        IncreaseCombo();

                        mParticle->PlayParticles();
                    }
                    else
                    {
                        Missed();
                        ResetCombo();
                    }
                    it->shape->Destroy();
                    it = fallingCircles.erase(it);
                    break;
                }
                else
                {
                    if (circleY > 900)
                    {
                        Missed();
                        ResetCombo();
                        it->shape->Destroy();
                        it = fallingCircles.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
        }

        if (outlineActive && outlineTimer.getElapsedTime().asSeconds() > outlineDuration) {
            outlineActive = false;
        }

        if (!sKeyNow) sKeyPressed = false;
        if (!dKeyNow) dKeyPressed = false;

        CalculateScoreAndAccuracy();

        if (mState == MusicScript::MUSICSTATE::STOPPED) return;

        accuracyText->GetComponent<Text>()->WriteText->setString("Accuracy: " + std::to_string(static_cast<int>(acc)) + "%");
        BPMText->GetComponent<Text>()->WriteText->setString("BPM: " + std::to_string(static_cast<int>(BPM)));
        scoreText->GetComponent<Text>()->WriteText->setString("Score: " + std::to_string(playerScore));

        comboText->GetComponent<Text>()->WriteText->setString("Combo: " + std::to_string(combo));
        maxComboText->GetComponent<Text>()->WriteText->setString("Max Combo: " + std::to_string(maxCombo));
        MissCount->GetComponent<Text>()->WriteText->setString("Miss : " + std::to_string(Misses));
        
    }
    if (noteDataList.empty() && fallingCircles.empty()) {
        mState = MUSICSTATE::STOPPED;
        MusicContainer->SetEnabled(false);
        music.stop();
        key1.setEnable(false);
        key2.setEnable(false);
    }
} 

void MusicScript::OnDisable()
{
    music.stop();
}

void MusicScript::OnRender(RenderWindow* window)
{
}


void MusicScript::IncreaseCombo() {
    combo++;
    if (combo > maxCombo) {
        maxCombo = combo;
    }

    if (combo == beatmapNotes) {
        fullComboText->SetEnabled(true);
    } else
    {
        fullComboText->SetEnabled(false);
    }

    playerScore += 100 * combo;
    outlineTimer.restart();
    outlineActive = true;
}


void MusicScript::ResetCombo() {
    combo = 0;
}

void MusicScript::Missed() {
    Misses++;
    outlineTimer.restart();
    outlineActive = true;
}

void MusicScript::CalculateScoreAndAccuracy()
{
    if (beatmapNotes == 0) {
        acc = 0.0f;
        return;
    }

    int hits = beatmapNotes - Misses;
    acc = static_cast<float>(hits) / beatmapNotes * 100.0f;
}

MusicScript::PlayerData MusicScript::GetData()
{
    if (noteDataList.size() == 0)
        return { playerScore, acc, Misses, maxCombo };
}