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


    void Update()
    {
        for (auto entity : GetSystemEntities())
        {
            auto& transform = entity.GetComponent<TransformComponent>();
            const auto rigidbody = entity.GetComponent<RigidBodyComponent>();

            transform.position.x += rigidbody.velocity.x;
            transform.position.y += rigidbody.velocity.y;

            Logging::Logger::Log(std::to_string(transform.position.x));
        }
    }
};
