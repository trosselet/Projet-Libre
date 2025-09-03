#include "pch.h"
#include "StatistiqueScript.h"

StatistiqueScript::StatistiqueScript(int pv, int damage, int armor, int movementSpeed) : m_pv(pv), m_damage(damage), m_armor(armor), m_movementSpeed(movementSpeed)
{
}

void StatistiqueScript::OnUpdate()
{
	if (m_pv < 0)
	{
		m_pv = 0;
	}
}

void StatistiqueScript::TakeDamage(int damage)
{
	if (damage - m_armor > 0)
	{
		m_pv -= damage - m_armor;
	}
}
