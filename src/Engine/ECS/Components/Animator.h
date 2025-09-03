#pragma once
#include "Component.h"
#include "Render/SpriteSheet.h"

class Texture;
class Animator : public Component
{
public:
	static constexpr int BITMASK = 1 << 11;

	Animator(Entity* entity, SpriteSheet* pSpriteSheet, float timeBetween = 0.1f);
	~Animator() override;

	void SetAnimation(SpriteSheet* pSpriteSheet, float timeBetween = 0.1f);

	SpriteSheet* mp_SpriteSheet = nullptr;

	bool m_isExtract = false;
	int m_startX;
	int m_startY;
	int m_singleWidth;
	int m_singleHeight;
	int m_width;
	int m_height;
	
	float m_timeBetween = 0;
	float m_elapsedTime = 0;

	float m_actualIndex = 0;

	int GetBitmask() override;
};

