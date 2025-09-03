#pragma once

class ECS;
class Animator;
class SpriteRenderer;

class AnimatorSystem
{
public:
	AnimatorSystem();
	~AnimatorSystem() = default;

	void Update(ECS* globalEC);

private:
	Animator* mp_Animator;
};

