#pragma once
#include "Steering.hpp"
#include <utility>
#include <algorithm>

enum class BotState { Racing, Overtake, Recover };

struct BotController {
    BotState state=BotState::Racing; Steering steering; int pathIdx=0;
    std::pair<float,float> update(float /*dt*/,
        const sf::Vector2f& pos, const sf::Vector2f& vel, float heading,
        const std::vector<sf::Vector2f>& path, const sf::Vector2f& playerPos){
        sf::Vector2f acc{0,0};
        if(state==BotState::Racing)        acc = steering.followPath(pos, path, 80.f, pathIdx);
        else if(state==BotState::Overtake)  acc = steering.arrive(pos, vel, playerPos, 260.f);
        else                                acc = steering.arrive(pos, vel, path[pathIdx], 220.f);
        sf::Vector2f f{std::cos(heading), std::sin(heading)}, r{-f.y, f.x};
        float forwardAcc = acc.x*f.x + acc.y*f.y;
        float lateralAcc = acc.x*r.x + acc.y*r.y;
        float throttle = std::clamp(forwardAcc/steering.maxAccel, -1.f, 1.f);
        float steer    = std::clamp(lateralAcc /steering.maxAccel, -1.f, 1.f);
        return {throttle, steer};
    }
};
