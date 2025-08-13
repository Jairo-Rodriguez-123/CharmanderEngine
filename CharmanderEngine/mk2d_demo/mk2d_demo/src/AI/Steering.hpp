#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cmath>
inline float mag(sf::Vector2f v){ return std::sqrt(v.x*v.x+v.y*v.y); }
inline sf::Vector2f norm(sf::Vector2f v){ float m=mag(v); return (m>1e-5f)? sf::Vector2f{v.x/m,v.y/m} : sf::Vector2f{0,0}; }

struct Steering {
    float maxAccel=600.f, slowRadius=140.f, arriveTime=0.5f;
    sf::Vector2f seek(const sf::Vector2f& pos, const sf::Vector2f& tgt){
        return norm(tgt - pos) * maxAccel;
    }
    sf::Vector2f arrive(const sf::Vector2f& pos, const sf::Vector2f& vel,
                        const sf::Vector2f& tgt, float targetSpeed){
        sf::Vector2f dir=tgt-pos; float dist=mag(dir); if(dist<5.f) return {0,0};
        float goalSpeed = (dist<slowRadius) ? targetSpeed*(dist/slowRadius) : targetSpeed;
        sf::Vector2f goalVel = norm(dir)*goalSpeed;
        return (goalVel - vel) * (1.f/arriveTime);
    }
    sf::Vector2f followPath(const sf::Vector2f& pos, const std::vector<sf::Vector2f>& path,
                            float lookAheadDist, int& idx){
        while(idx<(int)path.size()-1 && mag(path[idx]-pos)<lookAheadDist*0.5f) idx++;
        sf::Vector2f tgt = path[std::min(idx+1,(int)path.size()-1)];
        return seek(pos, tgt);
    }
};
