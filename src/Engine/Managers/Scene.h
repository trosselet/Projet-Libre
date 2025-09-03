#pragma once

class Scene
{
public:
	virtual ~Scene() = default;
	void virtual OnEnter() = 0;
	void virtual OnFixedUpdate();
	void virtual OnUpdate();
	void virtual OnExit();
	void virtual Render();
	void virtual OnEvent(const std::optional<sf::Event>);
};
