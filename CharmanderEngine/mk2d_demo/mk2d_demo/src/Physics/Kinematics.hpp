#pragma once
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cmath>

struct Kinematics {
    sf::Vector2f pos{0,0}, vel{0,0};
    float heading=0.f, speed=0.f, maxSpeed=300.f, accel=500.f, drag=2.0f;
    void integrate(float dt, float throttle, float steer){
        speed += throttle * accel * dt;
        speed = std::clamp(speed - drag*speed*dt, -maxSpeed*0.4f, maxSpeed);
        float steerGain = 2.5f * (0.3f + 0.7f * (1.f - std::min(speed/maxSpeed,1.f)));
        heading += steer * steerGain * dt;
        sf::Vector2f f{std::cos(heading), std::sin(heading)};
        vel = f * speed; pos += vel * dt;
    }
};
