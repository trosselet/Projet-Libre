#pragma once
#include "scripts/Script.h"

class ParticlesScript : public IScript
{

	struct Particle
	{
		sf::Vector2f velocity;
		float lifetime;
		sf::Color color;
	};

public:
	ParticlesScript(unsigned int count);
	~ParticlesScript() override;

	void OnStart() override;
	void OnUpdate() override;
	void OnRender(RenderWindow* window) override;
    
	void PlayParticles();

private:

	void ResetParticles();

private:

	bool m_updateParticles = false;

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	float m_lifetime;
	sf::Vector2f m_emitter;

	float m_elapsedTime = 0.f;

	sf::Shader* mp_shader;
};

