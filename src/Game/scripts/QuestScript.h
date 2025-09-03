#pragma once
#include "scripts/Script.h"
#include "scripts/interact/InteractEyeBallScript.h"
#include <vector>
#include "ECS/Components/Camera.h"

struct Quest
{
    unsigned int questNumber = -1;
    bool isComplete = false;
    std::string description;
    bool* condition = nullptr;
};

class QuestScript : public IScript
{
public:
    explicit QuestScript();
    ~QuestScript() override = default;

    void OnStart() override;
    void OnUpdate() override;
    void NextQuest();
    void AddQuest(unsigned int questId, std::string label);
    void SetObjective(unsigned int questId, bool* objective);
    void RemoveObjective(unsigned int questId);
    bool HasQuest();

    void SetState(bool active);

private:
    unsigned int m_questId = 0;
    std::map<int, Quest> m_questList;
    size_t m_actualQuest = 0;
    bool mIsClosed;
};

