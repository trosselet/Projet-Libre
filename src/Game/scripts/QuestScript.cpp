#include "pch.h"
#include "QuestScript.h"
#include "ObjectFactory.h"
#include "ECS/Components/ui/Text.h"
#include "ECS/Components/ui/Image.h"
#include "Resources.h"
#include "Engine.h"
#include "ECS/Systems/CameraSystem.h"

QuestScript::QuestScript()
{
}

void QuestScript::OnStart()
{
    if (!owner) return;
    Camera* mp_camera = Engine::GetCameraSystem()->GetActiveCamera();
    float scaleFactorX  = 1.0f * mp_camera->ZoomFactor;
    float scaleFactorY  = 0.4f * mp_camera->ZoomFactor;
    float windowWidth   = Engine::GetRenderWindow()->GetWindowWidth();
    float windowHeight  = Engine::GetRenderWindow()->GetWindowHeight();
    
    Image* image = ObjectFactory::CreateComponent<Image>(owner, Resources::instance().QUEST, sf::Vector2f{ 2125, 290 }, sf::Vector2f{ scaleFactorX, scaleFactorY });
    Text* textBase = ObjectFactory::CreateComponent<Text>(owner, Resources::instance().DEFAULT_FONT, 20 * mp_camera->ZoomFactor, "", sf::Vector2f{ 0, 0 });
    
    sf::FloatRect textBounds = textBase->WriteText->getLocalBounds();
    sf::FloatRect imageBounds = image->UIImage->getGlobalBounds();


    textBase->ScreenPosition = sf::Vector2f{ image->ScreenPosition.x + (textBounds.size.x * 0.5f) + 50, image->ScreenPosition.y + (textBounds.size.y * 0.5f) + 3 };
    textBase->WriteText->setFillColor(sf::Color::Color(128, 101, 33, 255));
}

void QuestScript::OnUpdate()
{
    if (mIsClosed == true) return;
    if (!owner) return;
    Text* textBase = owner->GetComponent<Text>();
    if (textBase)
    {
        textBase->WriteText->setString(m_questList[m_actualQuest].description);
        
    }

    if (GetKeyDown(Keyboard::Key::J))
    {
        NextQuest();
    }

    if (m_questList[m_actualQuest].condition != nullptr)
    {
        
        if (m_questList[m_actualQuest].condition && *m_questList[m_actualQuest].condition)
        {
            m_questList[m_actualQuest].isComplete = true;
        }

        if (m_questList[m_actualQuest].isComplete)
        {
            NextQuest();
        }
        
    }
}

void QuestScript::NextQuest()
{
    if (m_actualQuest + 1 < m_questList.size())
    {
        ++m_actualQuest;
        Debug::Log("Next Quest: " + std::to_string(m_actualQuest));
    }
}

void QuestScript::AddQuest(unsigned int questId, std::string label)
{
    m_questList.emplace(questId, Quest{questId, false, label, nullptr}); 
}

void QuestScript::SetObjective(unsigned int questId, bool* objective)
{
    m_questList.at(questId).condition = objective;
}

void QuestScript::RemoveObjective(unsigned int questId)
{
    m_questList.at(questId).condition = nullptr;
}

bool QuestScript::HasQuest()
{
    return !m_questList.empty();
}

void QuestScript::SetState(bool active)
{
    mIsClosed = active;
}
