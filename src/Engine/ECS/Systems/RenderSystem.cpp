#include "pch.h"
#include "RenderSystem.h"

#include <ranges>

#include "CameraSystem.h"
#include "Transform.h"
#include "ECS/ECS.h"
#include "../Components/SpriteRenderer.h"
#include "ECS/Components/Collider2D.h"
#include "ECS/Components/Tilemap.h"
#include "ECS/Components/Animator.h"
#include "Render/RenderWindow.h"
#include "Utils/Debug.h"

RenderSystem::RenderSystem(RenderWindow* window): window(window) {}

RenderSystem::~RenderSystem() {}

void RenderSystem::Render(ECS* globalEC)
{
    for (auto const& entity : std::views::values(globalEC->mEntitiesByLayer))
    {
        if (!entity) continue;
        for(Entity* entities : *entity)
        {
            if (!entities) continue;
            if (!entities->IsEnable()) continue;
            if (entities->IsDestroyed()) continue;
            
            if (entities->Bitmask >= 0)
            {
                if (globalEC->HasComponent<SpriteRenderer>(*entities->GetIndex()))
                {
                    SpriteRenderer* renderer = globalEC->GetComponent<SpriteRenderer>(*entities->GetIndex());
                    sf::Vector2f size = renderer->Image->getGlobalBounds().size / 2.0f;
                    TRANSFORM* transform = renderer->GetEntity()->GetTransform();
                    renderer->Image->setPosition(transform->position - size);
                    renderer->Image->setScale(transform->scale);
                    renderer->Image->setRotation(transform->rotation);
                    if (!renderer->Image) continue;

                    if (!renderer->RendererShader)
                        window->Draw(renderer->Image);
                    else
                        window->Draw(renderer->Image, renderer->RendererShader);
                }

                if (globalEC->HasComponent<Tilemap>(*entities->GetIndex()))
                {
                    Tilemap* tilemap = globalEC->GetComponent<Tilemap>(*entities->GetIndex());
                    window->draw(tilemap->VertexArray, tilemap->TilemapTexture);
                    window->draw(tilemap->PropsVertexArray, tilemap->TilemapTexture);
                }

                if (globalEC->HasComponent<Animator>(*entities->GetIndex()))
                {
                    Animator* animator = globalEC->GetComponent<Animator>(*entities->GetIndex());

                    animator->m_elapsedTime += Engine::GetDeltaTime();

                    sf::Vector2f size = animator->mp_SpriteSheet->getGlobalBounds().size * 0.5f;
                    TRANSFORM* transform = animator->GetEntity()->GetTransform();
                    animator->mp_SpriteSheet->setPosition(transform->position - size);
                    animator->mp_SpriteSheet->setScale(transform->scale);
                    animator->mp_SpriteSheet->setRotation(transform->rotation);


                    if (animator->m_elapsedTime >= animator->m_timeBetween)
                    {
                        animator->m_elapsedTime = 0;

                        animator->m_actualIndex++;
                        if (animator->m_actualIndex >= animator->mp_SpriteSheet->SpriteCount)
                        {
                            animator->m_actualIndex = 0;
                        }

                        animator->mp_SpriteSheet->SetSprite(animator->m_actualIndex);
                    }

                    window->Draw(animator->mp_SpriteSheet);
                }
            }

        }
    }
}
