#include "pch.h"
#include "ParticlesScript.h"
#include "Transform.h"

namespace {
    constexpr float PI = 3.14159265f;
}

ParticlesScript::ParticlesScript(unsigned int count) : m_particles(count), m_vertices(sf::PrimitiveType::Points, count), m_lifetime(0.3f), m_emitter(0.f, 0.f), mp_shader(nullptr)
{
    
}

ParticlesScript::~ParticlesScript()
{
    delete mp_shader;
}

void ParticlesScript::OnStart()
{
    mp_shader = new sf::Shader();
    if (!mp_shader->loadFromFile("../../res/Shader/Particles/particles.vert", "../../res/Shader/Particles/particles.frag"))
    {
        Debug::Log("Error while loading the particles shaders !");
        delete mp_shader;
        mp_shader = nullptr;
    }
}

void ParticlesScript::OnUpdate()
{
    if (GetKeyDown(Keyboard::Key::P))
    {
        PlayParticles();
    }

    if (!m_updateParticles)
        return;

    float deltaTime = Engine::GetDeltaTime();
    m_elapsedTime += deltaTime;

    bool allDead = true;

    for (size_t i = 0; i < m_particles.size(); ++i)
    {
        Particle& p = m_particles[i];
        p.lifetime -= deltaTime;

        if (p.lifetime > 0)
        {
            allDead = false;

            m_vertices[i].position += p.velocity * deltaTime;

            float ratio = p.lifetime / m_lifetime;
            ratio = std::clamp(ratio, 0.0f, 1.0f);

            sf::Color color = p.color;
            color.a = static_cast<unsigned int>(ratio * 255);
            m_vertices[i].color = color;
        }
        else
        {
            m_vertices[i].color.a = 0;
            m_vertices[i].position = sf::Vector2f(-100000.f, -100000.f);
        }
    }

    m_updateParticles = !allDead;
}

void ParticlesScript::OnRender(RenderWindow* window)
{
    if (mp_shader)
    {
        mp_shader->setUniform("u_time", m_elapsedTime);
        mp_shader->setUniform("u_emitter", m_emitter);
        window->draw(m_vertices, mp_shader);
    }
    else
    {
        window->draw(m_vertices);
    }
}

void ParticlesScript::PlayParticles()
{
    if (m_updateParticles)
        return;

    ResetParticles();
}

void ParticlesScript::ResetParticles()
{
    m_elapsedTime = 0.f;

    m_emitter = owner->GetTransform()->position;

    for (size_t i = 0; i < m_particles.size(); ++i)
    {
        float angle = (std::rand() % 360) * PI / 180.f;
        float speed = 150.f + static_cast<float>(std::rand() % 100);

        m_particles[i].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

        m_particles[i].lifetime = 0.3f + static_cast<float>(std::rand() % 300) / 1000.0f;

        int r = 200 + (std::rand() % 56);
        int g = 50 + (std::rand() % 150);
        int b = std::rand() % 50;
        m_particles[i].color = sf::Color(r, g, b);

        m_vertices[i].position = m_emitter;
        m_vertices[i].color = m_particles[i].color;
    }

    m_updateParticles = true;
}

