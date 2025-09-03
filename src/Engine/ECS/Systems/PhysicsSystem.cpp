#include "pch.h"
#include "PhysicsSystem.h"

#include "ECS/ECS.h"
#include "ECS/Entity.h"
#include "ECS/Components/RigidBody2D.h"
#include "Utils/Profiler.h"

void PhysicsSystem::OnFixedUpdate(ECS* globalEC)
{
    Profiler physic;

    physic.NewTask("PhysicsSystem.OnFixedUpdate");
    for (int i = 0; i < globalEC->mEntityCount; i++)
    {
        if (!globalEC->HasComponent<RigidBody2D>(i)) continue;
        RigidBody2D* rb = globalEC->GetComponent<RigidBody2D>(i);
        if (rb->GetState() == false)
            continue;

        float deltaTime = mFixedTimestep;

        if (rb->UseGravity)
        {
            sf::Vector2f gravity = sf::Vector2f(0, -rb->mGravity * rb->mMass);
            rb->AddForce(gravity);
        }
        
        // Apply gravity and other forces
        sf::Vector2f force = rb->GetForce();
        sf::Vector2f acceleration = force * rb->GetInvMass();

        // Update velocity with acceleration
        sf::Vector2f velocity = rb->mVelocity;
        velocity += acceleration * deltaTime;

        velocity *= 1.0f - rb->mDamping * deltaTime;
        rb->mVelocity = velocity;

        // Update position based on velocity
        sf::Vector2f position = rb->GetEntity()->GetTransform()->position;
        sf::Vector2f newPosition = position + rb->mVelocity * deltaTime;
        rb->GetEntity()->GetTransform()->SetPosition(newPosition);
        rb->ClearForces();
    }
    physic.EndTask();
}


