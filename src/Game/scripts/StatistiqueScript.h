#pragma once
#include "scripts/Script.h"

class StatistiqueScript : public IScript
{
public:
	StatistiqueScript(int pv, int damage, int armor, int movementSpeed);
	~StatistiqueScript() = default;

	void OnUpdate() override;

	void TakeDamage(int damage);

private:
	int m_pv;
	int m_damage;
	int m_armor;
	int m_movementSpeed;
};

