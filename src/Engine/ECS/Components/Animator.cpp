#include "pch.h"
#include "Animator.h"
#include "Render/Texture.h"

Animator::Animator(Entity* entity, SpriteSheet* pSpriteSheet, float timeBetween)
: Component(entity)
{
    mp_SpriteSheet = pSpriteSheet;

    m_singleWidth = pSpriteSheet->GetSize().x;
    m_singleHeight = pSpriteSheet->GetSize().y;
    m_width = pSpriteSheet->GetTotalSize().x;
    m_height = pSpriteSheet->GetTotalSize().y;

    m_timeBetween = timeBetween;

    mp_SpriteSheet->SetSprite(0);

}

Animator::~Animator()
{

}

void Animator::SetAnimation(SpriteSheet* pSpriteSheet, float timeBetween)
{

    mp_SpriteSheet = pSpriteSheet;

    m_singleWidth = pSpriteSheet->GetSize().x;
    m_singleHeight = pSpriteSheet->GetSize().y;
    m_width = pSpriteSheet->GetTotalSize().x;
    m_height = pSpriteSheet->GetTotalSize().y;

    m_timeBetween = timeBetween;

    mp_SpriteSheet->SetSprite(0);
    
}

int Animator::GetBitmask()
{
    return BITMASK;
}
