#include "Track.hpp"

bool Track::loadMarioCircuit3(){
  sf::Texture& tex = ResourceManager::I().texture("textures/tracks/mario_circuit_3.png");
  sprite.setTexture(tex);
  // Path aproximado para dar la vuelta
  m_path = {
    {80,640},{120,520},{150,400},{200,300},{300,250},
    {450,200},{650,180},{750,250},{780,400},{760,550},
    {600,600},{400,620},{200,650},{100,640}
  };
  m_checkpoints = {
    {{100,300},50}, {{400,150},50}, {{700,200},50}, {{750,500},50}
  };
  return true;
}

void Track::draw(sf::RenderWindow& win, bool debug){
  win.draw(sprite);
  if(debug){
    for(size_t i=1;i<m_path.size();++i){
      sf::Vertex line[] = { sf::Vertex(m_path[i-1], sf::Color::Yellow), sf::Vertex(m_path[i], sf::Color::Yellow) };
      win.draw(line, 2, sf::Lines);
    }
    for(auto& c : m_checkpoints){
      sf::CircleShape cc(c.r); cc.setOrigin(c.r,c.r); cc.setPosition(c.p); cc.setFillColor(sf::Color(255,255,0,50)); cc.setOutlineColor(sf::Color::Yellow); cc.setOutlineThickness(1);
      win.draw(cc);
    }
  }
}
