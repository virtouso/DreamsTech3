#pragma once

#include"../ECS.h"
#include "../Components/TransformComponent/RigidBodyComponent.h"
#include "../Components/TransformComponent/TransformComponent.h"

class MovementSystem : public System
{
public:
    MovementSystem()
    {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }


    void Update(double deltaTime)
    {
        for (auto entity : GetSystemEntities())
        {
            auto& transform = entity.GetComponent<TransformComponent>();
            const auto rigidbody = entity.GetComponent<RigidBodyComponent>();

            transform.position.x += rigidbody.velocity.x * deltaTime;
            transform.position.y += rigidbody.velocity.y * deltaTime;

            Logging::Logger::Log(std::to_string(transform.position.y));
        }
    }
};
