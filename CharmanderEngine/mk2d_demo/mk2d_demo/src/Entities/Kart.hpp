#pragma once
#include <SFML/Graphics.hpp>
#include "../Physics/Kinematics.hpp"

struct Kart {
  Kinematics kin;
  sf::Sprite sprite;
  int frames=1, frameW=0, frameH=0, curFrame=0;
  float animT=0.f, animSpeed=10.f;

  void setTexture(sf::Texture& t, int fw, int fh, int numFrames, sf::Vector2f origin){
    sprite.setTexture(t);
    frames = numFrames; frameW = fw; frameH = fh;
    sprite.setOrigin(origin);
    sprite.setTextureRect({0,0,frameW,frameH});
  }
  void update(float dt){
    animT += dt; if(frames>1 && animT > 1.f/animSpeed){
      animT = 0.f; curFrame = (curFrame+1)%frames;
      sprite.setTextureRect({curFrame*frameW,0,frameW,frameH});
    }
    sprite.setPosition(kin.pos);
    sprite.setRotation(kin.heading * 180.f/3.1415926f);
  }
  void draw(sf::RenderTarget& rt) const { rt.draw(sprite); }
};
